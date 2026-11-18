# Milestone 3 — minishell and philosophers

Two Unix programming projects in C. `minishell` deals with processes, file descriptors, command parsing, and the environment. `philosophers` is about threads that share resources and must avoid deadlocks and data races.

## minishell

Project: [`minishell/`](minishell/) · [Detailed README](minishell/README.md)

A Bash-like interactive shell built with `readline`, `fork`, `execve`, pipes, and file descriptor redirection. The point isn't to recreate Bash completely; it's to interpret and execute the required subset of shell syntax without delegating parsing to a system shell.

### Input to execution

```text
readline()
   |
   v
lexer              words, operators, quote context
   |
   v
parser             command and pipeline structure
   |
   v
expansion          $VARIABLE, $?, quote removal
   |
   v
executor           builtins, fork/execve, pipes, redirections
```

The shell resolves external executables using `PATH` and sets up pipes for commands such as `cat file | grep text | wc -l`. Redirections include `<`, `>`, `>>`, and heredocs (`<<`). Single and double quotes affect whether words are split or variables are expanded. The shell maintains an environment representation internally and converts it when passing the environment to `execve`.

The required builtins are `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`. Commands that change shell state, such as `cd` and `export`, must affect the parent shell when run as standalone builtins; running them only in a forked child would lose the changes.

Signals need different handling in the interactive prompt, a heredoc, and a child process. The source includes lexer, parser, expansion, heredoc, and redirection code, even though an older internal README described several of these as unfinished. See the internal README for the directory layout and work split.

```sh
cd minishell
make
./minishell
```

## philosophers

Project: [`philosophers/`](philosophers/)

An implementation of the dining philosophers problem with POSIX threads and mutexes. Each philosopher alternates between taking forks, eating, sleeping, and thinking. There are as many forks as philosophers, and each philosopher needs two to eat.

### The synchronization problem

A fork is shared state. If two philosophers grab it at the same time, the simulation is wrong; a mutex protects that fork. But using mutexes introduces the possibility of **deadlock**: every philosopher takes one fork and waits indefinitely for the other.

There is also **starvation**: a philosopher may not eat before their `time_to_die` limit even if the program hasn't deadlocked. A monitoring routine checks the last meal timestamps and stops the simulation when a death is detected or the optional meal target has been reached. Reads and writes to shared timestamps, stop flags, and meal counters must be synchronized as well; mutexes on forks alone do not prevent data races.

### Arguments

```sh
cd philosophers
make
./philo 5 800 200 200
./philo 4 410 100 100 7
```

```text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
```

All times are in milliseconds. With `meals_required`, the simulation can terminate once every philosopher has eaten enough; otherwise it runs until one dies. Output records a timestamp, philosopher ID, and action, for example:

```text
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
```

Test one philosopher separately: with only one fork, eating cannot begin. Also try tight timing values and compare runs with different philosopher counts. Tools like Valgrind's Helgrind can help detect accesses to shared state that were not protected by the same mutex.

Both programs require thinking beyond the happy path: `minishell` must preserve parent/child state correctly; `philosophers` must stay consistent even when thread scheduling changes between runs.
