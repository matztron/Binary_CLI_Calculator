//
//  calculator.h
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <vector>
#include "truthTable.h"
#include "binaryTree.h"
#include "exception.h"

//To match VARS with the corresponding boolean values
typedef struct
{
    Token token;
    int col_index;
} Tupel;

class Calculator
{
public:
    
    Calculator(int var_count, std::vector<Token> tokens);
        
    //The truth table
    TruthTable table;
    
    //Traverse tree and calculate each parent. Return global truth value
    bool calculateBooleanValue(Node* parent);
    
    void printResult();
    
    //Current row of truthTable beeing computed
    int computeRow_index;
    
private:
    
    //Get boolean value of token in context of current truthTable row
    bool lookUpVarValue(Token token);
    
    //Traverse input and remember Variables
    void fillTupels(std::vector<Token> tokens);
    
    //Holds the VAR and truthValue (col_index)
    std::vector<Tupel> tupels;
    
    //Logic-Gates:
    bool and_gate(bool op_one, bool op_two);
    bool or_gate(bool op_one, bool op_two);
    bool not_gate(bool op);
};

#endif // _CALCULATOR_H_
