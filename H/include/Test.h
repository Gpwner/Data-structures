#include <iostream>

using namespace std;

template<class T>
class Test
{

public:
    template <class S>
    friend ostream& operator << (ostream& out, const Test<S>& obj);
    Test(T n = 0) :num(n) {}
    Test(const Test<T>& copy)
    {
        num = copy.num;
    }
private:
    T num;
};
