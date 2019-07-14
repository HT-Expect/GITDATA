#include<algorithm>
#include<iostream>
#include<vector>
#include<list>
#include<limits.h>
#include<stack>
#include<queue>
using namespace std;
//红黑树
typedef int KeyType;
typedef enum {RED = 0, BLACK = 1} ColorType;
struct rb_node
{
	rb_node *leftchild;
	rb_node *parent;// BST AVL RB B 
	rb_node *rightchild;
	ColorType color;
	KeyType key;
};
typedef struct
{
	rb_node * head; 
	rb_node * Nil;
	int cursize;
}RBTree;

rb_node * Buynode(rb_node *pa = NULL,ColorType color = RED)
{
	rb_node *s = (rb_node*)malloc(sizeof(rb_node));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(rb_node));
	s->parent = pa;
	s->color = color;
	return s;
}
void Freenode(rb_node *p)
{
	free(p);
}

void InitRBTree(RBTree &myt)
{
	myt.Nil = Buynode(NULL,BLACK);
	myt.head = Buynode(myt.Nil); // head // root;
	myt.head->leftchild = myt.Nil;
	myt.head->rightchild = myt.Nil;
	myt.cursize = 0;
}
void RotateLeft(rb_node *head,rb_node *ptr)
{
	rb_node *newroot = ptr->rightchild;//#
	newroot->parent = ptr->parent; // 1
	ptr->rightchild = newroot->leftchild; // #
	if(newroot->leftchild != NULL)
	{
		newroot->leftchild->parent = ptr; //2
	}
	
	newroot->leftchild = ptr;  // #
	if(ptr == head->parent) // ptr => root;
	{
		head->parent = newroot;
	}
	else
	{
		if(ptr->parent->leftchild == ptr)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}
	ptr->parent = newroot; // 3
}
void RotateRight(rb_node *head, rb_node *ptr)
{
	rb_node *newroot = ptr->leftchild;
	newroot->parent = ptr->parent; // 1
	ptr->leftchild = newroot->rightchild;
	if(newroot->rightchild != NULL)
	{
		newroot->rightchild->parent = ptr; //2
	}
	newroot->rightchild = ptr;
	if(ptr == head->parent)
	{
		head->parent = newroot;
	}
	else
	{
		if(ptr->parent->leftchild == ptr)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}
	ptr->parent = newroot; // 3
}
void Adjust_RBTree(RBTree &myt,rb_node *ptr)
{
	rb_node *_X,*_Y;
	for(_X = ptr; _X->parent != myt.head && _X->parent->color == RED;)
	{
		if(_X->parent->parent->rightchild == _X->parent)  //_X的爷爷结点的右节点是否为_X的父亲节点
		{
			_Y = _X->parent->parent->leftchild;
			if(_Y->color == RED)
			{
				_Y->color = BLACK;
				_X->parent->color = BLACK;
				_X->parent->parent->color = RED;
				_X = _X->parent->parent;
			}
			else
			{
				if(_X->parent->leftchild == _X)
				{
					_X = _X->parent;
					RotateRight(myt.head,_X);
				}
				_X->parent->color = BLACK;
				_X->parent->parent->color = RED;
				RotateLeft(myt.head,_X->parent->parent);
			}
		}
		else // left;  _X的爷爷结点的左节点是否为_X的父亲节点
		{
			_Y = _X->parent->parent->rightchild;
			if(_Y->color == RED)
			{
				_Y->color = BLACK;
				_X->parent->color = BLACK;
				_X->parent->parent->color = RED;
				_X = _X->parent->parent;
			}
			else  //_Y->color == BLACK
			{
				if(_X->parent->rightchild == _X)
				{
					_X = _X->parent;
					RotateLeft(myt.head,_X);
				}
				_X->parent->color = BLACK;
				_X->parent->parent->color = RED;
				RotateRight(myt.head,_X->parent->parent);
			}
		}
	}

	myt.head->parent->color = BLACK;
}
bool InsertItem(RBTree &myt,KeyType kx)
{
	rb_node * pa = myt.head;       // head
	rb_node *p = myt.head->parent; // root
	while(p != myt.Nil && p->key != kx)
	{
		pa = p;
		p = kx < p->key? p->leftchild : p->rightchild;
	}
	if(p != myt.Nil  && p->key == kx) return false;

	p = Buynode(pa);
	p->key = kx;
	myt.cursize +=1;
	if(pa == myt.head)
	{
		myt.head->parent = p;
		myt.head->leftchild = p;
		myt.head->rightchild = p;
	}
	else
	{
		if(p->key < pa->key)
		{
			pa->leftchild = p;
			if(myt.head->leftchild->key > p->key)
			{
				myt.head->leftchild = p;
			}
		}
		else
		{
			pa->rightchild = p;
			if(myt.head->rightchild->key < p->key)
			{
				myt.head->rightchild = p;
			}
		}

		Adjust_RBTree(myt,p);
	}

	return true;
}
#if 0
//AVL
typedef int KeyType;
struct AVLNode
{
	AVLNode *leftchild;
	AVLNode *parent;// BST AVL RB B 
	AVLNode *rightchild;
	int balance;// -1,0,1;
	KeyType key;
};
typedef struct
{
	AVLNode * head; 
	int cursize;
}AVLTree;

