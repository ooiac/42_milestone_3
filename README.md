# 42 School — Milestone 3

Welcome to **Milestone 3** of the 42 School curriculum! This milestone contains two major projects that focus on **system programming, process management, and low-level Unix concepts**.

## Overview

Milestone 3 represents a significant step up in complexity from earlier milestones. It challenges students to implement sophisticated system tools and understand concurrent programming with multi-threading and multi-processing.

| Project | Type | Language | Key Concepts |
|---------|------|----------|--------------|
| **Minishell** | System Tool | C | Shell implementation, process management, file descriptors, parsing |
| **Philosophers** | Concurrent Simulation | C | Threading, mutex synchronization, deadlock prevention |

---

## Project 1: Minishell

### What It Is

**Minishell** is a simplified shell interpreter (like bash) written in C. It's one of the most comprehensive projects in the 42 curriculum, requiring students to build a complete command-line interpreter from scratch.

### Features Implemented

#### Environment & Variable Management
- **Environment Parsing**: Read and manage the process environment (`envp`)
- **Environment Variables**: Create, modify, and delete environment variables
- **Variable Expansion**: Expand `$VARIABLE` references in commands
- **Exit Status**: Track and expand `$?` (last command exit code)

#### Command Execution
- **Command Resolution**: Find executables using the `PATH` environment variable
- **Simple Commands**: Execute standalone programs with arguments
- **Pipelines**: Chain multiple commands together (e.g., `cat file.txt | grep "pattern" | wc -l`)
- **Process Management**: Fork and execute child processes using `fork()` and `execve()`

#### Built-in Commands (Shell Internals)
Unlike external programs, these run within the shell process:
- **`echo`**: Print text (with `-n` flag to omit newline)
- **`cd`**: Change directory
- **`pwd`**: Print working directory
- **`export`**: Define or modify environment variables
- **`unset`**: Remove environment variables
- **`env`**: Display all environment variables
- **`exit`**: Terminate the shell with an optional exit code

#### User Interface
- **Interactive Prompt**: Uses `readline()` library for user input
- **Command History**: Navigate previous commands (via readline)
- **Signal Handling**: Responds to Ctrl-C and other signals appropriately

### Under Development

- **Parser & Lexer**: Tokenizing input and building Abstract Syntax Trees (AST)
- **Redirections**: Input (`<`), output (`>`), append (`>>`)
- **Heredocs**: Multi-line input (`<<`)
- **Quote Handling**: Respecting single and double quotes semantics
- **Variable Expansion in All Contexts**: Proper expansion in quoted strings and redirections

### How It Works: Architecture

```
User Input (readline)
    ↓
Lexer (tokenization)
    ↓
Parser (syntax validation & AST building)
    ↓
Expander (variable expansion, quote removal)
    ↓
Executor (fork/execve or builtin invocation)
    ↓
Output Display or Environment Update
```

### Learning Outcomes

- **Understanding Unix processes**: How `fork()` and `execve()` work
- **File Descriptors & Pipes**: Inter-process communication
- **Parsing & Lexical Analysis**: Building interpreters
- **Environment Management**: Working with system variables
- **System Calls**: Deep dive into kernel interfaces

### Compilation & Usage

```bash
cd minishell
make              # Compile the project
./minishell       # Run the shell
exit              # Type to quit
```

---

## Project 2: Philosophers (Dining Philosophers Problem)

### What It Is

**Philosophers** simulates the classic "Dining Philosophers Problem"—a synchronization puzzle that illustrates deadlock, resource allocation, and concurrent programming challenges. Students implement it using **POSIX threads (pthreads)** and mutex locks.

### The Problem Scenario

Imagine N philosophers sitting at a round table with spaghetti in the center. Each philosopher needs two forks to eat (one on each side), but there are only N forks total—one between each pair of neighbors.

```
        🍴 Philosopher 1 🍴
        ↙              ↖
   Forks              Forks
        ↙              ↖
   🍴 Philosopher N    Philosopher 2 🍴
```

Each philosopher alternates between three states:
1. **Eating** (holding two forks)
2. **Sleeping** (thinking, no forks needed)
3. **Thinking** (reflecting, no forks needed)

### The Challenge

The core problem: **How do you prevent deadlock and starvation?**

**Deadlock** occurs when:
- Philosopher A picks up their left fork
- Philosopher B picks up their right fork
- A waits for their right fork (held by B)
- B waits for their left fork (held by A)
→ Both wait forever!

**Starvation** occurs when:
- Some philosophers never get to eat because others monopolize the forks

### Solution Approach

Your implementation uses:

