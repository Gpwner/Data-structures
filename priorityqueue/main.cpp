#include <iostream>
#include<PQueue.h>

using namespace std;
int main()
{
    PQueue<int> *pq=new PQueue<int>(5);
    for(int i=1; i<6; i++)
        pq->Insert(i*5);
    int value;
    if(pq->GetFront(value))
        cout<<"��ǰ��С����Ȩ���еĶ���Ԫ���ǣ�"<<value<<endl;
    for(int i=0;i<5;i++)
    {
        pq->RemoveMin(value);
        cout<<"ɾ������С��Ԫ�أ�"<<value<<endl;
    }
    return 0;
}
