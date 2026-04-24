#include <iostream>
#include <string>
#include <cstddef>
#include <locale>

int main (){
    
    std::wstring wstring;

    wchar_t wc; // 국제어를 표현할 때 사용. 국가별 설정 맞추는 게 번거로움.
    // 여러 나라에 서비스를 할 때.

    std::string s1 = "Hello";
    std::string s2 = "World";

    // 문자열 합치기
    std::string s3 = s1 + " " + s2; // "Hello World"

    // 길이 확인
    std::cout << "길이: " << s3.length() << std::endl; // 혹은 s3.size()

    // 특정 위치 문자 접근
    std::cout << "첫 글자: " << s3[0] << std::endl;

    // 문자열 비교 (==, !=, <, > 모두 가능)
    if (s1 == "Hello") {
        std::cout << "안녕" << std::endl;
    }

    // 부분 문자열 추출 (인덱스 6부터 5글자)
    std::string sub = s3.substr(6, 5); // "World"

    // 찾기
    size_t pos = s3.find("World");
    if (pos != std::string::npos) { // npos는 "못 찾음"을 뜻함
        std::cout << "World 발견 위치: " << pos << std::endl;
    }

    return 0;
}