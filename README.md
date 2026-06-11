*This project has been created as part of the 42 curriculum by dneves-d.*

# Libft - Your very first own library

## Description
The **Libft** project is a foundational assignment in the 42 São Paulo curriculum. Its primary goal is to re-code a subset of the standard C library (`libc`) functions, alongside additional utility functions and data structure manipulations using linked lists.

By implementing these functions from scratch, this project provides a deep, mechanical understanding of memory allocation, pointer arithmetic, string manipulation, and standard imperative programming patterns in C. The resulting archive file (`libft.a`) serves as a highly useful, personal utility library utilized throughout future C assignments in the school curriculum.

---

1. Libc Functions (Part 1)

   Re-implementations of classic functions from <string.h>, <ctype.h>, and <stdlib.h>. They adhere exactly to their behavior described in standard system man pages:

- Character Validation & Conversion: ft_isalpha, ft_isdigit, ft_isalnum, ft_isascii, ft_isprint, ft_toupper, ft_tolower.

- Memory Management: ft_memset, ft_bzero, ft_memcpy, ft_memmove, ft_memchr, ft_memcmp, ft_calloc.

- String Manipulation: ft_strlen, ft_strlcpy, ft_strlcat, ft_strchr, ft_strrchr, ft_strncmp, ft_strnstr, ft_strdup, ft_atoi.

2. Additional Functions (Part 2)

   Functional utilities either absent from standard libc or implemented in an altered design context tailored for future curriculum needs:

- ft_substr: Allocates and returns a substring from a given string context.

- ft_strjoin: Concatenates two strings together into a newly allocated string block.

- ft_strtrim: Trims predefined character sets away from both ends of a string.

- ft_split: Delimits a string into a clean array of newly allocated strings ending with a NULL pointer.

- ft_itoa: Converts integer primitives safely into dynamic string representations handling negatives.

- ft_strmapi / ft_striteri: Map or iterate application functions over string indices.

- ft_putchar_fd / ft_putstr_fd / ft_putendl_fd / ft_putnbr_fd: Simple safe data output streams targeted specifically via file descriptors.

3. Linked List Utility Functions (Bonus Part)

   A collection of node tools leveraging custom structure declarations (t_list) to orchestrate programmatic dynamic structures smoothly:

- ft_lstnew, ft_lstadd_front, ft_lstsize, ft_lstlast, ft_lstadd_back, ft_lstdelone, ft_lstclear, ft_lstiter, ft_lstmap.

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