AVLNode * Buynode(AVLNode *pa = NULL)
{
	AVLNode *s = (AVLNode*)malloc(sizeof(AVLNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(AVLNode));
	s->parent = pa;
	return s;
}
void Freenode(AVLNode *p)
{
	free(p);
}

void InitAVLTree(AVLTree &myt)
{
	myt.head = Buynode(); // head // root;
	myt.cursize = 0;
}
void RotateLeft(AVLNode *head,AVLNode *ptr)
{
	AVLNode *newroot = ptr->rightchild;//#
	newroot->parent = ptr->parent; // 1
	ptr->rightchild = newroot->leftchild; // #
	if(newroot->leftchild != NULL)
	{
		newroot->leftchild->parent = ptr; //2
	}
	
	newroot->leftchild = ptr;  // #
	if(ptr == head->parent) // ptr => root;
	{
		head->parent = newroot;
	}
	else
	{
		if(ptr->parent->leftchild == ptr)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}
	ptr->parent = newroot; // 3
}
void RotateRight(AVLNode *head, AVLNode *ptr)
{
	AVLNode *newroot = ptr->leftchild;
	newroot->parent = ptr->parent; // 1
	ptr->leftchild = newroot->rightchild;
	if(newroot->rightchild != NULL)
	{
		newroot->rightchild->parent = ptr; //2
	}
	newroot->rightchild = ptr;
	if(ptr == head->parent)
	{
		head->parent = newroot;
	}
	else
	{
		if(ptr->parent->leftchild == ptr)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}
	ptr->parent = newroot; // 3
}

void RightBalance(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *rightsub = ptr->rightchild, *leftsub = NULL;
	switch(rightsub->balance)
	{
	case 0: cout<<"right alread balance "<<endl; break;
	case 1:
		ptr->balance = 0;
		rightsub->balance = 0;
		RotateLeft(myt.head,ptr);
		break;
	case -1:
		leftsub = rightsub->leftchild;
		switch(leftsub->balance)
		{
		case 0:
			ptr->balance = 0;
			rightsub->balance = 0;
			break;
		case 1:
			ptr->balance = -1;
			rightsub->balance = 0;
			break;
		case -1:
			ptr->balance = 0;
			rightsub->balance = 1;
			break;
		}
		leftsub->balance = 0;
		RotateRight(myt.head,rightsub);
		RotateLeft(myt.head,ptr);
		break;
	}
}
void LeftBalance(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *leftsub = ptr->leftchild, *rightsub = NULL;
	switch(leftsub->balance)
	{
	case 0: cout<<"lear already balance "<<endl; break;
	case -1:
		ptr->balance = 0;
		leftsub->balance = 0;
		RotateRight(myt.head,ptr);
		break;
	case 1:
		rightsub = leftsub->rightchild;
		switch(rightsub->balance)
		{
		case 0: 
			ptr->balance = 0;
			leftsub->balance = 0;
			break;
		case 1: 
			ptr->balance = 0;
			leftsub->balance = -1;
			break;
			ptr->balance = 1;
			leftsub->balance = 0;
		case -1: 
			break;
		}
		rightsub->balance = 0;
		RotateLeft(myt.head,leftsub);
		RotateRight(myt.head,ptr);
		break;
	}
}
void Adjust_AVLTree(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *pa = ptr->parent;
	AVLNode *p = ptr;
	bool tell = true;
	for(; tell && pa != myt.head;)
	{
		if(pa->rightchild == p)
		{
			switch(pa->balance)
			{
			case 0: pa->balance=1; break;
			case -1: 
				pa->balance = 0; 
				tell = false;
				break;
			case 1: 
				RightBalance(myt,pa);
				tell = false;
				break;
			}
		}
		else // left
		{
			switch(pa->balance)
			{
			case 0: pa->balance = -1; break;
			case 1: 
				pa->balance = 0; 
				tell = false;
				break;
			case -1: 
				LeftBalance(myt,pa);
				tell = false;
				break;
			}
		}
		p = pa;
		pa = pa->parent;
	}
}

bool InsertItem(AVLTree &myt,KeyType kx)
{
	AVLNode * pa = myt.head;       // head
	AVLNode *p = myt.head->parent; // root
	while(p != NULL && p->key != kx)
	{
		pa = p;
		p = kx < p->key? p->leftchild : p->rightchild;
	}
	if(p != NULL && p->key == kx) return false;

	p = Buynode(pa);
	p->key = kx;
	myt.cursize +=1;
	if(pa == myt.head)
	{
		myt.head->parent = p;
		myt.head->leftchild = p;
		myt.head->rightchild = p;
	}
	else
	{
		if(p->key < pa->key)
		{
			pa->leftchild = p;
			if(myt.head->leftchild->key > p->key)
			{
				myt.head->leftchild = p;
			}
		}
		else
		{
			pa->rightchild = p;
			if(myt.head->rightchild->key < p->key)
			{
				myt.head->rightchild = p;
			}
		}

		Adjust_AVLTree(myt,p);
	}

	return true;
}
int main()
{
	int ar[]={16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int n = sizeof(ar)/sizeof(ar[0]);
	AVLTree myt;
	InitAVLTree(myt);
	for(int i = 0;i<n;++i)
	{
		InsertItem(myt,ar[i]);
	}

	cout<<endl;

	return 0;
}



typedef int KeyType;
struct AVLNode
{
	AVLNode *leftchild;
	AVLNode *parent;
	AVLNode *rightchild;
	int balance;// -1,0,1;
	KeyType key;
};
typedef struct
{
	AVLNode * head;
	int cursize;
}AVLTree;

AVLNode * Buynode(AVLNode *pa = NULL)
{
	AVLNode *s = (AVLNode*)malloc(sizeof(AVLNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(AVLNode));
	s->parent = pa;
	return s;
}
void Freenode(AVLNode *p)
{
	free(p);
}

void InitBSTree(AVLTree &myt)
{
	bst.head = Buynode(); // head // root;
	bst.cursize = 0;
}
void RotateRight(AVLTree &myt,AVLNode *ptr)
{
	AVLNode *newroot = ptr->leftchild;
	newroot->parent = ptr->parent;//1
	ptr->leftchild = newroot->rightchild;
	if(newroot->rightchild != NULL)
	{
		newroot->rightchild->parent = ptr;//2
	}
	newroot->rightchild = ptr;

	if(ptr == myt.head->parent) // root
	{
		myt.head->parent = newroot;
	}
	else
	{
		if(ptr == ptr->parent->leftchild)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}
	ptr->parent = newroot;//3
}
void RotateLeft(AVLTree &myt, AVLNode *ptr)
{
	AVLNode *newroot = ptr->rightchild;
	newroot->parent = ptr->parent;//1
	ptr->rightchild = newroot->leftchild;
	if(newroot->leftchild != NULL)
	{
		newroot->leftchild->parent = ptr;//2
	}
	newroot->leftchild = ptr;

	if(ptr == myt.head->parent) // root
	{
		myt.head->parent = newroot;
	}
	else
	{
		if(ptr == ptr->parent->leftchild)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}

	ptr->parent = newroot;

}


//二叉搜索树
typedef int KeyType;
struct BstNode
{
	BstNode *leftchild;
	BstNode *parent;
	BstNode *rightchild;
	KeyType key;
};
typedef struct
{
	BstNode * head;
	int cursize;
}BSTree;

BstNode * Buynode(BstNode *pa = NULL)
{
	BstNode *s = (BstNode*)malloc(sizeof(BstNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BstNode));
	s->parent = pa;
	return s;
}
void Freenode(BstNode *p)
{
	free(p);
}

void InitBSTree(BSTree &bst)
{
	bst.head = Buynode(); // head // root;
	bst.cursize = 0;
}
void DestroyBSTree(BSTree &bst)
{
}
BstNode * FindValue(BSTree &bst,KeyType kx)
{
	BstNode *p = bst.head->parent;// root;根节点
	while(p != NULL && p->key != kx)
	{
		p = kx < p->key? p->leftchild:p->rightchild;
	}
	return p;
}
BstNode * Search(BstNode *ptr,KeyType kx)
{
	if(ptr == NULL || ptr->key == kx) 
		return ptr;
	else if(kx < ptr->key)
		return Search(ptr->leftchild,kx);
	else
		return Search(ptr->rightchild,kx);
}
BstNode *SearchValue(BSTree &bst,KeyType kx)
{
	return Search(bst.head->parent,kx);
}
BstNode *First(BstNode *ptr)
{
	while(ptr != NULL && ptr->leftchild != NULL)
	{
		ptr = ptr->leftchild;
	}
	return ptr;
}
BstNode *Next(BSTree &myt,BstNode *ptr)
{
	if(ptr == NULL || ptr == myt.head) return NULL;
	if(ptr->rightchild != NULL)
	{
		return First(ptr->rightchild);
	}
	else
	{
		BstNode *pa = ptr->parent;
		while(pa != myt.head && pa->leftchild != ptr)
		{
			ptr = pa;
			pa = pa->parent;
		}
		if(pa == myt.head)
		{
			pa = NULL;
		}
		return pa;
	}
}
void NiceInOrder(BSTree &bst)
{
	for(BstNode *p = First(bst.head->parent);
		p != NULL ; p = Next(bst,p))
	{
		cout<<p->key<<" ";
	}
	cout<<endl;
}
bool InsertBST(BSTree &myt,KeyType kx)
{
	BstNode *pa = myt.head; // head;
	BstNode *p = myt.head->parent;  // root;
	while(p != NULL && p->key != kx)
	{
		pa = p;
		p = kx < p->key? p->leftchild:p->rightchild;
	}
	if(p != NULL && p->key == kx) return false;
	p = Buynode(pa);
	p->key = kx;
	if(pa == myt.head)
	{
		myt.head->parent = p;
		myt.head->leftchild = p;
		myt.head->rightchild = p;
	}
	else
	{
		if(p->key < pa->key)
		{
			pa->leftchild = p;
			if(p->key < myt.head->leftchild->key)
			{
				myt.head->leftchild = p;
			}
		}
		else
		{
			pa->rightchild = p;
			if(p->key > myt.head->rightchild->key)
			{
				myt.head->rightchild = p;
			}
		}
	}
	myt.cursize+=1;
	return true;
}
bool RemoveBST(BSTree &myt,KeyType kx)
{
	BstNode *p = FindValue(myt,kx);
	if(NULL == p) return false;
	if(p->leftchild != NULL && p->rightchild != NULL)
	{
		BstNode *s = Next(myt,p);
		p->key = s->key;
		p = s;
	}

	BstNode *pa = p->parent;
	BstNode *child = p->leftchild != NULL? p->leftchild:p->rightchild;
    if(child != NULL) child->parent = pa;
	if(pa == myt.head)
	{
		myt.head->parent = child;
	}
	else
	{
		if(p == pa->leftchild)
		{
			pa->leftchild = child;
		}
		else
		{
			pa->rightchild = child;
		}
	}
	Freenode(p);
	myt.cursize-=1;
	return true;
}
int main()
{
	int ar[]={53,17,78,9,45,65,87,23,81,94,88,17,23};
	int n = sizeof(ar)/sizeof(ar[0]);
	int kx;
	BSTree myt;
	InitBSTree(myt);
	for(int i = 0;i<n;++i)
	{
		cout<<InsertBST(myt,ar[i])<<" ";
	}
	cout<<endl;
	NiceInOrder(myt);

	while(cin>>kx,kx != -1)
	{
		RemoveBST(myt,kx);
		NiceInOrder(myt);
	}




	DestroyBSTree(myt);
	return 0;
}


template<class KeyType>
class BSTree
{
private:
	struct BstNode
	{
		BstNode *leftchild;
		BstNode *parent;
		BstNode *rightchild;
		KeyType key;
	};

	BstNode *& Left(BstNode *ptr) { return ptr->leftchild;}
	BstNode *& Right(BstNode *ptr) { return ptr->rightchild;}
	BstNode *& Parent(BstNode *ptr) { return ptr->parent;}
	KeyType & Key(BstNode *ptr) { return ptr->key;}

	BstNode * Buynode(BstNode *pa = NULL)
	{
		BstNode *s = (BstNode*)malloc(sizeof(BstNode));
		if(NULL == s) exit(1);
		memset(s,0,sizeof(BstNode));
		s->parent = pa;
		return s;
	}
	void Freenode(BstNode *p)
	{
		free(p);
	}
private:
	BstNode *head;
	int cursize;
public:

};


typedef char ElemType;
#define END '#'
typedef enum{LINK = 0,THREAD = 1} PointerTag;
typedef struct BiThrNode
{
	BiThrNode *leftchild;
	BiThrNode *rightchild;
	PointerTag Ltag,Rtag;
	ElemType data;
}BiThrNode, *BinaryThreadTree;


BiThrNode * Buynode()
{
	BiThrNode *s = (BiThrNode*)malloc(sizeof(BiThrNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BiThrNode));
	return s;
}
void Freenode(BiThrNode *p)
{
	free(p);
}
BiThrNode * CreateTree(ElemType *&str)
{
	BiThrNode *s = NULL;
	if(NULL != str && *str != END)
	{
		s = Buynode();
		s->data = *str;
		s->Ltag = s->Rtag = LINK;
		s->leftchild = CreateTree(++str);
		s->rightchild = CreateTree(++str);
	}
	return s;
}
void InOrder(BiThrNode *p)
{
	if(p != NULL)
	{
		InOrder(p->rightchild);
		cout<<p->data<<" ";
		InOrder(p->leftchild);
	}
}

void MakeThread(BiThrNode *p,BiThrNode *&ptr)
{
	if(p != NULL)
	{
		MakeThread(p->leftchild,ptr);
		if(p->leftchild == NULL)
		{
			p->leftchild = ptr;
			p->Ltag = THREAD;
		}
		if(ptr != NULL && ptr->rightchild == NULL)
		{
			ptr->rightchild = p;
			ptr->Rtag = THREAD;
		}
		ptr = p;
		MakeThread(p->rightchild,ptr);
	}
}


void MakeThreadTree(BiThrNode *p)
{
	BiThrNode *ptr = NULL;
	MakeThread(p,ptr);	
	if(ptr != NULL)
	{
		ptr->Rtag = THREAD;
		ptr->rightchild = NULL;
	}
}

BiThrNode * First(BiThrNode *ptr)
{
	while(ptr != NULL && ptr->Ltag != THREAD)
	{
		ptr = ptr->leftchild;
	}
	return ptr;
}
BiThrNode * Next(BiThrNode *ptr)
{
	if(NULL == ptr) return NULL;
	if(ptr->Rtag == THREAD)
	{
		return ptr->rightchild;
	}
	else
	{
		return First(ptr->rightchild);
	}
}
BiThrNode * Last(BiThrNode *ptr)
{
	while(ptr != NULL && ptr->Rtag != THREAD)
	{
		ptr = ptr->rightchild;
	}
	return ptr;
}
BiThrNode * Prev(BiThrNode *ptr)
{
	if(NULL == ptr) return NULL;
	if(ptr->Ltag == THREAD)
	{
		return ptr->leftchild;
	}
	else
	{
		return Last(ptr->leftchild);
	}
}
void NiceInOrder(BiThrNode *ptr)
{
	for(BiThrNode *p = First(ptr); p != NULL; p = Next(p))
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
}
void ResNiceInOrder(BiThrNode *ptr)
{
	for(BiThrNode *p = Last(ptr);p != NULL ; p = Prev(p))
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
}
int main()
{
	char *str = "ABC##DE##F##G#H##";
	BinaryThreadTree root = CreateTree(str);
	InOrder(root);
	cout<<endl;
	MakeThreadTree(root);
	NiceInOrder(root);
	ResNiceInOrder(root);
	return 0;
}

typedef char ElemType;
#define END '#'

typedef struct BtNode // BinaryTreeNode
{
	BtNode *leftchild;
	BtNode *rightchild;
	ElemType data;
}BtNode, *BinaryTree;

BtNode * Buynode()
{
	BtNode *s = (BtNode*)malloc(sizeof(BtNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BtNode));
	return s;
}
void Freenode(BtNode *p)
{
	free(p);
}

void PreOrder(BtNode *p)
{
	if(p != NULL)
	{
		cout<<p->data<<" ";
		PreOrder(p->leftchild);
		PreOrder(p->rightchild);
	}
}
void InOrder(BtNode *p)
{
	if(p != NULL)
	{
		InOrder(p->leftchild);
		cout<<p->data<<" ";
		InOrder(p->rightchild);
	}
}

void PastOrder(BtNode *p)
{
	if(p != NULL)
	{
		PastOrder(p->leftchild);
		PastOrder(p->rightchild);
		cout<<p->data<<" ";
	}
}


BtNode * CreateTree1()
{
	BtNode *s = NULL;
	ElemType item;
	cin>>item;
	if(item != END)
	{
		s = Buynode();
		s->data = item;
		s->leftchild = CreateTree1();
		s->rightchild = CreateTree1();
	}
	return s;
}
//A B C # # D E # # F # # G # H # #
BtNode * CreateTree2(ElemType *&str)
{
	BtNode *s = NULL;
	if(NULL != str && *str != END)
	{
		s = Buynode();
		s->data = *str;
		s->leftchild = CreateTree2(++str);
		s->rightchild = CreateTree2(++str);
	}
	return s;
}

int FindPos(ElemType *is,ElemType x,int n)
{
	int pos = -1;
	for(int i = 0;i<n;++i)
	{
		if(is[i] == x)
		{
			pos = i;
			break;
		}
	}
	return pos;
}
BtNode * CreatePI(ElemType *ps,ElemType *is,int n)
{
	BtNode *s = NULL;
	if(n > 0)
	{
		s = Buynode();
		s->data = ps[0];
		int pos = FindPos(is,ps[0],n);
		if(pos == -1) exit(1);
		s->leftchild = CreatePI(ps+1,is,pos);
		s->rightchild = CreatePI(ps+pos+1,is+pos+1,n - pos -1);
	}
	return s;
}
BtNode * CreateTreePI(ElemType *ps,ElemType *is,int n)
{
	if(NULL == ps || NULL == is || n < 1)
		return NULL;
	else
		return CreatePI(ps,is,n);
}

BtNode * CreateIL(ElemType *is,ElemType *ls,int n)
{
	BtNode *s = NULL;
	if(n > 0)
	{
		s = Buynode();
		s->data = ls[n-1];
		int pos = FindPos(is,ls[n-1],n);
		if(pos == -1) exit(1);
		s->leftchild = CreateIL(is,ls,pos);
		s->rightchild = CreateIL(is+pos+1,ls+pos,n-pos-1);
	}
	return s;
}
BtNode * CreateTreeIL(ElemType *is,ElemType *ls,int n)
{
	if(NULL == is || NULL == ls || n < 1)
		return NULL;
	else
		return CreateIL(is,ls,n);
}
////////////////////////////////////////
void PreOrder_Ar(int *ar,int i,int n)
{
	if(i < n && ar[i] != END)
	{
		cout<<ar[i]<<" "; // i*2+1;
		PreOrder_Ar(ar,i*2+1,n); // left;
		PreOrder_Ar(ar,i*2+2,n);
	}
}
void InOrder_Ar(int *ar,int i,int n)
{
	if(i < n && ar[i] != END)
	{
		InOrder_Ar(ar,i*2+1,n); // left;
		cout<<ar[i]<<" "; // i*2+1;
		InOrder_Ar(ar,i*2+2,n);
	}
}
void InOrder_Ar(int *ar,int n)
{
	if(NULL == ar || n < 1) 
		return ;
	InOrder_Ar(ar,0,n);
	cout<<endl;
}
BtNode * MakeAr(ElemType *ar,int i,int n)
{
	BtNode *s = NULL;
	if(i<n && ar[i] != END)
	{
		s = Buynode();
		s->data = ar[i];
		s->leftchild = MakeAr(ar,i*2+1,n);
		s->rightchild = MakeAr(ar,i*2+2,n);
	}
	return s;
}
BtNode * MakeAr_Tree(ElemType *ar,int n)
{
	if(ar == NULL || n < 1)
		return NULL;
	else
		return MakeAr(ar,0,n);
}
BtNode * CreateBalance(ElemType *ar,int left,int right)
{
	BtNode *s = NULL;
	if(left <= right)
	{
		int mid = (right - left + 1)/2 + left;
		s = Buynode();
		s->data = ar[mid];
		s->leftchild = CreateBalance(ar,left,mid-1);
		s->rightchild = CreateBalance(ar,mid+1,right);
	}
	return s;
}
BtNode * CreateBalanceTree(ElemType *ar,int n)
{
	if(ar == NULL || n < 1) 
		return NULL;
	else
		return CreateBalance(ar,0,n-1);
}

BtNode * CreateBalanceTree2(ElemType *ar,int n)
{
	BtNode *s = NULL;
	int left = 0, right = n-1;
	if(ar == NULL || n < 1) return s;
	
	while(left <= right)
	{
		int mid = (right - left + 1)/2 + left;
		s = Buynode();
		s->data = ar[mid];
		///if(val < ar[mid])
		{
			right = mid - 1;
		}
		///else
		{
			left = mid + 1;
		}
		s->leftchild ;
		s->rightchild;
	}
}

int GetSize(BtNode *ptr)
{
	if(ptr == NULL)
		return 0;
	else 
		return GetSize(ptr->leftchild) + GetSize(ptr->rightchild) + 1;
}
int GetDepth(BtNode *ptr)
{
	if(ptr == NULL) return 0;
	else return max(GetDepth(ptr->leftchild),GetDepth(ptr->rightchild)) + 1;
}
/////////////////////////////////////////////////////////////

BtNode * FindValue(BtNode *ptr,int val)
{
	if(ptr == NULL || ptr->data == val)
	{
		return ptr;
	}
	else
	{
		BtNode *p = FindValue(ptr->leftchild,val);
		if(NULL == p)
		{
			p = FindValue(ptr->rightchild,val);
		}
		return p;
	}
}
BtNode * Parent(BtNode *ptr,BtNode *child)
{
	if(ptr == NULL || 
		ptr->leftchild == child ||
		ptr->rightchild == child)
	{
		return ptr;
	}
	else
	{
		BtNode *p = Parent(ptr->leftchild,child);
		if(NULL == p)
		{
			p = Parent(ptr->rightchild,child);
		}
		return p;
	}
}
BtNode * FindParent(BtNode *ptr,BtNode *child)
{
	if(ptr == NULL || child == NULL || ptr == child)
	{
		return NULL;
	}
	else
	{
		return Parent(ptr,child);
	}
}
BtNode * FindNearParent(BtNode *ptr,BtNode *child1,BtNode *child2);

void PrintPath(BtNode *ptr,vector<ElemType> &vec,ElemType val)
{
	if(ptr != NULL)
	{
		vec.push_back(ptr->data);

		if(ptr->leftchild == NULL && ptr->rightchild == NULL)
		{
			ElemType sum =0;
			for(int i = 0;i < vec.size();++i)
			{
				sum += vec[i];
			}
			if(sum == val)
			{
				for(int i = 0;i  <vec.size();++i)
				{
					cout<<vec[i]<<" ";
				}
				cout<<sum<<endl;
			}
		}
		PrintPath(ptr->leftchild,vec,val);
		PrintPath(ptr->rightchild,vec,val);

		vec.pop_back();
	}
}
////////////////////////////////////////////
void NiceInOrder(BtNode *ptr)
{
	if(NULL == ptr) return;
	stack<BtNode *> st;

	while(ptr != NULL || !st.empty())
	{
		while(ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftchild;
		}
		ptr = st.top(); st.pop();
		cout<<ptr->data<<" ";
		ptr = ptr->rightchild;
	}
	cout<<endl;
}

void NicePastOrder(BtNode *ptr)
{
	if(NULL == ptr) return;
	stack<BtNode *> st;
	BtNode *tag = NULL;
	while(ptr != NULL || !st.empty())
	{
		while(ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftchild;
		}
		ptr = st.top(); st.pop();
		if(ptr->rightchild == NULL || ptr->rightchild == tag)
		{
			cout<<ptr->data<<" ";
			tag = ptr;
			ptr = NULL;
		}
		else
		{ 
			st.push(ptr);
			ptr = ptr->rightchild;
		}
	}
	cout<<endl;
}
//////////////////////////////////
struct StkNode
{
	BtNode *pnode;
	int popnum; 
public:
	StkNode(BtNode *p = NULL):pnode(p),popnum(0) {}
};
void StkNicePastOrder(BtNode *ptr)
{
	if(NULL == ptr) return ;
	stack<StkNode> st;
	st.push(StkNode(ptr));
	while(!st.empty())
	{
		StkNode node = st.top(); st.pop(); 
		if(++node.popnum == 3)
		{
			cout<<node.pnode->data<<" ";
		}
		else
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode(node.pnode->leftchild));
			}else if(node.popnum == 2 && node.pnode->rightchild != NULL)
			{
				st.push(StkNode(node.pnode->rightchild));
			}
		}
	}
	cout<<endl;
}

