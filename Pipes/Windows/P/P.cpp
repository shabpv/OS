#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string line;
    getline(cin, line);

    istringstream iss(line);
    int x;
    while (iss >> x) {
        cout << (x * x * x) << " ";
    }
    cout << endl;

    return 0;
}