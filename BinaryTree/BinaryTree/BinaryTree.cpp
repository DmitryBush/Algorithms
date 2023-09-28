#include "BinaryTree.h"
#include <iostream>

TreeNode* BinaryTree::Insert(const int& val, TreeNode* node)
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
		node->left = Insert(val, node->left);
	}
	else
	{
		node->right = Insert(val, node->right);
	}
	return node;
}

void BinaryTree::PrefixPass(TreeNode* node, int& vertex)
{
	if (node == nullptr)
		return;

	node->vertexNumb = vertex++;
	PrefixPass(node->left, vertex);
	PrefixPass(node->right, vertex);
}

void BinaryTree::InfixPass(TreeNode* node, const std::function<void(TreeNode* node)> t)
{
	if (node == nullptr)
		return;

	InfixPass(node->left, t);
	t(node);
	InfixPass(node->right, t);
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
			{
				stack[0]->left = nullptr;
				delete node;
			}
			else
			{
				stack[0]->right = nullptr;
				delete node;
			}
		}
		else if (node->left == nullptr)
		{
			if (node == stack[0]->left)
			{
				stack[0]->left = node->right;
				delete node;
			}
			else
			{
				stack[0]->right = node->right;
				delete node;
			}
		}
		else if (node->right == nullptr)
		{
			if (node == stack[0]->left)
			{
				stack[0]->left = node->left;
				delete node;
			}
			else
			{
				stack[0]->right = node->left;
				delete node;
			}
		}
		else if (node->right->left == nullptr)
		{
			TreeNode* del = node;
			if (node == stack[0]->left)
			{
				stack[0]->left = node->right;
				stack[0]->left->left = node->left;
				delete del;
			}
			else
			{
				stack[0]->right = node->right;
				stack[0]->right->left = node->left;
				delete del;
			}
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

void BinaryTree::Clear(TreeNode* node)
{
	if (node)
	{
		Clear(node->left);
		Clear(node->right);
		delete node;
	}
}

void BinaryTree::Task(TreeNode* node, int path, int* maxVal)
{
	if (node == nullptr)
		return;

	if (node->left)
	{
		if (node->left->value > node->value)
			Task(node->left, path + 1, maxVal);
		else
			Task(node->left, 1, maxVal);
	}

	if (node->right)
	{
		if (node->right->value > node->value)
			Task(node->right, path + 1, maxVal);
		else
			Task(node->right, 1, maxVal);
	}

	if (path > *maxVal)
		*maxVal = path;
}

BinaryTree::BinaryTree(): root(nullptr), countElements(0)
{}

void BinaryTree::Insert(const int& val)
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
		root->left = Insert(val, root->left);
	}
	else
	{
		root->right = Insert(val, root->right);
	}
	PrefixPass(root, vertexNumb);
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

void BinaryTree::Clear()
{
	Clear(root); 
	countElements = 0; root = nullptr;
}

void BinaryTree::Task()
{
	int* maxPath = new int{ 0 };
	if (root)
	{
		Task(root, 1, maxPath);
		std::cout << "Max path is " << *maxPath << '\n';
	}
	else
	{
		std::cout << "Error has occuried: Tree is empty" << '\n';
	}
	delete maxPath; maxPath = nullptr;
}

void BinaryTree::Print()
{
	if (root == nullptr)
		std::cout << "Theres no elements to show" << '\n';
	else
	{
		int a = 0;
		InfixPass(root, [](TreeNode* node) {std::cout << node->value << ' '; });
		std::cout << '\n';
	}	
}

BinaryTree::~BinaryTree() { Clear(); }
