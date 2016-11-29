#ifndef STACK_H
#define STACK_H
#include<ListNode.h>

/*
Create by 软件工程 gpwner  2016年11月28日17:37:23
*/
template <class Type>
class Stack
{
public:
    //构造函数
    Stack()
    {
        top=NULL;
    }
    //析构函数
    ~Stack()
    {

        while(top!=NULL)
        {
            ListNode<Type> *tempNode=top;
            top=top->GetNext();
            delete tempNode;
        }
    }
    //新元素进栈
    void Push(const &x)
    {
        ListNode<Type>  *newNode=new ListNode<Type>(x);
        if(top==NULL)
        {
            top=newNode;
        }
        else
        {
            newNode->SetNext(top);
            top=newNode;
        }
    }
    //栈顶元素出栈
    Type Pop()
    {
        if(top==NULL)
        {
            return NULL;
        }
        Type data=top->GetData();
        ListNode<Type> *tempNode=top;
        delete tempNode;
        top=top->GetNext();
        return data;
    }
    //判断当前栈是否为空
    bool IsEmpty()
    {
        if(top==NULL)
            //为空的时候返回false
            return false;
        else
            //非空的时候返回true
            return true;
    }
    //获取当前栈有多少个元素
    int Size()
    {
        int num=0;
        ListNode<Type> *current=top;
        while(current!=NULL)
        {
            current=current->GetNext();
            num++;
        }
        return num;
    }
    //获取栈顶元素
    Type Top()
    {
        if(top!=NULL)
            return top->GetData();
        return NULL;
    }
private:
    ListNode<Type> *top;
};

#endif // STACK_H
