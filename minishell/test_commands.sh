#!/bin/bash

echo "=== Testing Minishell ==="
echo ""

# Test 1: Echo command
echo "Test 1: Echo command"
echo 'echo "Hello, World!"' | ./minishell
echo ""

# Test 2: PWD command
echo "Test 2: PWD command"
echo 'pwd' | ./minishell
echo ""

# Test 3: ENV command
echo "Test 3: ENV command (showing first 5 lines)"
echo 'env' | ./minishell | head -5
echo ""

# Test 4: Export and echo variable
echo "Test 4: Export and echo variable"
echo -e 'export TEST_VAR=42\necho $TEST_VAR' | ./minishell
echo ""

# Test 5: CD command
echo "Test 5: CD command"
echo -e 'cd /tmp\npwd' | ./minishell
echo ""

# Test 6: Pipes
echo "Test 6: Pipes"
echo 'echo "test" | cat' | ./minishell
echo ""

# Test 7: Exit status
echo "Test 7: Exit status"
echo -e 'ls /nonexistent 2>&1\necho $?' | ./minishell
echo ""

# Test 8: Multiple commands
echo "Test 8: Multiple commands with semicolon"
echo 'echo "first" && echo "second"' | ./minishell
echo ""

echo "=== Tests completed ==="
