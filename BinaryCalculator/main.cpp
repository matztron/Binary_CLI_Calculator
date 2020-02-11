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
//g++ -o tst main.cpp tokenizer.cpp token.cpp truthTable.cpp binaryTree.cpp parser.cpp

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
    input = "AND(AND(a NOT(b)) c)"; //(debug) standard input

    try
    {
        //Generate tokens
        //std::cout << "Length of input: " << input.length() << std::endl;
        Tokenizer tokenizer(input);

        std::vector<Token> tst = tokenizer.collect();

        //debug
        std::cout << "Length of vector: " << tst.size() << std::endl;
        for (size_t i = 0; i < tst.size(); i++)
        {
            std::cout << tst[i].value << " Type: " << tst[i].type << std::endl;
        }
        std::cout << "------------------" << std::endl;

        
        Parser parser(tst);
        
        parser.readTokens(tst, parser.tree->root, 0);
        parser.tree->plotTree(parser.tree->root);
        
        Calculator calc(parser.getVarCount(), tst);
        
        for (int i = 0; i < calc.table.table_rows; i++) {
            bool result = calc.calculateBooleanValue(parser.tree->root->left);
            calc.table.resultColumn.push_back(result);
            calc.computeRow_index++;
            std::cout << "ENDRESULT: " << result << std::endl;
        }
        
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


//---

//either write: [prog_name] [binary equasion]
//or just call ./[prog_name] and then afterwards in while-true loop write equasions

// String wird von Tokenizer in Tokens umgewandelt und in Liste (vector) gespeichert
// 

//Reserved symbols:
// AND
// OR
// NOT
// XOR
// NAND
// NOR
// EQ
// (
// )
// TRUE
// FALSE

//Example: (A OR B) AND NOT C
// TRUE AND TRUE

// - Vorgehen -
// 1. Input von User bekommen
// 2. Tokens aus Userinput erzeugen
// 3. Parse-Tree erzeugen!
// 4. Anzahl der Variablen ermitteln und dementsprechend große Wertetabelle erzeugen
// 5. Wahrheitswerte einsetzen
// 6. Den Baum berechnen (von ganz unten nach oben)
// 7. Wahrheitstabelle mit Ergebnissplate ausgeben

//Proper exception catching implementation:
//https://stackoverflow.com/questions/1055387/throw-keyword-in-functions-signature

//New TODO
// 1. Make it operational <-
// 2. Make it possible to write both upper- and lowercase operators
// 2. Make stuff private that can be private
// 3. INtroduce destructors
// 4. Cleanup
// 5. Draw diagrams
