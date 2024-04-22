#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_OPERANDS 100
#define MAX_OPERATORS 100
#define MAX_TEMP_VARS 100
#define MAX_QUADRUPLES 100
#define MAX_TRIPLES 100

char operands[MAX_OPERANDS][10];
char operators[MAX_OPERATORS];
char temp_vars[MAX_TEMP_VARS][5];
char quadruples[MAX_QUADRUPLES][20];
char triples[MAX_TRIPLES][15];
int op_count = 0, temp_count = 0, quad_count = 0, triple_count = 0;

void gen_three_address_code(char *expr) {
    int i, j, k;
    char op1[10], op2[10], result[10];
    j = k = 0;

    for (i = 0; expr[i] != '\0'; i++) {
        if (isalnum(expr[i])) {
            operands[op_count][j++] = expr[i];
            operands[op_count][j] = '\0';
            op_count++;
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            operators[op_count] = expr[i];
            sprintf(temp_vars[temp_count], "t%d", temp_count);
            printf("%s = %s %c %s\n", temp_vars[temp_count], operands[op_count - 2], operators[op_count], operands[op_count - 1]);
            sprintf(quadruples[quad_count], "(OP, %c, %s, %s, %s)", operators[op_count], operands[op_count - 2], operands[op_count - 1], temp_vars[temp_count]);
            sprintf(triples[triple_count], "(%c, %s, %s, %s)", operators[op_count], operands[op_count - 2], operands[op_count - 1], temp_vars[temp_count]);
            quad_count++;
            triple_count++;
            op_count = op_count - 1;
            strcpy(operands[op_count], temp_vars[temp_count++]);
            j = 0;
        }
    }
}

int main() {
    char expr[100];
    printf("Enter an arithmetic expression: ");
    scanf("%s", expr);
    gen_three_address_code(expr);

    printf("\nQuadruples:\n");
    for (int i = 0; i < quad_count; i++) {
        printf("%s\n", quadruples[i]);
    }

    printf("\nTriples:\n");
    for (int i = 0; i < triple_count; i++) {
        printf("%s\n", triples[i]);
    }

    return 0;
}