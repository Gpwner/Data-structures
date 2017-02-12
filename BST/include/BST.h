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
        //输入结束标识符
        cin>>x;
        while(x!="#")
        {
            Insert(x,root);
            cin>>x;
        }
    }
    /** Default destructor */
    ~BST() {}
    //搜索
    bool Search(const K x)const
    {
        return Search(x,root)!=NULL?true:false;
    }
    //赋值
    BSTNode<E,K> & operator =(const BSTNode<E,K> & R) {}
    //置空
    void MakeEmpty()
    {
        MakeEmpty(root);
        root=NULL;
    }
    //输出
    void PrintTree()const
    {
        PrintTree(root);
    }
    //求最小值
    E Min()
    {
        return Min(root)->data;
    }
    //求最大值
    E Max()
    {
        return Max(root)->data;
    }
    //插入
    bool Insert(const E & e1)
    {
        return Insert(e1,root);
    }
    //删除含x的节点
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
            //新节点作为叶节点插入
            ptr=new BSTNode<E,K>(e1);
            if(NULL==ptr)
            {
                cout<<"Out of space"<<endl;
                exit(1);
            }
            return true;
        }//插入左节点
        else if(e1<ptr->data)
        {
            Insert(e1,ptr->left);
        }//插入右节点
        else if(e1>ptr->data)
        {
            Insert(e1,ptr->right);
        }//e1已经在树中存在，不再插入
        else
        {
            cout<<"数据已经在树中存在，不再插入！"<<endl;
            return false;
        }
    }
    bool Remove(const K x,BSTNode<E,K> *&ptr)
    {
        BSTNode<E,K> *temp;
        if(NULL!=ptr)
        {
            //在左子树中执行删除
            if(x<ptr->left)
            {
                Remove(x,ptr->left);
            }//在右子树中执行删除
            else if(x>ptr->right)
            {
                Remove(x,ptr->right);
            }
            //查找到该节点,该节点左右节点均不为空
            else if(ptr->left!=NULL&&ptr->right!=NULL)
            {
                //到该节点的右子树中查找最小的节点
                temp=ptr->right;
                while(temp->left!=NULL)
                {
                    temp=temp->left;
                }
                ptr->data=temp->data;
                //删除该节点的右子树中的最小的节点
                Remove(ptr->data,ptr->right);
            }
            //查找到该节点，该节点只有一个或者没有子节点
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
            cout<<"搜索二叉树中没有当前节点"<<endl;
            return false;
        }
    }
};

#endif // BST_H
