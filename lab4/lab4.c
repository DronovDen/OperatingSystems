#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 10
#define SUCCESS 0
#define MEMORY_ALLOC_ERROR -1

typedef struct List
{
    char* data;
    struct List* next;
} List;

void PrintReverse(List* head)
{
    if (head->next == NULL)
        return;
    PrintReverse(head->next);
    puts(head->data);
}

int PushToList(List*** head, char* buffer)
{
    List* newNode = (List*)malloc(sizeof(List));
    if (newNode == NULL)
        return MEMORY_ALLOC_ERROR;
    newNode->data = (char*)malloc(strlen(buffer) + 1);
    // because strlen does not include terminating symbol
    if (newNode->data == NULL)
        return MEMORY_ALLOC_ERROR;
    strcpy(newNode->data, buffer);

    newNode->next = (**head);
    (**head) = newNode;

    return SUCCESS;
}

int ScanStrings(List** head)
{
    char buffer[BUFSIZE];
    char prev_last = '\n';
    while (fgets(buffer, BUFSIZE, stdin) != NULL)
    {
        if (buffer[0] == '.' && prev_last == '\n') break;
        if (PushToList(&head, buffer) == MEMORY_ALLOC_ERROR)
        {
            return MEMORY_ALLOC_ERROR;
        }
        prev_last = buffer[strlen(buffer) - 1];
    }
    return SUCCESS;
}

void FreeList(List* head)
{
    List* tmpNode;
    while (head != NULL)
    {
        tmpNode = head;
        head = head->next;
        free(tmpNode);
    }
}

int main()
{
    // List creating
    List* head = (List*)malloc(sizeof(List));
    if (head == NULL)
    {
        perror("Failed to allocate memory for list!");
        return MEMORY_ALLOC_ERROR; // ENOMEM - defined in errno.h
    }
    head->data = NULL;
    head->next = NULL;

    int result = ScanStrings(&head);
    if (result == MEMORY_ALLOC_ERROR)
    {
        perror("Failed to allocate memory!");
        return MEMORY_ALLOC_ERROR; // ENOMEM - defined in errno.h
    }

    PrintReverse(head);
    FreeList(head);

    return SUCCESS;
}
