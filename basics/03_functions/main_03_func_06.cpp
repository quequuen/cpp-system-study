#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    cout << argc << endl;
    cout << argv << endl;
     
    for (int i = 0; i < argc; ++i)
    {
        string argv_value = argv[i];

        if(i == 1) 
        {
            int input_value = std::stoi(argv_value);
            cout << input_value + 1 << endl;
           
        }
        else cout << argv_value << endl;
    }
    return 0;
}