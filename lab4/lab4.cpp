#include <iostream>
#include <fstream>
#include <pthread.h>

std::ofstream oddOutput("./oddOutput.txt");
std::ofstream evenOutput("./evenOutput.txt");

void *whriteInOddFile(void *arg) {
    std::string str = *reinterpret_cast<std::string*>( arg );
    oddOutput << str << std::endl;
    pthread_exit(0);
}

void *whriteInEvenFile(void *arg) {
    std::string str = *reinterpret_cast<std::string*>( arg );
    evenOutput << str << std::endl;
    pthread_exit(0);
}

int main() {

    std::ifstream source("./source.txt");
    
    std::string line;
    pthread_t t1, t2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    while (true)
    {
        std::string evenStr;
        std::string oddStr;
        bool oddFlag = true, evenFlag = true;

        if (std::getline(source, evenStr)) {
            pthread_create(&t1, &attr, whriteInEvenFile, &evenStr);
        } else {
            evenFlag = false;
        }
        
        if (std::getline(source, oddStr)) {
            pthread_create(&t1, &attr, whriteInOddFile, &oddStr);
        } else {
            oddFlag = false;
        }
        
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        if (!(evenFlag && oddFlag)) {
            break;
        }
    }
    
    return 0;
}