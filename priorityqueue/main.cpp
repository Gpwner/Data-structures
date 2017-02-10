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
        cout<<"当前最小优先权队列的队首元素是："<<value<<endl;
    for(int i=0;i<5;i++)
    {
        pq->RemoveMin(value);
        cout<<"删除了最小的元素："<<value<<endl;
    }
    return 0;
}
