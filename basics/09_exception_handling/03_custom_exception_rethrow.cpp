#include <iostream>
#include <stdexcept>
#include <string>

class NetworkException : public std::runtime_error 
{
    public:
        NetworkException(const std::string& msg): std::runtime_error(msg){}
       
};

void connectServer()
{
    throw NetworkException("서버 응답 시간이 초과되었습니다.");
}

void processNetwork()
{
    try
    {
        connectServer();
    }
    catch(NetworkException& e)
    {
        std::cout << "[로그 기록]: 내부 함수에서 에러 감지 -> " << e.what() << std::endl;

        // rethrow: main에서 catch
        throw;
    }
}


int main()
{
    /*
    try
    {
        connectServer();
    }
    // 자식의 예외 처리를 먼저 기입하여야 한다. 
    catch(NetworkException& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    */

    try
    {
        processNetwork();
    }
    catch(const std::exception& e)
    {
        std::cerr << "[최종 에러 메시지]: " << e.what() << '\n';
        std::cerr << "서버 상태를 확인하고 다시 시도해 주세요." << std::endl;
    }
    
    
    return 0;
}