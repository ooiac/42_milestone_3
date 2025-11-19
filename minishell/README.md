# 🇺🇸 Minishell (42) — Shell Implementation in C

A minimalist shell interpreter developed in C as part of the 42 Minishell project.

## 📋 Description

This project implements a basic shell similar to bash, capable of:
- Executing commands with PATH resolution
- Managing environment variables
- Implementing builtins (echo, cd, pwd, export, unset, env, exit)
- Executing pipelines
- Managing redirections (in development)
- Command history via readline

## 🚀 Project Status

### ✅ Implemented (Half B - Execution)

**Environment Management:**
- ✅ Parsing `envp` to linked list
- ✅ Converting `t_env` → `char**` for `execve`
- ✅ Variable search and manipulation

**Executor:**
- ✅ Simple command execution with `fork/execve`
- ✅ PATH resolution
- ✅ Pipeline (base structure)
- ✅ Child process management

**Builtins:**
- ✅ `echo` (with `-n` flag)
- ✅ `cd` (directory navigation)
- ✅ `pwd` (current directory)
- ✅ `export` (add/modify variables)
- ✅ `unset` (remove variables)
- ✅ `env` (list environment)
- ✅ `exit` (with exit code)

**Interface:**
- ✅ Main loop with `readline()`
- ✅ Command history

### 🔄 In Development (Half A - Parser)

- ⏳ Lexer (tokenization)
- ⏳ Parser (AST construction)
- ⏳ Variable expansion (`$VAR`)
- ⏳ Redirections (`<`, `>`, `>>`)
- ⏳ Heredoc (`<<`)
- ⏳ Signals (Ctrl-C, Ctrl-\, Ctrl-D)
- ⏳ Quotes (single and double)

## 🛠️ Compilation

### Requirements:
- GCC or Clang
- Make
- readline library (`libreadline-dev`)
- Linux/Unix system or WSL (Windows)

### Compile:
```bash
make
```

### Run:
```bash
./minishell
```

### Clean:
```bash
make fclean
```

## 📁 Project Structure

```
minishell/
├── main.c                    # Entry point
├── Makefile
├── include/
│   └── minishell.h          # Main headers
├── libft/                    # libft library
├── src/
│   ├── env/                 # Environment management
│   │   ├── env.c
│   │   └── env_to_envp.c
│   ├── executor/            # Command execution
│   │   ├── exec.c
│   │   ├── resolve_path.c
│   │   ├── pipeline.c
│   │   └── pipeline_utils.c
│   ├── shell/               # Main loop
│   │   └── shell.c
│   └── builtins/            # Built-in commands
│       ├── builtin_utils.c
│       ├── builtin_echo.c
│       ├── builtin_pwd.c
│       ├── builtin_env.c
│       ├── builtin_cd.c
│       ├── builtin_export.c
│       ├── builtin_unset.c
│       └── builtin_exit.c
└── WORK_SPLIT.txt           # Work division
```

## 🧪 Basic Tests

```bash
minishell> pwd
minishell> echo hello world
minishell> echo -n test
minishell> env
minishell> export TEST=123
minishell> env | grep TEST
minishell> unset TEST
minishell> cd /tmp
minishell> pwd
minishell> ls -la
minishell> exit
```

## 📝 Norminette

Project developed following 42's Norminette:
- Maximum 25 lines per function
- Maximum 5 functions per file
- No `for`, only `while`
- Naming conventions

To check:
```bash
norminette
```

## 👥 Work Division

As per `WORK_SPLIT.txt`:
- **Half A**: Lexer, Parser, Expander, Heredoc (in development)
- **Half B**: Executor, Builtins, Env, Redirections (implemented)

## 📚 Resources

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [execve man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)

## ⚠️ Note

This project is under active development. Integration between parser (Half A) and executor (Half B) will be done later.

---

# 🇧🇷 Minishell (42) — Implementação de Shell em C

Um interpretador de shell minimalista desenvolvido em C como parte do projeto Minishell da 42.

## 📋 Descrição

