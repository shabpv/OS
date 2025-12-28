#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string line;
    getline(cin, line);

    istringstream iss(line);
    int x, sum = 0;
    while (iss >> x) {
        sum += x;
    }
    cout << sum << endl;

    return 0;
}