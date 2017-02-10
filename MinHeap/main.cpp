#include <iostream>
#include<MinHeap.h>
using namespace std;

int main()
{
    MinHeap<int> * heap=new MinHeap<int >(8);
    heap->Insert(53);
    heap->Insert(17);
    heap->Insert(78);
    heap->Insert(9);
    heap->Insert(45);
    heap->Insert(65);
    heap->Insert(87);
    heap->Insert(23);
    cout<<"依次删除最小堆中的元素<从小到大>：\n"<<endl;
    int value;
    heap->RemoveMin(value);
    cout<<value<<" ";

    heap->RemoveMin(value);
    cout<<value<<" ";

    heap->RemoveMin(value);
    cout<<value<<" ";

    heap->RemoveMin(value);
    cout<<value<<" ";

    heap->RemoveMin(value);
    cout<<value<<" ";


    heap->RemoveMin(value);
    cout<<value<<" ";

    heap->RemoveMin(value);
    cout<<value<<" ";

    heap->RemoveMin(value);
    cout<<value<<" \n\n";
    delete heap;
    return 0;
}
