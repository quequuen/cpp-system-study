#include <iostream>
#include <string>
#include <cstddef>
#include <locale>
#include <vector>
#include <sstream>
#include <iomanip>

// 어떤 타입이 들어오든 string 타입으로 바꾸어서 반환
template <typename T>
std::string ToString(T x)
{
    std::ostringstream osstream;
    osstream << std::setprecision(10);
    osstream << x;
    return osstream.str();
}

// x 타입으로 변환이 가능한지를 판별 후 bool 타입 반환
template <typename T>
bool FromString(const std::string & str, T &x)
{
    std::istringstream isstream(str);
    return (isstream >> x) ? true : false; 
}

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

    std::vector<char> vec_str;

    for(auto a: "Hello, World!") vec_str.push_back(a);

    // 이건 얕은 복사인지 깊은 복사인지 확인해보기
    // 아마 둘 다 참조형이라서 얕은 복사일 것 같다!
    std::string s4(vec_str.begin(), vec_str.end());
    std::string s5(vec_str.begin(), std::find(vec_str.begin(), vec_str.end(), ','));;

    std::cout << s4 << std::endl;
    std::cout << s5 << std::endl;

    std::string s6(std::to_string(4));

    std::cout << s6 << std::endl;

    float f = std::stof(s6);

    std::cout << f << std::endl;

    std::string s7(ToString(200006.30));

    std::cout << s7 << std::endl;

    double d;
    if (FromString(s7, d)) std::cout << d << std::endl;
    else std::cout << "double 변환 실패" << std::endl;
    
    // 문자열은 double로 변환 안됨
    if (FromString(s5, d)) std::cout << d << std::endl;
    else std::cout << "double 변환 실패" << std::endl;


    return 0;
}