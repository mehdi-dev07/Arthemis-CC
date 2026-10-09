gcc -Wall -Wextra -std=c11 -Iincludes \
  src/main.c src/lexer.c src/parser.c src/tokens.c \
  -o compiler
