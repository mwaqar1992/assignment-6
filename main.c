#include <stdio.h>
#include <thread.h>
#include <avr/io.h>
#include <util/delay.h>
#include <mutex.h>
#include <xtimer.h>
#include<unistd.h>

mutex_t busy;


struct params
{
        int a,b,c;
};

struct params and_param;

//mutex_t busy = MUTEX_INITIALIZER;


int gpio_init(gpio_t 10,gpio_mode_t GPIO_IN_PU);
int gpio_init(gpio_t 11,gpio_mode_t GPIO_IN_PU);
int gpio_init(gpio_t 12,gpio_mode_t GPIO_OUT);

void * AND_Inputs(void* arg)
{
	(void)arg;
	while(1)
	{
 

        mutex_lock (&busy);
        and_param.a = gpio_t 10;
        and_param.b = gpio_t 12;
        mutex_unlock (&busy);
      xtimer_usleep(1000);
	}

}


void * AND_Process(void* arg)
{
	(void)arg;
	while(1)
	{
        mutex_lock (&busy);

        and_param.c = and_param.a & and_param.b;
	gpio_t 12 =  and_param.c;

        mutex_unlock (&busy);
      xtimer_usleep(250);
	}
}


void * AND_Output(void* arg)
{
	(void)arg;

	while(1)
	{
        mutex_lock (&busy);

        printf("Output %d \n\r", and_param.c);

        mutex_unlock (&busy);

      xtimer_usleep(1000);
	}
}

char t1_stack[THREAD_STACKSIZE_MAIN];
char t2_stack[THREAD_STACKSIZE_MAIN];
char t3_stack[THREAD_STACKSIZE_MAIN];


int main(void)
{
	mutex_init(&busy);

	
        thread_create (t1_stack, sizeof(t1_stack), THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_WOUT_YIELD,  AND_Inputs, NULL, NULL);
	thread_create (t2_stack, sizeof(t2_stack), THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_WOUT_YIELD,  AND_Process, NULL, NULL);
	thread_create (t3_stack, sizeof(t3_stack), THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_WOUT_YIELD,  AND_Output, NULL, NULL);

        return 0;
}


