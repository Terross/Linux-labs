#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <signal.h>
#include <wait.h>

int fieldRead;

void sigUsr2Handler(int sig) {
    char ch;
    std::ofstream output2("output2.txt", std::ios::app);
    if (read(fieldRead, &ch, 1) > 0) {
        output2 << ch << std::endl;
        output2.close();
        //signal(SIGUSR2, sigUsr2Handler);
        kill(0, SIGUSR1);
    } else {
        std::ofstream output2("output2.txt", std::ios::app);
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
    // sigaddset(&mask, SIGUSR1);
    // sigaddset(&mask, SIGQUIT);
	// sigprocmask(SIG_SETMASK, &mask, NULL);
 
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigUsr2Handler;
    sigset_t   set; 
    sigemptyset(&set);                                                             
    sigaddset(&set, SIGUSR1); 
    sigaddset(&set, SIGQUIT);
    act.sa_mask = set;
    sigaction(SIGUSR2, &act, 0);

    //signal(SIGUSR2, sigUsr2Handler);

    pause();
}