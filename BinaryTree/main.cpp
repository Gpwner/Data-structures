#include <iostream>
#include<BinaryTree.h>
#include<string>
template <class T>
void visit(BinTreeNode<T> *p );
using namespace std;
int main()
{
    BinaryTree<string> *bin=new BinaryTree<string>();
    bin->CreateBinTree();
    if(bin->IsEmpty())
    {

        cout<<"��ǰ����Ϊ��,������нڵ㣺"<<endl;
        bin->Traverse(bin->root);
        cout<<endl;
        cout<<"��ǰ���ĸ߶��ǣ�"<<bin->Height()<<endl;
        cout<<"��ǰ���Ĵ�С�ǣ�"<<bin->Size()<<endl;
        cout<<"ǰ�������"<<endl;
        bin->preOrder(visit);
        cout<<"\n���������"<<endl;
        bin->inOrder(visit);
        cout<<"\n���������"<<endl;
        bin->postOrder(visit);
        cout<<endl;
        cout<<"���ĸ��ڵ��ǣ�"<<bin->getRoot()->data;
    }
    delete bin;
    return 0;
}
template < class T>
void visit(BinTreeNode<T> *p )
{
    cout<< p->data<<"  ";
}
