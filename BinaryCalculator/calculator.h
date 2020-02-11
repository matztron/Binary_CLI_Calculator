//
//  calculator.h
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#ifndef calculator_hpp
#define calculator_hpp

#include <vector>
#include "truthTable.h"
#include "binaryTree.h"
#include "exception.h"

//To match VARS with the right boolean values
typedef struct
{
    Token token;
    int col_index;
} Tupel;

class Calculator
{
public:
    
    Calculator(int var_count, std::vector<Token> tokens);
    
    //the truth table
    TruthTable table;
    
    int currentLine; //current line in TruthTable
    
    //Get boolean value of token in context of current truthTable row
    bool lookUpVarValue(Token token);

    //Traverse tree and calculate each parent. Return global truth value
    bool calculateBooleanValue(Node* parent);
    
    
    //Holds the VAR and truthValue (col_index)
    std::vector<Tupel> tupels;
    
    //current row of truthTable beeing computed
    int computeRow_index;
    
private:
    //Traverse tree and remember Variables
    void fillTupels(std::vector<Token> tokens);
    
    //Gates:
    bool and_gate(bool op_one, bool op_two);
    bool or_gate(bool op_one, bool op_two);
    bool not_gate(bool op);
};

#endif /* calculator_hpp */
