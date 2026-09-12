#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"


char* add_letter(char* word, char l)
{
    int len = strlen(word);
    char* new_word = realloc(word, len + 2);
    new_word[len] = l;
    new_word[len + 1] = '\0';
    return new_word;
}

bool check_if_identifier(char* word, int n)
{
    int i = 0;
    if(!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || word[i] == '_')){return false;}
    for ( i=1;i<n;i++)
    {
        if(!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || word[i] == '_' || word[i]>='0' && word[i]<= '9' )){return false;}
    }
    return true;
}

struct tokenStream* lexing(char* input, int n)
{
    struct tokenStream *stream = (struct tokenStream*)malloc(sizeof(struct tokenStream));
    tokenStream_init(stream);

    char* token = (char*)malloc(20* sizeof(char));
    int i,j;
    int len;
    int count = 0;
        for(i = 0; i<n ; i++)
        {
            if(input[i] == '(')
            {
                TokenValue value = {
                    .punctuation = TOKEN_LPAREN
                };
                tokenStream_push(stream, punctuation, "(", value);
            }
            if(input[i] == ')')
            {
                TokenValue value = {
                    .punctuation = TOKEN_RPAREN
                };
                tokenStream_push(stream, punctuation, ")", value);
            }
            if(input[i] == '{')
            {
                TokenValue value = {
                    .punctuation = TOKEN_LBRACE
                };
                tokenStream_push(stream, punctuation, "{", value);
            }
            if(input[i] == '}')
            {
                TokenValue value = {
                    .punctuation = TOKEN_RBRACE
                };
                tokenStream_push(stream, punctuation, "}", value);
            }
            if(input[i] == '+')
            {
                TokenValue value = {
                    .operation = TOKEN_PLUS
                };
                tokenStream_push(stream, operation, "+", value);
            }
            if(input[i] == '-')
            {
                TokenValue value = {
                    .operation = TOKEN_MINUS
                };
                tokenStream_push(stream, operation, "-", value);
            }
            if(input[i] == '*')
            {
                TokenValue value = {
                    .operation = TOKEN_STAR
                };
                tokenStream_push(stream, operation, "*", value);
            }
            if(input[i] == '/')
            {
                TokenValue value = {
                    .operation = TOKEN_SLASH
                };
                tokenStream_push(stream, operation, "/", value);
            }
            if(input[i] == '=' && input[i+1] == '=')
            {
                TokenValue value = {
                    .operation = TOKEN_EQUAL_EQUAL
                };
                tokenStream_push(stream, operation, "==", value);
            }

            if(input[i] == ' ')
            {
                j = i+1;
                do{
                    add_letter(token, input[j]);
                    j++;
                }while(input[j] != ' ');
            }
            len = j-i-1;
            i=j;

            if(check_if_identifier(token, len)){
                TokenValue value = {
                    .identifier = token
                };
                tokenStream_push(stream, identifier, token, value);
            }
            if(strcmp(token, "int")){
                TokenValue value = {
                    .keyword = TOKEN_INT
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "return")){
                TokenValue value = {
                    .keyword = TOKEN_RETURN
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "char")){
                TokenValue value = {
                    .keyword = TOKEN_CHAR
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "double")){
                TokenValue value = {
                    .keyword = TOKEN_DOUBLE
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "float")){
                TokenValue value = {
                    .keyword = TOKEN_FLOAT
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "if")){
                TokenValue value = {
                    .keyword = TOKEN_IF
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "else")){
                TokenValue value = {
                    .keyword = TOKEN_ELSE
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "while")){
                TokenValue value = {
                    .keyword = TOKEN_WHILE
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "do")){
                TokenValue value = {
                    .keyword = TOKEN_DO
                };
                tokenStream_push(stream, keyword, token, value);
            }
            if(strcmp(token, "for")){
                TokenValue value = {
                    .keyword = TOKEN_FOR
                };
                tokenStream_push(stream, keyword, token, value);
            }

        }
        return stream;
}
