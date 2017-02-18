#ifndef BST_H
#define BST_H

#include<stdlib.h>
#include<iostream>
using namespace std;
template<class E,class K>
struct BSTNode
{
    E data;
    BSTNode<E,K> *left,*right;
    BSTNode():left(NULL),right(NULL) {}
    BSTNode(const E d,BSTNode<E,K> *L=NULL,BSTNode<E,K> *R=NULL):data(d),left(L),right(R) {}
    ~BSTNode() {}
    void SetData(E d)
    {
        data=d;
    }
    E DetData()
    {
        return data;
    }
};
template <class E,class K>
class BST
{
public:
    /** Default constructor */
    BST()
    {
        root=NULL;

    }
    void CreateBST()
    {

        E x;
        //���������ʶ��
        cin>>x;
        while(x!="#")
        {
            Insert(x,root);
            cin>>x;
        }
    }
    /** Default destructor */
    ~BST() {}
    //����
    bool Search(const K x)const
    {
        return Search(x,root)!=NULL?true:false;
    }
    //��ֵ
    BSTNode<E,K> & operator =(const BSTNode<E,K> & R) {}
    //�ÿ�
    void MakeEmpty()
    {
        MakeEmpty(root);
        root=NULL;
    }
    //���
    void PrintTree()const
    {
        PrintTree(root);
    }
    //����Сֵ
    E Min()
    {
        return Min(root)->data;
    }
    //�����ֵ
    E Max()
    {
        return Max(root)->data;
    }
    //����
    bool Insert(const E & e1)
    {
        return Insert(e1,root);
    }
    //ɾ����x�Ľڵ�
    bool Remove(const K x)
    {
        return Remove(x,root);
    }

private:
    BSTNode<E,K> *root;
    BSTNode<E,K> *Search(const K x,BSTNode<E,K> *ptr)
    {
        if(NULL==ptr)
        {
            return NULL;
        }
        else if(x<ptr->data)
            return Search(x,ptr->left);
        else if(x>ptr->data)
            return Search(x,ptr->right);
        else
            return ptr;
    }
    void MakeEmpty(BSTNode<E,K> *&ptr) {}
    void PrintTree(BSTNode<E,K> *ptr)const {}
    BSTNode<E,K>* Copy(const BSTNode<E,K> *ptr) {}
    BSTNode<E,K>* Min(BSTNode<E,K> *ptr)const {}
    BSTNode<E,K>* Max(BSTNode<E,K> *ptr)const {}
    bool Insert(const E &e1,BSTNode<E,K> *&ptr)
    {
        if(NULL==ptr)
        {
            //�½ڵ���ΪҶ�ڵ����
            ptr=new BSTNode<E,K>(e1);
            if(NULL==ptr)
            {
                cout<<"Out of space"<<endl;
                exit(1);
            }
            return true;
        }//������ڵ�
        else if(e1<ptr->data)
        {
            Insert(e1,ptr->left);
        }//�����ҽڵ�
        else if(e1>ptr->data)
        {
            Insert(e1,ptr->right);
        }//e1�Ѿ������д��ڣ����ٲ���
        else
        {
            cout<<"�����Ѿ������д��ڣ����ٲ��룡"<<endl;
            return false;
        }
    }
    bool Remove(const K x,BSTNode<E,K> *&ptr)
    {
        BSTNode<E,K> *temp;
        if(NULL!=ptr)
        {
            //����������ִ��ɾ��
            if(x<ptr->left)
            {
                Remove(x,ptr->left);
            }//����������ִ��ɾ��
            else if(x>ptr->right)
            {
                Remove(x,ptr->right);
            }
            //���ҵ��ýڵ�,�ýڵ����ҽڵ����Ϊ��
            else if(ptr->left!=NULL&&ptr->right!=NULL)
            {
                //���ýڵ���������в�����С�Ľڵ�
                temp=ptr->right;
                while(temp->left!=NULL)
                {
                    temp=temp->left;
                }
                ptr->data=temp->data;
                //ɾ���ýڵ���������е���С�Ľڵ�
                Remove(ptr->data,ptr->right);
            }
            //���ҵ��ýڵ㣬�ýڵ�ֻ��һ������û���ӽڵ�
            else
            {
                temp=ptr;
                if(ptr->left==NULL)
                    ptr=ptr->right;
                else
                    ptr=ptr->left;
                delete temp;
                return true;
            }
        }
        else
        {
            cout<<"������������û�е�ǰ�ڵ�"<<endl;
            return false;
        }
    }
};

#endif // BST_H
