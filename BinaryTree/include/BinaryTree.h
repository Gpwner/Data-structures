#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<stack>
#include<iostream>
#include<stdlib.h>
#include<istream>
#include<queue>
#include<stack>
using namespace std;
//�ڵ�ṹ��
template <class T>
struct BinTreeNode
{
    T data ;
    BinTreeNode<T> *leftChild;
    BinTreeNode<T> *rightChild;
    BinTreeNode():leftChild(NULL),rightChild(NULL) {}
    BinTreeNode(T x,BinTreeNode<T> *l=NULL,BinTreeNode<T> *r=NULL):leftChild(l),rightChild(r),data(x) {}
};
//��������ķǵݹ��㷨�õ��Ľڵ�ṹ��
template <class T>
struct stacknode
{
    BinTreeNode<T> *ptr;
    int tag ;
    stacknode(BinTreeNode<T> *n=NULL):ptr(n),tag(1) {}
};

//��������

template <class T>
class BinaryTree
{
public:
    //��ָ��
    BinTreeNode<T> *root;
    /** Default constructor */
    BinaryTree():root(NULL) {}
    //�������캯��
    BinaryTree(const BinaryTree<T> &s)
    {
        root=Copy(s.root);
    }
    ~BinaryTree()
    {
        destroy(root);
    }
    //�ж϶������Ƿ�Ϊ��
    bool IsEmpty()
    {
        return (root!=NULL)?true:false;
    }
    //���ظ��ڵ�
    BinTreeNode<T> *Parent(BinTreeNode<T> *current)
    {
        return (root==NULL||root==current)?NULL:Parent(root,current);
    }
    //������ڵ�
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current)
    {
        return (current==NULL)?NULL:current->leftChild;
    }
    //�����ҽڵ�
    BinTreeNode<T> *RightChild(BinTreeNode<T>*current)
    {
        return(current==NULL)?NULL:current->rightChild;
    }
    //�������ĸ߶�
    int Height()
    {
        return Height(root);
    }
    //���ؽڵ���
    int Size()
    {
        return Size(root);
    }
    //��ø��ڵ�
    BinTreeNode<T> * getRoot ()
    {
        return root;
    }
////�ݹ��㷨����������
//    //ǰ�����
//    void preOrder(void(*visit)(BinTreeNode<T> *p))
//    {
//        //�ݹ��㷨
//        preOrder(root,visit);
//    }
//    //�������
//    void inOrder(void(*visit)(BinTreeNode<T> *p))
//    {
//        inOrder(root,visit);
//    }
//    //�������
//    void postOrder(void(*visit)(BinTreeNode<T> *p))
//    {
//        postOrder(root,visit);
//    }
//
    void preOrder(void(*visit)(BinTreeNode<T> *p))
    {
        stack<BinTreeNode<T> *> nodes;
        BinTreeNode<T> *temp=root;
        nodes.push(NULL);
        while(temp!=NULL)
        {
            visit(temp);
            if(temp->rightChild!=NULL)
            {
                nodes.push(temp->rightChild);
            }
            if(temp->leftChild!=NULL)
            {
                temp=temp->leftChild;
            }
            else
            {
                temp=nodes.top();
                nodes.pop();
            }
        }
    }
    //�������
    void inOrder(void(*visit)(BinTreeNode<T> *p))
    {
        stack<BinTreeNode<T> *> nodes;
        //����ָ�룬�Ӹ��ڵ㿪ʼ
        BinTreeNode<T> *temp=root;
        do
        {
            //����ָ��δ�������µĽڵ㣬����
            while(NULL!=temp)
            {
                //��������;�ڵ��ջ
                nodes.push(temp);
                temp=temp->leftChild;
            }
            if(!nodes.empty())
            {
                //ջ��Ϊ�յ�ʱ����ջ�����ʸ��ڵ㣬����ָ���������Ů�ڵ�
                temp=nodes.top();
                visit(temp);
                nodes.pop();
                temp=temp->rightChild;
            }
        }
        while(NULL!=temp||!nodes.empty());
    }
    //�������
    void postOrder(void(*visit)(BinTreeNode<T> *p))
    {
        stack<stacknode<T> > nodes;
        stacknode<T> temp;
        BinTreeNode<T> *p=root;
        do
        {
            while(NULL!=p)
            {
                temp.ptr=p;
                temp.tag=1;
                nodes.push(temp);
                p=p->leftChild;
            }
            int continue1=1;
            while(continue1&&!nodes.empty())
            {
                temp=nodes.top();
                nodes.pop();
                p=temp.ptr;
                switch(temp.tag)
                {
                case 1:
                    temp.tag=2;
                    nodes.push(temp);
                    continue1=0;
                    p=p->rightChild;
                    break;
                case 2:
                    visit(p);
                    break;
                }
            }

        }
        while(!nodes.empty());
    }




    //��α���
    void levelOrder(void (*visit)(BinTreeNode<T> *p))
    {
        queue<BinTreeNode<T> *> nodes;
        BinTreeNode<T> *temp=root;
        BinTreeNode<T> *tnode;
        nodes.push(temp);
        while(!nodes.empty())
        {
            tnode=nodes.front();
            nodes.pop();
            visit(tnode);
            if(NULL!=tnode->leftChild)
            {
                nodes.push(tnode->leftChild);
            }
            if(NULL!=tnode->rightChild)
            {
                nodes.push(tnode->rightChild);
            }
        }
    }
    //������Ԫ��
    void  Insert(const T &item) {}
    //����
    BinTreeNode<T> *Find(T &item) const {}
    void CreateBinTree()
    {
        CreateBinTree(root);
    }
    //ǰ��������

    void Traverse(BinTreeNode<T> * subTree)
    {
        if(NULL!=subTree)
        {

            cout<<subTree->data<<" ";
            //�ݹ����subTree��������
            Traverse(subTree->leftChild);
            //�ݹ����subTree��������
            Traverse(subTree->rightChild);
        }
    }

