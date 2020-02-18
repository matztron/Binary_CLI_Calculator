//
//  tokenizer.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#include "tokenizer.h"

//Constructor
Tokenizer::Tokenizer(std::string input_) 
{
    input = input_;
    input_length = input.length();
    index = -1;
}

//Generate a token
Token Tokenizer::getToken() 
{
    //Increment index
    index = index + 1;

    //Check if reached end of input string
    if (index >= input_length) {
        //Reached end of input string (NONE symbolizes end of input)
        return Token(NONE,"0", index);
    }

    char currentSymbol = input.at(index);

    //Filter out spaces
    while (currentSymbol == ' ') {
        index = index + 1;
        if (index < input_length)
        {
            currentSymbol = input.at(index);
        }
        else
        {
            //Reached end of input
            //Generate only none tokens from now on
            return Token(NONE,"0", index);
        }
    }
    
    //Brackets
    if (currentSymbol == '(')
    {
        // (
        return Token(BRC_OPEN,"",index);
    }
    else if (currentSymbol == ')')
    {
        // )
        return Token(BRC_CLOSE,"",index);
    }
    
    std::string word = peekAlphabetic(index);
    
    //Make input uppercase
    std::transform(word.begin(), word.end(),word.begin(), ::toupper);
    

    if (word == "AND") 
    {
        // AND
        return Token(AND,"",index);
    }
    else if (word == "OR")
    {
        // OR
        return Token(OR,"",index);
    }
    else if (word == "NOT")
    {
        // NOT
        return Token(NOT,"",index);
    }
    /*else if (word == "NAND")
    {
        // NAND
        return Token(NAND,"",index);
    }
    else if (word == "NOR")
    {
        // NOR
        return Token(NOR,"",index);
    }
    else if (word == "EQ") 
    {
        // EQ
        return Token(EQ,"",index);
    }
    else if (word == "XOR") 
    {
        // XOR
        return Token(XOR,"",index);   
    }*/
    else
    {
        // VAR
        return Token(VAR, word, index);
    }
}

//Peek
std::string Tokenizer::peekAlphabetic(int peekIndex)
{
    if (!isalpha(input[peekIndex]))
    {
        //Return "nothing" and jump over the word
        index = peekIndex - 1;
        return "";
    } else 
    {
        //Check next symbol
        return input[peekIndex] + peekAlphabetic(peekIndex + 1);
    }
}

//Collect
std::vector<Token> Tokenizer::collect() 
{
    std::vector<Token> tokens = std::vector<Token>();

    tokens.push_back(getToken());

    //Call getToken() till end of input is reached
    while (tokens.back().type != NONE) 
    {
        tokens.push_back(getToken());
    }
    return tokens;
}
