//
//  parser.h
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include "token.h"
#include "exception.h"
#include "binaryTree.h"

class Parser 
{
    public:
        //List of user-inputted tokens
        Parser(std::vector<Token> tokens_);
        Btree *tree;

        void readTokens(std::vector<Token> subTokens, Node* parent, int pos);

        int getVarCount();
        //void addChildren();


    private:
        std::vector<Token> tokens;

        //Return the number of variables in user-input
        int countVariables();
    
        //Return the number of functions in user-input
        int countOperands(std::vector<Token> subTokens);
    
        //Returns the sublist of tokens inside the brackets
        std::vector<Token> getBracketContent(std::vector<Token> subTokens, int index);
    
        //
        void getMonoOperator(std::vector<Token> subTokens, Node* parent);
        void getDualOperator(std::vector<Token> subTokens, Node* parent);

        std::vector<Token> getFirstOperand(std::vector<Token> subTokens);
        std::vector<Token> getSecondOperand(std::vector<Token> subTokens);
        
        //Returns index of corresponding closing bracket when index of operator is provided
        int findClosingBracket(int operatorIndex , std::vector<Token> subTokens);
};

#endif // _PARSER_H_
