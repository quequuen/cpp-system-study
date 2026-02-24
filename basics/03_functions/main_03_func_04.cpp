#include <iostream>
#include <vector>

using namespace std;

void countUp(int count)
{
    cout << count << endl;
    if (count < 10) countUp(count + 1);
    

}

int main()
{
    std::vector<int> v{1, 2, 3};
    // int *v_ptr = new int[3]{1, 2, 3};
    
    countUp(1);

    return 0;
}