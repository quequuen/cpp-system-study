#include <iostream>
#include <vector>

using namespace std;

void countUp(int count)
{
    cout << count << endl;
    if (count < 10) countUp(count + 1);
}

int fib(int n) {
    cout << "fib(" << n << ") 호출됨" << endl;
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

int main()
{
    std::vector<int> v{1, 2, 3};
    // int *v_ptr = new int[3]{1, 2, 3};
    
    // countUp(1);

    cout << fib(6) << endl;

    // 0 1 2 3 5 8 13;



    return 0;
}