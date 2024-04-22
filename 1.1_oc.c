#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 50
#define MAX_PROGRAM_LENGTH 10000

enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_SYMBOL,
    TOKEN_UNKNOWN,
    TOKEN_EOF
};

struct Token {
    enum TokenType type;
    char lexeme[MAX_IDENTIFIER_LENGTH];
};

bool is_valid_identifier_char(char c) {
    return isalnum(c) || c == '_';
}

bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool is_keyword(const char *lexeme) {
    const char *keywords[] = {"if", "else", "while", "for", "int", "float", "return"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
        if (strcmp(lexeme, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

void analyze_program(const char program[], int program_length, int *num_tokens, int *num_keywords, int *num_identifiers, int *num_numbers, int *num_operators, int *num_symbols, int *num_unknowns) {
    struct Token token;
    int i = 0;
    char identifiers[MAX_PROGRAM_LENGTH][MAX_IDENTIFIER_LENGTH] = {0};
    char keywords[MAX_PROGRAM_LENGTH][MAX_IDENTIFIER_LENGTH] = {0};
    char numbers[MAX_PROGRAM_LENGTH][MAX_IDENTIFIER_LENGTH] = {0};
    char operators[MAX_PROGRAM_LENGTH][MAX_IDENTIFIER_LENGTH] = {0};
    char symbols[MAX_PROGRAM_LENGTH][MAX_IDENTIFIER_LENGTH] = {0};
    char unknowns[MAX_PROGRAM_LENGTH][MAX_IDENTIFIER_LENGTH] = {0};
    int id_count = 0;
    int kw_count = 0;
    int num_count = 0;
    int op_count = 0;
    int sym_count = 0;
    int unk_count = 0;

    while (i < program_length) {
        char c = program[i];

        if (is_valid_identifier_char(c) && !isdigit(c)) {
            int j = 0;
            token.type = TOKEN_IDENTIFIER;
            while (is_valid_identifier_char(c) && j < MAX_IDENTIFIER_LENGTH - 1) {
                token.lexeme[j++] = c;
                c = program[++i];
            }
            token.lexeme[j] = '\0';
            if (is_keyword(token.lexeme)) {
                token.type = TOKEN_KEYWORD;
                strcpy(keywords[kw_count++], token.lexeme);
            } else {
                strcpy(identifiers[id_count++], token.lexeme);
            }
        } else if (isdigit(c)) {
            int j = 0;
            token.type = TOKEN_NUMBER;
            while ((isdigit(c) || c == '.') && j < MAX_IDENTIFIER_LENGTH - 1) {
                token.lexeme[j++] = c;
                c = program[++i];
            }
            token.lexeme[j] = '\0';
            strcpy(numbers[num_count++], token.lexeme);
        } else if (is_whitespace(c)) {
            ++i;
            continue;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>') {
            token.type = TOKEN_OPERATOR;
            token.lexeme[0] = c;
            token.lexeme[1] = '\0';
            strcpy(operators[op_count++], token.lexeme);
            ++i;
        } else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',') {
            token.type = TOKEN_SYMBOL;
            token.lexeme[0] = c;
            token.lexeme[1] = '\0';
            strcpy(symbols[sym_count++], token.lexeme);
            ++i;
        } else {
            token.type = TOKEN_UNKNOWN;
            token.lexeme[0] = c;
            token.lexeme[1] = '\0';
            strcpy(unknowns[unk_count++], token.lexeme);
            ++i;
        }
    }

    // Print identifiers
    printf("Identifiers: ");
    for (int j = 0; j < id_count; j++) {
        printf("%s", identifiers[j]);
        if (j != id_count - 1)
            printf(", ");
    }
    printf("\n");

    // Print keywords
    printf("Keywords: ");
    for (int j = 0; j < kw_count; j++) {
        printf("%s", keywords[j]);
        if (j != kw_count - 1)
            printf(", ");
    }
    printf("\n");

    // Print numbers
    printf("Numbers: ");
    for (int j = 0; j < num_count; j++) {
        printf("%s", numbers[j]);
        if (j != num_count - 1)
            printf(", ");
    }
    printf("\n");

    // Print operators
    printf("Operators: ");
    for (int j = 0; j < op_count; j++) {
        printf("%s", operators[j]);
        if (j != op_count - 1)
            printf(", ");
    }
    printf("\n");

    // Print symbols
    printf("Symbols: ");
    for (int j = 0; j < sym_count; j++) {
        printf("%s", symbols[j]);
        if (j != sym_count - 1)
            printf(", ");
    }
    printf("\n");

    // Print unknowns
    printf("Unknowns: ");
    for (int j = 0; j < unk_count; j++) {
        printf("%s", unknowns[j]);
        if (j != unk_count - 1)
            printf(", ");
    }
    printf("\n");

    // Print total number of tokens
    *num_tokens = id_count + kw_count + num_count + op_count + sym_count + unk_count;

    // Return counts
    *num_keywords = kw_count;
    *num_identifiers = id_count;
    *num_numbers = num_count;
    *num_operators = op_count;
    *num_symbols = sym_count;
    *num_unknowns = unk_count;
}

int main() {
    const char program[] = 
        "int main() {\n"
        "    int x = 10;\n"
        "    float y = 20.5;\n"
        "    if (x > 5) {\n"
        "        printf(\"x is greater than 5\\n\");\n"
        "    } else {\n"
        "        printf(\"x is less than or equal to 5\\n\");\n"
        "    }\n"
        "    return 0;\n"
        "}";
    int program_length = strlen(program);

    // Analyze the program
    int num_tokens, num_keywords, num_identifiers, num_numbers, num_operators, num_symbols, num_unknowns;
    analyze_program(program, program_length, &num_tokens, &num_keywords, &num_identifiers, &num_numbers, &num_operators, &num_symbols, &num_unknowns);
    printf("\nTotal number of tokens: %d\n", num_tokens);

    return 0;
}
