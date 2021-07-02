#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <iomanip>

using namespace std;

#define NULL 0

#define LEFT 1
#define RIGHT 2
#define ROOT 0


template<typename T>
class BinSearchTree
{
	class Iterator; //very important!!!

private:

	struct Node
	{
		T item;
		Node* parent;
		Node* left;
		Node* right;
	}; // Node

	Node *root;

	Node *largestNode;
	Node *smallestNode;

	int count;

	Iterator insertRec(Node *curr, Node *parent, const T& item, int side);
	int getHeightRec(Node* root)const;
	int getLeafCountRec(Node* root)const;
	void destroy(Node *curr);

public:

	// Postcondition: this BinSearchTree is empty.
	BinSearchTree(); //  default constructor

   // Postcondition: the number of items in this BinSearchTree
   //                has been returned.
	int size() const;

	int height() const; //
	int LeafCount()const;

	// Postcondition: item has been inserted into this BinSearchTree. An iterator 
	//                positioned at the inserted item has been returned. The
	//                averageTime(n) is O(log n) and worstTime(n) is O(n).
	Iterator insert(const T& item);

	// Postcondition: if there is an item in this BinSearchTree that equals item,
	//                the value returned is an iterator pointing to that item.
	//                Otherwise, the value returned is an iterator with the same
	//                value as the iterator returned by the end( ) method.  The
	//                averageTime(n) is O(log n) and worstTime(n) is O(n).
	Iterator find(const T& item) const;

	// Precondition: itr is positioned at an item in this BinSearchTree.
	// Postcondition: the item that itr is positioned at has been deleted from
	//                this BinSearchTree.  The averageTime(n) is O(log n)
	//                and worstTime(n) is O(n).
	void erase(Iterator itr);

	// Postcondition: The space allocated for this BinSearchTree has been
	//                deallocated.  The worstTime(n) is O(n).
	~BinSearchTree();
	
	void printTreeRec(Node* tempRoot);
	void printTree(); //please implement

	class Iterator
	{
		friend class BinSearchTree<T>;

	private:

		Node *curr;
		Iterator(Node *currNode);

	public:

		Iterator();

		Iterator& operator++ ();

		Iterator& operator-- ();

		T& operator* () const;

		bool operator== (const Iterator &otherIterator) const;

	}; // Iterator

	// Postcondition: if this BinSearchTree is non-empty, an iterator positioned
	//                at the smallest item in the tree has been returned.
	//                Otherwise, the iterator returned has the same value as the
	//                iterator returned by the end( ) method.
	Iterator begin();


	// Postcondition: the value returned is an iterator that can be used in a 
	//                comparison for ending the traversal of this BinSearchTree.
	//                If this BinSearchTree is non-empty, the largest item is in the
	//                position just before the position of the iterator returned.
	Iterator end();

}; // BinSearchTree


//************************the following is the implmentation of the bst class interfaces***********************************
template<typename T>
BinSearchTree<T>::BinSearchTree()
{
	root = NULL;

	largestNode = NULL;
	smallestNode = NULL;

	count = 0;
}

template<typename T>
int BinSearchTree<T>::size() const
{
	return count;
}


template<typename T>
int BinSearchTree<T>::getLeafCountRec(Node* root)const{
	if (root == NULL)
		return 0;
	else
	{
		if ((root->right ==NULL) && (root->left == NULL))
			return 1;
		else
			return getLeafCountRec(root->left) + getLeafCountRec(root->right);
	}
}

template<typename T>
int BinSearchTree<T>::LeafCount() const
{
	return getLeafCountRec(root);	//����Ҷ�ӽڵ��������
}

//�������ߵĵ�������
template<typename T>
int BinSearchTree<T>::getHeightRec(Node* tempRoot)  const {	
	if (tempRoot == NULL)	return -1;	//���������߶���Ϊ-1
	int leftHeight = getHeightRec(tempRoot->left);		//���㲢��������������
	int rightHeight = getHeightRec(tempRoot->right);	//���㲢��������������
	//�����������ߵ�Ϊ׼�������Լ�����ڵ㣬���ص�ǰ����
	if (leftHeight > rightHeight) return leftHeight+1;
	else return rightHeight+1;
}

