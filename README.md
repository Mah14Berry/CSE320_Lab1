# GDB Scavenger Hunt — CSE 320

## Overview

Your download contains a small program that hides **7 treasure values** in memory. The program **does not print the treasures** when it runs normally. Your job is to find every value using **GDB**.

This assignment is practice for the kind of debugging you will do on later homework (heap allocators, memory corruption, crashes). You will inspect:

- Global and static data
- The call stack
- Heap allocations and pointer chains
- Values that depend on control flow or computed inputs

Each treasure is a value you can recover in GDB (typically shown as hex when you submit).

---

## Provided files

| File | Description |
|------|-------------|
| `scavenger_hunt` | Stripped hunt binary (run this under GDB) |
| `scavenger_hunt.dbg` | Separate debug symbols (GDB loads these automatically) |
| `unhidden_maps.c` | Companion source with additional hunt logic |
| `README.md` | This document |

You do **not** need to modify these files for credit.

---

## Getting started

### Run under GDB

```bash
gdb ./scavenger_hunt
```

Inside GDB:

```
(gdb) break main
(gdb) run
```

The program sets up its hidden state, then enters an idle loop so you have time to explore. Use `Ctrl+C` in the terminal (or interrupt from GDB) if you need to regain control while it is paused.

### Useful first commands

| Command | Purpose |
| -------- | -------- |
| `info functions` | List function names — good for spotting interesting call chains |
| `info variables` | List global/static variables |
| `info locals` | Variables in the **current** stack frame |
| `info frame` | Details about the current frame |
| `up` / `down` | Move to caller / callee stack frames |
| `backtrace` / `bt full` | Show the call stack (with locals) |
| `print expr` | Evaluate a C expression |
| `x/s addr` | Examine memory at `addr` as a string |
| `x/Ngx addr` | Examine `N` eight-byte values in hex |
| `x/Nwx addr` | Examine `N` four-byte words in hex |
| `x/Nbx addr` | Examine `N` raw bytes |
| `finish` | Run until the current function returns |
| `continue` | Resume execution |

Replace `addr` with a symbol, variable, or pointer expression.

---

## Your task

Find all **7** treasures. For each one, record the value you will submit (hex is fine). Partial credit applies — submit what you found even if you did not get all 7.

When you are ready, use the course web form to check your seven values against the grader.

---

## Where secrets might be hiding

The program uses several hiding strategies. Below are **categories** to investigate; figuring out the exact symbol, frame, or pointer path is part of the hunt.

### 1. Global and static storage

Some values live in global or file-scope `static` variables for the entire run. They may have obvious names — or live inside functions that are never called from `main`.

**Ideas to try:** `info variables`, `info functions`, and `print` on suspicious symbols.

### 2. The call stack

Not every local variable is visible from `main`. Functions call other functions; a value may exist only in a **deeper stack frame**, or only on a particular iteration of a loop.

**Ideas to try:** Set breakpoints (including conditional breakpoints), use `info locals`, `up` / `down`, and `bt full`.

### 3. The heap

Setup code uses `malloc` / `calloc` to build structures on the heap. Treasures may sit:

- Behind a global pointer into an array or block
- Behind a chain of pointers (linked list)
- At an offset you discover by examining nearby pointers

**Ideas to try:** `print` global pointers that reference heap data, follow `->next` links, and use `x` / `x/w` on pointer expressions.

### 4. Computed values

Some treasures are not sitting in a variable waiting to be printed — you may need to call or step through a function with the **correct inputs** so a validity flag becomes true and the value is meaningful.

---

## Suggested workflow

1. **Break early** — `break main`, then `run`, then continue through setup so heap and stack state exist.
2. **Survey symbols** — skim `info functions` and `info variables` before guessing randomly.
3. **Work by category** — find globals first, then stack, then heap, then computed values.
4. **Write down values as you go** — you will need all seven for submission.

---

## Tips

- **Keep the `.dbg` file next to the binary** so GDB can resolve symbols and source lines.
- **Strings command:** From a shell, `strings scavenger_hunt` will not reveal the treasures — you need GDB.
- **If the program seems stuck:** It is waiting in a loop on purpose. Interrupt with `Ctrl+C`, set breakpoints, and `run` again from the start.
- **Examine memory as words when needed:** Prefer `x/wx` or `x/gx` for integer payloads; use `print` when you have a typed expression.
- **Pointer arithmetic:** In GDB you can cast and offset — adjust based on what you discover in `x` dumps and `print` output.

---

## GDB quick reference (memory examination)

```
print my_ptr                  # address stored in my_ptr
print *my_ptr                 # first level of dereference
x/s my_ptr                    # try as string
x/16bx my_ptr                 # 16 bytes in hex
x/4wx some_ptr                # four 4-byte words
info locals                   # locals in current frame
bt full                       # backtrace with locals
up                            # move to calling frame
```

---

## Academic integrity

You may discuss GDB techniques and general strategies with classmates. **Your submitted values and any write-up must be your own** — they should reflect work you did. Do not share completed treasure lists or copy another student’s answers.

Good hunting.
