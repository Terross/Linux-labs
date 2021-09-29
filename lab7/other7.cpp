#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
int main() {
    sigset_t new_mask;
	sigemptyset(&new_mask);
	sigaddset(&new_mask, SIGUSR1);
	sigaddset(&new_mask, SIGUSR2);
	sigprocmask(SIG_SETMASK, &new_mask, NULL);
    int fildes[2];

    if (pipe(fildes) == -1) {
        std::cout << "Error!";
        return -1;
    }

    pid_t child1,
          child2;
    switch (child1 = fork()) {
    case -1: {
        std::cout << "Error!";
        break;
    }
        
    case 0: {
        close(fildes[1]);

		sigset_t mask;
		sigemptyset(&mask);
		sigaddset(&mask, SIGUSR1);
		int sig;

		std::ofstream out1;
		char c;
		out1.open("output1.txt", std::ios::app);

		if (!out1.is_open()) {
			std::cout<<"Не удалось открыть файл."<< std::endl;
			return 1;
		}

		while(read(fildes[0], &c, 1) > 0){
			out1 << c << std::endl;
			killpg(0, SIGUSR2);
			sigwait(&mask, &sig);
		}
		killpg(0, SIGUSR2);


		close(fildes[0]);
		_exit(EXIT_SUCCESS);
    }
    

    default:
        switch (child2 = fork()) {
        case -1: {
            std::cout << "Error!";
            break;
        }
        case 0: {
            close(fildes[1]);

			sigset_t mask;
			sigemptyset(&mask);
			sigaddset(&mask, SIGUSR2);
			int sig;

			std::ofstream out2;
			char c;
			out2.open("output2.txt", std::ios::app);

			if (!out2.is_open()) {
				std::cout<<"Не удалось открыть файл."<< std::endl;
				return 1;
			}

			sigwait(&mask, &sig);
			while(read(fildes[0], &c, 1) > 0){
				out2 << c << std::endl;
				killpg(0, SIGUSR1);
				sigwait(&mask, &sig);
			}
			killpg(0, SIGUSR1);

			close(fildes[0]);
			_exit(EXIT_SUCCESS);

        }
        default:
            if (close(fildes[0]) == -1) {
                std::cout<<"Error!";
            }

            std::ifstream inputFile("input.txt");
            std::string str;
            while (getline(inputFile, str)) {
                std::cout << str.length();
                write(fildes[1], &str[0], str.length());
            }
            inputFile.close();

            if (close(fildes[1]) == -1) {
                std::cout<<"Error!";
            }
            waitpid(child1, nullptr, 0);
            waitpid(child2, nullptr, 0);
            exit(EXIT_SUCCESS);
            break;
        }
        break;
    }

    return 0;
}