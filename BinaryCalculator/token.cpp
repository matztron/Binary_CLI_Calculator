#include "token.h"

Token::Token() 
{
    this->type = NONE;
    this->value = "";
    this->index = 0;
}

Token::Token(TokenType type, std::string value, int index) 
{
    this->type = type;
    this->value = value;
    this->index = index;
}