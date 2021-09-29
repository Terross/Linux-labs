#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iomanip>

int main(int argc, char **argv) {
    std::string fileName;
    int parentDelay = atoi(argv[1]),
        child1Delay = atoi(argv[2]),
        child2Delay = atoi(argv[3]);
    std::cout << "Enter output file name: ";
    std::cin >> fileName;

    std::ofstream outputFile;

    outputFile.open(fileName);
    outputFile << "Задержки: " << "\nParent: " << parentDelay <<
                    "\nChild1: " << child1Delay <<
                    "\nChild2: " << child2Delay;
    outputFile.close();

    int child1 = fork();
    if (child1 == 0) {
        sleep(child1Delay);
        outputFile.open(fileName, std::ios_base::app);
        outputFile 
                << "\nChild 1 data:"
                << "\nSleep: " << child1Delay
                << "\nИндентификатор процесса: " << getpid()
                << "\nИдентификатор предка: " << getppid()
                << "\nИдентификатор сессии процесса: " << getsid(getpid())
                << "\nИдентификатор группы процессов: " << getpgid(getpid())
                << "\nРеальный идентификатор пользователя: " << getuid()
                << "\nЭффективный идентификатор пользователя: " << geteuid()
                << "\nРеальный групповой идентификатор: " << getgid()
                << "\nЭффективный групповой идентификатор: " << getegid() << std::endl;
        outputFile.close();
        exit(EXIT_SUCCESS);
    } else {
        int child2 = vfork();
        if (child2 == 0) {
            execl("child","child", fileName.c_str(), argv[3], NULL);
        } else {
            sleep(parentDelay);
            outputFile.open(fileName, std::ios_base::app);
            outputFile
                    << "\nParent data:"
                    << "\nSleep: " << parentDelay
                    << "\nИндентификатор процесса: " << getpid()
                    << "\nИдентификатор предка: " << getppid()
                    << "\nИдентификатор сессии процесса: " << getsid(getpid())
                    << "\nИдентификатор группы процессов: " << getpgid(getpid())
                    << "\nРеальный идентификатор пользователя: " << getuid()
                    << "\nЭффективный идентификатор пользователя: " << geteuid()
                    << "\nРеальный групповой идентификатор: " << getgid()
                    << "\nЭффективный групповой идентификатор: " << getegid() << std::endl;
            outputFile.close();
        
        }
        
    }
    
    return 0;
}