# Binary_CLI_Calculator
Write stuff like: and(a b) or not(and(or(a b) c)) and get a truth-table back.
AT THE MOMENT IT ONLY SUPPORTS AND, OR, NOT

## Compilation
In the directory of the main.cpp file execute:

```
g++ -o binaryCalc main.cpp tokenizer.cpp token.cpp truthTable.cpp binaryTree.cpp parser.cpp calculator.cpp
```

Afterwards do
```
./binaryCalc
```

## Usage

### Correct syntax

* The input absolutly not case sensitive
* There are three accepted operators (```AND, OR, NOT```)
* After an operator there need to be operands contained withhin brackets
* The ```AND, OR``` operators accept two arguments (operands)
* The ```NOT``` operator accepts one argument
* Operands need to be separated by at least one space
* Operands can be every (ASCI)-combination of input characters if they don't name an operand.

### Example input
```
AND(a b)
OR( a b )
NOT(affe)
OR(and(a b) c)
not(or(and(a b) a))
```

## How it works
Internally your input is divided into Tokens by the Tokenizer.

Using those tokens a (binary) tree is created by the Parser.

Then the tree is recursively traversed for every possible variable combination in the user input by the Calculator.

At the end the result get printed to the console with the corresponding variable states. -> A truth table!
