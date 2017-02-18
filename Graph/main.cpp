#include <iostream>
#include<Graphmtx.h>
using namespace std;

int main()
{
    Graphmtx<int,int> G(5);
    cin>>G;
    cout<<G;
    return 0;
}
template <class V,class W>
istream& operator >>(istream & in,Graphmtx<V,W> &G)
{
    //n�Ƕ�������m�Ǳ���
    int n,m;
    V e1,e2;
    W weight;
    cout<<"�����붥������������"<<endl;
    in>>n>>m;
    cout<<"�����붥�㣺"<<endl;
    for(int i=0; i<n; i++)
    {
        in>>e1;
        G.insertVertex(e1);
    }
    int i=0,j,k;
    cout<<"������ߵ����������Լ�Ȩֵ��"<<endl;
    while(i<m)
    {

        in>>e1>>e2>>weight;
        j=G.getVertexPos(e1);
        k=G.getVertexPos(e2);
        if(-1==j&&-1==k)
        {
            cout<<"�ߵ�������Ϣ�������������롣"<<endl;
        }
        else
        {
            G.insertEdge(j,k,weight);
            i++;
        }
    }
    return in;
}
template <class V,class W>
ostream& operator<<(ostream &out,Graphmtx<V,W> &G)
{
//������ж���ͱߵ���Ϣ
    int n,m;
    V e1,e2;
    W w;
    n=G.NumberOfvertices();
    m=G.NumberOfEdges();
    out<<"һ���ж�������"<<n<<"��    �ߣ�"<<m<<"��"<<endl;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
        {
            w=G.getWeight(i,j);
            if(w>0&&w<G.maxWeight)
            {
                e1=G.getValue(i);
                e2=G.getValue(j);
                out<<"("<<e1<<","<<e2<<","<<w<<")"<<endl;
            }
        }
    return out;
}
