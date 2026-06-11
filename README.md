*This project has been created as part of the 42 curriculum by dneves-d.*

# Libft - Your very first own library

## Description
The **Libft** project is a foundational assignment in the 42 São Paulo curriculum. Its primary goal is to re-code a subset of the standard C library (`libc`) functions, alongside additional utility functions and data structure manipulations using linked lists.

By implementing these functions from scratch, this project provides a deep, mechanical understanding of memory allocation, pointer arithmetic, string manipulation, and standard imperative programming patterns in C. The resulting archive file (`libft.a`) serves as a highly useful, personal utility library utilized throughout future C assignments in the school curriculum.

---

## Instructions

### Prerequisites
To compile and test this library, you require a C compiler (`gcc`) and the standard `ar` and `make` utilities.

### Compilation
All compilation files are managed through the provided `Makefile` located at the root of the repository. The Makefile compiles with standard safety flags (`-Wall -Wextra -Werror`) and does not perform unnecessary relinking.

* **Compile mandatory functions:**
    ```bash
    make
    ```
  or
    ```bash
    make all
    ```
* **Compile bonus functions (Linked Lists):**
    ```bash
    make bonus
    ```
* **Clean object files:**
    ```bash
    make clean
    ```
* **Clean object files and the compiled library archive:**
    ```bash
    make fclean
    ```
* **Re-compile the entire library from scratch:**
    ```bash
    make re
    ```

### Usage
To incorporate `libft` into your own development projects, include the header file in your C source files and link the static library during compilation:

```c
#include "libft.h"
