#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <unistd.h>
#include <sys/syscall.h>

#define NUM_THREADS 3
#define STACK_SIZE 8192

ucontext_t ctx[NUM_THREADS];
ucontext_t main_ctx;
int cur = 0;
char stacks[NUM_THREADS][STACK_SIZE];

long get_tid() {
    return syscall(SYS_gettid);
}

void thread_main(int id) {
    while(1) {
        printf("User Thread ID: %d | OS PID: %d | OS TID: %ld\n", id, getpid(), get_tid());

        // Round-robin yield logic
        int prev = cur;
        cur = (cur + 1) % NUM_THREADS;
        swapcontext(&ctx[prev], &ctx[cur]);
    }
}

int main() {
    for(int i = 0; i < NUM_THREADS; i++) {
        getcontext(&ctx[i]);
        ctx[i].uc_stack.ss_sp = stacks[i];
        ctx[i].uc_stack.ss_size = STACK_SIZE;
        ctx[i].uc_link = &main_ctx;
        makecontext(&ctx[i], (void (*)(void))thread_main, 1, i);
    }

    printf("Starting user-level threads...\n");
    swapcontext(&main_ctx, &ctx[0]);
    return 0;
}