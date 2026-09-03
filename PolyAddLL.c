#include <stdio.h>
#include <stdlib.h>

struct node {
    int coeff;
    int exp;
    struct node *next;
};

struct node* insert_end(struct node *head, int c, int e) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->coeff = c;
    newnode->exp = e;
    newnode->next = NULL;

    if (!head) return newnode;

    struct node *temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newnode;
    return head;
}

struct node* create_poly() {
    struct node *head = NULL;
    int n, c, e;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coeff & exp: ");
        scanf("%d%d", &c, &e);
        head = insert_end(head, c, e);
    }
    return head;
}

struct node* add_poly(struct node *p1, struct node *p2) {
    struct node *head3 = NULL;

    while (p1 && p2) {
        if (p1->exp == p2->exp) {
            int sum = p1->coeff + p2->coeff;
            if (sum != 0) head3 = insert_end(head3, sum, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            head3 = insert_end(head3, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            head3 = insert_end(head3, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    while (p1) {
        head3 = insert_end(head3, p1->coeff, p1->exp);
        p1 = p1->next;
    }
    while (p2) {
        head3 = insert_end(head3, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return head3;
}

void display(struct node *head) {
    if (!head) {
        printf("0\n");
        return;
    }
    struct node *temp = head;
    while (temp) {
        printf("%dx^%d", temp->coeff, temp->exp);
        if (temp->next) printf(" + ");
        temp = temp->next;
    }
    printf("\n");
}

void main() {
    printf("--- Polynomial 1 ---\n");
    struct node *poly1 = create_poly();

    printf("\n--- Polynomial 2 ---\n");
    struct node *poly2 = create_poly();

    struct node *poly3 = add_poly(poly1, poly2);

    printf("\nResultant Polynomial: ");
    display(poly3);
}
