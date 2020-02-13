//
//  main.cpp
//  BinaryCalculator
//
//  Created by Matthias Musch on 06.02.20.
//  Copyright © 2020 Matthias Musch. All rights reserved.
//

//Build with:
//[cmd] + [shift] + [b]
//or
//g++ -o tst main.cpp tokenizer.cpp token.cpp truthTable.cpp binaryTree.cpp parser.cpp calculator.cpp

//debug with:
//[cmd] + [shift] + [d]

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
    
    //getline(cin, input);
    input = "and(a or(c d))"; //(debug) standard input <-that works
    
    // Problem(s):
    // * There can be stuff on global scope which doesn't mae sense
    // * The stuff after the first expression will be ignored anyways
    //   (since the left branch of the root node gets parsed)

    try
    {
        //Generate tokens
        Tokenizer tokenizer(input);

        std::vector<Token> tst = tokenizer.collect();

        //debug
        /*std::cout << "Length of vector: " << tst.size() << std::endl;
        for (size_t i = 0; i < tst.size(); i++)
        {
            std::cout << tst[i].value << " Type: " << tst[i].type << std::endl;
        }
        std::cout << "------------------" << std::endl;*/

        
        Parser parser(tst);
        
        parser.readTokens(tst, parser.tree->root, 0);
        //parser.tree->plotTree(parser.tree->root);
        
        Calculator calc(parser.getVarCount(), tst);
        
        for (int i = 0; i < calc.table.table_rows; i++)
        {
            bool result = calc.calculateBooleanValue(parser.tree->root->left);
            calc.table.resultColumn.push_back(result);
            calc.computeRow_index++;
            //std::cout << "ENDRESULT: " << result << std::endl;
        }
        
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
// 1. Make it operational <-
// 2. Make it possible to write both upper- and lowercase operators
// 2. Make stuff private that can be private
// 3. INtroduce destructors
// 4. Cleanup
// 5. Draw diagrams
