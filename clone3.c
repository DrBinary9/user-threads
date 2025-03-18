#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdint.h>
#include <linux/sched.h>

int fun(void *arg) { 
    printf("Hello from child fun, PID: %d\n", getpid());
    return 0;
}

int main() {
    int *dumb_pointer = (int *)malloc(1024);

    struct clone_args args;

    args.flags = CLONE_VM | CLONE_SIGHAND | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID;
    args.pidfd = 0;
    args.child_tid = NULL;
    args.parent_tid = NULL;
    args.exit_signal = 0;
    args.stack = dumb_pointer + 1024;
    args.stack_size = 1024;
    args.tls = NULL;
    //args.set_tid = NULL;
    //args.set_tid_size = 0;
    //args.cgroup = 0;
    
    pid_t pid = syscall(SYS_clone3, &args, sizeof(struct clone_args));

    if (pid < 0) { 
        perror("something went wrong...");
    }
    if (pid > 0) { 
        printf("Parent PID: %d\n", getpid());
    } else { 
        printf("Child PID: %d\n", getpid());
    }

    sleep(1);
    free(dumb_pointer);

    return 0; 
}

