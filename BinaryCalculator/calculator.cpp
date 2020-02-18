//
//  calculator.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

#include "calculator.h"

//Constructor
Calculator::Calculator(int var_count, std::vector<Token> tokens) : table(var_count)
{
    //write true and false values into the table
    table.fillTable();
    
    //populate Tupel vector
    fillTupels(tokens);
    
    //start computing first row
    computeRow_index = 0;
}

//Calculate Parent and Children
//INITIALLY HAND THIS FUNCTION THE LEFT CHILD OF ROOT BECAUSE ROOT IS A NONE TOKEN AND THEY AREN'T HANDLED!
bool Calculator::calculateBooleanValue(Node* parent)
{
    if (parent->token.type == VAR)
    {
        //Directly return the boolean value
        return lookUpVarValue(parent->token);
    }
    else if (parent->token.type == NOT)
    {
        //NOT operators only have left childs
        return not_gate(calculateBooleanValue(parent->left));
    }
    else if (parent->token.type == AND)
    {
        return and_gate(calculateBooleanValue(parent->left), calculateBooleanValue(parent->right));
    }
    else if (parent->token.type == OR)
    {
        return or_gate(calculateBooleanValue(parent->left), calculateBooleanValue(parent->right));
    }
    else
    {
        //idk...
        throw GenericException("Internal error. This has likely nothing to do with your input", 0);
    }
    //traverse tree
    //idea:
    //  * start at root
    //  * if the branch to the left/right is not null and the type is not a VAR (so no leaf): call function for this branch again
    //  * the given return from this path is needed to calculate the current operator
    //  * if one of the branches contains a VAR use this one directly
    
    //  *- if we find a VAR we check what boolean value it should have in the current execution
    //  *- if you have computed up to the first node after the root node write this result into the truthTable
    //  *- plot the truthTable
    //  *- ???
    //  *- Profit!
}

bool Calculator::lookUpVarValue(Token token)
{
    int col_index;
    //Iterate through Tupels
    for (int i = 0; i < tupels.size(); i++) {
        
        if (tupels[i].token.value == token.value)
        {
            //Found the token
            col_index = i;
            //Look up boolean value in TruthTable (and return it)
            return table.getElement(computeRow_index, col_index);
        }
    }
    //The variable value could not be found!
    throw GenericException("Internal error. This has likely nothing to do with your input", token.index);
}

void Calculator::fillTupels(std::vector<Token> tokens)
{
    int count = 0;
    
    for (int i = 0; i < tokens.size(); i++) {
        //If we found a VAR
        if (tokens[i].type == VAR)
        {
            bool found = false;
            //check if we have seen it already
            for (int j = 0; j < tupels.size(); j++) {
                if (tokens[i].value == tupels[j].token.value)
                {
                    found = true;
                }
            }
            if (found == false)
            {
                Tupel newTupel;
                newTupel.token = tokens[i];
                newTupel.col_index = count;
                count++;
                //Add it to Tupel with an unique index
                tupels.push_back(newTupel);
            }
        }
    }
}

void Calculator::printResult()
{
    //Should plot something like this:
    //  ┌─┬─┐
    //  │1│0│
    //  ├─┼─┤
    //  │0│1│
    //  └─┴─┘
    
    string rowDelimiter;
    std::vector<int> colWidths;
    
    //Get column widths
    for (int i = 0; i < tupels.size(); i++) {
        int count = 0;
        for (int j = 0; j < tupels[i].token.value.length(); j++) {
            count++;
        }
        colWidths.push_back(count);
    }
    //dont forget about the Results column
    colWidths.push_back(6); //6 is the length of the string 'RESULT'
    
    //Build delimiter line
    rowDelimiter.append("├");
    for (int i = 0; i < colWidths.size(); i++) {
        for (int j = 0; j < colWidths[i]; j++) {
            rowDelimiter.append("─");
        }
        if (i < colWidths.size()-1)
        {
            rowDelimiter.append("┼");
        }
    }
    rowDelimiter.append("┤");
    
    //Print upper border
    std::cout << "┌";
    for (int i = 0; i < colWidths.size(); i++)
    {
        for (int j = 0; j < colWidths[i]; j++)
        {
            std::cout << "─";
        }
        if (i < colWidths.size()-1)
        {
            std::cout << "┬";
        }
    }
    std::cout << "┐" << std::endl;
    
    //Print headline
    std::cout << "│";
    for (int i = 0; i < tupels.size(); i++)
    {
        //Print a VAR
        std::cout << tupels[i].token.value << "│";
        
    }
    std::cout << "RESULT" << "│";
    std::cout << std::endl;
    
    //Print data with results at the end
    for (int i = 0; i < table.table_rows; i++)
    {
        //draw the delimiter line for prev. row
        std::cout << rowDelimiter << std::endl;
        
        //From right to left
        for (int j = 0; j < table.table_columns; j++)
        {
            std::cout << "│";
            std::cout << table.getElement(i, j);
            for (int k = 1; k < colWidths[j]; k++) {
                std::cout << " ";
            }
        }
        std::cout << "│";
        std::cout << table.resultColumn[i];
        for (int k = 1; k < colWidths.back(); k++) {
            std::cout << " ";
        }
        std::cout << "│" << std::endl;
    }
    
    //Print lower border
    std::cout << "└";
    for (int i = 0; i < colWidths.size(); i++)
    {
        for (int j = 0; j < colWidths[i]; j++)
        {
            std::cout << "─";
        }
        if (i < colWidths.size()-1)
        {
            std::cout << "┴";
        }
    }
    std::cout << "┘" << std::endl;
}

bool Calculator::and_gate(bool op_one, bool op_two)
{
    if (op_one == true && op_two == true) {
        return true;
    }
    else
    {
        return false;
    }
}

bool Calculator::or_gate(bool op_one, bool op_two)
{
    if (op_one == false && op_two == false) {
        return false;
    }
    else
    {
        return true;
    }
}

bool Calculator::not_gate(bool op)
{
    if (op == true)
    {
        return false;
    }
    else
    {
        return  true;
    }
}
