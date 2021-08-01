#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

# define INTERVAL 1000       // each thread generates 1000 random points
# define NUMBER_OF_THREADS 5  // 5 sub threads

double circle_points = 0, total_points = NUMBER_OF_THREADS*INTERVAL, pi = 0; // global variables
pthread_mutex_t mutex;

/*  function for threads to random generate points
    and calculate the number of points in the circle  */
void *calcute_points(void *param)
{
    double x = 0, y = 0 , in_circle = 0;
    // Initializing rand()
    srand(time(NULL));

    for(int i = 0; i < INTERVAL; i++) // generate (x,y) for 1000 times
    {
        x =(rand() % (INTERVAL + 1)) / (double)INTERVAL;  // INTERVAL needs casting to double
        y = (rand() % (INTERVAL + 1)) / (double)INTERVAL;

        if(x*x+y*y <= 1) // circle point
            in_circle ++;
    }
    
    // no race condition on updates to circle_points
    pthread_mutex_lock(&mutex);
    circle_points += in_circle;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

int main(int argc , char *argv[])
{
    /* Generating threads */
    // the thread identifiers
    pthread_t tid[NUMBER_OF_THREADS];

    // set of attributes for the thread
    pthread_attr_t attr;
    
    // get the default attributes
    pthread_attr_init(&attr);

    pthread_mutex_init(&mutex, NULL);

    /* Calculates circle points */
    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_create(&tid[i], &attr, calcute_points, argv[1]);
    }

    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    /* Main thread calculates estimated pi*/
    pi = 4*circle_points/total_points;
    printf("Estimation of Pi = %f\n", pi);


    return 0;
}