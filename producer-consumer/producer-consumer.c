
#include "producer-consumer.h"
#include "logging.h"
#include <pthread.h>


pthread_mutex_t mutex;
pthread_cond_t podeProd;
pthread_cond_t podeCons;



int buf[queue->pcq_capacity];
int not_full=0;
int consptr=0;
int count=0;


// pcq_enqueue: insert a new element at the front of the queue
//
// If the queue is full, sleep until the queue has space

int pcq_enqueue(pc_queue_t *queue, void *elem) {
    while(1) {
        int item = produz();
        pthread_mutex_lock(&queue->pcq_current_size_lock);
    
        while (&queue->count == &queue->pcq_capacity) {
            pthread_cond_wait(&queue->not_full, queue->pcq_current_size_lock);
        }

        queue->pcq_buffer[queue->pcq_head] = elem;
        queue->pcq_head = (queue->pcq_head + 1) % queue->pcq_capacity;
        queue->count++;

        pthread_cond_signal(&queue->not_empty);
        pthread_mutex_unlock(queue->pcq_current_size_lock);
    }
    return 0;
}
// pcq_dequeue: remove an element from the back of the queue
//
// If the queue is empty, sleep until the queue has an element
void *pcq_dequeue(pc_queue_t *queue){
   int a;
   int b;
   b = a + 1;
}

