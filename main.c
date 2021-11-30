#include <stdio.h>
#include <stdlib.h>


/*
double linked list of integers
a function to access an element by index for O(N/2)
how to fill initially - doesn't matter
*/

struct preferenceList
{
    int count;
    struct linkedList *half;
};

struct linkedList
{
    int value;
    int index;
    struct preferenceList* data;
    struct linkedList* next;
    struct linkedList* prev;
    struct linkedList* head;
};

struct linkedList* add_elem(struct linkedList* list, int value)
{
    struct linkedList* new_node = malloc(sizeof(struct linkedList));
    new_node->value = value;

    if (list == NULL) {
        new_node->prev = NULL;
        new_node->next = NULL;
        new_node->head = new_node;
        new_node->data = malloc(sizeof(struct preferenceList));
        new_node->data->count = 1;
        new_node->index = 0;

        new_node->data->half = new_node;
        return new_node;
    }
    else {
        list->next = new_node;
        new_node->prev = list;
        new_node->next = NULL;
        new_node->head = list->head;
        new_node->data = list->data;
        new_node->data->count++;
        new_node->index = list->index + 1;

        if (new_node->data->count % 2) {
            new_node->data->half = list->head->data->half->next;
        }

        return new_node;
    }
}

void freeList(struct linkedList* list)
{
    struct linkedList* currentElement = list;

    free(list->data);
    while (1)
    {
        free(currentElement);
        if (currentElement->next == NULL) break;
        currentElement = currentElement->next;
    }
}

int getElementByIndex(struct linkedList* list, int index, int *value)
{
    struct linkedList* currentElement = list->head;

    if (index < 0 || index >= currentElement->data->count) return 0;
    while (1)
    {
        if (currentElement->index == index) {
            *value = currentElement->value;
            return 1;
        }
        if (currentElement->next == NULL) break;
        currentElement = currentElement->next;
    }
    return 0;
}

int getElementByIndex2(struct linkedList* list, int index, int *value)
{
    struct linkedList* currentElement = list->head;

    if (index < 0 || index >= list->head->data->count) return 0;
    currentElement = list->head->data->half;

    if (index > list->head->data->half->index)
    {
        while (1)
        {
            if (currentElement->index == index) {
                *value = currentElement->value;
                return 1;
            }
            if (currentElement->next == NULL) break;
            currentElement = currentElement->next;
        }
    }
    else
    {
        while (1)
        {
            if (currentElement->index == index) {
                *value = currentElement->value;
                return 1;
            }
            if (currentElement->prev == NULL) break;
            currentElement = currentElement->prev;
        }
    }
    return 0;
}



void test_double_linked_list()
{
    struct linkedList* list = NULL;
    int value, result;

    list = add_elem(list, 100);
    list = add_elem(list, 200);
    list = add_elem(list, 300);
    list = add_elem(list, 700);
    list = add_elem(list, 500);
    list = add_elem(list, 750);
    list = add_elem(list, 770);

    printf("\ndouble_linked_list\n");
    result = getElementByIndex(list, 5, &value);
    printf("%d. v = %d\n", result, value) ;


    result = getElementByIndex2(list, 1, &value);
    printf("%d. v = %d\n", result, value) ;
    result = getElementByIndex2(list, 2, &value);
    printf("%d. v = %d\n", result, value) ;

    result = getElementByIndex2(list, 4, &value);
    printf("%d. v = %d\n", result, value) ;
    result = getElementByIndex2(list, 5, &value);
    printf("%d. v = %d\n", result, value) ;

    result = getElementByIndex2(list, 3, &value);
    printf("%d. v = %d\n", result, value) ;

    result = getElementByIndex2(list, 7, &value);
    printf("%d. v = %d\n", result, value) ;

    freeList(list);
}

/* sort array */
void swap(int *a, int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void q_sort(int *a, int start, int end)
{
    int i, last;

    if (start >= end) return;
    swap(a, start, (start + end) / 2);
    last = start;
    for (i = start + 1; i <= end; i++) {
        if (a[i] < a[start]) swap(a, ++last, i);
    }
    swap(a, start, last);
    q_sort(a, start, last - 1);
    q_sort(a, last + 1, end);
}


void test_q_sort()
{
    int i, n;
    int array[15] = {1, 2, 500, 7, 9,
                     3, 5, 6,  8, 4,
                     6, 10, 1, 5, 100,};

    n = sizeof(array) / sizeof(array[0]);
    q_sort(array, 0, n - 1);

    printf("\nsort array\n");
    for (i=0; i < n; i++) printf("%d) %d\n", i, array[i]);
}
int main()
{

    test_double_linked_list();

    test_q_sort();

    return 0;
}
