#include <stdlib.h>
#include <string.h>

enum KEYWORDS {
    TOKEN_INT,
    TOKEN_CHAR,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    TOKEN_VOID,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_DO,
    TOKEN_SWITCH,
    TOKEN_CASE,
    TOKEN_DEFAULT,
    TOKEN_RETURN,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_GOTO,
    TOKEN_UNION,
    TOKEN_STRUCT,
    TOKEN_TYPEDEF,
    TOKEN_ENUM,
    TOKEN_STATIC,
    TOKEN_SIZEOF,
    TOKEN_EXTERN,
    TOKEN_CONST,
}KEYWORD;

enum PUNCTUATION
{
    TOKEN_LPAREN,
    TOKEN_LBRACE,
    TOKEN_RPAREN,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_QUESTION,
}PUNCTUATION;

enum OPERATOR
{
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_ASSIGN,
    TOKEN_PLUS_ASSIGN,
    TOKEN_MINUS_ASSIGN,
    TOKEN_EQUAL_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,
    TOKEN_PLUS_PLUS,
    TOKEN_MINUS_MINUS,
    TOKEN_DOT, TOKEN_ARROW, TOKEN_AMP_AMP, TOKEN_PIPE_PIPE,
    TOKEN_BANG,
    TOKEN_AMP,
    TOKEN_PIPE,
    TOKEN_TILDE,
    TOKEN_CARET,
}OPERATION;

typedef enum category
{
    keyword,
    punctuation,
    operation,
    constant,
    identifier
}category;

typedef struct Token{
    enum category type;
    char *lexeme;
} Token;

typedef struct tokenStream
{
    Token *tokens;
    int capacity;
    int size;
} TokenStream;

void tokenStream_init(TokenStream *s)
{
    s->tokens = NULL;
    s->capacity = 0;
    s->size = 0;
}

void tokenStream_push(TokenStream *s, category type, const char *lexeme)
{
    if (s->size == s->capacity)
    {
        s->capacity = s->capacity == 0 ? 1 : s->capacity * 2;
        s->tokens = realloc(s->tokens, s->capacity * sizeof(Token));
    }
    s->tokens[s->size].type = type;
    s->tokens[s->size].lexeme = strdup(lexeme);
    s->size++;
}

void tokenStream_free(TokenStream *s)
{
    for (int i = 0; i < s->size; i++)
    {
        free(s->tokens[i].lexeme);
    }
    free(s->tokens);
    s->tokens = NULL;
    s->capacity = 0;
    s->size = 0;
}
