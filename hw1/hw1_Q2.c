#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_SEQUENCE 10

typedef struct{
    long fib_sequence[MAX_SEQUENCE];
    int sequence_size;
} shared_data;

int main(int argc , char *argv[]) {
    
    //check to validate atleast two arguments
    if(argc != 2) {
        printf("Missing arg\n");
        exit(0);
    }
	
	// a. Error checking to ensure the parameter is <= MAX_SEQUENCE
	if(atoi(argv[1]) > MAX_SEQUENCE){
	    printf("Max Input Size: %d\n", MAX_SEQUENCE);
        exit(0);
	}

    // b. Create a shared-memory segment of size shared_data
    int shm_fd;
    shared_data *shared_mem;
    const char *name = "OS";
    int SIZE = sizeof(shared_data);

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE); 
	
    // c. Attach the shared-memory segment to its address space
    shared_mem = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // d. Set the value of sequence_size to the parameter in the cmd
    shared_mem->sequence_size = atoi(argv[1]);

    // e. Fork the child process and invoke the wait() sys call to wait for the child to finish
	pid_t pid;
    pid = fork();

    int fib_0 = 0, fib_1 = 1;

    if(pid < 0){
	    printf("Fork Failed\n");
	    return 1;
	}
    else if(pid == 0){ //c hild process
        shared_mem->fib_sequence[0] = fib_1;

        for(int i = 1; i < shared_mem->sequence_size; i++){
            shared_mem->fib_sequence[i] = fib_0 + fib_1;
            fib_0 = fib_1;
            fib_1 = shared_mem->fib_sequence[i];
        }
    }
    else{ // parent process
        wait(NULL);
        // f. Output the value of Fibonacci sequence in the shared-memory sequence
        for(int i = 0; i < shared_mem->sequence_size; i++){
            if(i == shared_mem->sequence_size-1){
                printf("%ld", shared_mem->fib_sequence[i]);
            }
            else{
                printf("%ld," ,shared_mem->fib_sequence[i]);
            }
        }
    // g. Detach and remove the shared-memory segment to its address space
    shm_unlink(name);
    }

	return 0;
}