protected:

    //���ö�����ǰ���������������
    void CreateBinTree(BinTreeNode<T> *&subTree)
    {
        T item;
        if((cin>>item)&&item!="#")
        {
            subTree=new BinTreeNode<T>(item);
            if(subTree==NULL)
            {
                cerr<<"�洢�������"<<endl;
                exit(1);
            }
            CreateBinTree(subTree->leftChild);
            CreateBinTree(subTree->rightChild);
        }
        else
        {
            //���ָ���������ָ��
            subTree=NULL;
        }
    }
    //����
    bool Insert(BinTreeNode<T> *&subTree,const T& x) {}
    //����
    bool Find(BinTreeNode<T> *subTree,const T& x)const {}
    //����ֵ���ҽ��
    BinTreeNode<T>* Find(BinTreeNode<T> *subTree,const T &x ) {}
    //����
    BinTreeNode<T> *Copy(BinTreeNode<T> *originnode)
    {
        if(originnode==NULL)
        {
            return NULL;
        }
        BinTreeNode<T> *temp=new BinTreeNode<T>();
        temp->data=originnode->data;
        temp->leftChild=originnode->leftChild;
        temp->rightChild=originnode->rightChild;
        return temp;
    }
    //��������
    void destroy(BinTreeNode<T> *subTree)
    {
        if(subTree!=NULL)
        {
            destroy(subTree->leftChild);
            destroy(subTree->rightChild);
            delete subTree;
        }
    }
    //���ظ��ڵ㣬�ӽڵ�subTree��ʼ������current�ڵ�ĸ��ڵ�
    BinTreeNode<T> *Parent(BinTreeNode<T> *subTree,BinTreeNode<T> *current)
    {
        if(current==NULL)
            return NULL;
        //�ҵ����ظ��ڵ�
        if(subTree->leftChild==current||subTree->rightChild==current)
            return subTree;
        BinTreeNode<T> *p;
        //���������ֵݹ����
        if((p=Parent(subTree->leftTree,current))!=NULL)
            return p;
        //���������ֵݹ����
        else
            return Parent(subTree->rightChild,current);
    }
    //�������ĸ߶�
    int Height(BinTreeNode<T> *subTree)
    {
        if(subTree==NULL)
        {
            return 0;
        }
        else
        {
            int leftHieght=Height(subTree->leftChild);
            int rightHeight=Height(subTree->rightChild);
            return (leftHieght>rightHeight)?leftHieght+1:rightHeight+1;
        }

    }
    //���ظ��ڵ�
    int Size(BinTreeNode<T> *subTree) const
    {
        if(subTree==NULL)
        {
            //�ݹ�������ڵ����Ϊ0
            return 0;
        }
        else
        {
            return 1+Size(subTree->leftChild)+Size(subTree->rightChild);
        }
    }
    //ǰ�����
    void preOrder(BinTreeNode<T>*subTree,void(*visit)(BinTreeNode<T> *p))
    {
        if(subTree!=NULL)
        {

            visit(subTree);
            preOrder(subTree->leftChild,visit);
            preOrder(subTree->rightChild,visit);
        }
    }
    //�������
    void inOrder(BinTreeNode<T> *subTree,void(*visit)(BinTreeNode<T> *p))
    {
        //�ݹ麯��,=NULL����ֹ�ݹ�����
        if(subTree!=NULL)
        {
            inOrder(subTree->leftChild,visit);
            visit(subTree);//���ʸ��ڵ�
            inOrder(subTree->rightChild,visit);
        }
    }
    //�������
    void postOrder(BinTreeNode<T> *subTree,void(*visit)(BinTreeNode<T> *p))
    {
        if(subTree!=NULL)
        {
            postOrder(subTree->leftChild,visit);
            postOrder(subTree->rightChild,visit);
            visit(subTree);
        }
    }
};

#endif // BINARYTREE_H
