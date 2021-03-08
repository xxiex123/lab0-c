#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        printf("malloc fail.\n");
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

    list_ele_t *temp;

    temp = q->head->next;
    q->head->next = NULL;
    free(q->head->value);
    free(q->head);
    while (temp) {
        q->head = temp;
        temp = temp->next;
        q->head->next = NULL;
        free(q->head->value);
        free(q->head);
    }
    free(q);
}

bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) {
        printf("q is NULL.\n");
        return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL) {
        printf("malloc error.\n");
        return false;
    }
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));

    if (newh->value == NULL) {
        printf("malloc error.\n");
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    newh->next = q->head;

    if (q->head == NULL) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->head = newh;
    }
    q->size++;
    return true;
}

bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL) {
        printf("q is NULL.\n");
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL) {
        printf("malloc error.\n");
        return false;
    }
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));

    if (newh->value == NULL) {
        printf("malloc error\n");
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
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
    if (q == NULL) {
        printf("q is NULL.");
        return false;
    } else if (q->head == NULL) {
        printf("q is empty.");
        return false;
    }

    list_ele_t *temp;

    if (sp != NULL) {
        for (int i = 0; i < bufsize - 1; i++)
            sp[i] = q->head->value[i];
        sp[bufsize - 1] = '\0';
    }
    free(q->head->value);

    temp = q->head->next;
    q->head->next = NULL;
    free(q->head);
    q->head = temp;
    if (q->head == NULL)
        q->tail = NULL;
    q->size = q->size - 1;
    return true;
}

int q_size(queue_t *q)
{
    if (q == NULL) {
        printf("q is NULL.");
        return 0;
    } else
        return q->size;
}

void q_reverse(queue_t *q)
{
    if (q == NULL)
        return;
    else if (q->size <= 1)
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