template<typename T>
int BinSearchTree<T>::height() const
{
	return getHeightRec(root);	//�������ߵ�������
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::insertRec(Node *curr, Node *parent, const T& item, int side)
{
	if (curr == NULL)//insert leaf
	{
		curr = new Node;
		curr->item = item;
		curr->parent = parent;
		curr->left = NULL;
		curr->right = NULL;

		if (side == LEFT)
			parent->left = curr;
		if (side == RIGHT)
			parent->right = curr;

		count++;
		if (count == 1)
			root = curr;//root

		return Iterator(curr);
	}
	else
	{
		if (item < curr->item) //insert left
			return insertRec(curr->left, curr, item, LEFT);
		else //insert right
			return insertRec(curr->right, curr, item, RIGHT);
	}
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::insert(const T& item)
{
	return insertRec(root, NULL, item, ROOT);
}


template<typename T>
void BinSearchTree<T>::printTreeRec(Node* tempRoot) {
	//����1�����ڵ�û���Һ��ӵ�������޷��������ĸ�ĸ�������ȵ����ж�
	if(tempRoot==root && tempRoot->right==NULL)		
		cout << tempRoot->item << "\n";	
	//����2���Һ������Ľ�β���У������Ϊ�˱��������������ڵ�Ĵ�ӡ�غϣ��ּ��������������Ǹ��ڵ���Һ��ӽڵ�
	else if (tempRoot->right == NULL && tempRoot->parent->right==tempRoot)
		cout << tempRoot->item<<"\n";
	//����3����������ͷ�����Ҫͳ��tab���͡�|���Ĵ�ӡλ��
	else if (tempRoot != root && tempRoot->parent->left == tempRoot) {
		Node* temp = tempRoot->parent;	//������ʱ�ڵ㣬����������ǰ�ڵ�����ڽڵ㣬�ж�tab���͡�|���Ĵ�ӡλ��
		vector <string> tab;	//��������tab��������tab�͡�|��

		//������ǰ�ڵ�����ڽڵ�
		while (temp != root) {
			if(temp->parent->left != NULL && temp->item != 101) 
				tab.push_back("��\t");	//����˽ڵ�δ����ǣ�����Ҫ��ӡ��|������
			else 
				tab.push_back("\t"); //����˽ڵ㱻���Ϊ101��˵���Դ�ӡ������Ҫ�ٴ�ӡ��|������
			temp = temp->parent;
		}

		//��tab�����������
		for (int i = tab.size(); i >0; i--) {
			cout << tab[i-1];
		}

		if (tempRoot->right == NULL) {	//����3.1���������ڵ������������ʼ��������������β
			cout << "������������\t" << tempRoot->item << "\n";
			tempRoot->item = 101;	//������������������
		}
		else {	//����3.2���������ڵ������������ʼ���������Һ���
			cout << "������������\t" << tempRoot->item << "��������\t";
			tempRoot->item = 101;	//������������������
		}
	}
	else cout << tempRoot->item <<"��������\t";	//����4��������������ͨ���


	//�ݹ����
	if (tempRoot->right != NULL) {
		printTreeRec(tempRoot->right);
	}
	if (tempRoot->left != NULL) {
		printTreeRec(tempRoot->left);		
	}
	if (tempRoot->right == NULL && tempRoot->left == NULL) return;

}
//please implement
template<typename T>
void BinSearchTree<T>::printTree()
{
	printTreeRec(root);
}

//not implemented
template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::find(const T& item) const
{
	return Iterator();
}

//not implemented
template<typename T>
void BinSearchTree<T>::erase(Iterator itr)
{

}


template<typename T>
void BinSearchTree<T>::destroy(Node *curr)
{
	if (curr != NULL)
	{
		destroy(curr->left);
		destroy(curr->right);
		delete curr;
	}
}

template<typename T>
BinSearchTree<T>::~BinSearchTree()
{
	destroy(root);
}

//not implemented
template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::begin()
{
	
}

//not implemented
template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::end()
{

}

//************************the following is the implmentation of the iterator inner class***********************************
template<typename T>
BinSearchTree<T>::Iterator::Iterator(Node *currNode)
{
	curr = currNode;
}

//not implemented
template<typename T>
BinSearchTree<T>::Iterator::Iterator( )
{
}

//not implemented
template<typename T>
typename BinSearchTree<T>::Iterator& BinSearchTree<T>::Iterator::operator++()
{
}

//not implemented
template<typename T>
typename BinSearchTree<T>::Iterator& BinSearchTree<T>::Iterator::operator--()
{
}

template<typename T>
T& BinSearchTree<T>::Iterator::operator* () const
{
	return curr->item;
}

//not implemented
template<typename T>
bool  BinSearchTree<T>::Iterator::operator==(const Iterator &otherIterator) const
{
}


#endif