/**
 * @file queueArrayList.c
 * 
 * @brief Provides an implementation of the ADT Queue with an array list
 * as the underlying data structure.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "queue.h" 
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 20

typedef struct queueImpl {
	
} QueueImpl;


PtQueue queueCreate() {
	PtQueue queue = (PtQueue)malloc(sizeof(QueueImpl));
	if (queue == NULL) return NULL;

	queue->elements = (QueueElem *)malloc(sizeof(QueueElem) * INITIAL_CAPACITY);
	if (queue->elements == NULL) {
		free(queue);
		return NULL;
	}

	queue->size = 0;
	queue->capacity = INITIAL_CAPACITY;

	return queue;
}

int queueDestroy(PtQueue *ptQueue) {
	if (ptQueue == NULL || *ptQueue == NULL) return QUEUE_NULL;

	free((*ptQueue)->elements);
	free(*ptQueue);
	*ptQueue = NULL;

	return QUEUE_OK;
}

int queueEnqueue(PtQueue queue, QueueElem elem) {
	if (queue == NULL) return QUEUE_NULL;

	if (queue->size == queue->capacity) {
		int newCapacity = queue->capacity * 2;
		QueueElem *newArray = realloc(queue->elements, sizeof(QueueElem) * newCapacity);
		if (newArray == NULL) return QUEUE_NO_MEMORY;

		queue->elements = newArray;
		queue->capacity = newCapacity;
	}

	queue->elements[queue->size] = elem;
	queue->size++;

	return QUEUE_OK;
}


int queueDequeue(PtQueue queue, QueueElem *ptElem) {
	if (queue == NULL) return QUEUE_NULL;

	if (queue->size == 0) return QUEUE_EMPTY;

	*ptElem = queue->elements[0];

	for (int i = 0; i < queue->size - 1; i++) {
		queue->elements[i] = queue->elements[i + 1];
	}

	queue->size--;

	return QUEUE_OK;
}


int queueFront(PtQueue queue, QueueElem *ptElem) {
	if (queue == NULL) return QUEUE_NULL;

	if (queue->size == 0) return QUEUE_EMPTY;

	*ptElem = queue->elements[0];

	return QUEUE_OK;
}


int queueSize(PtQueue queue, int *ptSize) {
	if (queue == NULL) return QUEUE_NULL;

	*ptSize = queue->size;
	return QUEUE_OK;
}


bool queueIsEmpty(PtQueue queue) {
	if (queue == NULL) return true;

	return (queue->size == 0);
}


int queueClear(PtQueue queue) {
	if (queue == NULL) return QUEUE_NULL;

	queue->size = 0;
	return QUEUE_OK;
}

void queuePrint(PtQueue queue) {
	if (queue == NULL) {
		printf("(Queue NULL)\n");
	}
	else if (queueIsEmpty(queue)) {
		printf("(Queue Empty)\n");
	}
	else {
		printf("Queue contents (front to rear): \n");

		for (int i = 0; i < queue->size; i++) {
			queueElemPrint(queue->elements[i]);  // já fornecida
		}

		printf("--- rear ---\n");
	}
	printf("\n");
}


