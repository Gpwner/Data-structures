#include<iostream>
#include<Test.h>
using namespace std;
int main()
{
    Test<int> t(666);
    cout<<t;
    return 0;
}

template<class T>
ostream& operator << (ostream& out, const Test<T>& obj)
{
    out << obj.num << endl;

    return out;
}