void StkNiceInOrder(BtNode *ptr)
{
	if(NULL == ptr) return ;
	stack<StkNode> st;
	st.push(StkNode(ptr));
	while(!st.empty())
	{
		StkNode node = st.top(); st.pop(); 
		if(++node.popnum == 2)
		{
			cout<<node.pnode->data<<" ";
			if(node.pnode->rightchild != NULL)
			{
				st.push(StkNode(node.pnode->rightchild));
			}
		}
		else
		{
			st.push(node);
			if(node.popnum == 1 && node.pnode->leftchild != NULL)
			{
				st.push(StkNode(node.pnode->leftchild));
			}
		}
	}
	cout<<endl;
}

void NicePreOrder(BtNode *ptr)
{
	if(NULL == ptr) return ;
	stack<BtNode*> st;
	st.push(ptr);
	while(!st.empty())
	{
		ptr = st.top(); st.pop();
		cout<<ptr->data<<" ";
		if(ptr->rightchild != NULL)
		{
			st.push(ptr->rightchild);
		}
		if(ptr->leftchild != NULL)
		{
			st.push(ptr->leftchild);
		}
	}
	cout<<endl;
}
//////////////////////////////////////////////
void NiceLevelOrder(BtNode *ptr)
{
	if(NULL == ptr);
	queue<BtNode *> qu;
	qu.push(ptr);
	while(!qu.empty())
	{
		ptr = qu.front(); qu.pop();
		cout<<ptr->data<<" ";
		if(ptr->leftchild != NULL)
		{
			qu.push(ptr->leftchild);
		}
		if(ptr->rightchild != NULL)
		{
			qu.push(ptr->rightchild);
		}
	}
	cout<<endl;
}
void Print_K(BtNode *ptr,int k)
{
	if(ptr != NULL && k == 0)
	{
		cout<<ptr->data<<" ";
	}
	else if(ptr != NULL)
	{
		Print_K(ptr->leftchild,k-1);
		Print_K(ptr->rightchild,k-1);
	}
}
void Print_K_Level_Item(BtNode *ptr,int k)
{
	if(ptr == NULL || k < 0) return ;
	Print_K(ptr,k);
	cout<<endl;
}
void LevelOrder(BtNode *ptr)
{
	int n = GetDepth(ptr);
	for(int i = 0;i<n;++i)
	{
		Print_K_Level_Item(ptr,i);
	}
	cout<<endl;
}

