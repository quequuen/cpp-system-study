#include <iostream>
#include <cstdarg>

using namespace std;

double sum(int count, ...) {
    double total = 0;
    va_list args;      // 인자 목록을 저장할 변수
    va_start(args, count); // 시작 지점 설정

    for (int i = 0; i < count; ++i) {
        total += va_arg(args, double); // 하나씩 꺼내기 (타입 명시 필요)
    }

    va_end(args);      // 정리
    return total;
}

int main(int argc, char *argv[])
{

    cout << argc << endl;
    cout << argv << endl;
     
    for (int i = 0; i < argc; ++i)
    {
        string argv_value = argv[i];
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
        if(i == 1) // 인수 타입 변환 및 출력
        {
            int input_value = std::stoi(argv_value);
            cout << input_value + 1 << endl;
           
        }
        else cout << argv_value << endl;
    }


    return 0;
}