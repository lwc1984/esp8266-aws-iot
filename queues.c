#include "queues.h"

int init_queues(void) {
  aws_publish_queue = xQueueCreate(PUBLISH_QUEUE_LENGTH, PUBLISH_QUEUE_ITEM_SIZE);
  if( aws_publish_queue == NULL ) {
    /* Queue was not created and must not be used. */
    return -1;
  }

  aws_subscribe_queue = xQueueCreate(SUBSCRIBE_QUEUE_LENGTH, SUBSCRIBE_QUEUE_ITEM_SIZE);
  if( aws_subscribe_queue == NULL ) {
    /* Queue was not created and must not be used. */
    return -1;
  }

  return 0;
}