bool Is_Full_BinaryTree(BtNode *ptr)
{
	bool res = true;
	if(NULL == ptr) return res;
	int n = 1;
	queue<BtNode *> qu;
	qu.push(ptr);
	while(!qu.empty())
	{
		int i = 0;
		for(; i<n && !qu.empty(); ++i)
		{
			ptr = qu.front(); qu.pop();
			if(ptr->leftchild != NULL)
			{
				qu.push(ptr->leftchild);
			}
			if(ptr->rightchild != NULL)
			{
				qu.push(ptr->rightchild);
			}
		}
		if(i < n)
		{
			res = false;
			break;
		}
		n+=n;	
	}
	return res;
}

bool Is_Comp_BinaryTree(BtNode *ptr)
{
	bool res = true;
	if(NULL == ptr) return res;
	int n = 1;
	queue<BtNode *> qu;
	qu.push(ptr);
	while(!qu.empty())
	{
		ptr = qu.front(); qu.pop();
		if(NULL == ptr) break;
		qu.push(ptr->leftchild);
		qu.push(ptr->rightchild);
	}
	while(!qu.empty())
	{
		ptr = qu.front(); qu.pop();
		if(ptr != NULL)
		{
			res = false;
			break;
		}
	}
	return res;
}
int main()
{
	ElemType *ar="ABC##DE##F##G#H##";
	BinaryTree root = NULL;
	root = CreateTree2(ar);
	NiceInOrder(root);
	NicePastOrder(root);
	StkNicePastOrder(root);
	StkNiceInOrder(root);
	NicePreOrder(root);
	NiceLevelOrder(root);

	LevelOrder(root);
	return 0;
}

