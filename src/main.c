#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

static void destroy(void* data) 
{
	//free(data);
	data = NULL;
}

static void print(void* data)
{
	printf("data = %d\n", *((int*)data));
}

static Compare node_compare(void* data,void* value)
{
	int data_to_int = *((int*)data);
	int value_to_int = *((int*)value);
	return data_to_int == value_to_int ? EQUAL : (data_to_int > value_to_int ? BIGGER : SMALLER);

}



int main(int argc,char* argv[])
{
    List* list = NULL;
	int temp;    
	DestroyFunc destroyfunc = &destroy;
	list = list_create(destroyfunc);
    
	temp = 45;
    list_append(list,&temp);
	int a = 55;
    list_insert(list,&a,1);
    int temp1 = (rand()%100+1);
	list_append(list,&temp1);
	int temp2 = (rand()%100+1);
	list_append(list,&temp2);
	int temp3 = (rand()%100+1);
	list_append(list,&temp3);
	int temp4 = (rand()%100+1);
	list_append(list,&temp4);
	int temp5 = (rand()%100+1);
	list_append(list,&temp5);
	int temp6 = (rand()%100+1);
	list_append(list,&temp6);
	list_foreach(list,&print);
	printf("Total node :%d\n\n",list->size);

	printf("find 55 index is %d\n",list_find(list,&a,&node_compare));

    int temp7 = 505;
    list_insert(list,&temp7,5);
	int temp8 = 120;
    list_insert(list,&temp8,6); 
	list_foreach(list,&print);
    printf("Total node :%d\n\n",list->size);

	list_remove(list,1);
	list_foreach(list,&print);
    printf("Total node :%d\n\n",list->size);
    list_clean(list);
	list_destroy(&list);
	list_foreach(list,&print);
 
    return 0;
}
