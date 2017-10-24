#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "common.h"

List* list_create(DestroyFunc func)
{
	List* list = NULL;

	list = (List*)malloc(sizeof(List));
	return_NULL_if_malloc_fail(list == NULL);
	
	list->head = NULL;
	list->size = 0;
    list->destroy_func = func;
	return list;
}

Ret list_insert(List* thiz,void* data,int index)
{
	Node* node = NULL;
	Node* temp = NULL;
	
	return_value_if_fail((thiz == NULL || thiz->size <index),OTHER_ERROR);

	node = (Node*)malloc(sizeof(Node));
	return_value_if_fail((node == NULL),MALLOC_MEMORY_FAILED);
                                        
	node->data = data;
	node->next = NULL;
	temp = thiz->head;

	if (index == 0) {
		node->next = thiz->head;
		thiz->head = node;
	} else {
		while(index > 1) {
			temp = temp->next;
			--index;
		}

		node->next = temp->next;
		temp->next = node;
	}

	thiz->size++;
	return NO_ERROR;
}

Ret list_append(List* thiz,void* value)
{
	return list_insert(thiz,value,thiz->size);
}

int list_find(List* thiz,void* value,CompareFunc func)
{
	return_value_if_fail((thiz == NULL || func == NULL),OTHER_ERROR);
	
	int index = 0;
	Node* node = thiz->head;
	while (node != NULL) {
		if (func(node->data,value) == EQUAL) {
			return index;
		} else {
			index++;
			node = node->next;
		}
	}
	return -1;
}

Ret list_remove(List* thiz,int index)
{
	Node* node = NULL;
	Node* pre = NULL;

	return_value_if_fail((thiz == NULL || thiz->size <index),OTHER_ERROR);
	node = thiz->head;
	while (node != NULL && index > 0) {
		pre = node;
		index--;
		node = node->next;
	}

	if (pre == NULL) {
		thiz->head = node->next;
	} else {
		pre->next = node->next;
	}

	if (thiz->destroy_func != NULL) {
		thiz->destroy_func(node->data);
	}
	free(node);
	thiz->size--;
	return	NO_ERROR;
}

Ret list_clean(List* thiz)
{
	Node* node = NULL;
	Node* temp = NULL;
	
	return_value_if_fail((thiz == NULL),OTHER_ERROR);
	node = thiz->head;
	while (node != NULL) {
		temp = node;
		node = node->next;
		if (thiz->destroy_func != NULL) {
			thiz->destroy_func(temp->data);
		}
	}

	thiz->size = 0;

	return NO_ERROR;
}


void list_destroy(List** thiz)
{
	if ((*thiz) != NULL) {
		list_clean(*thiz);
		free(*thiz);
		(*thiz) = NULL;
	}
}

void list_foreach(List* thiz,ForeachFunc func)
{
	Node* node = NULL;
	return_if_fail((thiz == NULL || func == NULL));
    node = thiz->head;	
	while(node != NULL) {
		func(node->data);
		node = node->next;
	}
}
