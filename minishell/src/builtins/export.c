/* ************************************************************************** */
/*   export.c - builtin export (pseudocódigo)                                  */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
bi_export(argv, &env):
  se sem argumentos: imprimir env ordenado no formato export
  senão para cada arg KEY=VAL:
    validar nome; se inválido -> erro e continuar
    env_set(&env, KEY, VAL, overwrite=1)
  return status (1 se algum inválido)
*/
