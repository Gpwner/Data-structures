#include <iostream>
#include<List.h>
#include<stdlib.h>
using namespace std;

int main()
{
    List<string> *stringList=new List<string>();
    string name;
    cout<<"������ı�ͷ��ʼ�������ݣ�����������5�����ݣ�"<<endl;
    for(int i=0; i<5; i++)
    {
        cin>>name;
        stringList->Insert(name);
    }
    cout<<"\n��������"<<endl;
    stringList->Traverse();
    cout<<"\n������Ҫ����Ľڵ�����ݺ�λ�ã�";
    string data;
    int index;
    cin>>data>>index;
    cout<<stringList->Insert(data,index)<<endl;

    stringList->Traverse();
    return 0;
}
