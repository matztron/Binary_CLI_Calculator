#include "binaryTree.h"

//Constructor
Btree::Btree()
{
	//root = NULL;
	root = new Node();
}

//Destructor
Btree::~Btree(){
    //Destroy entire tree
	destroy_tree();
}

//Public: Destroy entire tree
void Btree::destroy_tree()
{
    destroy_tree(root);
}

//Private: Destroy node and all sub nodes
void Btree::destroy_tree(Node *leaf)
{
	if(leaf != NULL){
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void Btree::insert(Node* newNode, Node* parent /*, Token leftChild, Token rightChild*/)
{
	if (parent->left == NULL)
	{
		//insert right
		parent->left = newNode;
	}
	else if (parent->right == NULL)
	{
		//insert left
		parent->right = newNode;
	}
    else
    {
        throw GenericException("Internal error. This has likely nothing to do with your input (Parent is satisified)", 0);
    }
}

void Btree::plotTree(Node * parent)
{
    //std::cout << "Hello I am the " << parent->token.type << " And those are my children:" << std::endl;

    if (parent->left != NULL)
    {
        if (parent->left->token.type == VAR)
        {
            std::cout << "I am " << parent->token.type << " I have a left child called: " << parent->left->token.value << std::endl;
        }
        else
        {
            std::cout << "I am " << parent->token.type << " I have a left child called: " << parent->left->token.type << std::endl;
        }
        plotTree(parent->left);
    }
    if (parent->right != NULL)
    {
        if (parent->right->token.type == VAR)
        {
            std::cout << "I am " << parent->token.type << " I have a right child called: " << parent->right->token.value << std::endl;
        }
        else
        {
            std::cout << "I am " << parent->token.type << " I have a right child called: " << parent->right->token.type << std::endl;
        }
        plotTree(parent->right);
    }
}
