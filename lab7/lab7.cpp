#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int main() {
    sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
	sigprocmask(SIG_SETMASK, &mask, NULL);

    int fildes[2];

    if (pipe(fildes) == -1) {
        std::cout << "Error!";
        return -1;
    }

    pid_t child1 = fork();
   
    if (child1 == 0) {
        execl("child1","child1",&fildes[1], &fildes[0], NULL);
    } else {
        
        pid_t child2 = fork();
        if (child2 == 0) {
            execl("child2", "child2", &fildes[1], &fildes[0], NULL);
        } else {
            std::ifstream inputFile("input.txt");
            std::string str;
            while (getline(inputFile, str)) {
                write(fildes[1], &str[0], str.length());
            }
            for (int i = 0; i < 5; i++) {
                char ch;
                read(fildes[0], &ch, 1);
                std::cout << ch;
            }
            inputFile.close();
            sleep(1);
            kill(0, SIGQUIT);
    
            if (close(fildes[1]) == -1) {
                std::cout<<"Error!";
            }
            sleep(2);
            while(wait(NULL) != -1) {
                std::cout<<112312;
            }
        }
    }
    return 0;
}