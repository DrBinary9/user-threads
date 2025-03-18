#ifndef UTHREAD_H
#define UTHREAD_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>  

#define STACK_SIZE 1024 * 1024  

typedef pid_t uthread_t;

typedef struct uthread {
    uthread_t tid;         
    void *(*start_routine)(void *);  
    void *arg;              
    void *stack_base;      
    size_t stack_size;     
} uthread;

int uthread_create(uthread_t *thread, void *(*start_routine)(void *), void *arg);

#endif 
