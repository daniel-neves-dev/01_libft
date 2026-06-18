*This project has been created as part of the 42 curriculum by dneves-d.*
<h1 align="center">Libft</h1>

<p align="center">
  <b>The foundational framework of the 42 curriculum.</b><br>
  An implementation of a custom C library replicating standard system behaviors and dynamic data structures.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c&logoColor=white" alt="Language" />
  <img src="https://img.shields.io/badge/Build-Makefile-9cc2e5?style=flat-square&logo=gnu&logoColor=black" alt="Build" />
  <img src="https://img.shields.io/badge/Norm-v3-success?style=flat-square" alt="Norm" />
</p>

---

## 📋 Description
The **Libft** project serves as the introduction to the imperative programming pipeline at 42. Its objective is to re-code a core selection of functions from the standard C library (`libc`), alongside a set of custom algorithmic string utilities and linked list manipulation structures.

Developing this library from scratch enforces a rigorous understanding of memory allocation models, raw pointer manipulation, boundary checking, and compilation flags. The compiled static archive (`libft.a`) acts as a persistent resource used across subsequent school assignments (such as *get_next_line*, *ft_printf*, and *push_swap*).

---

## 🛠️ Instructions

### Prerequisites
* A standard Unix-like environment (Linux, macOS)
* A C compiler (`cc`)
* GNU `make` and `ar` utilities

### Installation & Compilation
Clone your repository and navigate to the root directory. The project is managed by a strict `Makefile` configured with `-Wall -Wextra -Werror` to prevent errors or illegal relinking routines.

```bash
# Compile all mandatory libc and additional utility functions
make

# Compile mandatory functions along with bonus linked-list structures
make bonus

# Remove intermediate object files (.o) safely
make clean

# Purge all object files and the final libft.a static archive
make fclean

# Reset the build pipeline completely
make re
```
🗂️ Library Architecture & LayoutThe toolkit functions are separated logically across three explicit components:
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

----

📚 Resources & Learning Footprint
Industry Documentation & StandardizationsGNU C Library Manual Reference   Linux Kernel Standard Base Specifications / System Man Pages

AI Usage & Integrity Framework
In accordance with Chapters III and V of the project guidelines, AI systems were exclusively configured as a peer-dialogue conceptual scaffold rather than an automated writing tool:
