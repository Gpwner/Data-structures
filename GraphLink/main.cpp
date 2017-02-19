#include <iostream>
#include<Graphlink.h>
#include<queue>
using namespace std;

int main()
{
    return 0;
}
template <class V,class W>
istream& operator >>(istream & in,Graphlink<V,W> &G)
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
ostream& operator<<(ostream &out,Graphlink<V,W> &G)
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
//深度优先访问
template<class T,class E>
void DFS(Graphlink<T,E> &G,const T &v)
{
    int i,loc,n=G.NumberOfVertices();
    bool *visited=new bool[n];
    for(int i=0; i<n; i++)
        visited[i]=false;
    loc=G.getVertexPos(v);
    DFS(G,loc,visited);
    delete []visited;
}
//递归子过程
template <class T,class E>
void DFS(Graphlink<T,E> &G,int v,bool visited[])
{
    cout<<G.getValue(v)<<"  ";
    visited[v]=true;
    int w=G.getFirstNeighbor(v);
    while(-1!=w)
    {
        if(false==visited[w])
            DFS(G,w,visited);
        w=G.getNextNeighbor(v,w);
    }
}
//广度优先访问
template <class T,class E>
void BFS(Graphlink<T,E> &G,const T& v)
{
    int w,n=G.NumberOfVertices();
    bool *visited=new bool[n];
    for(int i=0; i<n; i++)
        visited[i]=false;
        int loc=G.getVertexPos(v);
        cout<<G.getValue(loc)<<endl;
        visited[v]=true;
        queue<int> Q;
        Q.push(loc);
        while(!Q.empty())
        {
            loc=Q.pop();
            w=G.getFirstNeighbor(loc);
            while(-1!=w)
            {
                if(false==visited[w])
                {
                    cout<<G.getValue(w)<<endl;
                    visited[w]=true;
                    Q.push(w);
                }
               w=G.getNextNeighbor(loc,w);
            }
        }
        delete []visited;
}