int main()
{
	int ar[]={10,5,4,-1,-1,7,-1,-1,12,-1,-1};
	int *p = ar;
	BinaryTree root = CreateTree2(p);
	vector<ElemType> vec;
	ElemType val = 22;
	PrintPath(root,vec,val);
	return 0;
}

int main()
{
	int ar[]={31,23,12,66,-1,5,17,70,62,-1,-1,-1,88,-1,55};
	const int n = sizeof(ar)/sizeof(ar[0]);
	int br[n];
	BinaryTree root = NULL;
	root = MakeAr_Tree(ar,n);

	MakeLinkTree_Ar(root,br);
	return 0;
}


bool Is_Full;
bool Is_Comp;
bool Is_BST;
bool Is_Balance;
int main()
{
	char *ps = "ABCDEFGH";
	char *is = "CBEDFAGH";
	char *ls = "CEFDBHGA";
	int n = strlen(ps);
	BinaryTree root = NULL;
	root = CreateTreeIL(is,ls,n);
	PreOrder(root);
	cout<<endl;
	InOrder(root);
	cout<<endl;
	PastOrder(root);
	cout<<endl;
	return 0;
}

int main()
{
	ElemType *ar="ABC##DE##F##G#H##";
	BinaryTree root = NULL;
	root = CreateTree2(ar);
	PreOrder(root);
	cout<<endl;
	InOrder(root);
	cout<<endl;
	PastOrder(root);
	cout<<endl;
	return 0;
}

