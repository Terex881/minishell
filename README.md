# Minishell

## 📋 Project Overview

**Minishell** is a custom-built shell developed as part of the 42 Network curriculum. It aims to replicate the behavior of standard Unix shells by implementing core functionalities such as command parsing, execution, redirection, and piping.

---

## 🚀 Features

- 🛠️ **Command Execution**: Executes binaries found in `PATH` and handles built-in commands.
- 🔁 **Redirection & Piping**: Supports input (`<`), output (`>`, `>>`), and pipes (`|`) for command chaining.
- 📦 **Built-in Commands**:
  - `echo`
  - `cd`
  - `pwd`
  - `env`
  - `export`
  - `unset`
  - `exit`
- 🔐 **Secure Parsing**: Handles single/double quotes and metacharacters correctly to ensure reliable input parsing.
- 📄 **Environment Variables**: Built-in management for exporting, unsetting, and using env variables.
- 🧠 **Signal Handling**: Manages `CTRL-C`, `CTRL-D`, and `CTRL-\` for better terminal experience.

---

## 💡 Implementation Highlights

- Custom lexer and parser for tokenizing complex shell input
- Built-in command handler using function pointers
- File descriptor management for input/output duplication and piping
- `fork()`, `execve()`, and `waitpid()` used for process execution

---

## 🧪 How to Use

### 🔧 Compilation

```bash
make
```

### ▶️ Running Minishell

```bash
./minishell
```

You can now run commands just like in Bash or Zsh, e.g.:

```bash
echo Hello | cat -e > out.txt
export PATH=$PATH:/my/bin
cd ~/Desktop
```

---

## ⚙️ Development Stack

- Language: C
- Libraries: `readline`, `termios`, `signal`, `unistd`
- System Calls: `fork`, `execve`, `pipe`, `dup2`, `waitpid`

---

## 🔍 Key Considerations

- Proper memory and file descriptor cleanup after each command
- Full quote and escape character compliance
- Bash-like behavior for built-ins and syntax

---

## 📜 License

This project is part of the **42 Network** curriculum and is provided for educational purposes.

---

## 🙋‍♂️ Contributors
@sdemnati (Salah Demnati) — Parsing, signal handling, and input management

@cmasnaou (Chorouk Masnaoui) — Command execution, piping, and redirection
