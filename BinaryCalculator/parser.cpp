//
//  parser.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#include "parser.h"

//Constructor
Parser::Parser(std::vector<Token> tokens_) 
{
    tokens = tokens_;
    tree = new Btree();
}

//Get the number of variables in the user input
int Parser::countVariables() 
{
    //Example:
    //input: AND(a OR(a b))
    //output: 2
    std::vector<string> alreadyFoundVars;
    int count = 0;
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].type == VAR) 
        {
            bool found = false;
            for (int j = 0; j < alreadyFoundVars.size(); j++) {
                if (tokens[i].value == alreadyFoundVars[j])
                {
                    found = true;
                }
            }
            if (found == false)
            {
                count++;
                //add current VAR to alreadyFound
                alreadyFoundVars.push_back(tokens[i].value);
            }
        }
    }
    return count;
}

//Get variable count externally
int Parser::getVarCount()
{
    return countVariables();
}

//Count operands
int Parser::countOperands(std::vector<Token> subTokens)
{
    int count = 0;
    //Example:
    //input: NOT(b) OR(b d) d AND ( s a )
    //output: 4
    for (int i = 0; i < subTokens.size(); i++) {
        //If it is anything with brackets:
        if (subTokens[i].type == AND || subTokens[i].type == OR || subTokens[i].type == NOT) {
            
            count++;
            
            if (subTokens[i + 1].type == BRC_OPEN) {
                i = findClosingBracket(i, subTokens);
            }
            else
            {
                throw GenericException("Expected opening bracket", subTokens[i].index);
            }
        }
        else if (subTokens[i].type == VAR)
        {
            count++;
        }
        else if (subTokens[i].type == NONE)
        {
            //reached end of list
            return count;
        }
    }
    return count;
}

//Read next sublist of vectors
void Parser::readTokens(std::vector<Token> subTokens, Node* parent, int pos)
{
    //Example:
    // input: AND ( OR ( a b ) c )
    // output: builds tree from that
    
    if (countOperands(subTokens) > 1) {
        throw GenericException("Too many operands provided. Only 1 expected :)", subTokens[0].index);
    }
    
    if (subTokens[pos].type == AND || subTokens[pos].type == OR) 
    {
        std::vector<Token> bracketContent = getBracketContent(subTokens, pos); //Example: hand over: ( OR ( a b ) c )
        
        Node* newNode = new Node;
        newNode->token = subTokens[pos];

        tree->insert(newNode, parent);

        getDualOperator(bracketContent,newNode);
    }
    else if (subTokens[pos].type == NOT) 
    {
        std::vector<Token> bracketContent = getBracketContent(subTokens, pos);

        Node* newNode = new Node;
        newNode->token = subTokens[pos];

        tree->insert(newNode, parent);

        getMonoOperator(bracketContent,newNode);
    }
    else if (subTokens[pos].type == VAR)
    {
        Node* newNode = new Node;
        newNode->token = subTokens[pos];

        tree->insert(newNode, parent);
    }
    else if (subTokens[pos].type == BRC_OPEN)
    {
        //this is a useless bracket
        //like: _(_ NOT ( b ) OR ( b d ) _)_
        //      this                ...and this

        throw GenericException("Don't use pointless brackets", subTokens[0].index);
    }
    else
    {
        //This can not happen since there aren't any additional token-types
        //They can however easily be added in the tokeinzer and token classes
        throw GenericException("Unhandled token in input", subTokens[0].index);
    }
    
}

void Parser::getMonoOperator(std::vector<Token> subTokens, Node* parent)
{
    std::vector<Token> first = getFirstOperand(subTokens);
    
    if (countOperands(subTokens) > 1) {
        throw GenericException("Too many operands provided. Only 1 expected", subTokens[0].index);
    }

    //call again for first
    readTokens(first, parent, 0);
}

void Parser::getDualOperator(std::vector<Token> subTokens, Node* parent) 
{
    std::vector<Token> first = getFirstOperand(subTokens);
    std::vector<Token> second = getSecondOperand(subTokens);
    
    if (countOperands(subTokens) > 2) {
        throw GenericException("Too many operands provided. Only 2 expected", subTokens[0].index);
    }

    //call again for first & second
    readTokens(first, parent, 0);
    readTokens(second, parent, 0);   
}

std::vector<Token> Parser::getFirstOperand(std::vector<Token> subTokens) 
{
    // Get this: NOT(b) OR(b d)
    if (subTokens[0].type == AND || subTokens[0].type == OR || subTokens[0].type == NOT) 
    {
        //traverse right till closing bracket
        int closingBracketIndex = findClosingBracket(0, subTokens);
        return std::vector<Token>(subTokens.begin(), subTokens.end() - (subTokens.size() - closingBracketIndex - 1));
    }
    else if (subTokens[0].type == VAR)
    {
        //just one var
        std::vector<Token> firstOp;
        firstOp.push_back(subTokens[0]);
        return firstOp;
    }
    else if (subTokens[0].type == BRC_OPEN)
    {
        throw GenericException("Don't use pointless brackets", subTokens[0].index);
    }
    else if (subTokens[0].type == NONE)
    {
        //there is no operand
        throw GenericException("Operator needs more argument(s)", subTokens[0].index);
    }
    else
    {
        //This can not happen since there aren't any additional token-types
        //They can however easily be added in the tokeinzer and token classes
        throw GenericException("Unhandled token in input", subTokens[0].index);
    }
}