int Partition(vector<int> &ar,int left,int right)
{
	int i = left,j = right;
	int tmp = ar[i];
	while(i<j)
	{
		while(i<j && ar[j] > tmp) --j;
		if(i<j) { ar[i] = ar[j];}
		while(i<j && ar[i] <= tmp) ++i;
		if(i<j) { ar[j] = ar[i];}
	}
	ar[i] = tmp;
	return i;
}

int SelectK(vector<int> &ar,int left,int right,int k)
{
	if(left == right && k == 1) return ar[left];
	int index = Partition(ar,left,right);
	int pos = index - left + 1;
	if(k<=pos) return SelectK(ar,left,index,k);
	else return SelectK(ar,index+1,right,k-pos);
}
int SelectK_Min(vector<int> &ar,int k)
{
	return SelectK(ar,0,ar.size()-1,k);
}
int MaxS(vector<int> &ar,int left,int right)
{
	return ar[right];
}
int MinS(vector<int> &ar,int left,int right)
{
	int min = ar[left];
	for(int i = left+1;i<=right;++i)
	{
		if(min>ar[i])
		{
			min = ar[i];
		}
	}
	return min;
}

int MinS(int d1,int d2,int d3)
{
	return min(d1,min(d2,d3));
}
int Cpair(vector<int> &ar,int left,int right)
{
	if(right - left <= 0) // if(left == right)
	{
		return INT_MAX;
	}
	int k = (right - left + 1)/2;
	int index = left + k - 1;
	SelectK(ar,left,right,k);

	int d1 = Cpair(ar,left,index);//s1;
	int d2 = Cpair(ar,index+1,right); //s2;
	int maxs1 = MaxS(ar,left,index); //s1;
	int mins2 = MinS(ar,index+1,right); //s2;
	return MinS(d1,d2,mins2 - maxs1);
}
int Cpair(vector<int> &ar)
{
	if(ar.size() < 2)
		return INT_MAX;
	else
		return Cpair(ar,0,ar.size()-1);
}
int main()
{

	//41 67 34 0 69 24 78 58 62 64 5  45
	//0  1   2 3  4  5  6 7  8  9  10 11 
	vector<int> ivec;
	int n = 12;
	for(int i = 0;i<n;++i)
	{
		ivec.push_back(rand()%100);
	}
	//ivec.push_back(5);
	
	n = ivec.size();
	for(int i = 0;i<n;++i)
	{
		cout<<ivec[i]<<" ";
	}
	std::partition
	cout<<endl;
	int mindif = Cpair(ivec);
	cout<<mindif<<endl;
	return 0;
	


}




