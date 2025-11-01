/* ************************************************************************** */
/*   cd.c - builtin cd (pseudocódigo)                                         */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
bi_cd(argv, &env):
  path = argv[1] ? argv[1] : env_get(env, "HOME")
  if chdir(path) < 0: imprimir erro; return 1
  atualizar PWD e OLDPWD no env
  return 0
*/
