/* ************************************************************************** */
/*   exit.c - builtin exit (pseudocódigo)                                      */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
bi_exit(argv, &should_exit):
  imprimir "exit" no modo interativo (como bash)
  if argv[1] não numérico: erro "numeric argument required", status=2, should_exit=1
  else if muitos argumentos: erro "too many arguments", return 1, should_exit=0
  else: should_exit=1, status = (argv[1] ? atoi(argv[1]) : last_status)
*/
