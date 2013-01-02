/*
 * CharDomen.hpp
 *
 *      Author: dmitry
 */

#pragma once
#include <vector>
#include <list>
#include <string>
#include <memory>
#include <iostream>

#include "CharTree.hpp"

/** Each characters domen could work with fixed amount of characters.
 * Characters domen consist strings and its tree index
 */
class CharDomen
{
public:
	/** Each domen must control at least three symbols
	 *
	 * @param[in] ch1 First symbol
	 * @param[in] ch2 Second symbol
	 * @param[in] ch3 Third symbol
	 * @param[in] ch4 Four symbol ( optional )
	 * @return
	 */
	CharDomen(char ch1,
			  char ch2,
			  char ch3,
			  char ch4 = 0)
	{
		trees_.insert( std::make_pair( ch1, CharTree() ));
		trees_.insert( std::make_pair( ch2, CharTree() ));
		trees_.insert( std::make_pair( ch3, CharTree() ));
		if( ch4 ) trees_.insert( std::make_pair( ch4, CharTree() ));
	}

	~CharDomen()
	{

	}

	/**
	 *
	 * @param[in] value
	 * @param[out] words
	 */
	void getSuggestedWords(const std::string &value,
						         std::list<std::string> &words)
	{
		//todo
	}

	/** \brief
	 * 		This method works with unique string only
	 *  \note
	 * 		It doesn't consist any checks if this word already exists or not.
	 * 		Words must be unique.
	 *
	 * @param value[in]	Input string
	 */
	void Add( const std::string &value )
	{
		auto it = trees_.find( std::toupper( value[0] ) );

		if( it == trees_.end() )
		{
			throw std::runtime_error( "[Internal error] Undefined domen for string: " + std::string( value ) );
		}

		storage_.push_back( value );

		//std::cout << "Adding " << value ;

		CharTree &ct = it->second;
		ct.Add( value, 1, storage_.size()-1 );
	}

private:

	typedef std::unordered_map<char, CharTree> Map;

	Map trees_; 							//!< Trees for each symbol in domen
	std::vector<std::string> storage_; 		//!< String storage
};