void Print2Min(vector<int> &ar)
{
	int n = ar.size();
	if(n < 2) return ;
	int min1 = ar[0]<ar[1]? ar[0]:ar[1];
	int min2 = ar[0]<ar[1]? ar[1]:ar[0];
	for(int i = 2;i<n;++i)
	{
		if(min1 > ar[i])
		{
			min2 = min1;
			min1 = ar[i];
		}else if(min2 > ar[i])
		{
			min2 = ar[i];
		}
	}
	printf("min1 => %d min2 => %d\n",min1,min2);
}
void fun(int *ar,int *br,int i,int n)
{
	if(i >= n)
	{
		for(int j = 0 ;j<n;++j)
		{
			if(br[j])
			{
				cout<<ar[j]<<" ";
			}
		}
		cout<<endl;
	}
	else
	{
		br[i] = 1;
		fun(ar,br,i+1,n); // left
		br[i] = 0;

		fun(ar,br,i+1,n); // right
	}
}
int main()
{
	int ar[]={1,2,3};
	const int n = sizeof(ar)/sizeof(ar[0]);
	int br[n]={0,0,0};
	fun(ar,br,0,n);
	return 0;
}

int fac(unsigned int n,unsigned int a,unsigned int b)
{
	if(n <= 2) return a;
	return fac(n-1,a+b,a);
}
int fac(unsigned int n)
{
	unsigned a = 1, b = 1;
	return fac(n,a,b);
}

