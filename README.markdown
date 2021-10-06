# Introduction to programming (C++)

This repository contains an introductory programming course, in the C++
language.

The assumption is that you go through the course on a Linux system. The course
should be adaptable to various BSD systems (including their derivatives like Mac
OS), but this is not tested. The course is largely incompatible with the Windows
family of operating systems.

Course commentary can be found in the [PRG.markdown](./PRG.markdown) file. It is
provided in Polish. Source code can be found in the `src` directory, any header
files in the `include` directory.

--------------------------------------------------------------------------------

To compile an example program execute the following command:

    $ make build/00-example-name.bin

This requires you to have a C++ compiler, capable of compiling C++17 source
code, installed on your system. Supported compilers are GCC and Clang.

To run compiled program execute the following command:

    $ ./build/00-example-name.bin

To clean the build directory execute the following command:

    $ make clean

Cleaning the build directory and making a clean compilation should be the first
thing you do when debugging your programs.

--------------------------------------------------------------------------------

To format your source code execute the following command:

    $ make format

It requires the `.clang-format` file to be present in your working directory. I
suggest using the file supplied with this repository in your projects.

--------------------------------------------------------------------------------

Crash courses and primers on useful tools and programs are provided in the
[`Collapse_curricula`](./Collapse_curricula) directory. The most important ones
for this course are:

- [Git](./Collapse_curricula/Git.markdown)
- [SSH](./Collapse_curricula/SSH.markdown)
- [GNU Make](./Collapse_curricula/GNU_Make.markdown)
