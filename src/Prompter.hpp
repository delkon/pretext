/*
 * Prompter.hpp
 *
 *      Author: dmitry
 */

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

    virtual void readDictionary( const Strings &words )=0;
    virtual StringList getSuggestedWords( const Digits &digits )=0;
};

namespace {

static const int MaxRowChar = 8;
static const int MaxColChar = 4;

/** Possible symbols for domen and digits to symbol conversion
 *
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
}

/** \brief
 * 		Prompter implementation
 */
class Prompter: public IPrompter
{
public:

    Prompter()
    {
    	CreateCharDomens();
    }
    
    virtual ~Prompter()
    {
    }

    virtual void readDictionary( const Strings &words )
    {
    	int cnt = 0;
        for( auto it=words.begin(); it!=words.end(); ++it )
		{
        	CharDomen *domen = LookupForDomen( (*it)[0] );

        	if( domen )
        	{
        		++cnt;
        		domen->Add( *it );
        	}
		}

        std::cout << "Loaded successfully, total words:  " << cnt << std::endl;
    }

    std::string DigitsToString( const Digits &digits )
    {
        int prev_digit=0;
        int cnt=0;

        std::string str;
        for( auto it = digits.begin(); it != digits.end(); ++it )
        {
            if( *it < 2 || *it > 9 ) continue;

            if( prev_digit == *it )
            {
                ++cnt;

                if( cnt > 3 ) cnt=3;
            }
            else
            {
                prev_digit = *it;
                cnt = 0;
            }

            const char ch = chars[ prev_digit - 2 ][ cnt ];
            str.append( sizeof(ch), ch );
        }

        return str;
    }


    virtual StringList getSuggestedWords( const Digits &digits )
    {
        StringList tmp;
        tmp.push_back("1");

        // CharDomen.getSuggestedWords( DigitsToString(digits), tmp );

        std::cout << DigitsToString(digits) << std::endl;

        return tmp;
    }

private:

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

			Shared d( new CharDomen(chs[0], chs[1], chs[2], chs[3]) );

			std::cout << "Created Domen for " << chs[0] << chs[1] << chs[2] << chs[3] << std::endl;

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

};
