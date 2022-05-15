#include <signal.h>
#include <stdio.h>
#include<unistd.h>
#include<limits.h>

void yes(int i, siginfo_t *info, void *context)
{
	(void)context;
	printf("\n---signal handler(start)\nPID:%d\n", (int)(info->si_pid)); fflush(stdout);
	i = 0;
	while (i < INT_MAX)
	{
		i++;
	}
	printf("\nsignal handler(end)\n"); fflush(stdout);
}

int main(void)
{
	struct sigaction seta;
	struct sigaction act;
	struct sigaction notact;

	//sigemptyset(&(seta.sa_mask));
	//seta.sa_flags = SA_SIGINFO;
	//seta.sa_sigaction = yes;
	//sigaction(SIGINT, &seta, NULL);
	sigemptyset(&(act.sa_mask));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = yes;
	sigemptyset(&(notact.sa_mask));
	sigaddset(&(notact.sa_mask), SIGINT);
	notact.sa_sigaction = NULL;
	notact.sa_flags = SA_SIGINFO;
	while (1)
	{
		printf("---SIGINT is ok\n"); fflush(stdout);
		sigaction(SIGINT, &act, NULL);
		//sigaction(SIGINT, &seta, NULL);
		sleep(5);
		printf("---SIGINT is masked\n"); fflush(stdout);
		signal(SIGINT, SIG_IGN);
		sleep(5);
	}
	return 0;
}
