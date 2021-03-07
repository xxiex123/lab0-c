#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if(q == NULL){
    printf("malloc fail.\n");
    return NULL;
    }q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

void q_free(queue_t *q)
{
    if(q == NULL)
	return;
    else if(q->head == NULL){
	free(q);
        return;
    }

    list_ele_t *temp;
    temp = malloc(sizeof(list_ele_t));
    if(temp == NULL){
    printf("malloc error.");
    return;
    }
    
    temp = q->head->next;
    free(q->head->value);
    free(q->head);
    while(temp){
    q->head = temp;
    temp = temp->next;
    free(q->head->value);
    free(q->head); 
    }
    free(q);
}

bool q_insert_head(queue_t *q, char *s)
{
    if(q == NULL){
    printf("q is NULL.");
    return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    
    if(newh == NULL){
    printf("malloc error.");
    return false;
    }newh->value = malloc(sizeof(char) * (strlen(s)+1));
    
    if(newh->value == NULL){
    printf("malloc error");
    return false;
    }strcpy(newh->value,s);
    newh->next = q->head;
    
    if(q==NULL){
    q->head = newh;
    q->tail = newh;
    }else{
    q->head = newh;
    }
    q->size++;
    return true;
}

bool q_insert_tail(queue_t *q, char *s)
{
    if(q == NULL)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    
    if(newh == NULL){
    printf("malloc error.");
    return false;
    }newh->value = malloc(sizeof(char) * (strlen(s)+1));
    
    if(newh->value == NULL){
    printf("malloc error");
    return false;
    }strcpy(newh->value,s);
    newh->next = NULL;
    
    if(q->head == NULL){
    q->head = newh;
    q->tail = newh;
    }else{
    q->tail->next = newh;
    q->tail = newh;
    }
    q->size++;
    return true;
}

bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if(q == NULL){
    printf("q is NULL.");
    return false;    
    }else if(q->head == NULL){
    printf("q is empty.")
    return false;
    }
  
    list_ele_t *temp;
    temp = malloc(sizeof(list_ele_t));
    if(temp == NULL){
    printf("malloc error.");
    return false;
    }

    if(sp != NULL){
    for(int i = 0; i < bufsize-1 ; i++)
	sp[i] = q->head->value[i];
    sp[bufsize] = '\0';
    }
    free(q->head->value);
    
    temp = q->head->next;
    q->head->next = NULL;
    q->head = temp;
    if(q->head == NULL)
	q->tail == NULL;
    return true;
}

int q_size(queue_t *q)
{
    if(q == NULL){
    printf("q is NULL.");
    return 0;
    }else if(q->head == NULL){
    printf("q is empty.");
    return 0;
    }

    return q->size;
}

void q_reverse(queue_t *q)
{
    if(q == NULL)
        return;
    else if(q->head == NULL)
	return;
    
    list_ele_t *tempOne , *tempTwo;
    tempOne = malloc(sizeof(list_ele_t));
    tempTwo = malloc(sizeof(list_ele_t));
    if(tempOne == NULL || tempTwo == NULL){
    printf("malloc error.");
    return;
    }

    tempOne = q->head->next;
    q->head->next = NULL;
    q->tail = tempTwo = q->head;
    while(tempOne){
    q->head = temp;
    tempOne = temp->next;
    q->head->next = tempTwo;
    tempTwo = q->head;
    }

}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if(q == NULL){
        return;
    }else if(q->head == NULL){
        return;
    }else if(q->head->next == NULL){
	return;
    }



    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
