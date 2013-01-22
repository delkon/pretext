Task
----------------------------------------------------------------------------------------
This library allow to emulate prediction text (T9 auto complete) on PC.
Input data (digits in this format):

    2 = ABC
    3 = DEF
    4 = GHI
    5 = JKL
    6 = MNO
    7 = PQRS
    8 = TUV
    9 = WXY(Z)
    
    // 2 2 4 5 6 = BGJM

and returns closest 20 words.
For example:

    Prompter prompt;
    Prompter::Strings words = LoadFromFile( somefile );
    prompt.readDictionary( words );
    Prompter::StringList prewords = prompt.getSuggestedWords( {2,2,4,5,6} );

Speed Summary:
=========================================================================================


    1) Test on Dell D830 ( Core 2 Duo, 2.5GHz )
    
    GCC 4.4.3
    bin/pretext > out.log
    
    Data base loading: Elapsed time: 311 milliseconds
    Tests: 		   Elapsed time: 15 milliseconds, per 1000 iteration
    
    2) Test on Raspberry Pi (Model B) ( ARM1176JZF-S , 850Mhz )
    
    GCC 4.7.2
    bin/pretext > out.log
    
    Data base loading: Elapsed time: 3448 milliseconds
    Tests: 		   Elapsed time: 184 milliseconds, per 1000 iteration


Memory leak report:
=======================================================================================

    valgrind --leak-check=full --show-reachable=no --error-limit=no --error-exitcode=1 bin/pretext.
    
    ==12914== Memcheck, a memory error detector
    ==12914== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
    ==12914== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
    ==12914== Command: bin/pretext
    ==12914== 
    ...
    ==12914== 
    ==12914== HEAP SUMMARY:
    ==12914==     in use at exit: 0 bytes in 0 blocks
    ==12914==   total heap usage: 2,830,760 allocs, 2,830,760 frees, 76,315,594 bytes allocated
    ==12914== 
    ==12914== All heap blocks were freed -- no leaks are possible
    ==12914== 
    ==12914== For counts of detected and suppressed errors, rerun with: -v
    ==12914== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 18 from 7)
