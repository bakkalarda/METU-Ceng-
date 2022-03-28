#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
	head = NULL;
	size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
	if(obj.head == NULL)
    {
    	head = NULL;
	}
	else if ((obj.head != NULL) && (obj.head->next == obj.head))
	{
	    head = new Node<T>(obj.head->data);
	    head->next = head;
		head->prev = head;
	}
	else
	{
	    head = new Node<T>(obj.head->data);
		Node<T> *curr1;
		Node<T> *curr2;;
		curr1 = head;
		curr2 = obj.head;
		curr1->prev = curr1;
		curr1->next = curr1;
		while(curr2->next != obj.head)
		{
			insertAfterNode(curr2->next->data, curr1);
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
	}
	size = obj.size; 
}

template<class T>
LinkedList<T>::~LinkedList() {
    if(head != NULL)
    {
        Node<T> *curr;
        Node<T> *temp;
        curr = head->next;
        while(curr != head)
        {
            temp = curr->next;
        	curr->next = NULL;
        	curr->prev = NULL;
        	delete curr;
        	curr = temp;
    	}
    	delete head;
    }
}

template<class T>
int LinkedList<T>::getSize() const {
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    if(this->head == NULL)
    {
    	return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    if(head == NULL && node == NULL)
    {
        return true;
    }
    else if(head == NULL && node != NULL)
    {
        return false;
    }
    else
    {
        Node<T> *curr;
        curr = head;
        int test = 0;
        while(curr->next != head)
        {
            if(curr == node)
            {
            	test = 1;
            	break;
        	}
        	curr = curr->next;
        }
        if(curr->next == head)
        {
            if(curr == node)
            {
            	return true;
        	}
        	else
        	{
        		return false;
        	}
        }
        if(test)
        {
        	return true;
        }
        else
        {
        	return false;
        }	 
    }
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    if(isEmpty())
    {
    	return NULL;
	}
	else
	{
		return head;
	}
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    if(isEmpty())
    {
    	return NULL;
	}
	else
	{
		return head->prev;
	}
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    if(head == NULL)
	{
		return NULL;
	}
	else
	{
	    if(size == 1)
		{
			if(head->data == data)
			{
				return head;
			}
			else
			{
				
				return NULL;
			}
		}
		else
		{
		    Node<T> *curr;
	        curr = head;
	        int test = 0;
			while(curr->next != head)
			{
				if(curr->data == data)
				{
					test = 1;
					break;
				}
				curr = curr->next;
			}
			if(test == 0)
			{
				if(curr->next == head && curr->data == data)
				{
					return curr;
				}
				else
				{
					return NULL;
				}
			}
			else
			{
				return curr;
			}
		}
	}
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
	if(index >= size || index < 0)
    {
    	return NULL;
	}
	else if(head == NULL)
	{
	    return NULL;
	}
	else
	{
		Node<T> *curr;
		curr = head;
		for(int i=0; i<index; i++)
		{
			curr = curr->next;
		}
		return curr;
	}
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    if (head == NULL)
	{
	    delete head;
	    head = NULL;
		head = new Node<T>(data);
		head->next = head;
		head->prev = head;
		size = 1;
	}
	else if (head != NULL && head->next == head)
	{
	    Node<T> *ins = new Node<T>(data);
	    ins->next = head;
	    head->next = ins;
	    head->prev = ins;
	    ins->prev = head;
	    head = ins;
	    size++;
	}
	else
	{
	    Node<T> *ins = new Node<T>(data);
	    Node<T> *curr = head;
	    while(curr->next != head)
	    {
	        curr = curr->next;
	    }
	    curr->next = ins;
	    ins->prev = curr;
	    ins->next = head;
	    head->prev = ins;
	    head = ins;
	    size++;
	}
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    if (head == NULL)
	{
	    delete head;
	    head = NULL;
	    head = new Node<T>(data);
		head->next = head;
		head->prev = head;
		size = 1;
	}
	else
	{
	    if(head->next == head)
		{
		    Node<T> *ins = new Node<T>(data);
		    ins->next = head;
		    ins->prev = head;
		    head->next = ins;
		    head->prev = ins;
		    size++;
		}
		else
		{
		    Node<T> *ins = new Node<T>(data);
		    Node<T> *end;
    	    end = head;
    	    while(end->next != head)
    	    {
    		    end = end->next;
		    }
		    end->next = ins;
    		ins->prev = end;
    		ins->next = head;
    		head->prev = ins;
    		size++;
		}
	}
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    if(head != NULL && node != NULL)
    {
        Node<T> *curr;
        int test=0;
        curr = head;
        while(curr->next != head)
        {
        	if(curr == node)
        	{
        		test = 1;
        		break;
    		}
    		curr = curr->next;
    	}
    	if(curr->next == head && curr == node)
    	{
    		test=1;
    	}
    	if(test)
    	{
    		if(curr == head)
    		{
    		    Node<T> *ins = new Node<T>(data);
    			ins->prev = node;
    			ins->next = node->next;
    			node->next->prev = ins;
    			node->next = ins;
    			size++;
    			
    		}
    		else if(curr->next == head && curr != head)
    		{
    			insertAtTheEnd(data);
    		}
    		else
    		{
    		    Node<T> *ins = new Node<T>(data);
    			ins->prev = node;
    			ins->next = node->next;
    			node->next->prev = ins;
    			node->next = ins;
    			size++;
    		}
    	}
    }
    else if (head == NULL && node == NULL)
    {
        head->data = data;
		head->next = head;
		head->prev = head;
		size = 1;
    }
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    if(k>=2)
    {
    	if(k<=size)
    	{
    		Node<T> *currx;
    		int x=1;
    		currx = head;
    		while(currx->next != head)
    		{
    			if((x+1)%k == 0)
	    		{
	    			insertAfterNode(data, currx);
	    			x++;
	    			currx = currx->next;
				}
				else
				{
					x++;
					currx = currx->next;
				}
			}
			if(currx->next == head && ((x+1)%k == 0))
			{
				insertAtTheEnd(data);
			}
    	}
	}
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    if(head == NULL)
    {
        return;
    }
    else if(head == node)
	{
		if(size == 1)
		{
		    node->prev = NULL;
		    node->next = NULL;
		    delete node;
		    head = NULL;
		    size = 0;
		    return;
		}
		else
		{
		    Node<T> *curr;
            curr = head->next;
			if(curr->next == head)
			{
				Node<T> *temp;
				temp = node;
				temp->next = NULL;
				curr->prev = temp->prev;
				temp->prev = NULL;
				delete temp;
				head = curr;
				head->next = head;
				head->prev = head;
				size = 1;
				return;
			}
			else
			{
				Node<T> *temp;
				temp = node;
				head->prev->next = curr;
				curr->prev = head->prev;
				head = curr;
				temp->next = NULL;
				temp->prev = NULL;
				delete temp;
				size--;
				return;
			}
		}
	}
	else
	{
	    Node<T> *curr;
        curr = head;
        int test=0;
	    while(curr->next != head)
        {
            if(curr == node)
        	{
        		test = 1;
        		break;
    		}
    		curr = curr->next;
    	}
    	if(curr->next == head && curr == node)
    	{
    	    test =1;
    	}
    	else
    	{
    	    
    	}
    	if(test)
    	{
    		if(curr->next == head)
    		{
    			curr->prev->next = head;
    			head->prev = curr->prev;
    			curr->prev = NULL;
    			curr->next = NULL;
    			delete curr;
    			size--;
    		}
    		else
    		{
    			curr->prev->next = curr->next;
    			curr->next->prev = curr->prev;
    			curr->next = NULL;
    			curr->prev = NULL;
    			delete curr;
    			size--;
    		}
    	}
    	else
    	{
    	    return;
    	}
	}	
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    if(head == NULL)
    {
        return;
    }
    else if(head->data == data && size == 1)
    {
    	head->prev = NULL;
    	head->next = NULL;
    	Node<T>* temp = head;
    	delete temp;
    	head = NULL;
    	size = 0;
    }
    else
    {
        Node<T> *curr;
        Node<T> *temp;
        curr = head;
        while(curr->next != head)
    	{
    		if(curr->data == data)
    		{
    			temp = curr;
    			curr = curr->next;
    			curr->prev = temp->prev;
    			removeNode(temp);
    		}
    		else
    		{
    			curr = curr->next;
    		}
    	}
    	if(curr->next == head)
    	{
    		if(curr->data == data)
    		{
    	        removeNode(curr);
    		}
    	}
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    if(head == NULL)
    {
        return;
    }
	else
    {
        Node<T> *temp;
        Node<T> *curr;
        curr = head->next;
        while(curr != head)
        {
            temp = curr->next;
            curr->next = NULL;
            curr->prev = NULL;
            delete curr;
            curr = temp;
        }
        delete head;
    }
    head = NULL;
    size = 0;
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    if(k>=2)
    {
    	if(k<=size)
    	{
    		Node<T> *curr;
    		Node<T> *temp;
    		Node<T> *head2;
    		int x=2;
    		curr = head->next;
    		head2 = head;
    		while(curr != head2)
    		{
    			if(x%k == 0)
	    		{
	    			temp = curr;
	    			curr = curr->next;
	    			curr->prev = temp->prev;
	    			removeNode(temp);
	    			x++;
				}
				else
				{
					x++;
					curr = curr->next;
				}
			}
    	}
	}
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    if(contains(node1) && contains(node2))
	{
		if(node1 != node2)
		{
			int test1=0;
			int test2=0;
			Node<T> *curr1;
			Node<T> *curr2;
			Node<T> *prev1;
			Node<T> *prev2;
			Node<T> *next1;
			Node<T> *next2;
			curr1 = head;
			curr2 = head;
			while(curr1->next != head)
			{
				if(curr1 == node1)
				{
					test1 =1;
					break;
				}
				curr1 = curr1->next;
			}
			if((curr1->next == head) && (curr1 == node1))
			{
				test1 = 1;
			}
			while(curr2->next != head)
			{
				if(curr2 == node2)
				{
					test2 = 1;
					break;
				}
				curr2 = curr2->next;
			}
			if((curr2->next == head) && (curr2 == node2))
			{
				test2 = 1;
			}
			if(test1 && test2)
			{
				if(curr1 == head)
				{
					head = curr2;
				}
				else if(curr2 == head)
				{
					head = curr1;
				}
				if(curr1->next == curr2)
				{
					curr1->prev->next = curr2;
					curr2->prev = curr1->prev;
					curr1->next = curr2->next;
					curr2->next->prev = curr1;
					curr2->next = curr1;
					curr1->prev = curr2;
				}
				else if(curr2->next == curr1)
				{
					curr2->prev->next = curr1;
					curr1->prev = curr2->prev;
					curr2->next = curr1->next;
					curr1->next->prev = curr2;
					curr1->next = curr2;
					curr2->prev = curr1;
				}
				else
				{
					prev1 = curr1->prev;
					prev2 = curr2->prev;
					next1 = curr1->next;
					next2 = curr2->next;
					prev1->next = curr2;
					prev2->next = curr1;
					curr1->prev = prev2;
					curr2->prev = prev1;
					next1->prev = curr2;
					next2->prev = curr1;
					curr2->next = next1;
					curr1->next = next2;
				}
			}
		}
	}
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
	Node<T> *curr1;
	Node<T> *curr2;
	int x;
	int a;
	int b;
	for(int i=0; i<size; i++)
    {
    	curr1 = head;
    	curr2 = head;
    	x = (i*i+seed)%size;
    	if(i+1<=size && x<=size)
    	{
    		a = 0;
    		while(curr1->next != head)
    		{
    			if(a == i)
    			{
    				break;
				}
				a++;
				curr1 = curr1->next;
			}
			b = 0;
    		while(curr2->next != head)
    		{
    			if(b == x)
    			{
    				break;
				}
				b++;
				curr2 = curr2->next;
			}
    		swap(curr1, curr2);
		}
	}
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    if(rhs.head == NULL)
    {
        removeAllNodes();
        this->head = NULL;
    }
    else if(rhs.head->next == rhs.head)
    {
        removeAllNodes();
        head = new Node<T>(rhs.head->data);
        head->next = head;
        head->prev = head;
        
    }
    else
    {
        removeAllNodes();
        head = new Node<T>(rhs.head->data);
        head->next = head;
        head->prev = head;
        Node<T> *curr1 = head;
        Node<T> *curr2 = rhs.head;
        for(int i=0; i<rhs.getSize()-1; i++)
        {
            insertAfterNode(curr2->next->data, curr1);
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
    }
    this->size = rhs.size;
    return *this;
}


#endif //LINKEDLIST_H