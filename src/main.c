#include "../includes/lexer.h"
#include "../includes/token.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error: could not open file %s\n", filename);
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *input = (char *)malloc(file_size + 1);
  if (input == NULL) {
    printf("Error: could not allocate memory\n");
    fclose(file);
    return 1;
  }

  size_t read = fread(input, 1, file_size, file);
  if (read != file_size) {
    printf("Error: could not read entire file\n");
    free(input);
    fclose(file);
    return 1;
  }
  input[file_size] = '\0';
  fclose(file);

  TokenStream *stream;

  stream = lexing(input, file_size);
  for (int i = 0; i < stream->size; i++) {
    printf("%s ", stream->tokens[i].lexeme);
  }
  printf("\n");

  tokenStream_free(stream);
  free(input);
  return 0;
}
