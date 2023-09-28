#pragma once
#include <functional>
#include "TreeNode.h"
#include "List.h"

class BinaryTree
{
private:
	TreeNode* root;
	unsigned int countElements;

	TreeNode* Insert(const int& val, TreeNode* node);
	void PrefixPass(TreeNode* node, int& vertex);
	void InfixPass(TreeNode* node, const std::function<void(TreeNode* node)> t);
	void DeleteNode(TreeNode* node, list& stack, const int& val);
	void Clear(TreeNode* node);
	void Task(TreeNode* node, int path, int* maxVal);
public:
	BinaryTree();

	void Insert(const int& val);
	void DeleteNode(const int& val);

	void Clear();

	void Task();
	void Print();

	~BinaryTree();
};