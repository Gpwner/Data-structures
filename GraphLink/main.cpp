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
ostream& operator<<(ostream &out,Graphlink<V,W> &G)
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
//������ȷ���
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
//�ݹ��ӹ���
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
//������ȷ���
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
