#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 50

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

struct Token get_next_token() {
    struct Token token;
    char c;
    int i = 0;

    do {
        c = getchar();
        if (c == '/') {
            char next_char = getchar();
            if (next_char == '/') {
                while (c != '\n' && c != EOF) {
                    c = getchar();
                }
            } else {
                ungetc(next_char, stdin);
            }
        }
    } while (is_whitespace(c));

    if (c == EOF) {
        token.type = TOKEN_EOF;
        return token;
    }

    if (is_valid_identifier_char(c)) {
        token.type = TOKEN_IDENTIFIER;
        token.lexeme[i++] = c;
        while ((c = getchar()) != EOF && is_valid_identifier_char(c) && i < MAX_IDENTIFIER_LENGTH - 1) {
            token.lexeme[i++] = c;
        }
        token.lexeme[i] = '\0';
        ungetc(c, stdin);
        if (is_keyword(token.lexeme)) {
            token.type = TOKEN_KEYWORD;
        }
        return token;
    }


    if (isdigit(c)) {
        token.type = TOKEN_NUMBER;
        token.lexeme[i++] = c;
        while ((c = getchar()) != EOF && (isdigit(c) || c == '.') && i < MAX_IDENTIFIER_LENGTH - 1) {
            token.lexeme[i++] = c;
        }
        token.lexeme[i] = '\0';
        ungetc(c, stdin);
        return token;
    }


    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>') {
        token.type = TOKEN_OPERATOR;
        token.lexeme[i++] = c;
        token.lexeme[i] = '\0';
        return token;
    }

    if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',') {
        token.type = TOKEN_SYMBOL;
        token.lexeme[i++] = c;
        token.lexeme[i] = '\0';
        return token;
    }

    token.type = TOKEN_UNKNOWN;
    token.lexeme[0] = c;
    token.lexeme[1] = '\0';
    return token;
}

int main() {
    struct Token token;
    do {
        token = get_next_token();
        switch (token.type) {
            case TOKEN_IDENTIFIER:
                printf("Identifier: %s\n", token.lexeme);
                break;
            case TOKEN_NUMBER:
                printf("Number: %s\n", token.lexeme);
                break;
            case TOKEN_OPERATOR:
                printf("Operator: %s\n", token.lexeme);
                break;
            case TOKEN_KEYWORD:
                printf("Keyword: %s\n", token.lexeme);
                break;
            case TOKEN_SYMBOL:
                printf("Symbol: %s\n", token.lexeme);
                break;
            case TOKEN_UNKNOWN:
                printf("Unknown: %s\n", token.lexeme);
                break;
            case TOKEN_EOF:
                printf("End of file\n");
                break;
            default:
                break;
        }
    } while (token.type != TOKEN_EOF);

    return 0;
}
// int main() {
//     int x = 10;
//     float y = 20.5;
//     if (x > 5) {
//         printf("x is greater than 5\n");
//     } else {
//         printf("x is less than or equal to 5\n");
//     }
//     return 0;
// }