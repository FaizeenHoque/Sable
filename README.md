# Sable Shell

`sable` is a lightweight Unix-style shell written in C. It supports executing external commands, basic built-ins (`cd`, `exit`), and displays a colorized prompt showing your username and current working directory.

---

## Features

* Execute external programs (e.g. `ls`, `echo`, `pwd`)
* Built-in commands:

  * `cd` — change directories
  * `exit` — quit the shell
* Colored prompt for clarity:

  * **Blue** — username
  * **Green** — current directory
* Simple and readable codebase for learning shell design

---

## Project Structure

```
Sable/
├── src/
│   ├── main.c
│   ├── loop.c
│   ├── execute.c
│   ├── builtin.c
│   ├── utils.c
│   └── sable.h
├── Makefile
└── README.md
```

All source and header files live in the `src/` directory.
The `Makefile` handles compilation and cleanup automatically.

---

## Requirements

* GCC or Clang compiler
* A Unix-like environment (Linux, macOS, or WSL)

---

## Building

To compile the shell, run:

```bash
make
```

This creates an executable named `sable` in the `build/` directory.

To rebuild from scratch:

```bash
make clean
make
```

---

## Running

```bash
./build/sable
```

Once running, you can execute commands, change directories with `cd`, or exit using `exit`.

Prompt example:

```
username:/current/directory$
```

---

## Notes

* Built-ins like `cd` and `exit` are handled internally.
* Features such as pipes, redirection, or background jobs are **not yet implemented**.
* Intended as a learning tool and foundation for more advanced shells.

---

## License

[MIT](LICENSE)
