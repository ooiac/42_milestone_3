# minishell

*A shell written in C for the 42 Common Core.*

This project implements a subset of Bash: an interactive prompt, command parsing, environment variables, builtins, external commands, pipelines, redirections, and heredocs. It uses `readline` for the prompt and command history.

The original README documented an early split between the parser and executor teams. Those parts have since been integrated in the source, so the old “parser in development” checklist is no longer a useful description of the project.

## Supported features

- External commands found through `PATH`, or called by a relative/absolute path.
- Pipelines using `pipe`, `dup2`, `fork`, and `execve`.
- Redirections: `<`, `>`, `>>`, and heredocs (`<<`).
- Single and double quotes, variable expansion (`$NAME`) and the last exit status (`$?`).
- Interactive history and signal handling.
- Builtins: `echo` (including `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

This is not a drop-in Bash replacement. Features outside the 42 subject, such as full job control or Bash scripting syntax, are not the goal.

## How a command gets executed

```text
readline(input)
    |
    v
lexer -> tokens and quote context
    |
    v
parser -> commands and pipeline structure
    |
    v
expansion / heredoc processing
    |
    v
executor -> builtins or child processes
    |
    v
wait / update exit status
```

A command such as `cat file.txt | grep test > result.txt` needs two child processes, a pipe between them, and the output file opened and connected to the appropriate descriptor. The parent shell closes the descriptors it doesn't need, then waits for its children.

Standalone builtins that change shell state (`cd`, `export`, `unset`, `exit`) are different from external commands. A `cd` executed only inside a child process would change the child's directory and leave the parent shell where it was.

Environment variables are stored internally in a linked representation. For external commands that use `execve`, that data has to be converted back to a NULL-terminated `char **envp` array. The implementation also keeps track of the previous exit status so `$?` works.

## Build

Requires Linux/Unix, a C compiler, Make, and readline development headers/libraries.

```sh
cd minishell
make
./minishell
```

Use `make clean`, `make fclean`, or `make re` to clean or rebuild. Run `norminette` if you're checking 42 formatting rules.

## Tests to try

```sh
pwd
echo hello world
echo -n "no newline"
export TEST=123
echo "$TEST"
echo '$TEST'
ls -la | wc -l
echo content > /tmp/minishell_test
cat < /tmp/minishell_test
cat << EOF
unset TEST
cd /tmp
pwd
exit
```

The two quoted `echo` commands should behave differently: `$TEST` expands in double quotes but stays literal in single quotes. Also check syntax errors, missing files, a failed executable, multiple pipes, and Ctrl-C at the prompt versus during a running child.

## Project layout and work division

| Area | Responsibility |
| --- | --- |
| `src/env/` | Environment variables and conversion for `execve`. |
| `src/lexer/`, `src/parser/` | Tokens, syntax validation, and command structure. |
| `src/expander/`, `src/heredoc/` | Expansion and heredoc input. |
| `src/executor/` | PATH resolution, processes, pipes, and redirections. |
| `src/builtins/` | Built-in shell commands. |
| `src/signals/`, `src/shell/` | Signals and interactive loop. |
| `include/`, `libft/` | Headers and common C functions. |

The original team division was **Half A** (lexer, parser, expansion, heredocs) and **Half B** (execution, builtins, environment, redirections). See `WORK_SPLIT.txt` for the original assignment.

References: [Bash reference manual](https://www.gnu.org/software/bash/manual/), `man 2 execve`, `man 2 pipe`, and [readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html).

---

## Resumo em português

O `minishell` é um shell interativo em C. A entrada passa pelo lexer, parser e expansor antes de chegar ao executor. Comandos externos usam `fork`/`execve` e busca pelo `PATH`; pipelines usam pipes e redirecionamento de descritores. Os builtins (`cd`, `export`, `unset`, etc.) alteram o estado do próprio shell quando executados isoladamente.

O README anterior estava desatualizado e marcava o parser e os heredocs como “em desenvolvimento”. O código atual já contém essas partes integradas. Os detalhes de compilação, estrutura e testes estão acima; os comandos são os mesmos nas duas línguas.
