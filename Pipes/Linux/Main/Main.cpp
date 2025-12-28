#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cout << "¬ведите ваш номер в списке (N): ";
    cin >> N;
    cin.ignore();

    const int NUM_PROCESSES = 4;
    const int NUM_PIPES = NUM_PROCESSES + 1;
    int pipefd[NUM_PIPES][2];

    for (int i = 0; i < NUM_PIPES; i++) {
        if (pipe(pipefd[i]) == -1) {
            perror("pipe failed");
            exit(1);
        }
    }

    string exes[NUM_PROCESSES] = { "./M", "./A", "./P", "./S" };

    pid_t pids[NUM_PROCESSES];

    for (int i = 0; i < NUM_PROCESSES; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork failed");
            exit(1);
        }
        else if (pids[i] == 0) {
            for (int j = 0; j < NUM_PIPES; j++) {
                if (j != i) close(pipefd[j][0]);
                if (j != i + 1) close(pipefd[j][1]);
            }
            dup2(pipefd[i][0], 0);
            dup2(pipefd[i + 1][1], 1);
            close(pipefd[i][0]);
            close(pipefd[i + 1][1]);

            if (exes[i] == "./A") {
                execl(exes[i].c_str(), "A", to_string(N).c_str(), (char*)NULL);
            }
            else {
                execl(exes[i].c_str(), exes[i].substr(2).c_str(), (char*)NULL);
            }
            perror("execl failed");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_PIPES; i++) {
        if (i < NUM_PIPES - 1) close(pipefd[i][0]);
        if (i > 0) close(pipefd[i][1]);
    }

    string input = "1 2 3 4 5\n";
    write(pipefd[0][1], input.c_str(), input.length());
    close(pipefd[0][1]);

    char buffer[1024];
    ssize_t nread = read(pipefd[NUM_PIPES - 1][0], buffer, sizeof(buffer) - 1);
    if (nread > 0) {
        buffer[nread] = '\0';
        cout << "–езультат работы цепочки: " << buffer << endl;
    }
    else {
        perror("read failed");
    }
    close(pipefd[NUM_PIPES - 1][0]);

    for (int i = 0; i < NUM_PROCESSES; i++) {
        waitpid(pids[i], NULL, 0);
    }

    return 0;
}