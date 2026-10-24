#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define K 5

typedef struct {
    int buf[K];
    int in, out, count;
    pthread_mutex_t mutex;
    pthread_cond_t notFull;
    pthread_cond_t notEmpty;
} Queue;

void q_init(Queue *q) {
    q->in = 0; q->out = 0; q->count = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->notFull, NULL);
    pthread_cond_init(&q->notEmpty, NULL);
}

void put(Queue *q, int val) {
    pthread_mutex_lock(&q->mutex);
    while (q->count == K)
        pthread_cond_wait(&q->notFull, &q->mutex);
    q->buf[q->in] = val;
    q->in = (q->in + 1) % K;
    q->count++;
    pthread_cond_signal(&q->notEmpty);
    pthread_mutex_unlock(&q->mutex);
}

int get(Queue *q) {
    pthread_mutex_lock(&q->mutex);
    while (q->count == 0)
        pthread_cond_wait(&q->notEmpty, &q->mutex);
    int val = q->buf[q->out];
    q->out = (q->out + 1) % K;
    q->count--;
    pthread_cond_signal(&q->notFull);
    pthread_mutex_unlock(&q->mutex);
    return val;
}

Queue Q1, Q2;

void* stage1(void* arg) {
    for (int i = 0; i < 10; i++) {
        put(&Q1, i);
    }
    put(&Q1, -1); // Sentinel end-of-stream
    return NULL;
}

void* stage2(void* arg) {
    while (1) {
        int x = get(&Q1);
        if (x == -1) {
            put(&Q2, -1);
            break;
        }
        put(&Q2, x * x);
    }
    return NULL;
}

void* stage3(void* arg) {
    long long s = 0;
    while (1) {
        int y = get(&Q2);
        if (y == -1) break;
        s += y;
    }
    printf("Task 8 - Pipeline Final Sum = %lld\n", s);
    return NULL;
}

int main() {
    q_init(&Q1);
    q_init(&Q2);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, stage1, NULL);
    pthread_create(&t2, NULL, stage2, NULL);
    pthread_create(&t3, NULL, stage3, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Task 8 - Three-Stage Pipeline successfully run ho gaya hai!\n");
    return 0;
}