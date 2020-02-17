//
//  tokenizer.hpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include <string>
#include <vector>

#include "token.h"

//Debug
#include <iostream>
//---

class Tokenizer 
{
    public:
        //Constructor
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
