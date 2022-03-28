#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    bool contains(BSTNode<T> *root, BSTNode<T> *node) const;
    void insert(BSTNode<T> *&root, const T &data);
    void remove(BSTNode<T> *&root, const T &data);
    void deletetree(BSTNode<T> *&root);
    void copying(BSTNode<T> *&root, BSTNode<T> *obj);
    BSTNode<T> *search(BSTNode<T> *root, const T &data) const;
    BSTNode<T> *right_min(BSTNode<T> *root) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *root, BSTNode<T> *node, TraversalPlan tp) const;
    BSTNode<T> *fparent(BSTNode<T> *root, BSTNode<T> *node) const;
private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    root = NULL;
    
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    if(obj.root == NULL)
    {
    	root = NULL;
	}
    else
    {
        copying(this->root, obj.root);
    }
}

template<class T>
BST<T>::~BST() {
    deletetree(root);
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    if(root == NULL)
    {
        return NULL;
    }
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    if(root == NULL)
    {
    	return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    return contains(root, node);
}
template<class T>
void BST<T>::insert(const T &data) {
    insert(root, data);
    
}

template<class T>
void BST<T>::remove(const T &data) {
    remove(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    deletetree(root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    return search(root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {

    if (tp == inorder) {
        if(node == NULL || root == NULL)
        {
            return NULL;
        }
        return getSuccessor(root, node, inorder);
    } else if (tp == preorder) {
        if(node == NULL || root == NULL)
        {
            return NULL;
        }
        return getSuccessor(root, node, preorder);
        
    } else if (tp == postorder) {
        if(node == NULL || root == NULL)
        {
            return NULL;
        }
        return getSuccessor(root, node, postorder);
    }
    return NULL;
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;

    } else if (tp == preorder) {
        if(isEmpty())
        {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        else{
            std::cout << "BST_preorder{" << std::endl;
            print(root, preorder);
            std::cout << std::endl << "}" << std::endl;
        }
    } else if (tp == postorder) {
        if(isEmpty())
        {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        else{
            std::cout << "BST_postorder{" << std::endl;
            print(root, postorder);
            std::cout << std::endl << "}" << std::endl;
        }
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    deletetree(this->root);
    copying(this->root, rhs.root);
    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
	}
    else if (tp == preorder) 
	{
	    std::cout << "\t" << node->data;
	    if(node->left)
	    {
	        std::cout << "," << std::endl;
	    }
	    print(node->left, preorder);
	    if(node->right)
	    {
	        std::cout << "," << std::endl;
	    }
	    print(node->right, preorder);
	}
    else if (tp == postorder) {
        print(node->left, postorder);
        if(node->left)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if(node->right)
        {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->data;
    }
}

/* HELPER FUNCS */

template<class T>
bool BST<T>::contains(BSTNode<T> *root, BSTNode<T> *node) const {

	if(root == NULL)
	{
		return false;
	}
	else
	{
		if(root->data == node->data)
		{
			return true;
		}
		if(root->left != NULL)
		{
			contains(root->left, node);
		}
		if(root->right != NULL)
		{
			contains(root->right, node);
		}
	}
}

template<class T>
void BST<T>::insert(BSTNode<T> *&root, const T &data)
{
	if(root == NULL)
	{
        root = new BSTNode<T>(data, NULL, NULL);
        
	}
	else
	{
		if(data < root->data)
		{
			insert(root->left, data);
		}
		if(data > root->data)
		{
			insert(root->right, data);
		}
	}
	
}

template<class T>
void BST<T>::remove(BSTNode<T> *&root, const T &data)
{
    if(root == NULL)
    {
        return;
    }
    else if(root->data > data)
    {
        remove(root->left, data);
    }
    else if(root->data < data)
    {
        remove(root->right, data);
    }
    else if(root->data == data)
    {
        if(root->left != NULL && root->right != NULL)
        {
            root->data = right_min(root->right)->data;
            remove(root->right, root->data);
        }
        else if(root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if(root->left == NULL && root->right != NULL)
        {
            BSTNode<T> *curr;
            curr = root;
            root = root->right;
            delete curr;
        }
        else if(root->left != NULL && root->right == NULL)
        {
            BSTNode<T> *curr;
            curr = root;
            root = root->left;
            delete curr;
        }
    }
    return;
}

template<class T>
BSTNode<T> * BST<T>::search(BSTNode<T> *root, const T &data) const {

    if(root == NULL || root->data == data)
	{
		return root;
	}
	if(root->data > data)
	{
		return search(root->left, data);
	}
	if(root->data < data)
	{
		return search(root->right, data);
	}
    return NULL;
}

template<class T>
void BST<T>::deletetree(BSTNode<T> *&root)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        deletetree(root->left);
        deletetree(root->right);
        delete root;
        root = NULL;
    }
}
template<class T>
void BST<T>::copying(BSTNode<T> *&root, BSTNode<T> *obj)
{
    if(obj == NULL)
    {
        root = NULL;
        return;
    }
    else
    {
        root = new BSTNode<T>();
        root->data = obj->data;
        copying(root->left, obj->left);
        copying(root->right, obj->right);
    }
}

template<class T>
BSTNode<T> * BST<T>::right_min(BSTNode<T> *root) const
{   
    if(root != NULL)
    {
        if(root->left == NULL)
        {
            return root;
        }
        else{
            return right_min(root->left);
        }
    }
    else{
        return NULL;
    }
    
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *root, BSTNode<T> *node, TraversalPlan tp) const
{
    if(tp == inorder)
    {
        if(node->right != NULL)
        {
            return right_min(node->right);
        }
        BSTNode<T> *x = NULL;
        while(root != NULL)
        {
            if(node->data < root->data)
            {
                x = root;
                root = root->left;
            }
            else if(node->data > root->data)
            {
                root = root->right;
            }
            else{
                break;
            }
        }
        return x;
    }
    else if (tp == preorder)
    {
        if(node->left != NULL)
        {
            return node->left;
        }
        else if(node->left == NULL && node->right != NULL)
        {
            return node->right;
        }
        else if(node->left == NULL && node->right == NULL)
        {
            BSTNode<T> *parent = NULL;
            parent = fparent(root, node);
            if(parent != NULL && node == parent->left)
            {
                while(parent != NULL)
                {
                    if(parent->right != NULL && parent->left != NULL)
                    {
                        return parent->right;
                    }
                    else{
                        parent = fparent(root, parent);
                    }
                }
                return parent;
            }
            else if(parent != NULL && node == parent->right){
                BSTNode<T> *curr = node;
                while(parent != NULL)
                {
                    
                    if(curr == parent->left && parent->right != NULL)
                    {
                        return parent->right;
                    }
                    else{
                        curr = parent;
                        parent = fparent(root, parent);
                    }
                }
                return parent;
            }
            return NULL;
        }
    }
    else if(tp == postorder)
    {
        BSTNode<T> *parent = NULL;
        parent = fparent(root, node);
        if(parent != NULL)
        {
            if(parent->right == node)
            {
                return parent;
            }
            else if(parent->left == node && parent->right == NULL)
            {
                return parent;
            }
            else if(parent == NULL)
            {
                return NULL;
            }
            else if(parent->left == node && parent->right != NULL)
            {
                BSTNode<T> *x = parent->right;
                while(x->right != NULL || x->left != NULL)
                {
                    if(x->left != NULL)
                    {
                        x = x->left;
                    }
                    else{
                        x = x->right;
                    }
                }
                return x;
            }
        }
        else{
            return NULL;
        }
    }
    return NULL;
}

template<class T> 
BSTNode<T> *BST<T>::fparent(BSTNode<T> *root, BSTNode<T> *node) const
{
    if(root == NULL || node == NULL)
    {
        return NULL;
    }
    if(root->left == NULL && root->right == NULL)
    {
        return NULL;
    }
    else if(root->left == node || root->right == node)
    {
        
        return root;
    }
    else{
        if(node->data < root->data)
        {
            return fparent(root->left, node);
        }
        else if(node->data > root->data)
        {
            return fparent(root->right, node);
        }
    }
    return NULL;
}