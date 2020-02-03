#include "parser.h"

Parser::Parser(std::vector<Token> tokens_) 
{
    tokens = tokens_;
    tree = new Btree();
}

//Get the number of variables in the user input
int Parser::countVariables() 
{
    int count = 0;
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].type == VAR) 
        {
            count++;
        }
    }
    return count;
}


void Parser::readTokens(std::vector<Token> subTokens, Node* parent, int pos)
{
    // input: AND ( OR ( a b ) c )

    //int pos = 0;
    if (subTokens[pos].type == AND || subTokens[pos].type == OR) 
    {
        std::vector<Token> bracketContent = getBracketContent(subTokens, pos + 1); //hand over: ( OR ( a b ) c )

        Node* newNode = new Node;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->token = subTokens[pos];

        tree->insert(newNode, parent);

        getDualOperator(bracketContent,newNode);
    }
    else if (subTokens[pos].type == NOT) 
    {
        std::vector<Token> bracketContent = getBracketContent(subTokens, pos + 1);

        Node* newNode = nullptr;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->token = subTokens[pos];

        tree->insert(newNode, parent);

        getMonoOperator(bracketContent,newNode);
    }
    else if (subTokens[pos].type == BRC_OPEN)
    {
        //ist ein nutzloser Klammernausdruck
        //wie: _(_ NOT ( b ) OR ( b d ) _)_
        //    das               ...und das

        //schaue nochmal aber eins weiter rechts
        readTokens(subTokens, parent, pos++);
    }
    else
    {
        //ist nur einene variable
        // what should I do now?
        //kann ja eig nur bei einem not oder bei nur 1ner var im Input auftreten
    }
    
}

void Parser::getMonoOperator(std::vector<Token> subTokens, Node* parent)
{
    std::vector<Token> first = getFirstOperand(subTokens);

    //call again for first
    readTokens(first, parent, 0);
}

void Parser::getDualOperator(std::vector<Token> subTokens, Node* parent) 
{
    std::vector<Token> first = getFirstOperand(subTokens);
    std::vector<Token> second = getSecondOperand(subTokens);

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
        return std::vector<Token>(subTokens.begin() + 2, subTokens.end() - (subTokens.size() - closingBracketIndex));
    }
    else if (subTokens[0].type == VAR)
    {
        //just one var
        std::vector<Token> firstOp;
        firstOp.push_back(subTokens[0]);
        return firstOp;
    }
    //there could be a bracket to ignore... useless brackets or sth... 
    //some error cases
    return std::vector<Token>();
    
}

std::vector<Token> Parser::getSecondOperand(std::vector<Token> subTokens) 
{
    int closingBracketIndex = findClosingBracket(0, subTokens);
    if (subTokens[0].type == AND || subTokens[0].type == OR || subTokens[0].type == NOT) 
    {
        //traverse right till closing bracket
        return std::vector<Token>(subTokens.begin() + closingBracketIndex + 2, subTokens.end() - (subTokens.size() - 1));
    }
    else if (subTokens[closingBracketIndex + 2].type == VAR)
    {
        //just one var
        std::vector<Token> secondOp;
        secondOp.push_back(subTokens[0]);
        return secondOp;
    }
    return std::vector<Token>();
}

int Parser::findClosingBracket(int openingBracketIndex , std::vector<Token> subTokens) 
{
    //check if at 0th index is a opening bracket. This needs to be the case for this function to be justified...
    if (subTokens[0].type == BRC_OPEN)
    {
        int closingIndex = 0;
        for (int i = 0; i < subTokens.size(); i++)
        {
            if (subTokens[i].type == BRC_CLOSE) 
            {
                closingIndex = i;
                break;
            }
        }
            return closingIndex;
    }
    else
    {
        std::cout << "SYNTACTICAL ERROR!" << std::endl;
        std::cout << "Expected opening bracket" << std::endl;
        throw GenericException("Expected opening bracket after operand", subTokens[0].index);
    }
}

std::vector<Token> Parser::getBracketContent(std::vector<Token> subTokens, int index)
{
    // input:   AND ( NOT ( b ) OR ( b d ) )
    // output:  ( NOT ( b ) OR ( b d )
    
    if (subTokens[index /*+ 1*/].type != BRC_OPEN) 
    {
        //SYNTACTICAL ERROR!!!
        //Expected opening bracket after operand
        std::cout << "SYNTACTICAL ERROR!" << std::endl;
        std::cout << "Expected opening bracket after operand" << std::endl;
        throw GenericException("Expected opening bracket after operand", subTokens[index + 1].index);
    }

    //std::cout << "getOperands: index: " << tokens[index].type << std::endl;
    //std::cout << "getOperands: index+1: " << tokens[index + 1].type << std::endl;
    //std::cout << "------------------" << std::endl;

    //Go to the right till there is the corresponding ')'
    int brackets = 0;
    //increment for opening brackets
    //decrement for closing brackets
    for (int i = index; i < subTokens.size(); i++)
    {
        std::cout << "Index: " << i << std::endl;
        std::cout << "Schleifeniteration Typ: " << subTokens[i].type << std::endl;
        if (subTokens[i].type == BRC_OPEN) 
        {
            std::cout << "New opening klammer" << subTokens[i].type << std::endl;
            brackets++;
        }
        else if (subTokens[i].type == BRC_CLOSE) 
        {
            std::cout << "New closing klammer" << subTokens[i].type << std::endl;
            brackets--;
        }

        if (brackets == 0) 
        {
            //THIS DOESN'T WORK
            std::cout << "BRACKETS EQUAL OUT!!!" << std::endl;
            //the right bracket to close off the original one has been found
            return std::vector<Token>(subTokens.begin() + index + 1, subTokens.end() - (subTokens.size() - i));
        }
    }
    //SYNTACTICAL ERROR!!!
    //Brackets opening and closing doesn't match
    std::cout << "SYNTACTICAL ERROR!" << std::endl;
    std::cout << "Brackets opening and closing doesn't match" << std::endl;
    throw GenericException("Brackets opening and closing doesn't match", subTokens[index].index /* ??? */);
    
    //Return just so something is returned (for now) to supress a 'weird' error
    return std::vector<Token>();
}

void Parser::addChildren ()
{
    int tree_depth = 0;

    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].type == AND || tokens[i].type == OR || tokens[i].type == NOT) 
        {
            //getBracketContent(i);
        }
    }
    
}


// AND (NOT(b) OR(b d))
    //idea:
    //geh nach rechts,
    //im 1. Schritt muss eine '(' kommen
    //dann kommt bei dem 1. Operator entweder eine VAR oder eine Operator(And, Or...)
    //den nehmen und als CHILD an die Operator-Node hängen
    //
