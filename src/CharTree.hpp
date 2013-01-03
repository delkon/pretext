/*
 * CharTree.hpp
 *
 *      Author: dmitry
 */

#pragma once
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

/**
 *
 */
class CharTree
{
	typedef std::shared_ptr< CharTree > Shared;
	typedef std::unordered_map< char, Shared > Map;

public:

	typedef std::vector< int > Set;

	CharTree()
	{
	}

	~CharTree()
	{
	}

	void Add( const std::string &value,
			  size_t pos,
			  int storage_pos,
			  CharTree *node = 0 )
	{
		if( pos >= value.length() )
		{
			throw std::runtime_error( "[Internal error] CharTree::Add, Position out of bounds");
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
		dest->SetParent( node );

		if( pos < value.length()-1 )
		{
			Add( value, ++pos, storage_pos, dest );
		}
	}

	void GetSuggestedWords( const std::string &value,
			  	  	  	    Set &lines )
	{
		const size_t MaxLines = 20;
		//1) simple approach every time searching from beginning

		CharTree *node = SearchInTree( value, 1 );

		if( node )
		{
			CreateLines( node, lines, MaxLines );
		}

		if( !node || lines.size() < MaxLines )
		{
			//convert to ordered due to order problems
			std::map<char, Shared> ordered(childs_.begin(), childs_.end());

			for( auto it=ordered.begin(); it!=ordered.end(); ++it )
			{
				CreateLines( it->second.get(), lines, MaxLines );

				if( lines.size() >= MaxLines ) break;
			}
		}
	}

private:

	void CreateLines( CharTree *node, Set &lines, size_t MaxLines )
	{
		if( node->positions_.size() > MaxLines )
		{
			Copy_N( lines, node->positions_, abs( MaxLines - lines.size() ) );
		}
		else
		{
			lines = node->positions_;
			CharTree *dest = node;

			size_t len=0;
			while( lines.size() <= MaxLines )
			{
				len=lines.size();
				dest = dest->Parent();
				if( !dest ) break;

				Copy_N( lines, dest->positions_, abs( MaxLines - lines.size() ));
			}
		}
	}

	void Copy_N( Set &src, const Set &dest, size_t n )
	{
		size_t jt=0;
		if( n > dest.size() ) n = dest.size();
		if( n <= 0 ) return;

		for( auto it=dest.begin(); it!=dest.end(); ++it )
		{
			src.push_back( *it );

			if( ++jt >= n ) break;
		}
	}

	CharTree *SearchInTree( const std::string &value,
							size_t pos,
							CharTree *node = 0 )
	{
		if( value.length() == 1 )
		{
			return 0;
		}

		if( pos >= value.length() )
		{
			throw std::runtime_error( "[Internal error] CharTree::SearchInTree, Incorrect Position");
			return node;
		}

		char ch = std::toupper( value[ pos ] );
		CharTree *dest = node;
		Map *childs = (!dest ? &childs_ : &dest->childs_);

		if( !childs )
		{
			throw std::runtime_error( "[Internal error] CharTree::SearchInTree, Null pointer");
		}

		auto it = childs->find( ch );

		if( it != childs->end() )
		{
			dest = it->second.get();

			if( pos < value.length()-1 )
			{
				return SearchInTree( value, ++pos, dest );
			}
		}

		return dest;
	}

	void AddPosition( int spos )
	{
		positions_.push_back( spos );
	}

	CharTree* AddChild( Map *childs, char ch )
	{
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

	void SetParent( CharTree *parent )
	{
		parent_ = parent;
	}

	CharTree *Parent() const
	{
		return parent_;
	}

	Map childs_;			//!< Tree leafs
	CharTree *parent_;		//!< Link to prev. leaf
	Set positions_;			//!< Positions in string storage for specified tree node
};



