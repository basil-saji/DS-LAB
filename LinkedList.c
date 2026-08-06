#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* head = NULL;

void push(int val) {
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    temp->data = val;
    temp->next = head;
    head = temp;
}

void pop() {
    if (head == NULL) {
        printf("UNDERFLOW\n");
        return;
    }
    struct node* ptr = head;
    head = head->next;
    free(ptr);
}

void display() {
    if (head == NULL) {
        printf("STACK IS EMPTY\n");
        return;
    }
    struct node* ptr = head;
    while (ptr != NULL) {
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
}

void main() {
    int choice, val;
    
    while (1) {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &val);
                push(val);
                break;
            case 2:
                pop();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid Choice\n");
        }
    }
}
