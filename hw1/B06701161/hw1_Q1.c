#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc , char *argv[]) {
	
	pid_t pid;
	int k = 0, fib_0 = 0, fib_1 = 1;
	
	// Error checking...
	if(argc < 2){
	    printf("Missing arg\n");
	    exit(0);
	}
	
	if(atoi(argv[1]) < 0){
	    printf("Negative number\n");
	    exit(0);
	}
	
	pid = fork(); // create child process
	
	if(pid < 0){
	    printf("Fork Failed\n");
	    return 1;
	}
	else if(pid == 0){//child process
	    k = atoi(argv[1]);
	    int fib[k+1];
	    
	    fib[0] = fib_1;
	    
	    for(int i = 1; i < k; i++){
	        fib[i] = fib_0 + fib_1;
	        fib_0 = fib[i-1];
	        fib_1 = fib[i];
	    }
	    
	    for(int i = 0; i < k; i++){
	        if(i == k-1){
	            printf("%d", fib[i]);
	        }
	        else{
	            printf("%d,", fib[i]);
	        }
	    }
	}
	else{//parent process
	    wait(NULL);
	    //printf("Done\n");
	}
	
	return 0;
}