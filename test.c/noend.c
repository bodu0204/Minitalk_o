#include <signal.h>
#include <stdio.h>
#include<unistd.h>
#include<limits.h>

void yes(int i)
{
	sigset_t s;

	printf("\n---signal handler(start)\n"); fflush(stdout);
	i = 0;
	while (i < INT_MAX)
	{
		i++;
	}
	sigfillset(&s);
	sigprocmask(SIG_BLOCK, &s, NULL);
	printf("\nsignal handler(end)\n"); fflush(stdout);
}

int main(void)
{
	void (*f) (int);
	sigset_t s;

	f = signal(SIGINT, yes);
	printf("SIG_ERR=%p\nSIG_DFL=%p\nSIG_IGN=%p\nf=%p\n", SIG_ERR, SIG_DFL, SIG_IGN, f);
	//f = signal(SIGINT, yes);
	//printf("SIG_ERR=%p\nSIG_DFL=%p\nSIG_IGN=%p\nf=%p\n", SIG_ERR, SIG_DFL, SIG_IGN, f);
	sigfillset(&s);
	while (1)
	{
		printf("---SIGINT is ok\n"); fflush(stdout);
		sigprocmask(SIG_UNBLOCK, &s, NULL);
		//signal(SIGINT, yes);
		sleep(15);
		printf("---masked if signal has come\n"); fflush(stdout);
		sleep(5);
	}
	return 0;
}
