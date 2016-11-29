#ifndef LISTNODE_H
#define LISTNODE_H
#include<iostream>
/*
Create by ������� gpwner  2016��11��28��17:37:23
*/
using namespace std;
template<class Type>
class ListNode
{
public:

    //�����㹹�캯��
    ListNode ( ):link(NULL) {}
    ListNode ( const Type& item ):data(item),link(NULL) {}
    ~ListNode()
    {
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
