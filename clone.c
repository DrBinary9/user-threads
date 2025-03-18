#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int child_function(void *arg) {
    printf("Hello from child function CID: %d\n", getpid());
    return 0;
}

int main() {
    int *st = (int *)malloc(1024); //top most location  

    int flags = CLONE_VM | CLONE_SIGHAND | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID;
    pid_t pid = clone(child_function, st+(1024), flags, NULL);

    if (pid < 0) {
        perror("clone error");
    }
    if (pid > 0) {
        printf("Parent PID: %d\n", getpid());
    } else {
        printf("Child PID: %d\n", getpid());
    }
    sleep(1); 
    free(st);

    return 0;
}

