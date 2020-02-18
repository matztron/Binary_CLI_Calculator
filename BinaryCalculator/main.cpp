//
//  main.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

//Instructions for compiling the project:
//
//In this folder execute:
//g++ -o tst main.cpp tokenizer.cpp token.cpp truthTable.cpp binaryTree.cpp parser.cpp calculator.cpp
//
//debug with:
//[cmd] + [shift] + [d]
//[cmd] + [r]
//

#include <iostream>
#include <string>
#include <vector>

#include "tokenizer.h"
#include "parser.h"
#include "exception.h"
#include "calculator.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string input;
    
    std::cout << "Insert binary expression" << std::endl;
    //getline(cin, input);
    input = "or(and(a b) c)"; //(debug) input
    
    try
    {
        //Generate tokens
        Tokenizer tokenizer(input);

        //Get list of all tokens in input
        std::vector<Token> tokens = tokenizer.collect();

        //Hand tokens to a parser-object
        Parser parser(tokens);
        
        //Build parse-tree
        parser.readTokens(tokens, parser.tree->root, 0);
        
        //Generate a calculator
        Calculator calc(parser.getVarCount(), tokens);
        
        //Calculate result for each row
        for (int i = 0; i < calc.table.table_rows; i++)
        {
            //The root node only has left-children
            bool result = calc.calculateBooleanValue(parser.tree->root->left);
            calc.table.resultColumn.push_back(result);
            calc.computeRow_index++;
        }
        
        //Plot the results that have been calculated
        calc.printResult();
        
    }
    catch(const GenericException& e)
    {
        cout << "There was an error calculating your input." << endl;
        cout << e.what() << endl;
        cout << "The character at position \033[1;31m" << e.position + 1 << "\033[0m of your input is faulty." << endl;
        cout << input << endl;

        //Print spaces before faulty input
        for (unsigned int i = 0; i < e.position; i++) {
            cout << " ";
        }
        cout << "\033[1;31m^\033[0m" << endl;
    }

    return 0;
}

//New TODO
// 1. Make it operational
// 2. Make it possible to write both upper- and lowercase operators
// 2. Make stuff private that can be private <-
// 3. INtroduce destructors
// 4. Cleanup
// 5. Draw diagrams
