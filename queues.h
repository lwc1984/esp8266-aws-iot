
#include <FreeRTOS.h>
#include <queue.h>

#ifndef INC_QUEUES_H
#define INC_QUEUES_H


// The size of each individual message
#define PUBLISH_QUEUE_ITEM_SIZE 64

// The length of the publish queue
#define PUBLISH_QUEUE_LENGTH 3

// The size of each individual message size
#define SUBSCRIBE_QUEUE_ITEM_SIZE 64

// The length of the subscribe queue
#define SUBSCRIBE_QUEUE_LENGTH 3


// The queue to publish messages.
QueueHandle_t aws_publish_queue;

// The queue to receive messages.
QueueHandle_t aws_subscribe_queue;

// Initializes all the queue declared in this header file.
// Returns 0 on successful initialization. -1 for error.
int init_queues(void);

#endif
