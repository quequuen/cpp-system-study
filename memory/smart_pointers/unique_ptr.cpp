template <typename T>
class unique_ptr {
    T* ptr; // 실제 데이터의 주소를 들고 있는 원시 포인터
public:
    // 복사 생성자 & 복사 대입은 삭제 (Delete)
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // 이동 생성자: &&를 사용해 소유권을 뺏어옴
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr; // 원본의 연결을 끊음
    }

    ~unique_ptr() {
        delete ptr; // 소멸 시 자동을 메모리 해제.
    }
};