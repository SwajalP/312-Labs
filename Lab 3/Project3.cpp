/**
 * NAME: Swajal Padhi
 * EID: skp2628
 * Spring 2024
 * Santacruz
 */

#include "UTQueue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>

/*
 * ALREADY DONE FOR YOU
 * Prints the passed in queue to make it easy to visualize.
 */
void utqueueprint(UTQueue *src) {
  printf("[");
  for (int i = 0; i < src->size - 1; i++)
    printf("%d, ", src->data[i]);
  printf("%d]\n", src->data[src->size - 1]);
}

/*
 * Allocate a UTQueue on the heap.
 * The size of the input array is n.
 * Initialize the queue correctly by copying src
 * Return a pointer to the newly created UTQueue. 
 */
UTQueue *utqueuedup(const int *src, int n) {  
    struct UTQueue *utQ = (UTQueue*) malloc(sizeof(UTQueue));
    utQ->data = (int*) malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
       utQ->data[i] = src[i]; 
    }
    utQ->size = n;
    return utQ; 
   }

/* 
 * Free all memory associated with the given UTQueue.
 */
void utqueuefree(UTQueue *self) {
  free(self->data);
  free(self);
} 
/*
 * Push (enqueue) an integer "value" into the queue.
 */
UTQueue *utqueuepush(UTQueue *src, int value) { 
  src->data = (int*) realloc(src->data, (src->size) * (sizeof(int)) + sizeof(int));
  src->data[src->size] = value;
  src->size++;
  return src;
}

/*
 * Pop (dequeue) an element from the queue
 * should fail an assertion if the queue is empty
 */  
int utqueuepop(UTQueue *src) {
  assert(src->size != 0); // change false to make this assertion fail only if src has 0
  int num = src->data[0];
for(int i = 0; i < src->size-1; i++){
  src->data[i] = src->data[i+1];
} 
  src->size--;
  if(src->size > 0){
    src->data = (int*) realloc(src->data, src->size * sizeof(int));
  }  
  return num;  
}

/*
 * Reverses the queue in src.
 */
UTQueue *utqueuerev(UTQueue *src) { 
  for(int i = 0; i < src->size/2; i++){
    int rightPointer = src->size-i-1;
    int temp = src->data[i];
    src->data[i] = src->data[rightPointer];
    src->data[rightPointer] = temp;
  }
  return src;
}

/*
 * combines the elements of UTQueues dst and src INTO dst.
 * src should be deleted after the combination
 */
UTQueue *utqueuecombine(UTQueue *dst, UTQueue *src) { 

  for(int i = 0; i < src->size; i++){
    utqueuepush(dst, src->data[i]);
  }
  
  utqueuefree(src);
  return dst;
 }
  
  
/*
 * Swap the two queues.
 * q1 should "have" the contents of q2 and vice verse.
 * There is more than one way to do this
 */
void utqueueswap(UTQueue *q1, UTQueue *q2) {
    int* temp = q1->data;
    q1->data = q2->data;
    q2->data = temp;
  

    int tempSize = q1->size;
    q1->size = q2->size;
    q2->size = tempSize;
}  

/*
 * Copy values from src array into dst.
 * Assume dst is a valid UTQueue.
 * src is an array of numbers.
 * Do not allocate any additional storage: only copy as many numbers
 * as will actually fit into the current UTQueue dst.
 * If all of src can fit into dst, leave the remaining ints in dst.
 * return the pointer to dst with the changes.
 */
UTQueue *utqueuecpy(UTQueue *dst, const int *src, int n) { 
  for(int i = 0; i < n && i < dst->size; i++){
      dst->data[i] = src[i];
  }
  return dst;
 }
