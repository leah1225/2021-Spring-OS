#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define INTERVAL 20000

double circle_points = 0, total_points = 0, pi = 0;

/*  function for threads to random generate points
    and calculate the number of points in the circle  */
void *calcute_points(void *param)
{
    double x = 0, y = 0;

    // Initializing rand()
    srand(time(NULL));

    for(int i = 0; i < INTERVAL*INTERVAL; i++) // generate (x,y)
    {
        x =(rand() % (INTERVAL + 1)) / (double)INTERVAL;  // INTERVAL needs casting to double
        y = (rand() % (INTERVAL + 1)) / (double)INTERVAL;

        if(x*x+y*y <= 1) // square point
            circle_points ++;
        
        total_points ++;
    }
    pthread_exit(0);
}

int main(int argc , char *argv[])
{
    // the thread identifier
    pthread_t tid;

    // set of attributes for the thread
    pthread_attr_t attr;
    
    // get the default attributes
    pthread_attr_init(&attr);

    // create the thread
    pthread_create(&tid, &attr, calcute_points, argv[1]);

    // wait for the thread to exit
    pthread_join(tid, NULL);

    pi = 4*circle_points/total_points;

    printf("Estimation of Pi = %f\n", pi);
 
 
 return 0;   
}