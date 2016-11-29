#ifndef LISTNODE_H
#define LISTNODE_H
#include<iostream>
/*
Create by 软件工程 gpwner  2016年11月28日17:37:23
*/
using namespace std;
template<class Type>
class ListNode
{
public:

    //链表结点构造函数
    ListNode ( ):link(NULL) {}
    ListNode ( const Type& item ):data(item),link(NULL) {}
    //给出当前结点的下一结点地址
    ListNode<Type> *NextNode ( )
    {
        return link;
    }
    //在当前结点后插入结点p
    void InsertAfter ( ListNode<Type> *p )
    {
        link->link=p;
    }
    //摘下当前结点的下一结点
    ListNode<Type> *RemoveAfter ( )
    {
        ListNode<Type> *tempptr=link;
        if(tempptr==NULL)
        {
            return NULL;
        }
        //重新链接
        link=link->link;
        return tempptr;
    }
    Type GetData()
    {

        return  data;
    }
    ListNode<Type> *GetNext()
    {
        return link;

    }
    void SetNext(ListNode<Type> *node)
    {
        link=node;
    }
private:
    Type data;
    ListNode<Type> *link;
};

#endif // LISTNODE_H
