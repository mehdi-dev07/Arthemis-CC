#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *input = (char *)malloc(file_size + 1);
    if(input == NULL)
    {
        printf("Error: could not allocate memory\n");
        fclose(file);
        return 1;
    }

    size_t read = fread(input, 1, file_size, file);
    if(read != file_size)
    {
        printf("Error: could not read entire file\n");
        free(input);
        fclose(file);
        return 1;
    }
    input[file_size] = '\0';

    fclose(file);
    struct tokenStream *tokens = lexing(input, file_size);

    for (int i = 0; i < tokens->size; i++)
    {
        printf("%s\n", tokens->tokens[i].lexeme);
    }

    free(input);
    tokenStream_free(tokens);
    return 0;
}
