
#include <iostream>
#include <fstream>
#include <memory>

#include "binary_search_tree.h"

void Visit( int& value )
{
	std::cout << value << ", ";
}

int main()
{
	BinarySearchTree< int > bst;

	std::ifstream file( "values.txt" );
	for ( int i = 0; i < 100; i++ )
	{
		int input;
		file >> input;
		bst.Add( input );
	}

	std::cout << "Binary Search Tree using 'values.txt'" << std::endl;
	std::cout << "Tree height: " << bst.get_height() << std::endl;
	std::cout << "Preorder traversal: \n{";
	bst.PreorderTraverse( Visit );
	std::cout << '}' << std::endl << "Inorder traversal: \n{";
	bst.InorderTraverse( Visit );
	std::cout << '}' << std::endl << "Postorder traversal: \n{";
	bst.PostorderTraverse( Visit );
	std::cout << '}' << std::endl;
}