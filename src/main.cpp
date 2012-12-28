#include <iostream>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <limits>
#include <stdlib.h>
#include <time.h>

#include "Prompter.hpp"

static const char *dict_file_ = "scowl/final/english-words.80";

int main()
{
    Prompter::Strings words;

    std::cout << "Loading data from file: " << dict_file_ << std::endl;
    {
        std::ifstream ifs( dict_file_ );
        if( ifs.good() )
        {
            std::copy( std::istream_iterator<std::string>(ifs),
                       std::istream_iterator<std::string>(),
                       std::back_inserter(words));
        }
        else throw std::runtime_error( "can't find file " +
                                       std::string( dict_file_ ) );
    }

    Prompter prompt;
    prompt.readDictionary( words );

    int d[] = { 2,3,4,5,6,7,8,9 };

    Prompter::Digits digits;

    //generate 100*10 words
    const int MaxTestIteration = 100;
    const size_t MaxWordLength=10;

    std::cout << "Test started, tests iteration:  " << MaxTestIteration << std::endl;

    for( int test=0; test<MaxTestIteration; ++test )
    {
        digits.clear();
        const size_t len = sizeof(d)/sizeof(int);
        for( size_t i=0; i < MaxWordLength; ++i )
        {
            digits.push_back( d[ rand() % len ] );
            Prompter::StringList words = prompt.getSuggestedWords( digits );

            //if generated word incorrect and doesn't have predicted words
            if( !words.size() ) break;
        }
    }


return 0;
}
