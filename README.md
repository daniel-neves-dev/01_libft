*This project has been created as part of the 42 curriculum by dneves-d.*
<h1 align="center">📚 ibft</h1>

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
# Compile all functions.
make

# Remove intermediate object files (.o) safely
make clean

# Purge all object files and the final libft.a static archive
make fclean

# Reset the build pipeline completely
make re
```
### Project example:
Creat a 'main.c' file:

```c
#include "libft.h"
#include <stdio.h>

size_t count_words(char **words)
{
    size_t  i;

    if(!words)
        return (-1);

    i = 0;
    while(*words)
    {
        words++;
        i++;
    }
    return (i);
}

int	main(void)
{
    char const  *str = "  Hello 42 Brazil, testing   ";
    char        *clean_str;
    char        **words;
    int         i;

    printf("Original str: %s\n", str);

    // Using 'ft_strtrim' to remove spaces from beginning and end of the text.'
    clean_str = ft_strtrim(str, " ");
    if (!clean_str)
        return (1);
    
    printf("Str no spaces: %s\n", clean_str);

    //Using 'ft_split' to split the text in separated words.
    words = ft_split(clean_str, ' ');
    if(!words)
    {
        free(clean_str);
        return (1);
    }

    printf("\nWas found %lu words.\n\n", count_words(words));

    //Using 'ft_putstr_fd' to print the words.
    i = 0;
    while (words[i] != NULL)
    {
        
        ft_putstr_fd(words[i], 1);
        ft_putstr_fd("\n", 1);
        free(words[i]);
        i++;
    }
    
    return (0);
}

