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
	typedef std::shared_ptr< CharTree > Shared;
	typedef std::unordered_map< char, Shared > Map;
	typedef std::unordered_set< int > Set;

public:

	CharTree()
	{

	}

	CharTree( int spos )
	{
		AddPosition( spos );
	}

	~CharTree()
	{

	}

	void AddPosition( int spos )
	{
		positions_.insert( spos );
	}

	void Add( const std::string &value,
			  size_t pos,
			  int storage_pos,
			  CharTree *node = 0 )
	{
		if( pos >= value.length() )
		{
			throw std::runtime_error( "[Internal error] CharTree::Add, Incorrect Position");
		}

		char ch = std::toupper( value[ pos ] );
		CharTree *dest = node;
		Map *childs = (!dest ? &childs_ : &dest->childs_);

		if( !childs )
		{
			throw std::runtime_error( "[Internal error] CharTree::Add, Null pointer");
		}

		auto it = childs->find( ch );

		( it == childs->end() ?	dest = AddChild( childs, ch ):
								dest = it->second.get() );

		dest->AddPosition( storage_pos );

		if( pos < value.length()-1 )
		{
			Add( value, ++pos, storage_pos, dest );
		}
	}

private:

	CharTree* AddChild( Map *childs, char ch )
	{
		//std::cout << "--Adding " << ch ;
		std::pair<Map::iterator,bool> answer = childs->insert(
												std::make_pair( ch, Shared( new CharTree() )));
		if( !answer.second )
		{
			throw std::runtime_error( "[Internal error] CharTree::AddChild, Can't insert");
		}

		return answer.first->second.get();
	}

	int Childs() const
	{
		return childs_.size();
	}

	Map childs_;			//!< Tree leafs
	CharTree *parent_;		//!< Link to prev. leaf
	Set positions_;			//!< Positions in string storage for specified tree node
};



