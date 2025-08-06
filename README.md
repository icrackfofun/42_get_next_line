# 42_get_next_line

> A function that reads from a file descriptor and returns one line at a time, developed as part of the 42 curriculum.

## 📚 About

`get_next_line` is a project at [42 School](https://42.fr/) where the goal is to implement a function that reads from a file descriptor and returns each line, one at a time, including the newline character (`\n`) if present. This project is a great exercise in memory management, file I/O, and buffer handling in C.

## 🛠️ Function Prototype

```c
char *get_next_line(int fd);
