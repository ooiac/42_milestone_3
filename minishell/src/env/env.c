/* ************************************************************************** */
/*   env.c - gestão de ambiente (pseudocódigo)                                 */
/* ************************************************************************** */

/* PSEUDOCÓDIGO
env_from_environ(envp):
  criar lista ligada t_env com pares key=val

env_get(env, key):
  percorrer lista e retornar valor ou NULL

env_set(&env, key, val, overwrite):
  se existe e overwrite: atualizar
  se não existe: inserir novo nó

env_unset(&env, key):
  remover nó correspondente

env_to_envp(env):
  converter lista para char ** "KEY=VAL"
*/
