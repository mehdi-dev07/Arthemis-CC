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
    Token *tokens;
    struct tokenStream *stream;
    tokenStream_init(stream);

    tokens = (Token*)malloc(10 * sizeof(Token));
    char* token = (char*)malloc(20* sizeof(char));
    int i,j;
    int len;
    int count = 0;
        for(i = 0; i<n ; i++)
        {
            if(input[i] == '(')
            {
                tokenStream_push(stream, punctuation, "(");
            }
            if(input[i] == ')')
            {
                tokenStream_push(stream, punctuation, ")");
            }
            if(input[i] == '{')
            {
                tokenStream_push(stream, punctuation, "{");
            }
            if(input[i] == '}')
            {
                tokenStream_push(stream, punctuation, "}");
            }
            if(input[i] == '+')
            {
                tokenStream_push(stream, operation, "+");
            }
            if(input[i] == '-')
            {
                tokenStream_push(stream, operation, "-");
            }
            if(input[i] == '*')
            {
                tokenStream_push(stream, operation, "*");
            }
            if(input[i] == '/')
            {
                tokenStream_push(stream, operation, "/");
            }
            if(input[i] == '=' && input[i+1] == '=')
            {
                tokenStream_push(stream, operation, "==");
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
                tokenStream_push(stream, identifier, token);
            }
            if(strcmp(token, "int")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "return")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "char")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "double")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "float")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "if")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "else")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "while")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "do")){
                tokenStream_push(stream, keyword, token);
            }
            if(strcmp(token, "for")){
                tokenStream_push(stream, keyword, token);
            }

        }
        return stream;
}
