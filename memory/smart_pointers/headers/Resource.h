#pragma once
// #ifndef RESOURCE_H
// #define RESOURCE_H

#include <iostream>

class Resource
{
    private:
    int* data;
    size_t size;

    public:
    Resource(size_t n); // 생성자
    ~Resource(); // 소멸자

    // 이동 생성자 (Move Constructor)
    Resource(Resource&& other) noexcept;

    // 이동 대입 연산자 (Move Assignment Operator)
    Resource& operator = (Resource&& other) noexcept;

    void printStatus() const;
};

// #endif