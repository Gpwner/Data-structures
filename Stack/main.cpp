#include <iostream>
#include<Stack.h>
using namespace std;
/*
Create by 软件工程 gpwner  2016年11月28日17:37:23
*/
int main()
{
    Stack<int> *mstack=new Stack<int>();
    for(int i=10; i<20; i++)
        mstack->Push(i);
    mstack->Pop();
    mstack->Push(99);
    cout<<"当前栈中元素个数:"<<mstack->Size()<<endl;
    cout<<"栈顶元素是："<<mstack->Top()<<endl;

    cout<<"当前栈中的所有的元素(栈顶--->栈底)："<<endl;
    while(mstack->IsEmpty())
    {
        cout<<mstack->Top()<<"  ";
        mstack->Pop();
    }
    cout<<endl;
    return 0;
}
