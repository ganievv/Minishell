# Minishell

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Built-in Commands](#built-in-commands)
6. [Known Issues](#known-issues)
7. [Contributor](#contributor)

## Introduction

Minishell is a simple shell project that aims to replicate basic functionalities of a Unix shell. Created as part of a 42 curriculum project, it is written entirely in C and provides an interactive command-line interface for executing various commands.

## Features

- Custom shell prompt for user interaction.
- Command execution through PATH or absolute/relative paths.
- Handling of single (`'`) and double (`"`) quotes for meta-character prevention.
- Input/output redirection and piping.
- Support for environment variables and expansion of `$?`.
- Implementation of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` behaviors as in bash.
- Built-in commands, including `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

## Installation

Clone this repository and navigate to the project directory:

```bash
git clone https://github.com/ganievv/Minishell.git
cd Minishell
```

Compile the project using the provided Makefile:

```bash
make
```

## Usage

Launch Minishell by executing the compiled binary:

```bash
./minishell
```

The shell will provide a prompt for user input. You can enter commands as you would in a standard shell environment.

## Built-in Commands

Minishell implements several built-in commands:

- `echo [-n] [string ...]` - Outputs strings to the terminal.
- `cd [path]` - Changes the current directory.
- `pwd` - Prints the current working directory.
- `export [name[=value] ...]` - Sets environment variables.
- `unset [name ...]` - Unsets environment variables.
- `env` - Prints the environment.
- `exit [status]` - Exits the shell.

## Known Issues

- Potential memory leaks from `readline()` (outside project control).
- No support for specific advanced features such as job control.

## Contributor

- [Thomas Nakas](link-to-profile)