```
At the terminal type:

```bash
make
gcc main.c -L. libft.a -o my_program
./my_program
```

## 🗂️ Library Architecture & Layout. The toolkit functions are separated logically across three explicit components:

### 1. Library C Functions (Part 1)

#### Character classification

All return `1` if the character belongs to the tested class, `0` otherwise.

| Function | Description |
|---|---| 
| `int ft_isalpha(int c)` | Checks if `c` is a letter (a-z, A-Z) |
| `int ft_isdigit(int c)` | Checks if `c` is a digit (0-9) |
| `int ft_isalnum(int c)` | Checks if `c` is a letter or digit |
| `int ft_isascii(int c)` | Checks if `c` is in the ASCII table (0–127) |
| `int ft_isprint(int c)` | Checks if `c` is a printable character |

#### Character conversion

| Function | Description |
|---|---|
| `int ft_toupper(int c)` | Converts lowercase to uppercase |
| `int ft_tolower(int c)` | Converts uppercase to lowercase |

#### String manipulation

| Function | Description |
|---|---|
| `size_t ft_strlen(const char *s)` | Returns the length of the string |
| `char *ft_strchr(const char *s, int c)` | First occurrence of `c` in `s` |
| `char *ft_strrchr(const char *s, int c)` | Last occurrence of `c` in `s` |
| `int ft_strncmp(const char *s1, const char *s2, size_t n)` | Compares up to `n` bytes of two strings |
| `char *ft_strnstr(const char *h, const char *n, size_t len)` | Finds needle in haystack within `len` bytes |
| `size_t ft_strlcpy(char *dst, const char *src, size_t size)` | Safe string copy with NUL-termination guarantee |
| `size_t ft_strlcat(char *dst, const char *src, size_t size)` | Safe string concatenation with NUL-termination guarantee |

#### Memory

| Function | Description |
|---|---|
| `void *ft_memset(void *s, int c, size_t n)` | Fills `n` bytes with value `c` |
| `void ft_bzero(void *s, size_t n)` | Zeroes `n` bytes |
| `void *ft_memcpy(void *dst, const void *src, size_t n)` | Copies `n` bytes (no overlap) |
| `void *ft_memmove(void *dst, const void *src, size_t n)` | Copies `n` bytes (overlap-safe) |
| `void *ft_memchr(const void *s, int c, size_t n)` | Finds byte `c` in the first `n` bytes |
| `int ft_memcmp(const void *s1, const void *s2, size_t n)` | Compares `n` bytes of two memory regions |

#### Numeric conversion and allocation

| Function | Description |
|---|---|
| `int ft_atoi(const char *nptr)` | Converts string to integer |
| `void *ft_calloc(size_t nmemb, size_t size)` | Allocates and zeroes memory |
| `char *ft_strdup(const char *s)` | Duplicates a string into allocated memory |

---

### 2. Additional Functions (Part 2)

| Function | Description |
|---|---|
| `char *ft_substr(char const *s, unsigned int start, size_t len)` | Extracts substring from `s` starting at `start`, up to `len` chars |
| `char *ft_strjoin(char const *s1, char const *s2)` | Concatenates `s1` and `s2` into a new allocated string |
| `char *ft_strtrim(char const *s1, char const *set)` | Removes chars from `set` at both ends of `s1` |
| `char **ft_split(char const *s, char c)` | Splits `s` by delimiter `c`, returns NULL-terminated array |
| `char *ft_itoa(int n)` | Converts integer to string (handles negatives) |
| `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` | Applies `f` to each char, returns new string |
| `void ft_striteri(char *s, void (*f)(unsigned int, char*))` | Applies `f` in-place to each char of `s` |
| `void ft_putchar_fd(char c, int fd)` | Writes `c` to file descriptor `fd` |
| `void ft_putstr_fd(char *s, int fd)` | Writes string `s` to fd |
| `void ft_putendl_fd(char *s, int fd)` | Writes `s` followed by newline to fd |
| `void ft_putnbr_fd(int n, int fd)` | Writes integer `n` to fd |

---

### 3. Linked List Utility Functions

   A collection of node tools leveraging custom structure declarations (t_list) to orchestrate programmatic dynamic structures smoothly:

The `t_list` structure:

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

| Function | Description |
|---|---|
| `t_list *ft_lstnew(void *content)` | Creates a new node with `content` |
| `void ft_lstadd_front(t_list **lst, t_list *new)` | Inserts new node at the beginning of the list |
| `void ft_lstadd_back(t_list **lst, t_list *new)` | Inserts new node at the end of the list |
| `int ft_lstsize(t_list *lst)` | Counts the number of nodes |
| `t_list *ft_lstlast(t_list *lst)` | Returns the last node |
| `void ft_lstdelone(t_list *lst, void (*del)(void *))` | Free one node (does not free the next) |
| `void ft_lstclear(t_list **lst, void (*del)(void *))` | Frees the entire list and sets pointer to NULL |
| `void ft_lstiter(t_list *lst, void (*f)(void *))` | Applies a **function** to each node's content |
| `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` | Creates a new list by applying a **function** to each node |

----

### 🗃️ Resources:

#### Documentation & Articles:

- [man7.org — Linux man pages](https://man7.org/linux/man-pages/) — primary reference for each function's behavior.
Input/Output on File Descriptors (GNU C Library)

 - [C Programming Tutorial](https://www.geeksforgeeks.org/c/c-programming-language/)

- [Linked list - geeksforgeeks](https://www.geeksforgeeks.org/c/how-to-create-a-linked-list-in-c/)

- [Implematation lists - geeksforgeeks](https://www.geeksforgeeks.org/c/c-program-to-implement-singly-linked-list/)

- The man command: In your terminal, type man strlen, man memcpy, etc. This is your absolute source of truth. Pay close attention to what happens when you pass NULL pointers or a size of 0.

### 🤖 AI Usage Disclaimer:
As per the 42 ICT training framework rules, AI tools were utilized responsibly during this project:

- **Tasks Assisted:** Conceptual explanations of static pointer arrays, understanding memory management edge cases during errors, and structuring documentation guidelines.

- **Control Practices:** No direct code generation or copy-pasting shortcuts were utilized. Code logic was built manually from foundational reasoning and peer collaboration to prepare for internet-free examination conditions.
All function implementations were written manually.

<div align="center">
<sub>42 School Brazil · dneves-d · 06 / 2026</sub>
</div>