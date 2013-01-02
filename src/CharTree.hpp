/*
 * CharTree.hpp
 *
 *      Author: dmitry
 */

#pragma once
#include <unordered_map>
#include <unordered_set>
#include <memory>

/**
 *
 */
class CharTree
{
public:

	CharTree()
	{

	}

	~CharTree()
	{

	}

private:

	typedef std::shared_ptr< CharTree > Shared;
	typedef std::unordered_map< char, Shared > Map;
	typedef std::unordered_set< int > Set;

	Map childs_;			//!< Tree leafs
	CharTree *parent_;		//!< Link to prev. leaf
	Set positions_;			//!< Positions in string storage for specified tree node
};



