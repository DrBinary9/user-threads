#include "include/uthread.h"

int uthread_create(uthread_t *thread, void *(*start_routine)(void *), void *arg) {
    void *stack = malloc(STACK_SIZE);
    if (stack == NULL) {
        return EAGAIN; 
    }

    int flags = CLONE_SIGHAND | CLONE_VM | CLONE_FS | CLONE_FILES; 

    int (*clone_func)(void *) = (int (*)(void *))start_routine;

    pid_t pid = clone(clone_func, stack + STACK_SIZE, flags, arg);

    if (pid == -1) {
        free(stack); 
        return EAGAIN;
    }

    *thread = pid;

    return 0;
}

void *thread_func(void *arg) {
    printf("Arg: %s\n", (char *)arg);
    return NULL;
}

int main() {
    uthread_t thread_id;

    char *arg = "Hello";
    int result = uthread_create(&thread_id, thread_func, (void *)arg);

    if (result == 0) {
        printf("Thread created successfully! Thread ID: %ld\n", (long)thread_id);
    } else {
        perror("uthread_create");
    }

    sleep(1);

    return 0;
}

