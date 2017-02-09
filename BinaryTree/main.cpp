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

        cout<<"当前树不为空,输出所有节点："<<endl;
        bin->Traverse(bin->root);
        cout<<endl;
        cout<<"当前树的高度是："<<bin->Height()<<endl;
        cout<<"当前树的大小是："<<bin->Size()<<endl;
        cout<<"前序遍历："<<endl;
        bin->preOrder(visit);
        cout<<"\n中序遍历："<<endl;
        bin->inOrder(visit);
        cout<<"\n后序遍历："<<endl;
        bin->postOrder(visit);
        cout<<endl;
        cout<<"树的根节点是："<<bin->getRoot()->data;
    }
    delete bin;
    return 0;
}
template < class T>
void visit(BinTreeNode<T> *p )
{
    cout<< p->data<<"  ";
}
