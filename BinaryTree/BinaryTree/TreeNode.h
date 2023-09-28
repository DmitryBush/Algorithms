#pragma once

class TreeNode
{
public:
	int value, vertexNumb;
	TreeNode* left, * right;

	TreeNode(const int& val = 0) : right(nullptr), value(val),
		vertexNumb(0), left(nullptr) {}
};