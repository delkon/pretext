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

private:

	typedef std::unordered_map<char, CharTree> Map;

	Map trees_; 							//!< Trees for each symbol in domen
	std::vector<std::string> storage_; 		//!< String storage
};
