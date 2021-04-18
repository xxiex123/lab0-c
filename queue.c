#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    else if (q->size == 0) {
        free(q);
        return;
    }

    while (q->head) {
        list_ele_t *temp;
        temp = q->head;
        q->head = q->head->next;
        free(temp->value);
        free(temp);
    }
    free(q);
}

bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL) {
        return false;
    }
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));

    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    for (int i = 0; i < strlen(s) + 1; i++)
        newh->value[i] = s[i];
    newh->next = q->head;
    if (q->head == NULL)
        q->tail = newh;
    q->head = newh;
    q->size++;
    return true;
}

bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL) {
        return false;
    }
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));

    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    for (int i = 0; i < strlen(s) + 1; i++) {
        newh->value[i] = s[i];
    }
    newh->next = NULL;
    if (q->head == NULL) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }
    q->size++;
    return true;
}

bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
        return false;

    list_ele_t *temp = q->head;
    q->head = q->head->next;

    if (sp != NULL) {
        for (int i = 0; i < bufsize - 1; i++)
            sp[i] = temp->value[i];
        sp[bufsize - 1] = '\0';
    }

    free(temp->value);
    free(temp);
    if (q->head == NULL)
        q->tail = NULL;
    q->size--;
    return true;
}

int q_size(queue_t *q)
{
    if (q == NULL) {
        return 0;
    } else
        return q->size;
}

void q_reverse(queue_t *q)
{
    if (q == NULL || q->size <= 1)
        return;

    list_ele_t *tempOne;
    list_ele_t *tempTwo;

    tempOne = q->head->next;
    q->head->next = NULL;
    q->tail = tempTwo = q->head;
    while (tempOne) {
        q->head = tempOne;
        tempOne = tempOne->next;
        q->head->next = tempTwo;
        tempTwo = q->head;
    }
}

void split(queue_t *q, queue_t *left, queue_t *right)
{
    int middle = q->size / 2 - 1;
    left->head = q->head;
    left->size = middle + 1;
    right->tail = q->tail;
    right->size = q->size - left->size;
    for (int i = 0; i < middle; i++)
        q->head = q->head->next;
    left->tail = q->head;
    right->head = q->head->next;
    left->tail->next = NULL;
}

void merge(queue_t *q, queue_t *left, queue_t *right)
{
    if (strcmp(left->head->value, right->head->value) < 0) {
        q->tail = q->head = left->head;
        left->head = left->head->next;
    } else {
        q->tail = q->head = right->head;
        right->head = right->head->next;
    }

    while (left->head && right->head) {
        if (strcmp(left->head->value, right->head->value) < 0) {
            q->tail->next = left->head;
            q->tail = left->head;
            left->head = left->head->next;
        } else {
            q->tail->next = right->head;
            q->tail = right->head;
            right->head = right->head->next;
        }
    }

    if (right->head) {
        q->tail->next = right->head;
        q->tail = right->tail;
    } else {
        q->tail->next = left->head;
        q->tail = left->tail;
    }
    q->size = left->size + right->size;
}

void mergesort(queue_t *q)
{
    if (q->size <= 1)
        return;

    queue_t left, right;

    split(q, &left, &right);
    mergesort(&left);
    mergesort(&right);
    merge(q, &left, &right);
}

void q_sort(queue_t *q)
{
    if (q == NULL) {
        return;
    } else if (q->size < 2) {
        return;
    }

    mergesort(q);
}
