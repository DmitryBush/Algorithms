#pragma once
#include <functional>
#include "TreeNode.h"
#include "List.h"

class BinaryTree
{
private:
	TreeNode* root;
	unsigned int countElements;

	TreeNode* AddNode(const int& val, TreeNode* node);
	void ForwardPass(TreeNode* node, int& vertex);
	void ForwardSortedPass(TreeNode* node, const std::function<void(TreeNode* node)> t);
	void DeleteNode(TreeNode* node, list& stack, const int& val);
public:
	BinaryTree();

	void AddNode(const int& val);
	void DeleteNode(const int& val);

	void Print();

	~BinaryTree();
};