#!/bin/bash
> output_diff.txt
# Define the command you want to run
testing()
{
  local CMD="$1"
  # Run the command in bash and capture the exit code and output
  bash_output=$(eval $CMD 2>&1 | grep -o "lso.*")
  bash_exit_code=$?

  # Write the exit code and output to a file
  echo "exit code: $bash_exit_code" > output_bash.txt
  echo "$bash_output" >> output_bash.txt

  # Run the command in your minishell and capture the exit code and output
  minishell_output=$(echo "$CMD" | ./ms.out | grep -v "Welcome to" | grep -v "ms ")
  minishell_exit_code=$?

  # Write the exit code and output to the same file
  echo "exit code: $minishell_exit_code" > output_ms.txt
  echo "$minishell_output" >> output_ms.txt
  >> output_diff.txt diff output_ms.txt output_bash.txt
}

while IFS= read -r line; do
  testing "$line"
done < minihell.txt
