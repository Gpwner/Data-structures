#include <iostream>
#include<Stack.h>
using namespace std;
/*
Create by ������� gpwner  2016��11��28��17:37:23
*/
int main()
{
    Stack<int> *mstack=new Stack<int>();
    for(int i=10; i<20; i++)
        mstack->Push(i);
    mstack->Pop();
    mstack->Push(99);
    cout<<"��ǰջ��Ԫ�ظ���:"<<mstack->Size()<<endl;
    cout<<"ջ��Ԫ���ǣ�"<<mstack->Top()<<endl;

    cout<<"��ǰջ�е����е�Ԫ��(ջ��--->ջ��)��"<<endl;
    while(mstack->IsEmpty())
    {
        cout<<mstack->Top()<<"  ";
        mstack->Pop();
    }
    cout<<endl;
    return 0;
}
