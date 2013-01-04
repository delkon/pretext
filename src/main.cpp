#include <iostream>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ctime>
#include <inttypes.h>

#include "Prompter.hpp"

//Input data from: http://wordlist.sourceforge.net/
static const char *dict_file_ = "scowl/final/english-words.80";

typedef unsigned long long timestamp_t;
long mtime, seconds, useconds;
struct timeval start, end;

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
	std::cout << "Data base generating ... please wait  " << std::endl;

    gettimeofday(&start, NULL);

    prompt.readDictionary( words );

	gettimeofday(&end, NULL);

	seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    std::cout << "Loaded successfully, total words in data base:  " << prompt.WordsInDictionary() << std::endl;
    std::cout << "Elapsed time: " << mtime << " milliseconds" << std::endl;

    int d[] = { 2,3,4,5,6,7,8,9 };

    Prompter::Digits digits;

    //generate 100*10 words
    const int MaxTestIteration = 100;
    const size_t MaxWordLength=10;

    std::cout << "\nTests started, amount of iteration:  " << MaxTestIteration << std::endl;
    std::cout << "Each iteration consists:  " << MaxWordLength << " words" << std::endl;

    srand ( time(NULL) );
    gettimeofday(&start, NULL);

    for( int test=0; test<MaxTestIteration; ++test )
    {
        digits.clear();
        const int len = sizeof(d)/sizeof(int);
        int r = rand() % len;

        for( size_t i=0; i < MaxWordLength; ++i )
        {
        	int repeats = rand() % 20;
        	if( !(repeats % 2) ) r = rand() % len;

            digits.push_back( d[ r ] );

            std::cout << " ---> " << std::flush;
            Prompter::StringList words = prompt.getSuggestedWords( digits );
            std::cout << "( ";
			for( auto it=digits.begin(); it!=digits.end(); ++it ) std::cout << *it << " ";
			std::cout<< " )" << std::endl;

            if( words.size() )
            {

				std::copy( words.begin(),
						   words.end(),
						   std::ostream_iterator<std::string>(std::cout, "\n") );
				std::cout << " <---- found: " <<  words.size() << " words" << std::endl;

#if 0
				if( words.size() != 20 )
				{
					throw std::runtime_error( "less then 20" );
				}
#endif

            }

        }
    }

    gettimeofday(&end, NULL);

	seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    std::cout << "Time elapsed: " << mtime << " milliseconds, per " << MaxTestIteration*MaxWordLength << " iteration" << std::endl;
return 0;
}
