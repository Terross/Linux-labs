#include <iostream>
#include <signal.h>

void zeroError(int signum) {
    std::cout << "Деление на ноль";
    exit(1);
}

void memoryError(int signum) {

    std::cout << "Нарушение защиты памяти";
    exit(2);
}

int main() {
    int errorType;

    std::cout << "1 - деление на ноль\n"
              << "2 - нарушение защиты памяти\n>>";

    std::cin >> errorType;

    signal(SIGFPE, zeroError);
    signal(SIGSEGV, memoryError);

    switch (errorType) {
        case 1: {
            int x = 1/0;
            break;
        }

        case 2: {
            int *ptr = nullptr;
            std::cout << ptr[5];
            break;
        }

    }
    return 0;
}