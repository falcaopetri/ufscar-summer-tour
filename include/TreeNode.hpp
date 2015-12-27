#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

template <class T>
class TreeNode {
private:
	T value;
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode<T> () {
		left = right = nullptr;
	}

public:
	TreeNode<T> (T _value)
		: TreeNode()
	{
		value = _value;
	}

	T& getValue() {
		return value;
	}

	~TreeNode<T> () {
		if (left) delete left;
		if (right) delete right;
	}

	friend class BTUtil;
};

#endif
