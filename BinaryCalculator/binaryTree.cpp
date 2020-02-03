#include "binaryTree.h"

Btree::Btree(){
	//root = NULL;
	root = new Node();
}

Btree::~Btree(){
	destroy_tree();
}

void Btree::destroy_tree(Node *leaf){
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
        std::cout << "Error: Tried to insert a third element in binary tree whichs parent is already full" << std::endl;
        return;
    }
    //if both are occupied do nothing. This should never happen
    //might make an error case here!!!
	
	/*if(root != NULL){
		//there is already a node
		//add it to another
	}else{
		//currently no node
		node* left_node;
		left_node->token = token;
		left_node->left = NULL;
		left_node->right = NULL;

		node* right_node;
		right_node->token = token;
		right_node->left = NULL;
		right_node->right = NULL;

		root = newNode;
		//root->token = token;
		//root->left = left_node NULL;
		//root->right = right_node NULL;
	}*/
}

void Btree::plotTree(Node * parent)
{
    //std::cout << "Hello I am the " << parent->token.type << " And those are my children:" << std::endl;

    if (parent->left != NULL)
    {
        std::cout << "I am " << parent->token.type << " I have a left child called: " << parent->left->token.type << std::endl;
        plotTree(parent->left);
    }
    if (parent->right != NULL)
    {
        std::cout << "I am " << parent->token.type << " I have a right child called: " << parent->right->token.type << std::endl;
        plotTree(parent->right);
    }
}


/*void Btree::insert(int key, node *leaf){

	if(key < leaf->value){
		if(leaf->left != NULL){
			insert(key, leaf->left);
		}else{
			leaf->left = new node;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}else if(key >= leaf->value){
		if(leaf->right != NULL){
			insert(key, leaf->right);
		}else{
			leaf->right = new node;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}
	}

}*/

/*void Btree::insert(int key){
	if(root != NULL){
		insert(key, root);
	}else{
		root = new node;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}*/

/*node *Btree::search(int key, node *leaf){
	if(leaf != NULL){
		if(key == leaf->value){
			return leaf;
		}
		if(key < leaf->value){
			return search(key, leaf->left);
		}else{
			return search(key, leaf->right);
		}
	}else{
		return NULL;
	}
}*/

/*node *Btree::search(int key){
	return search(key, root);
}*/

void Btree::destroy_tree(){
	destroy_tree(root);
}

/*void Btree::inorder_print(){
	inorder_print(root);
	cout << "\n";
}*/

/*void Btree::inorder_print(node *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}*/

/*void Btree::postorder_print(){
	postorder_print(root);
	cout << "\n";
}*/

/*void Btree::postorder_print(node *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		cout << leaf->value << ",";
	}
}*/

/*void Btree::preorder_print(){
	preorder_print(root);
	cout << "\n";
}*/

/*void Btree::preorder_print(node *leaf){
	if(leaf != NULL){
		cout << leaf->value << ",";
		inorder_print(leaf->left);
		inorder_print(leaf->right);
	}
}*/

/*int main(){

	//btree tree;
	btree *tree = new btree();

	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);

	tree->preorder_print();
	tree->inorder_print();
	tree->postorder_print();

	delete tree;

}*/
