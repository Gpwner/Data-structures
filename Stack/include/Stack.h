#ifndef STACK_H
#define STACK_H
#include<ListNode.h>

/*
Create by ������� gpwner  2016��11��28��17:37:23
*/
template <class Type>
class Stack
{
public:
    //���캯��
    Stack()
    {
        top=NULL;
    }
    //��������
    ~Stack()
    {

        while(top!=NULL)
        {
            ListNode<Type> *tempNode=top;
            top=top->GetNext();
            delete tempNode;
        }
    }
    //��Ԫ�ؽ�ջ
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
    //ջ��Ԫ�س�ջ
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
    //�жϵ�ǰջ�Ƿ�Ϊ��
    bool IsEmpty()
    {
        if(top==NULL)
            //Ϊ�յ�ʱ�򷵻�false
            return false;
        else
            //�ǿյ�ʱ�򷵻�true
            return true;
    }
    //��ȡ��ǰջ�ж��ٸ�Ԫ��
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
    //��ȡջ��Ԫ��
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
