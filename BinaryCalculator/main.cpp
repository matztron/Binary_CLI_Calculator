//Build with:
//[cmd] + [shift] + [b]
//or
//g++ -o tst main.cpp tokenizer.cpp token.cpp truthTable.cpp binaryTree.cpp parser.cpp

//debug with:
//[cmd] + [shift] + [d]

#include <iostream>
#include <string>

#include "tokenizer.h"
#include "parser.h"
#include "exception.h"

//debug
#include <vector>
#include "truthTable.h"
#include "binaryTree.h"
#include "calculator.h"
//---

using namespace std;

int main(int argc, char const *argv[])
{
    string input;
    //getline(cin, input);
    input = "OR ( a abc )"; //(debug) standard input

    //Problem when:
    // a) too few of stuff is throwing errors BUT too much of stuff isn't!
    //          idea:   when you have found all you need the next token should be a NONE token
    //                  if this isnt the case then a error should be thrown
    
    //Debug
    //cout << input << endl;

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

        //Parser parser(tokenizer.collect());
        
        //Main code:
        Parser parser(tst);
        parser.readTokens(tst, parser.tree->root, 0);
        parser.tree->plotTree(parser.tree->root);
        
        Calculator calc(3, tst);
        bool result = calc.calculateBooleanValue(parser.tree->root->left);
        std::cout << "ENDRESULT: " << result << std::endl;
        
        //test input AND ( OR ( a b ) c )
        //std::vector<Token> tstTwo = parser.getBracketContent(tst , 0);
        //test opcount
        //int opCount = parser.countOperands(tstTwo);
        //std::cout << "Operand count is: " << opCount << std::endl;
        
        //test findClosingBracket
        //int closing = parser.findClosingBracket(0, tst);
        //std::cout << "CLOSING: " << closing << std::endl;
        
        //test getSecondOperand and getFirstOperand
        /*std::vector<Token> tstThree = parser.getFirstOperand(tstTwo);
        std::vector<Token> tstFour = parser.getSecondOperand(tstTwo);
        std::cout << "First operand:" << std::endl;
        std::cout << "------------------" << std::endl;
        for (int i = 0; i < tstThree.size(); i++)
        {
            std::cout << tstThree[i].value << " Type: " << tstThree[i].type << std::endl;
        }
        
        std::cout << "Second operand:" << std::endl;
        for (int i = 0; i < tstFour.size(); i++)
        {
            std::cout << tstFour[i].value << " Type: " << tstFour[i].type << std::endl;
        }*/
        
        //!! !
        //parser.readTokens(tst,parser.tree->root, 0);
        //parser.tree->plotTree(parser.tree->root);
        //debug
        
        //std::cout << "Length of vector: " << tst.size() << std::endl;
        /*std::cout << "------------------" << std::endl;
        std::cout << "Subline" << std::endl;
        std::cout << "Subline len: " << tstTwo.size() << std::endl;
        for (int i = 0; i < tstTwo.size(); i++)
        {
            std::cout << tstTwo[i].value << " Type: " << tstTwo[i].type << std::endl;
        }*/
        
        //---
        //DEBUG: Truthtable
        //construct table object
        //TruthTable table(3);
        //table.fillTable();
        //table.plotTable();
        //---
        
        //---
        //DEBUG: Binary Tree
        /*Btree *tree = new Btree();
        
        //test nodes
        Node* node_one = new Node;
        Token token_one;
        token_one.type = AND;
        node_one->token = token_one;
        
        Node* node_two = new Node;
        Token token_two;
        token_two.type = OR;
        node_two->token = token_two;
        
        Node* node_three = new Node;
        Token token_three;
        token_three.type = VAR;
        node_three->token = token_three;
        
        tree->insert(node_one, tree->root);
        tree->insert(node_two, node_one);
        //tree->insert(node_three, tree->root);
        
        //tree->insert(node_three, node_one);
        //tree->insert(node_three, node_two);
        //plot the result
        tree->plotTree(tree->root);
        //delete tree; ???
        //---
        */
        
        //---
        /*tree->insert(10);
	    tree->insert(6);
	    tree->insert(14);
	    tree->insert(5);
	    tree->insert(8);
	    tree->insert(11);
	    tree->insert(18);

	    tree->preorder_print();
	    tree->inorder_print();
	    tree->postorder_print();

	    //delete tree;*/
        //---
        
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
// 2. Make stuff private that can be private
// 3. INtroduce destructors
// 4. Cleanup
// 5. Draw diagrams
