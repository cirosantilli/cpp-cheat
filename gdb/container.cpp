/*
- https://stackoverflow.com/questions/11606048/how-to-pretty-print-stl-containers-in-gdb
- https://stackoverflow.com/questions/253099/how-do-i-print-the-elements-of-a-c-vector-in-gdb
- https://stackoverflow.com/questions/427589/inspecting-standard-container-stdmap-contents-with-gdb
*/

#include <map>
#include <utility>
#include <vector>

int main() {
    std::vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    std::map<int,int> m;
    m.insert(std::make_pair(0, 0));
    m.insert(std::make_pair(1, -1));
    m.insert(std::make_pair(2, -2));
}
