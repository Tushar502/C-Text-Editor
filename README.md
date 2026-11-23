# C Text Editor

A terminal-based text editor developed using the C programming language and the **ncurses** library. This project provides basic text-editing functionality directly within the terminal, including inserting, deleting, navigating, opening, and saving text files.

## Features

- **Text Insertion:** Insert characters at the current cursor position.
- **Character Deletion:** Delete characters using Backspace or Delete.
- **Line Management:** Insert new lines and merge lines.
- **Cursor Navigation:** Move through the document using arrow keys.
- **Home & End:** Jump to the beginning or end of a line.
- **File Handling:** Open and save text files.
- **Save As:** Save the document with a new filename.
- **Dynamic Memory Allocation:** Allocate and expand memory as additional lines are inserted.
- **Scrolling:** Navigate through documents that exceed the visible terminal area.
- **Status Bar:** Display the current row, column, cursor position, and total number of lines.

## Technologies Used

- C Programming Language
- ncurses Library
- File Handling
- Pointers and Dynamic Memory Allocation
- Structures and String Manipulation

## Requirements

- Linux-based operating system
- GCC Compiler
- ncurses development library

Install ncurses on Ubuntu:

```bash
sudo apt install libncurses-dev
```

## Compilation

Compile the project using GCC:

```bash
gcc project.c -o text_editor -lncurses
```

## How to Run

Run the executable by providing the filename, number of rows, and number of columns:

```bash
./text_editor sample.txt 20 80
```

Here:
- `sample.txt` – File to edit.
- `20` – Initial number of allocated rows.
- `80` – Maximum number of characters per line.

## Keyboard Shortcuts

| Key | Function |
|---|---|
| Arrow Keys | Move cursor |
| Backspace | Delete character before cursor |
| Delete | Delete character at cursor |
| Enter | Insert a new line |
| Home | Move to beginning of line |
| End | Move to end of line |
| F2 | Save file |
| F3 | Open file |
| F4 | Save As |
| Esc | Exit editor |

## Learning Outcomes

Through this project, I explored:

- Dynamic memory allocation using `malloc()` and `realloc()`.
- Working with pointers and double pointers.
- File operations using `fopen()`, `fread()`, `fwrite()` and `fprintf()`.
- String manipulation in C.
- Keyboard input handling using ncurses.
- Terminal-based user interface development.
- Managing text using dynamically allocated memory.

## Author

Developed as a C programming project.
