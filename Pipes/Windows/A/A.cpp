#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Ошибка: укажите N как аргумент" << endl;
        return 1;
    }

    int N = stoi(argv[1]);

    string line;
    getline(cin, line);

    istringstream iss(line);
    int x;
    while (iss >> x) {
        cout << x + N << " ";
    }
    cout << endl;

    return 0;
}