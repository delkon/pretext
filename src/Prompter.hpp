/*
 * Predictive text library
 * Prompter.hpp
 *
 * Copyright(C) 2013: Dmitry
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the BSD License
 *****************************************************************************/

#pragma once
#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "CharDomen.hpp"

/** \brief
 * 		Prompter interface
 */
struct IPrompter
{
    typedef std::list<std::string> StringList;
    typedef std::vector<std::string> Strings;
    typedef std::vector<int> Digits;

    /** \brief
     * 		Generates words data base
     * @param words	Container with strings
     */
    virtual void readDictionary( const Strings &words )=0;

    /** \brief
     * 		Returns suggested words for specified keys.
     * 		A=2, B=22, C=333 and so on
     * @param digits	Input digits ( e.g 22234569 )
     * @return String list with suggested words
     */
    virtual StringList getSuggestedWords( const Digits &digits )=0;
};

namespace {

// constants for table
static const int MaxRowChar = 8;
static const int MaxColChar = 4;

/** \brief
 * 		Table for conversion from digits to symbols.
 * 		It contains only allowed symbols.
 */
static char chars[MaxRowChar][MaxColChar] =
{
         {'A','B','C',0},     //2 = ABC
         {'D','E','F',0},     //3 = DEF
         {'G','H','I',0},     //4 = GHI
         {'J','K','L',0},     //5 = JKL
         {'M','N','O',0},     //6 = MNO
         {'P','Q','R','S'},   //7 = PQRS
         {'T','U','V',0},     //8 = TUV
         {'W','X','Y','Z'}    //9 = WXY(Z)
};

}	// end of anonymous namespace

/** \brief
 * 		Prompter implementation
 */
class Prompter: public IPrompter
{
public:

    Prompter() :
    	words_cnt_(0)
    {
    	CreateCharDomens();
    }
    
    virtual ~Prompter()
    {
    }

    /** \brief
     * 		Generates words data base
     * @param words	Container with strings
     */
    virtual void readDictionary( const Strings &words )
    {
        for( auto it=words.begin(); it!=words.end(); ++it )
		{
        	CharDomen *domen = LookupForDomen( (*it)[0] );

        	if( domen )
        	{
        		++words_cnt_;
        		domen->Add( *it );
        	}
        	else
        	{
        		std::cout << "\tWarning: Input string: '" <<
        		      *it << "' doesn't comply to input data policy and will be ignored"
        		          << std::endl;
        	}
		}
    }

    /** \brief
     * 		Returns suggested words for specified keys.
     * 		A=2, B=22, C=333 and so on
     * @param digits	Input digits ( e.g 22234569 )
     * @return String list with suggested words
     */
    virtual StringList getSuggestedWords( const Digits &digits )
    {
        StringList tmp;
        const std::string value = DigitsToString(digits);

        std::cout << "lookup suggested words for: " << value << std::flush;

        CharDomen *domen = LookupForDomen( value[0] );

		if( !domen )
		{
			throw std::runtime_error( "Domens for this string doesn't exists: (" + value +")" );
		}

        domen->getSuggestedWords( value, tmp );

        return tmp;
    }

    /** \brief
     * 		Returns amount of words in prompter data base
     *
     * @return int amount of words
     */
    int WordsInDictionary() const
    {
    	return words_cnt_;
    }

private:

    std::string DigitsToString( const Digits &digits )
    {
    int prev=0;
    int next=0;
    int cnt=0;

        std::string str;
        for( auto it = digits.begin(); it != digits.end(); ++it )
        {
            if( *it < 2 || *it > 9 ) continue;

            next=0;
            if( it+1 != digits.end())
            {
            	next = *(it+1);
            }
			if( prev == *it )
			{
			  if( cnt < MaxColChar-1 )
			  {
				  const char check = chars[ prev - 2 ][ cnt+1 ];
				  if( check ) ++cnt;
			  }
			}
            else
            {
                prev = *it;
                cnt = 0;
            }

            if( prev != next )
            {
            	const char ch = chars[ prev - 2 ][ cnt ];
            	str.append( sizeof(ch), ch );
            }
        }

    return str;
    }

    /** \brief
     * 		For each symbols triplet this method creates own domen
     */
    void CreateCharDomens()
    {
    	if( domens_.size() )
    	{
    		throw std::runtime_error( "Domens already exists " );
    	}

    	for( int i=0; i<MaxRowChar; ++i )
    	{
			char chs[ MaxColChar ] = { 0 };

			for( int j=0; j<MaxColChar; ++j )
			{
				chs[j] = chars[i][j];
			}

			// create domen for symbols triplet
			Shared d( new CharDomen(chs[0], chs[1], chs[2], chs[3]) );

			// assign each symbol to domen for searching
			for( int n=0; n<MaxColChar; ++n )
			{
				if( chs[n] )
				{
					domens_.insert( std::make_pair( chs[n], d) );
				}
			}
    	}
    }

    /** \brief
     * 		Lookup for domen pointer for specified character
     * @param ch	first character in word
     * @return CharDomen* or NULL
     */
    CharDomen* LookupForDomen( char ch )
	{
    	auto it = domens_.find( std::toupper(ch) );
    	if( it == domens_.end() )
    	{
    		return NULL;
    	}

    	return it->second.get();
	}

	typedef std::shared_ptr<CharDomen> Shared;
    std::unordered_map< char, Shared > domens_;
    int words_cnt_;

};