Este projeto implementa um shell básico similar ao bash, capaz de:
- Executar comandos com resolução de PATH
- Gerenciar variáveis de ambiente
- Implementar builtins (echo, cd, pwd, export, unset, env, exit)
- Executar pipelines
- Gerenciar redireções (em desenvolvimento)
- Histórico de comandos via readline

## 🚀 Status do Projeto

### ✅ Implementado (Metade B - Execução)

**Gerenciamento de Ambiente:**
- ✅ Parsing de `envp` para lista encadeada
- ✅ Conversão `t_env` → `char**` para `execve`
- ✅ Busca e manipulação de variáveis

**Executor:**
- ✅ Execução de comandos simples com `fork/execve`
- ✅ Resolução de PATH
- ✅ Pipeline (estrutura base)
- ✅ Gestão de processos filhos

**Builtins:**
- ✅ `echo` (com flag `-n`)
- ✅ `cd` (navegação de diretórios)
- ✅ `pwd` (diretório atual)
- ✅ `export` (adicionar/modificar variáveis)
- ✅ `unset` (remover variáveis)
- ✅ `env` (listar ambiente)
- ✅ `exit` (com código de saída)

**Interface:**
- ✅ Loop principal com `readline()`
- ✅ Histórico de comandos

### 🔄 Em Desenvolvimento (Metade A - Parser)

- ⏳ Lexer (tokenização)
- ⏳ Parser (construção de AST)
- ⏳ Expansão de variáveis (`$VAR`)
- ⏳ Redireções (`<`, `>`, `>>`)
- ⏳ Heredoc (`<<`)
- ⏳ Sinais (Ctrl-C, Ctrl-\, Ctrl-D)
- ⏳ Aspas (simples e duplas)

## 🛠️ Compilação

### Requisitos:
- GCC ou Clang
- Make
- Biblioteca readline (`libreadline-dev`)
- Sistema Linux/Unix ou WSL (Windows)

### Compilar:
```bash
make
```

### Executar:
```bash
./minishell
```

### Limpar:
```bash
make fclean
```

## 📁 Estrutura do Projeto

```
minishell/
├── main.c                    # Entry point
├── Makefile
├── include/
│   └── minishell.h          # Headers principais
├── libft/                    # Biblioteca libft
├── src/
│   ├── env/                 # Gerenciamento de ambiente
│   │   ├── env.c
│   │   └── env_to_envp.c
│   ├── executor/            # Execução de comandos
│   │   ├── exec.c
│   │   ├── resolve_path.c
│   │   ├── pipeline.c
│   │   └── pipeline_utils.c
│   ├── shell/               # Loop principal
│   │   └── shell.c
│   └── builtins/            # Comandos internos
│       ├── builtin_utils.c
│       ├── builtin_echo.c
│       ├── builtin_pwd.c
│       ├── builtin_env.c
│       ├── builtin_cd.c
│       ├── builtin_export.c
│       ├── builtin_unset.c
│       └── builtin_exit.c
└── WORK_SPLIT.txt           # Divisão de trabalho
```

## 🧪 Testes Básicos

```bash
minishell> pwd
minishell> echo hello world
minishell> echo -n test
minishell> env
minishell> export TEST=123
minishell> env | grep TEST
minishell> unset TEST
minishell> cd /tmp
minishell> pwd
minishell> ls -la
minishell> exit
```

## 📝 Norminette

Projeto desenvolvido seguindo a Norminette da 42:
- Máximo 25 linhas por função
- Máximo 5 funções por arquivo
- Sem `for`, apenas `while`
- Naming conventions

Para verificar:
```bash
norminette
```

## 👥 Divisão de Trabalho

Conforme `WORK_SPLIT.txt`:
- **Metade A**: Lexer, Parser, Expander, Heredoc (em desenvolvimento)
- **Metade B**: Executor, Builtins, Env, Redireções (implementado)

## 📚 Recursos

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [execve man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)

## ⚠️ Nota

Este projeto está em desenvolvimento ativo. A integração entre parser (Metade A) e executor (Metade B) será feita posteriormente.
