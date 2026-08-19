#include <stdio.h>
#include <ctype.h>

char infix[100], postfix[100], stack[100];
int top = -1, p_val, eval_stack[100], eval_top = -1, result;

void get_prec(char c) {
    p_val = 0;
    if (c == '+' || c == '-') p_val = 1;
    if (c == '*' || c == '/' || c == '%') p_val = 2;
    if (c == '^') p_val = 3;
}

void infix_to_postfix() {
    int i, k = 0, p1, p2;

    top = -1;

    for (i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isalnum(c)) {
            postfix[k++] = c;
        }
        else if (c == '(') {
            stack[++top] = c;
        }
        else if (c == ')') {
            while (top >= 0 && stack[top] != '(')
                postfix[k++] = stack[top--];
            if (top >= 0)
                top--;
        }
        else if (c == '+' || c == '-' || c == '*' ||
                 c == '/' || c == '%' || c == '^') {

            get_prec(c);
            p1 = p_val;

            while (top >= 0 && stack[top] != '(') {
                get_prec(stack[top]);
                p2 = p_val;

                if ((c == '^' && p2 > p1) ||
                    (c != '^' && p2 >= p1))
                    postfix[k++] = stack[top--];
                else
                    break;
            }

            stack[++top] = c;
        }
    }

    while (top >= 0)
        postfix[k++] = stack[top--];

    postfix[k] = '\0';
}

void eval_postfix() {
    int i, a, b, temp, j;
    char c;

    eval_top = -1;

    for (i = 0; postfix[i] != '\0'; i++) {
        c = postfix[i];

        if (isdigit(c))
            eval_stack[++eval_top] = c - '0';

        else if (isalpha(c))
            eval_stack[++eval_top] = tolower(c) - 'a' + 1;

        else {
            b = eval_stack[eval_top--];
            a = eval_stack[eval_top--];

            if (c == '+') temp = a + b;
            if (c == '-') temp = a - b;
            if (c == '*') temp = a * b;
            if (c == '/') temp = a / b;
            if (c == '%') temp = a % b;

            if (c == '^') {
                temp = 1;
                for (j = 0; j < b; j++)
                    temp *= a;
            }

            eval_stack[++eval_top] = temp;
        }
    }

    result = eval_stack[eval_top];
}

int main() {
    printf("Enter infix expression: ");
    scanf(" %[^\n]", infix);

    infix_to_postfix();

    printf("Postfix : %s\n", postfix);

    eval_postfix();

    printf("Result  : %d\n", result);

    return 0;
}
