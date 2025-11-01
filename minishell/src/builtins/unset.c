/* ************************************************************************** */
/*   unset.c - builtin unset (pseudocódigo)                                    */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
bi_unset(argv, &env):
  para cada nome em argv[1..]:
    validar nome
    env_unset(&env, nome)
  return 0
*/
