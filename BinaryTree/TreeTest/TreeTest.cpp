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

		TEST_METHOD(RightLeftNULL)
		{
			BinaryTree tree;

			tree.Insert(78);
			tree.Insert(42);
			tree.Insert(46);
			tree.Insert(26);
			tree.Insert(16);
			tree.Insert(34);
			tree.Insert(36);

			tree.DeleteNode(26);
			tree.Print();
		}

		TEST_METHOD(Two_Sons)
		{
			BinaryTree tree;

			tree.Insert(78);
			tree.Insert(40);
			tree.Insert(16);
			tree.Insert(44);
			tree.Insert(42);
			tree.Insert(41);
			tree.Insert(43);
			tree.Insert(47);
			tree.Insert(46);
			tree.Insert(48);

			tree.DeleteNode(44);
			tree.Print();
		}
	};
}
