#include "BinaryTree.h"
#include <iostream>

TreeNode* BinaryTree::AddNode(const int& val, TreeNode* node)
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

void BinaryTree::ForwardPass(TreeNode* node, int& vertex)
{
	if (node == nullptr)
		return;

	node->vertexNumb = vertex++;
	ForwardPass(node->left, vertex);
	ForwardPass(node->right, vertex);
}

void BinaryTree::ForwardSortedPass(TreeNode* node, const std::function<void(TreeNode* node)> t)
{
	if (node == nullptr)
		return;

	ForwardSortedPass(node->left, t);
	t(node);
	ForwardSortedPass(node->right, t);
}

void BinaryTree::DeleteNode(TreeNode* node, list& stack, const int& val)
{
	if (node == nullptr)
		return;
	else if (val < node->value)
	{
		stack.PushForward(node);
		DeleteNode(node->left, stack, val);
	}
	else if (val > node->value)
	{
		stack.PushForward(node);
		DeleteNode(node->right, stack, val);
	}
	else
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			if (node == stack[0]->left)
				stack[0]->left = nullptr;
			else
				stack[0]->right = nullptr;
			delete node;
		}
		else if (node->left == nullptr)
		{
			TreeNode* del = node;
			node = node->right; delete del;
		}
		else if (node->right == nullptr)
		{
			TreeNode* del = node;
			node = node->left; delete del;
		}
		else if (node->right->left == nullptr)
		{
			TreeNode* del = node;
			node = node->right; node->left = del->left;
			delete del;
		}
		else
		{
			TreeNode* del = node->right->left, * preElem = node->right;
			while (del->left) { del = del->left;  preElem = preElem->left; }

			preElem->left = nullptr;
			node->value = del->value;
			delete del;
		}
	}
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
	ForwardPass(root, vertexNumb);
}

void BinaryTree::DeleteNode(const int& val)
{
	list stack;
	if (root == nullptr)
		return;
	else if (val < root->value)
	{
		stack.PushForward(root);
		DeleteNode(root->left, stack, val);
	}
	else if (val > root->value)
	{
		stack.PushForward(root);
		DeleteNode(root->right, stack, val);
	}
	else
	{
		if (root->left == nullptr && root->right == nullptr)
		{
			delete root; root = nullptr;
		}
		else if (root->left == nullptr)
		{
			TreeNode* del = root;
			root = root->right; delete del;
		}
		else if (root->right == nullptr)
		{
			TreeNode* del = root;
			root = root->left; delete del;
		}
		else if(root->right->left == nullptr)
		{
			TreeNode* del = root;
			root = root->right; root->left = del->left;
			delete del;
		}
		else
		{
			TreeNode* del = root->right->left, *preElem = root->right;
			while (del->left) { del = del->left;  preElem = preElem->left; }

			preElem->left = nullptr;
			root->value = del->value; 
			delete del;
		}
	}
}

void BinaryTree::Print()
{
	if (root == nullptr)
		std::cout << "Theres no elements to show" << '\n';
	else
		ForwardSortedPass(root, [](TreeNode* node) {std::cout << node->value << ' '; });
}

BinaryTree::~BinaryTree()
{

}
