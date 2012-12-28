#include <list>
#include <vector>
#include <string>
#include <iostream>

//! \brief
//!		Prompter interface
struct IPrompter
{
    typedef std::list<std::string> StringList;
    typedef std::vector<std::string> Strings;
    typedef std::vector<int> Digits;

    virtual void readDictionary( const Strings &words )=0;
    virtual StringList getSuggestedWords( const Digits &digits )=0;
};

//! \brief
//!		Prompter implementation
class Prompter: public IPrompter
{
public:

    Prompter()
    {
    }
    
    virtual ~Prompter()
    {
    }

    virtual void readDictionary( const Strings &words )
    {
        std::cout << "Loaded successfully, total words:  " << words.size() << std::endl;
    }

    std::string DigitsToString( const Digits &digits )
    {
        int prev_digit=0;
        int cnt=0;

        char chars[8][4] =
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

            //std::cout << *it;

            const char ch = chars[ prev_digit - 2 ][ cnt ];
            str.append( &ch );
        }

        //std::cout << "--->";

        return str;
    }


    virtual StringList getSuggestedWords( const Digits &digits )
    {
        StringList tmp;
        tmp.push_back("1");

        std::cout << DigitsToString(digits) << std::endl;

        return tmp;
    }
};
