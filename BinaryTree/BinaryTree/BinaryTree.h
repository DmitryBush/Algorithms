#pragma once
#include <functional>

class BinaryTree
{
private:
	class TreeNode
	{
	public:
		int value, vertexNumb;
		TreeNode* left, * right;

		TreeNode(const int& val = 0) : right(nullptr), value(val),
			vertexNumb(0), left(nullptr) {}
	};

	TreeNode* root;
	unsigned int countElements;
	TreeNode* AddNode(const int& val, TreeNode* node);
	void ForwardNumbering(TreeNode* node, int& vertex);
	void ForwardPass(TreeNode* node, const std::function<void(TreeNode* node)> t);
public:
	BinaryTree();

	void AddNode(const int& val);

	void Print();

	~BinaryTree();
};