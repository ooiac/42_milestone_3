/* ************************************************************************** */
/*   tokenize.c - Helpers do lexer (pseudocódigo)                              */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
is_operator_char(c):
  return (c == '|' || c == '<' || c == '>')

read_word(line, i):
  buffer = ""
  while i < len and not espaço e not operador:
    if line[i] == '\'' -> copiar até próxima '\''
    if line[i] == '"' -> copiar até próxima '"'
    else copiar char normal
  return buffer, i
*/
