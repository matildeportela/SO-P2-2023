
#include "producer-consumer.h"
#include "logging.h"
#include <pthread.h>


pthread_mutex_t mutex;
pthread_cond_t podeProd;
pthread_cond_t podeCons;


int count = 0;

pthread_cond_t not_empty;
pthread_cond_t not_full;


// pcq_enqueue: insert a new element at the front of the queue
//
// If the queue is full, sleep until the queue has space

int pcq_enqueue(pc_queue_t *queue, void *elem) {
    void *buf[queue->pcq_capacity];
    
    pthread_mutex_lock(&queue->pcq_current_size_lock);

    while (count == queue->pcq_capacity) {
        pthread_cond_wait(&not_full, &mutex);
    }

    buf[queue->pcq_head] = elem;
    queue->pcq_head = (queue->pcq_head + 1) % queue->pcq_capacity;
    count++;

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);

    return 0;
    }
  

// pcq_dequeue: remove an element from the back of the queue
//
// If the queue is empty, sleep until the queue has an element

void *pcq_dequeue(pc_queue_t *queue) {
    void *elem = NULL;
    pthread_mutex_lock(&queue->pcq_current_size_lock);
    while (count == 0) {
        pthread_cond_wait(&not_empty, &queue->pcq_current_size_lock);
    }
    
    elem = queue->pcq_buffer[queue->pcq_tail];
    queue->pcq_tail = (queue->pcq_tail + 1) % queue->pcq_capacity;
    count--;
    
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&queue->pcq_current_size_lock);
    
    return elem;
}

