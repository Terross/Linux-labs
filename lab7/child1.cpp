#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <signal.h>
#include <wait.h>

int fieldRead;
void sigQuitHandler(int sig) {
    kill(getpid(), SIGUSR1);
}

void sigUsr1Handler(int sig) {
    char ch;
    std::ofstream output1("output1.txt", std::ios::app);
    if (read(fieldRead, &ch, 1) > 0) {
        output1 << ch << std::endl;
        output1.close();
        kill(0, SIGUSR2);
    } else {
        std::ofstream output2("output1.txt", std::ios::app);
        output2 << 12131231;
        output2.close();
        close(fieldRead);
        exit(EXIT_SUCCESS);
    }
    
}

int main(int argc, char** argv) {
    int fieldWrite = *argv[1];
    fieldRead = *argv[2];
    close(fieldWrite);

    // sigset_t mask;
	// sigemptyset(&mask);
    // sigaddset(&mask, SIGUSR2);
	// sigprocmask(SIG_SETMASK, &mask, NULL);
    // signal(SIGQUIT, sigQuitHandler);
    // signal(SIGUSR1, sigUsr1Handler);

    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigUsr1Handler;
    sigset_t   set; 
    sigemptyset(&set);                                                             
    sigaddset(&set, SIGUSR2); 
    act.sa_mask = set;
    sigaction(SIGUSR1, &act, 0);

    pause();
}