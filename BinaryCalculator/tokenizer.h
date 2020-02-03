#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include <string>
#include <vector>

#include "token.h"
//#include "exception.h"

//Debug
#include <iostream>
//---

class Tokenizer 
{
    public:
        Tokenizer(std::string input);

        //Create Token-List from user input
        std::vector<Token> collect();

    private:
        //generate token
        Token getToken();
        std::string peekAlphabetic(int peekIndex);

        std::string input;
        int input_length;
        int index;


};

#endif //_TOKENIZE_H_