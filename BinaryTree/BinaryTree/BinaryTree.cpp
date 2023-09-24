#include "BinaryTree.h"
#include <iostream>

BinaryTree::TreeNode* BinaryTree::AddNode(const int& val, TreeNode* node)
{
	if (node == nullptr)
	{
		try
		{
			node = new TreeNode(val);
			countElements++;
		}
		catch (const std::bad_alloc& ex)
		{
			std::cout << "An error has occured" << "(code: " << ex.what()
				<< "Not enough free RAM. Close other programs and try again" << std::endl;
		}
	}
	else if (val < node->value)
	{
		node->left = AddNode(val, node->left);
	}
	else
	{
		node->right = AddNode(val, node->right);
	}
	return node;
}

void BinaryTree::ForwardNumbering(TreeNode* node, int& vertex)
{
	if (node == nullptr)
		return;

	node->vertexNumb = vertex++;
	ForwardNumbering(node->left, vertex);
	ForwardNumbering(node->right, vertex);
}

void BinaryTree::ForwardPass(TreeNode* node, const std::function<void(TreeNode* node)> t)
{
	if (node == nullptr)
		return;

	ForwardPass(node->left, t);
	t(node);
	ForwardPass(node->right, t);
}

BinaryTree::BinaryTree(): root(nullptr), countElements(0)
{}

void BinaryTree::AddNode(const int& val)
{
	int vertexNumb = 1;
	if (root == nullptr)
	{
		try
		{
			root = new TreeNode(val);
			countElements++;			
		}
		catch (const std::bad_alloc& ex)
		{
			std::cout << "An error has occured" << "(code: " << ex.what()
				<< "Not enough free RAM. Close other programs and try again" << std::endl;
		}
	}
	else if (val < root->value)
	{
		root->left = AddNode(val, root->left);
	}
	else
	{
		root->right = AddNode(val, root->right);
	}
	ForwardNumbering(root, vertexNumb);
}

void BinaryTree::Print()
{
	if (root == nullptr)
		std::cout << "Theres no elements to show" << '\n';
	else
	{
		/*TreeNode* firstElem = root;
		while (firstElem->left) { firstElem = firstElem->left; }*/
		ForwardPass(root, [](TreeNode* node) {std::cout << node->value << ' '; });
	}
}

BinaryTree::~BinaryTree()
{
}
