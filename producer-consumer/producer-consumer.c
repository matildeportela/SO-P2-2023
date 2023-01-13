// #ifndef __PRODUCER_CONSUMER_H__
// #define __PRODUCER_CONSUMER_H__

// #include <pthread.h>


// pthread_mutex_t mutex;
// pthread_cond_t podeProd, podeCons;

// int buf[capacity];
// int not_full=0;
// int consptr=0;
// int count=0;


// // pcq_enqueue: insert a new element at the front of the queue
// //
// // If the queue is full, sleep until the queue has space
// int pcq_enqueue(pc_queue_t *queue, void *elem) {
//     while(TRUE) {
//         int item = produz();
//         pthread_mutex_lock(&mutex);
    
//     while (queue->count == queue->capacity) {
//         pthread_cond_wait(&queue->not_full, &mutex);
//     }

//     buf[queue->head] = elem;
//     queue->head = (queue->head + 1) % queue->capacity;
//     count++;

//     pthread_cond_signal(&queue->not_empty);
//     pthread_mutex_unlock(&queue->lock);
//     return 0;
// }


// // pcq_dequeue: remove an element from the back of the queue
// //
// // If the queue is empty, sleep until the queue has an element
// void *pcq_dequeue(pc_queue_t *queue){
//     while(TRUE) {
//         int item;
//         pthread_mutex_lock(&mutex);
//     while (count == 0) {
//         pthread_cond_wait(&podeCons,&mutex);
//         }
//         item = buf[consptr];
//         consptr ++; 
//         if (consptr == N){
//             consptr = 0;
//             }

//     pthread_cond_signal(&podeProd);
//     pthread_mutex_unlock(&mutex);
// }
// }

// #endif // __PRODUCER_CONSUMER_H__
