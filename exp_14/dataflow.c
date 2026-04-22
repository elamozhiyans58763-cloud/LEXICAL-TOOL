#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

typedef struct {
    char var[MAX];
    int size;
} Set;

void initSet(Set *s) {
    s->size = 0;
}

void add(Set *s, char c) {
    for (int i = 0; i < s->size; i++)
        if (s->var[i] == c)
            return;
    s->var[s->size++] = c;
}

void removeElem(Set *s, char c) {
    for (int i = 0; i < s->size; i++) {
        if (s->var[i] == c) {
            for (int j = i; j < s->size - 1; j++)
                s->var[j] = s->var[j + 1];
            s->size--;
            return;
        }
    }
}

Set unionSet(Set a, Set b) {
    Set result = a;
    for (int i = 0; i < b.size; i++)
        add(&result, b.var[i]);
    return result;
}

Set diffSet(Set a, Set b) {
    Set result = a;
    for (int i = 0; i < b.size; i++)
        removeElem(&result, b.var[i]);
    return result;
}

int equalSet(Set a, Set b) {
    if (a.size != b.size)
        return 0;
    for (int i = 0; i < a.size; i++) {
        int found = 0;
        for (int j = 0; j < b.size; j++) {
            if (a.var[i] == b.var[j])
                found = 1;
        }
        if (!found)
            return 0;
    }
    return 1;
}

void printSet(Set s) {
    printf("{");
    for (int i = 0; i < s.size; i++) {
        printf("%c", s.var[i]);
        if (i < s.size - 1) printf(",");
    }
    printf("}");
}

void use_def(char *stmt, Set *use, Set *def) {
    initSet(use);
    initSet(def);

    char lhs = stmt[0];
    add(def, lhs);

    for (int i = 2; stmt[i] != '\0'; i++) {
        if (isalpha(stmt[i]) && stmt[i] != lhs)
            add(use, stmt[i]);
    }
}

int main() {
    char statements[MAX][20] = {
        "a=b+c",
        "d=a-e",
        "b=d+c",
        "e=b-a"
    };

    int n = 4;

    Set IN[MAX], OUT[MAX];

    for (int i = 0; i < n; i++) {
        initSet(&IN[i]);
        initSet(&OUT[i]);
    }

    int changed = 1;

    while (changed) {
        changed = 0;

        for (int i = n - 1; i >= 0; i--) {
            Set use, def;
            use_def(statements[i], &use, &def);

            Set old_in = IN[i];
            Set old_out = OUT[i];

            if (i < n - 1)
                OUT[i] = IN[i + 1];

            Set temp = diffSet(OUT[i], def);
            IN[i] = unionSet(use, temp);

            if (!equalSet(old_in, IN[i]) || !equalSet(old_out, OUT[i]))
                changed = 1;
        }
    }

    printf("Statement\tIN\tOUT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t", statements[i]);
        printSet(IN[i]);
        printf("\t");
        printSet(OUT[i]);
        printf("\n");
    }

    return 0;
}
