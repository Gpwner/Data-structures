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
    //n是顶点数，m是边数
    int n,m;
    V e1,e2;
    W weight;
    cout<<"请输入顶点数、边数："<<endl;
    in>>n>>m;
    cout<<"请输入顶点："<<endl;
    for(int i=0; i<n; i++)
    {
        in>>e1;
        G.insertVertex(e1);
    }
    int i=0,j,k;
    cout<<"请输入边的两个顶点以及权值："<<endl;
    while(i<m)
    {

        in>>e1>>e2>>weight;
        j=G.getVertexPos(e1);
        k=G.getVertexPos(e2);
        if(-1==j&&-1==k)
        {
            cout<<"边的两端信息有误，请重新输入。"<<endl;
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
//输出所有顶点和边的信息
    int n,m;
    V e1,e2;
    W w;
    n=G.NumberOfvertices();
    m=G.NumberOfEdges();
    out<<"一共有顶点数："<<n<<"个    边："<<m<<"条"<<endl;
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
