#ifndef LIST_H
#define LIST_H
#include<iostream>
#include<stdlib.h>

using namespace std;

template<class Type>
class List;

template<class Type>
class ListNode
{
public:
    friend class List<Type>;
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

template<class Type>
class List
{
private:
    ListNode<Type> *first, *last;
public:
    //创建数据为item，指针为next的新结点
    ListNode<Type> *GetNode ( const Type& item, ListNode<Type> *next )
    {
        ListNode<Type> *newnode =new ListNode<Type> ( item );
        newnode->link = next;
        return newnode;

    }
    //构造函数
    List (  )
    {
        last=first=NULL;
    }
    //析构函数
    ~List ( )
    {

        ListNode<Type> *node;
        while(first->link!=NULL)
        {
            node=first->link;
            first->link=node->link;
        }
        delete first;
    }

    //求链表长度
    int Length ( ) const
    {

        //求单链表的长度
        ListNode<Type> *node = first;
        //检测指针p指示第一个结点
        int count = 0;
        //逐个结点检测
        while ( node != NULL )
        {
            node = node->link;
            count++;
        }
        return count;

    }
    //根据值查找节点
    ListNode<Type> *Find ( Type value )
    {

        //在链表中从头搜索其数据值为value的结点
        ListNode<Type> *node = first;
        //检测指针 p 指示第一个结点
        while ( node != NULL && node->GetData() != value )
        {
            node = node->link;
        }
        // p 在搜索成功时返回找到的结点地址
        // p 在搜索不成功时返回空值
        return node;

    }
    //根据序列查找节点
    ListNode<Type> *Find ( int i )
    {

        //在链表中从头搜索第 i 个结点，不计头结点
        if ( i < 1 )
            return NULL;
        if ( i == 1 )
            return first;	    // i 应  0
        ListNode<Type> *p = first;
        int j = 1;
        while ( p != NULL && j < i )          // j = i 停
        {
            p = p->link;
            j++;
        }
        return p;
    }
    void Insert(Type value)
    {
        ListNode<Type> *node=new ListNode<Type>(value);
        if(first==NULL)
        {
            first=node;
            last=node;
        }
        else
        {
            ListNode<Type> *temp=last;
            last->SetNext(node);
            last=node;
        }
    }
    //在第i个位置插入节点
    int Insert ( Type value, int i )
    {
        ListNode<Type> *newNode=new ListNode<Type>(value);
        if(first==NULL||i==0)
        {
            if(newNode==NULL)
            {
                cout<<"创建新节点时，内存分配错误"<<endl;
                exit(1);
            }
            newNode->SetNext(first);
            first=newNode;
        }
        else
        {

            ListNode<Type> *current=first;
            for(int k=1; k<i; k++)
            {
                if(current==NULL)
                {
                    break;
                }
                else
                {
                    current=current->GetNext();
                }
            }
            if(current==NULL)
            {
                cerr<<"无效的插入位置"<<endl;
                return 0;
            }
            else
            {
                if(newNode==NULL)
                {
                    cout<<"创建新节点时，内存分配错误"<<endl;
                    exit(1);
                }
                else
                {
                    newNode->SetNext(current->GetNext());
                    current->SetNext(newNode);
                }
            }
            return 1;
        }

    }
    //移除第i个节点的函数
    Type *Remove ( int i )
    {

        //从链表中删去第 i 个结点
        ListNode<Type> *node= Find (i-1), *tempnode;
        if ( node == NULL || node->link == NULL )
            return NULL;
        tempnode = node->link;
        node->link = tempnode->link;    //重新链接
        Type value = new Type ( tempnode->GetData() );
        if ( tempnode == last )
            last = node;

        delete tempnode;
        return &value;

    }
    void Traverse()
    {
        int i=1;
        ListNode<Type> *node=first;
        while(node!=NULL)
        {
            cout<<i++<<"--"<<node->GetData()<<"  ";
            node=node->GetNext();
        }

    }
    //获取第i个节点的函数
    Type Get ( int i ) //提取第 i 个结点的数据
    {
        ListNode<Type> *node = Find ( i );
        // p 指向链表第 i 个结点
        if ( node == NULL )
            return NULL;
        else
            return node->GetData();
    }
    ListNode<Type>  * getFirst()
    {
        return first;
    }
    ListNode<Type> * getLast()
    {
        return last;
    }

};
#endif // LIST_H
