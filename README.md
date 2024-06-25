<div align="center">
  <!-- Logo -->
  <a href="https://github.com/celinenguyentu/GetNextLine">
  <img src="docs/get_next_linem.png" alt="Logo" width="150" height="150">
  </a>
</div>

# GetNextLine

This project is about coding a very convenient function that reads one line at a time from a file descriptor. It should be added to the [Libft](https://github.com/celinenguyentu/Libft) collection for future projects.

Grade : 125/100 \
Subjects v.12 : [`FR`](docs/GetNextLine_v12.fr.pdf) [`EN`](docs/GetNextLine_v12.en.pdf) \
42 Norm v.4 : [`FR`](docs/norm_v4.fr.pdf) [`EN`](docs/norm_v4.en.pdf)

## Content

```c
char	*get_next_line(int fd)
```
The function returns a line read from a file descriptor. Consecutive calls returns the consecutive lines one at a time. A line is a sequence of characters ended by a terminating `\n` character, except if the end of file was reached and does not end with a `\n` character. \
**Parameter(s)** : \
`fd` - the file descriptor to read from \
**Return value** : \
A string containing the next line read. If there is nothing else to read, or an error occured, it returns `NULL`.

The bonus version can handle multiple files at the same time and read from a different file descriptor per call without loosing the reading thread of each one. 

## Usage

Include either one of these headers in your code :
```c
#include "get_next_line.h"
#include "get_next_line_bonus.h"
```
Compile your `main.c` code using the appropriate files
```bash
[ gcc | clang | gcc ] main.c get_next_line.c get_next_line_utils.c
```
```bash
[ gcc | clang | gcc ] main.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

## Testers

I recommand you to code your own tests. It is not only an important part of the learning process but also allows to run thorough tests that might not be included in other people's testers.

I have coded a basic program to run theses functions using a various range of test files and allowing to modify the size of the buffer that reads and stores data. Please find it in this repository : [GetNextLineTest](https://github.com/celinenguyentu/GetNextLineTest). 

Those are third-party tester to run complementary tests, use them at your own risk :
- @Tripouille [gnlTester](https://github.com/Tripouille/gnlTester)
- @xicodomingues [francinette](https://github.com/xicodomingues/francinette)