std::vector<Token> Parser::getSecondOperand(std::vector<Token> subTokens) 
{
    //Skip first operand
    int endOfFirstOp = 0;
    if (subTokens[0].type == AND || subTokens[0].type == OR || subTokens[0].type == NOT)
    {
        endOfFirstOp = findClosingBracket(0, subTokens);
    }
    else if (subTokens[0].type == VAR)
    {
        endOfFirstOp = 0;
    }
    
    //Check second operand
    if (subTokens[endOfFirstOp + 1].type == AND || subTokens[endOfFirstOp + 1].type == OR || subTokens[endOfFirstOp + 1].type == NOT)
    {
        //Traverse right till closing bracket
        int endOfSecOp = findClosingBracket(endOfFirstOp + 1, subTokens); // +1 for next Operator
        return std::vector<Token>(subTokens.begin() + endOfFirstOp + 1, subTokens.end() - (subTokens.size() - endOfSecOp - 1));
    }
    else if (subTokens[endOfFirstOp + 1].type == VAR)
    {
        //... VAR
        std::vector<Token> secondOp;
        secondOp.push_back(subTokens[endOfFirstOp + 1]);
        return secondOp;
    }
    else if (subTokens[endOfFirstOp + 1].type == BRC_OPEN)
    {   //... (
        throw GenericException("Don't use pointless brackets", subTokens[endOfFirstOp + 1].index);
    }
    else if (subTokens[endOfFirstOp + 1].type == BRC_CLOSE)
    {   //... )
        throw GenericException("Brackets don't add up", subTokens[endOfFirstOp + 1].index);
    }
    else if (subTokens[endOfFirstOp + 1].type == NONE)
    {
        //... NONE
        throw GenericException("Operator requires 2 arguments but only 1 was provided", subTokens[endOfFirstOp + 1].index); //This is a hack: +1 is the artificial NONE token which has an index of 0 (for the error message)
    }
    else
    {
        throw GenericException("Unexpected symbol", subTokens[0].index);
    }
}

int Parser::findClosingBracket(int operatorIndex , std::vector<Token> subTokens)
{
    //Given:    AND ( NOT ( b ) OR ( b d ) ) and openingBracketIndex is 3
    //Returns: 5       |      |
    
    //Check if at 0th index is a opening bracket. This needs to be the case for this function to be justified...
    if (subTokens[operatorIndex + 1].type == BRC_OPEN)
    {
        int bracketCount = 0;
        for (int i = operatorIndex + 1; i < subTokens.size(); i++)
        {
            if (subTokens[i].type == BRC_OPEN)
            {
                bracketCount++;
            }
            else if (subTokens[i].type == BRC_CLOSE)
            {
                bracketCount--;
            }
            
            if (bracketCount == 0)
            {
                return i;
            }
        }
        //The brackets don't add up
        throw GenericException("No curresponding closing bracket found", subTokens[operatorIndex + 1].index);
    }
    else
    {
        //There was no opening bracket at the beginning
        throw GenericException("Expected opening bracket after operand", subTokens[operatorIndex + 1].index);
    }
}

std::vector<Token> Parser::getBracketContent(std::vector<Token> subTokens, int index)
{
    // input:   AND ( NOT ( b ) OR ( b d ) )
    // output:  NOT ( b ) OR ( b d )
    
    if (subTokens[index + 1].type != BRC_OPEN) 
    {
        throw GenericException("Expected opening bracket after operand", subTokens[index + 1].index);
    }

    //Go to the right till there is the corresponding closing bracket ')'
    //Increment for opening brackets
    //Decrement for closing brackets
    
    int brackets = 0;
    
    for (int i = index + 1; i < subTokens.size(); i++)
    {
        if (subTokens[i].type == BRC_OPEN) 
        {
            //Found a opening bracket -> Increment count
            brackets++;
        }
        else if (subTokens[i].type == BRC_CLOSE) 
        {
            //Found a closing bracket -> Decrement count
            brackets--;
        }

        if (brackets == 0) 
        {
            //The right bracket to close off the original one has been found
            std::vector<Token> bracket_content = std::vector<Token>(subTokens.begin() + index + 2, subTokens.end() - (subTokens.size() - i));
            
            //Add an artificial NONE Token at the end to symbolise end of input
            bracket_content.push_back(Token(NONE, "", 0));
            return bracket_content;
        }
    }
    throw GenericException("Brackets opening and closing doesn't match", subTokens[index].index);
}
