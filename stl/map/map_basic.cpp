#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> inventory;

    inventory["Sword"] = 1;      // 가장 직관적인 방법
    inventory.insert({"Shield", 5}); 

    std::cout << "Sword 개수: " << inventory["Sword"] << "\n";

    // it->first는 Key, it->second는 Value를 의미함
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        std::cout << "아이템: " << it->first << ", 수량: " << it->second << "\n";
    }

    return 0;
}