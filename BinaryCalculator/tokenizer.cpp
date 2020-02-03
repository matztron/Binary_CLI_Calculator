#include "tokenizer.h"

//Constructor
Tokenizer::Tokenizer(std::string input_) 
{
    input = input_;
    input_length = input.length();
    index = -1;
}

//Destructor
//...

//Generate a token
Token Tokenizer::getToken() 
{
    //Increment index
    index = index + 1;

    //Check if reached end of input string
    if (index >= input_length - 1) {
        //std::cout << "end of input!" << std::endl;
        //Reached end of input string (NONE symbolizes end of input)
        return Token(NONE,"0", index);
    }

    char currentSymbol = input.at(index);

    //Filter out spaces
    while (currentSymbol == ' ') {
        index = index + 1;
        currentSymbol = input.at(index);
    }

    std::string word = peekAlphabetic(index);

    //Debug
    //std::cout << "---" << std::endl;
    //std::cout << "current index: " << index << std::endl;
    //std::cout << "current word: " << word << std::endl;

    //todo here: make word all upperstring

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
    else if (word == "NAND")
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
    }
    else if (word == "(") 
    {
        // (
        return Token(BRC_OPEN,"",index);
    }
    else if (word == ")") 
    {
        // )
        return Token(BRC_CLOSE,"",index);
    }
    else if (word == "1" || word == "TRUE") 
    {
        // TRUE
        return Token(TRUE,"",index);
    }
    else if (word == "0" || word == "FALSE") 
    {
        // FALSE
        return Token(FALSE,"",index);
    }
    else
    {
        // VAR
        return Token(VAR, word, index);
    }
    
    //get words and then look if they are a reserved word
    // _x _x a _ _ _ b AND c

    //wenn ein

}

//Peek
std::string Tokenizer::peekAlphabetic(int peekIndex)
{
    if (!isalpha(input[peekIndex]) && input[peekIndex] != '1' && input[peekIndex] != '0' && input[peekIndex] != '(' && input[peekIndex] != ')') 
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
    /*std::vector<Token> tokens = std::vector<Token>();
    tokens.push_back(getToken());
    tokens.push_back(getToken());
    tokens.push_back(getToken());
    tokens.push_back(getToken());
    tokens.push_back(getToken());
    tokens.push_back(getToken());
    return tokens;*/

    std::vector<Token> tokens = std::vector<Token>();

    tokens.push_back(getToken());

    //Call getToken() till end of input is reached
    while (tokens.back().type != NONE) 
    {
        tokens.push_back(getToken());
    }
    //std::cout << "fertig" << std::endl;
    return tokens;
}
