#ifndef _LIST_H_
#define _LIST_H_

typedef void (*DestroyFunc)(void* data);
typedef void (*ForeachFunc)(void* data);

typedef enum _Compare
{
	EQUAL = 0,
	BIGGER = 1,
	SMALLER = -1

} Compare;

typedef enum _Ret
{
	NO_ERROR = 0,
	MALLOC_MEMORY_FAILED = -1,
	OTHER_ERROR = -2
} Ret;

typedef struct _Node
{
	void* data;
    struct _Node* next;
} Node;

typedef struct _List
{
	Node* head;
	int size;
	DestroyFunc destroy_func;
} List;

typedef Compare (*CompareFunc)(void* data,void* value);

List* list_create(DestroyFunc func);
Ret   list_insert(List* thiz, void* value, int index);
Ret   list_append(List* thiz, void* value);
Ret   list_find(List* thiz, void* value,CompareFunc func);
void  list_foreach(List* thiz, ForeachFunc func); 
Ret   list_remove(List* thiz, int index);
Ret   list_clean(List* thiz); 
void   list_destroy(List** thiz);

#endif
