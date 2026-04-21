#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

int main()
{

    list<int> cont_list = {10, 20, 30};

    cont_list.push_front(40);
    cont_list.push_back(50);

    cout << "list 순회" << endl;

    for (auto itr = cont_list.begin(); itr != cont_list.end(); ++itr) cout << *itr << " ";

    cout << endl;

    vector<int> cont_vector;

    for(int i = 0; i < 10; ++i) cont_vector.push_back(i);

    cout << "\nvector 순회" << endl;

    for (auto itr = cont_vector.begin(); itr != cont_vector.end(); ++itr) 
        cout << *itr << " ";
    
    cout << endl;

    set<string> cont_set = {"ga", "na", "da", "da"};

    cout << "\nset 순회" << endl;

    for (auto itr = cont_set.begin(); itr != cont_set.end(); ++itr) 
        cout << *itr << " ";
    
    cout << endl;

    map<int, char> cont_map;
    for (int i = 0; i < 10; ++i) cont_map.insert(make_pair(i, char(i + 65)));

    cout << "\nmap 순회" << endl;

    for (auto itr = cont_map.begin(); itr != cont_map.end(); ++itr)
        cout << itr->first << " " << itr -> second << endl;

    return 0;
}
