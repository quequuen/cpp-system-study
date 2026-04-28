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
    
    // std::cout << vec_str << std::endl;
    // vector는 배열이기 때문에 << 가 정의 되어있지 않으면 출력 안됨. for문 돌려야 함.


    for (auto a: vec_str) std::cout << a;

    std::cout << std::endl;

    // 생성자를 이용한 copy는 깊은 복사!
    std::string s4(vec_str.begin(), vec_str.end());
    std::string s5(vec_str.begin(), std::find(vec_str.begin(), vec_str.end(), ','));;

    std::cout << "원본 주소: " << &vec_str << std::endl;
    std::cout << "복본 주소: " << &s4 << std::endl;

    vec_str[2] = 'L' ;

    for (auto a: vec_str) std::cout << a;

    std::cout << std::endl;

    
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

    std::string s8("012345678");
    s8.reserve(1000);

    // bool 값 true/false로 출력하게 설정
    std::cout << std::boolalpha;
    
    // 현재 문자열의 실제 길이를 반환
    std::cout << s8.length() << std::endl;

    // length()와 완전히 동일함 
    // STL 컨테이너들과의 일관성을 위해 존재
    std::cout << s8.size() << std::endl;

    // 새로 메모리를 할당하지 않고도 담을 수 있는 최대 용량 
    // 실제 글자 수보다 크거나 같음. 여유 공간을 포함함
    std::cout << s8.capacity() << std::endl;

    // 시스템 (OS/컴파일러)에서 이론적으로 가질 수 있는 문자열의 최대 길이
    std::cout << s8.max_size() << std::endl;

    std::ostringstream oss;
int age = 27;
std::string name = "Han GaYeon";

// cout처럼 << 연산자를 사용함
oss << "이름: " << name << ", 나이: " << age;

// 문자열로 변신
std::string result = oss.str();
std::cout << result << std::endl; // "이름: Han GaYeon, 나이: 27"

std::string data = "222 3.14 Hello";
std::istringstream iss(data); // 문자열을 스트림에 넣음

int n;
double d2;
std::string s;

// cin처럼 >> 연산자를 사용하여 데이터를 뽑아냄
iss >> n >> d2 >> s;
// 데이터를 넣을 때 순서를 지켜야 함.

std::cout << n << " / " << d2 << " / " << s << std::endl;
// 출력: 222 / 3.14 / Hello

// std::cout << typeid(s).name() << std::endl;

    return 0;
}