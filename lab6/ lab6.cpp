#include <iostream>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <sys/wait.h>

int i = 0;
unsigned int end_time;

void alarmSignal(int signum) {
    pid_t childPid = fork();
    i++;
    
    if (childPid == 0) {
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        std::cout << "\nPID потомка = " << getpid();
        std::cout << "\nДата и время: " << asctime(timeinfo);
    
        exit(0);
    }
    wait(&childPid);
    end_time = clock();
}

int main(int argc, char **argv) {
    unsigned int start_time =  clock();
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGTSTP);
    sigprocmask(SIG_SETMASK, &mask, nullptr);
    
    signal(SIGALRM, alarmSignal);

    int period = atoi(argv[1]);
    int startCount = atoi(argv[2]);

    itimerval value, ovalue;

    value.it_interval.tv_sec = period;
    value.it_interval.tv_usec = 0;
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 1;

    
   
    setitimer(ITIMER_REAL, &value, &ovalue);
    while (i < startCount) {}
   
    unsigned int search_time = end_time - start_time;
    std::cout << "\nЗатраченное время: " << search_time/1000.0;
    return 0;
}