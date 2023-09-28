#include "pch.h"
#include "CppUnitTest.h"
#include "..\BinaryTree\BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeTest
{
	TEST_CLASS(TreeTest)
	{
	public:
		
		TEST_METHOD(LeftRigthNULL)
		{
			BinaryTree tree;

			tree.Insert(89);
			tree.Insert(65);
			tree.Insert(71);
			tree.Insert(71);
			tree.Insert(77);
			tree.Insert(28);
			tree.Insert(1);
			tree.Insert(16);
			tree.Insert(20);
			tree.Insert(12);
			tree.Insert(5);

			tree.DeleteNode(1);
			tree.Print();
		}
	};
}
