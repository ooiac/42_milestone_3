/* ************************************************************************** */
/*   echo.c - builtin echo (pseudocódigo)                                      */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
bi_echo(argv):
  flag_n = 0
  pular nome do comando
  enquanto argv[i] começa com -n e só tem 'n': flag_n=1; i++
  imprimir argv[i..] separados por espaço
  se !flag_n: imprimir "\n"
  return 0
*/
