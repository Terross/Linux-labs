#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iomanip>

int main(int argc, char *argv[]) {
    std::ofstream outputFile;
    outputFile.open(argv[1], std::ios_base::app);
    sleep(atoi(argv[2]));
    outputFile 
                << "\nChild 2 data:"
                << "\nSleep: " << atoi(argv[2])
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
}