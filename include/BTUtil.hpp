#include "TreeNode.hpp"

class BTUtil {
public:
	template <class T>
	static TreeNode<T>* leftSubtree(TreeNode<T>* tree) {
		if (tree) return tree->left;
		else return nullptr;
	}

	template <class T>
	static TreeNode<T>* rightSubtree(TreeNode<T>* tree) {
		if (tree) return tree->right;
		else return nullptr;
	}
    template <class T>
	static bool isLeaf(TreeNode<T>* tree) {
	    if (!tree)
            return false;

        if (tree->left || tree->right)
            return false;
        else
            return true;
	}
	template <class T>
	static bool insertLeft(TreeNode<T>* tree, T key, T value) {
		if (tree == nullptr)
			return false;

		if (tree->value == key) {
			if (tree->left == nullptr) {
				tree->left = new TreeNode<T>(value);
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return insertLeft(tree->left, key, value)
					|| insertLeft(tree->right, key, value);
		}
	}

	template <class T>
	static TreeNode<T>* buildTree(T elements[][3], unsigned count, T nullValue) {
		if (count == 0)
			return nullptr;

		TreeNode<T>* tree = new TreeNode<T>(elements[0][0]);
		for (unsigned i = 0; i < count; i++) {
			if (elements[i][1] != nullValue)
				insertLeft(tree, elements[i][0], elements[i][1]);
			if (elements[i][2] != nullValue)
				insertRight(tree, elements[i][0], elements[i][2]);
		}
		return tree;
	}

	template <class T>
	static bool insertRight(TreeNode<T>* tree, T key, T value) {
		if (tree == nullptr)
			return false;

		if (tree->value == key) {
			if (tree->right == nullptr) {
				tree->right = new TreeNode<T>(value);
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return insertRight(tree->left, key, value)
					|| insertRight(tree->right, key, value);
		}
	}

	template <class T>
	static int height (TreeNode<T>* tree) {
		if (tree == nullptr)
			return 0;
		else
			return 1 + max(height(tree->left), height(tree->right));
	}
};
