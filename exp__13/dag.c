#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    char op;
    char left[10];
    char right[10];
    char result[10];
} Node;

Node dag[MAX];
int n = 0;

int findNode(char *l, char *r, char op) {
    for (int i = 0; i < n; i++) {
        if (dag[i].op == op &&
            strcmp(dag[i].left, l) == 0 &&
            strcmp(dag[i].right, r) == 0) {
            return i;
        }
    }
    return -1;
}

void addNode(char *res, char *l, char *r, char op) {
    int idx = findNode(l, r, op);

    if (idx == -1) {
        strcpy(dag[n].left, l);
        strcpy(dag[n].right, r);
        dag[n].op = op;
        strcpy(dag[n].result, res);
        n++;
    } else {
        printf("%s = %s (reused node %d)\n", res, dag[idx].result, idx);
        return;
    }

    printf("%s = %s %c %s\n", res, l, op, r);
}

int main() {
    int i, num;
    char expr[20], res[10], l[10], r[10], op;

    printf("Enter number of expressions: ");
    scanf("%d", &num);

    for (i = 0; i < num; i++) {
        printf("Enter expression (format: a=b+c): ");
        scanf("%s", expr);

        res[0] = expr[0];
        res[1] = '\0';

        l[0] = expr[2];
        l[1] = '\0';

        op = expr[3];

        r[0] = expr[4];
        r[1] = '\0';

        addNode(res, l, r, op);
    }

    printf("\n--- DAG Nodes ---\n");

    for (i = 0; i < n; i++) {
        printf("%d: %s = %s %c %s\n",
               i,
               dag[i].result,
               dag[i].left,
               dag[i].op,
               dag[i].right);
    }

    return 0;
}