- **Pthreads**: Create one thread per philosopher
- **Mutexes**: Lock each fork to prevent simultaneous access
- **Synchronization**: Coordinate philosopher actions without deadlock
- **Timing**: Track meal times and enforce time limits (death if too hungry)

### Key Parameters

The program takes command-line arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [optional: number_of_meals]
```

| Parameter | Meaning |
|-----------|---------|
| `number_of_philosophers` | How many philosophers (also number of forks) |
| `time_to_die` | Milliseconds a philosopher can go without eating before dying |
| `time_to_eat` | Milliseconds it takes to eat |
| `time_to_sleep` | Milliseconds a philosopher sleeps |
| `number_of_meals` | (Optional) If specified, simulation ends after each philosopher eats this many times |

### Example Usage

```bash
# 5 philosophers, 800ms until starvation, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Philosophers eat 7 meals each, then stop
./philo 4 410 100 100 7
```

### What Happens at Runtime


The program should output lines showing each philosopher's actions with timestamps:

```
[timestamp] [philosopher_number] has taken a fork
[timestamp] [philosopher_number] is eating
[timestamp] [philosopher_number] is sleeping
[timestamp] [philosopher_number] is thinking
[timestamp] [philosopher_number] died
```

Example:
```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
500 2 has taken a fork
500 2 is eating
...
```

### Learning Outcomes

- **Concurrent Programming**: Managing multiple threads
- **Synchronization Primitives**: Mutex locks and thread safety
- **Deadlock Prevention**: Strategies to avoid circular wait conditions
- **Race Conditions**: Identifying and fixing data races
- **System Timing**: Working with millisecond precision using `gettimeofday()`
- **Thread Lifecycle**: pthread creation, joining, and cleanup

### Compilation & Usage

```bash
cd philosophers
make                    # Compile
./philo 5 800 200 200  # Run simulation
```

---

## Why These Projects Matter

### Minishell
- **Practical Real-World Skill**: Shells are essential Unix tools
- **Comprehensive Systems Knowledge**: Touches every major OS concept (processes, environment, file descriptors)
- **Code Organization**: Large project requires thoughtful architecture
- **Parsing Skills**: Useful across programming disciplines

### Philosophers
- **Critical Concurrency Patterns**: Threading is everywhere in modern software
- **Synchronization Mastery**: Mutex locks, condition variables, and deadlock prevention
- **Performance Considerations**: How to write efficient multi-threaded code
- **Debugging Complexity**: Concurrent bugs are notoriously hard to find and fix

---

## Curriculum Context

| Milestone | Projects | Focus |
|-----------|----------|-------|
| 0 | libft | Build foundational C library |
| 1 | ft_printf, get_next_line | I/O and string manipulation |
| 2 | push_swap, minitalk | Algorithms and inter-process communication |
| **3** | **minishell, philosophers** | **Systems programming & concurrency** |
| 4 | cub3d | Graphics and ray-casting |

Milestone 3 is where students prove they understand how Unix systems work at a deep level. Success here opens doors to understanding virtually any systems-level code.

---

## Resources & References

### For Minishell:
- bash manual: `man bash`
- execve(2): `man execve`
- fork(2): `man fork`
- readline(3): GNU readline library documentation

### For Philosophers:
- pthread(7): `man pthread`
- pthread_create(3), pthread_join(3), pthread_mutex_lock(3)
- The classic paper: "Dining Philosophers Problem" by Edsger Dijkstra

---

## Checklist for Success

### Minishell
- [ ] Environment variables work correctly
- [ ] Builtins (echo, cd, pwd, export, unset, env, exit) function properly
- [ ] Pipes connect commands correctly
- [ ] PATH resolution finds executables
- [ ] Child processes fork and execute without hanging
- [ ] Readline integration works smoothly
- [ ] Edge cases handled (empty commands, missing files, etc.)

### Philosophers
- [ ] Threads start and stop cleanly
- [ ] All philosophers can eat (no indefinite starvation)
- [ ] Death detection works accurately
- [ ] Philosophers don't pick up the same fork twice
- [ ] Timestamps are accurate (millisecond precision)
- [ ] Optional meal limit works when specified
- [ ] No data races or segmentation faults

---

## Tips for Success

1. **Minishell**: Start with parsing and lexing early. A solid AST makes everything else easier.
2. **Philosophers**: Test with small numbers of philosophers first (2-3) to debug synchronization issues.
3. **Both**: Write clear, modular code. These aren't small projects—organization is key.
4. **Testing**: Create comprehensive test cases before implementation.
5. **Debugging**: Use tools like `strace`, `ltrace`, and `gdb` to understand system behavior.

---

**Good luck! Milestone 3 is challenging but incredibly rewarding.**
