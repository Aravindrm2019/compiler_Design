#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simple.tab.h"

FILE *yyin = NULL;
extern YYSTYPE yylval;
int lexical_error = 0;

static char buffer[256];
static int buffer_pos = 0;
static int input_pos = 0;
static int total_read = 0;

int read_char() {
    if (input_pos >= total_read) {
        total_read = fread(buffer, 1, sizeof(buffer), yyin);
        input_pos = 0;
        if (total_read == 0) return EOF;
    }
    return buffer[input_pos++];
}

void unread_char(int c) {
    if (input_pos > 0) input_pos--;
}

int yylex() {
    int c;
    char text[256];
    int pos = 0;

    // Skip whitespace
    while ((c = read_char()) != EOF && strchr(" \t\n\r", c));
    
    if (c == EOF) return 0;

    if (c == ';' || c == '(' || c == ')' || c == '{' || c == '}') {
        printf("DELIM %c\n", c);
        return c;
    }

    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>') {
        printf("OP %c\n", c);
        return c;
    }

    if (isdigit(c)) {
        text[pos++] = c;
        while ((c = read_char()) != EOF && isdigit(c)) {
            text[pos++] = c;
        }
        unread_char(c);
        text[pos] = '\0';
        printf("INTEGER %s\n", text);
        yylval.ival = atoi(text);
        return INTEGER;
    }

    if (isalpha(c) || c == '_') {
        text[pos++] = c;
        while ((c = read_char()) != EOF && (isalnum(c) || c == '_')) {
            text[pos++] = c;
        }
        unread_char(c);
        text[pos] = '\0';

        // Check for keywords
        if (strcmp(text, "int") == 0 || strcmp(text, "float") == 0 || 
            strcmp(text, "if") == 0 || strcmp(text, "else") == 0 || 
            strcmp(text, "while") == 0 || strcmp(text, "return") == 0) {
            printf("KEYWORD %s\n", text);
            return KEYWORD;
        }

        printf("IDENTIFIER %s\n", text);
        yylval.sval = strdup(text);
        return IDENTIFIER;
    }

    printf("LEXICAL ERROR : %c\n", c);
    lexical_error = 1;
    return c;
}

int yywrap() {
    return 1;
}
