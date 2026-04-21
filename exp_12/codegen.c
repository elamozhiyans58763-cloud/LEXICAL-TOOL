#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

void code_gen(char expr[]) {
    char stack[MAX][10];
    int top = -1;
    int reg = 1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        // if operand
        if (isalnum(ch)) {
            stack[++top][0] = ch;
            stack[top][1] = '\0';
        }
        // if operator
        else {
            char op2[10], op1[10];

            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);

            printf("R%d = %s %c %s\n", reg, op1, ch, op2);

            sprintf(stack[++top], "R%d", reg);
            reg++;
        }
    }
}

int main() {
    char expr[MAX];

    printf("Enter postfix expression: ");
    scanf("%s", expr);

    printf("\nThree Address Code:\n");
    code_gen(expr);

    return 0;
}