void Swap(int &a,int &b)
{
	int c = a;
	a = b;
	b = c;
}
void Perm(int *br,int k,int m)
{
	if(k == m)// 
	{
		for(int i = 0;i<=m;++i)
		{
			cout<<br[i]<<"  ";
		}
		cout<<endl;
	}
	else
	{
		for(int j = k ; j<=m;++j)
		{
			Swap(br[j],br[k]);
			Perm(br,k+1,m);
			Swap(br[j],br[k]);
		}
	}
}
int main()
{
	int ar[]={1,2,3};
	int n = sizeof(ar)/sizeof(ar[0]);
	Perm(ar,0,n-1);
	return 0;
}


int main()
{
	int ar[]={12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar)/sizeof(ar[0]);
	vector<int> ivec(ar,ar+n);
	binary_search(ivec.begin(),ivec.end(),23);
	//lower_bound;
}



// 3
void * PrintInt(void *p)
{
	int *ip = (int*)p;
	printf("%d ",*ip);
	return ip+1;
}
void * PrintDouble(void *p)
{
	double *dp = (double*)p;
	printf("%f ",*dp);
	return dp + 1;
}
void PrintArray(void *ar,int n , void * (*viste)(void *) )
{
	if(NULL == ar || n < 1) return ;
	for(int i = 0;i<n;++i)
	{
		ar = viste(ar);
	}
	printf("\n");
}

void main()
{
	int ar[]={12,23,34,45,56,67,78,89};
	int n = sizeof(ar)/sizeof(ar[0]);
	double dr[]={1.2,2.3,3.4,4.5,5.6,7.6};
	int m = sizeof(dr)/sizeof(dr[0]);
	PrintArray(ar,n,PrintInt);
	PrintArray(dr,m,PrintDouble);

}

//
int SearchValue(int *br,int left,int right,int val)
{
	int pos = -1;
	if(left <= right)
	{
		int mid = (right - left + 1)/2 + left;
		if(val < br[mid])
		{
			pos = SearchValue(br,left,mid-1,val);
		}else if(val > br[mid])
		{
			pos = SearchValue(br,mid+1,right,val);
		}else
		{
			while(mid > left && val == br[mid-1]) --mid;
			pos = mid;
			break;
		}
	}
	return pos;
}
int FindValue(int *br,int n,int val)
{
	if(NULL == br || n < 1) return -1;
	return SearchValue(br,0,n-1,int val);
}
int main()
{
	int ar[]={12,23,34,45,56,67,78,98,90,100,110,120};
	int n = sizeof(ar)/sizeof(ar[0]);
	int x;
	cin>>x;
	int pos = FindValue(); // index // -1

	return 0;
}
// n = 10
int FindValue(int *br,int n,int val)
{
	if(NULL == br || n < 1) return -1;
	int pos = -1;
	int left = 0, right = n-1;
	while(left <= right) // while(left < right) // left 1 right =1
	{
		//int mid = (left + right)/ 2;
		int mid = (right - left + 1)/2 + left;
		if(val < br[mid])
		{
			right = mid-1;
		}else if(val > br[mid])
		{
			left = mid+1;
		}else
		{
			while(mid > left && val == br[mid-1]) --mid;
			pos = mid;
			break;
		}
	}
	return pos;
}
// gcc 
// g++ yhp.cpp -o yhp -g -Ml , stack = xxxx

int fac(unsigned int n)
{
	if(n <= 2) return 1;
	else return fac(n-1) + fac(n-2);
}
int fun(unsigned int n)
{
	int a = 1, b = 1 , c = 1;
	for(int i = 3;i<=n;++i)
	{
		c = a + b;
		b = a;
		a = c;
	}
	return c;
}
// 
int main()
{
	int n,sum;
	cin>>n;
	sum = fac(n);
	cout<<n<<" => "<<sum<<endl;
	return 0;
}

int fun(unsigned int n)
{
	int sum = 1;
	for(int i = 1;i<=n;++i)
	{
		sum = sum *i;
	}
	return sum;
}
int fac(int n)
{
	if(n <= 1) return 1;
	else return fac(n-1)*n;
}
int main()
{
	int n,sum;
	cin>>n;
	sum = fun(n);
	cout<<sum<<endl;
	return 0;
}
#endif
