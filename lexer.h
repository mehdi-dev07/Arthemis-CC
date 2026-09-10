#include <stdbool.h>

struct tokenStream* lexing(char* input, int n);
bool check_if_identifier(char* token, int len);
char* add_identifier(char* token, int len);
