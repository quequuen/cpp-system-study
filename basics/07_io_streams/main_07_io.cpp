#include <iostream> // cout, cin, endl 등 입출력 스트림 라이브러리 포함
#include <cstdio> // printf, scanf 함수 사용을 위한 C 표준 입출력 라이브러리 포함

int main(){

    int x = 123;
    double y = 3.141592;

    std::cout << "I love this!\n" << std::endl;
    // endl: end line, 줄바꿈 문자 출력 후 버퍼 비우기 (출력 대기 중인 내용 강제 출력)

    std::cout << "x = " << x << ", pi = " << y << std::endl;

    std::cout << "abc" << "\t" << "def" << std::endl;
    



    return 0;
}