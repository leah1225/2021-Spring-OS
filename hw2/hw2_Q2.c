#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define MAX 10 // total number of values
#define NUMBER_OF_THREADS 3 // total number of threads(2 sort thread + 1 merge thread)

int unsorted[MAX]; // storing unsorted values
int sorted[MAX]; // sotring sorted values

void *sorting(void *params); // sorting function for threads
void *merging(void *params); // merging function for threads

// a structure to pass down starting and ending indices for sorting
typedef struct
{
    int from_index;
    int to_index;
} parameters;


int main(int argc , char *argv[])
{
    // Generate 10 random values
    srand(time(NULL));
    for(int i = 0; i < MAX; i++) 
    {
        unsorted[i] = rand()%100;
        //printf("%d\n", unsorted[i]);
    }

    /* Generating threads */
    // the thread identifiers
    pthread_t tid[NUMBER_OF_THREADS];
    
    // set of attributes for the thread
    pthread_attr_t attr;
    
    // get the default attributes
    pthread_attr_init(&attr);

    // the first sorting thread
    parameters *index_1 = (parameters*) malloc(sizeof(parameters));
    index_1->from_index = 0;
    index_1->to_index = (MAX/2) - 1;
    pthread_create(&tid[0], &attr, sorting, index_1);

    // the second sorting thread
    parameters *index_2 = (parameters*) malloc(sizeof(parameters));
    index_2->from_index = MAX/2;
    index_2->to_index = MAX - 1;
    pthread_create(&tid[1], &attr, sorting, index_2);

    // wait for the two sorting thread to finish
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    
    // the merge thread
    parameters *index_3 = (parameters*) malloc(sizeof(parameters));
    index_3->from_index = 0;
    index_3->to_index = MAX/2;
    pthread_create(&tid[2], &attr, merging, index_3);

    // wait for the merge thread to finish
    pthread_join(tid[2], NULL);

    // output result
    for(int i = 0; i < 10; i++)
    {
        if(i != 9)
            printf("%d%s", sorted[i], " ");
        else
            printf("%d", sorted[i]);
    }

    return 0;
}

void *sorting(void *params)
{
    parameters* p = (parameters *)params;

    int start = p->from_index;
    int end = p->to_index;

    for(int i = start; i <= end; i++)
    {
        for(int j = start; j < end; j++)
        {
            if(unsorted[j] > unsorted[j+1])
            {
                int temp = unsorted[j];
                unsorted[j] = unsorted[j+1];
                unsorted[j+1] = temp;
            }
        }
    }
   pthread_exit(0);
}

void *merging(void *params)
{
    parameters* p = (parameters *)params;
    
    int i = 0,j = 0;
    i = p->from_index;
    j = p->to_index;
  
   int position = 0;  // position being inserted into result
  
   while (i < p->to_index && j < MAX) 
   {
       if (unsorted[i] <= unsorted[j])
           sorted[position++] = unsorted[i++];
       else
           sorted[position++] = unsorted[j++];
   }
      
   // copy the remainder
   if (i < p->to_index)
   {
       while (i < p->to_index)
       {
           sorted[position++] = unsorted[i++];
       }
   }
   else {
       while (j < MAX)
       {
           sorted[position++] = unsorted[j++];
       }
   }
   pthread_exit(0);
}