#include <iostream>
#include<List.h>
#include<stdlib.h>
using namespace std;

int main()
{
    List<string> *stringList=new List<string>();
    string name;
    cout<<"从链表的表头开始插入数据，请依次输入5个数据："<<endl;
    for(int i=0; i<5; i++)
    {
        cin>>name;
        stringList->Insert(name);
    }
    cout<<"\n遍历链表："<<endl;
    stringList->Traverse();
    cout<<"\n请输入要插入的节点的数据和位置：";
    string data;
    int index;
    cin>>data>>index;
    cout<<stringList->Insert(data,index)<<endl;

    stringList->Traverse();
    return 0;
}
