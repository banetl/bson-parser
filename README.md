# BSON parser

## The project

A simple BSON (Binary Json) parser in C++.
Bson is a binary version of JSON, frequenlty used in web apps. only partially reversed.

The programm provided parses the BSON into a class architechture detailled below.
It then calls the ``dump()`` method to pretty print the BSON file content in
a human readable way.

### Specification

[http://bsonspec.org/spec.html](http://bsonspec.org/spec.html)

### Requirements

* A compiler supporting c++17. (gcc >= 7.0 or clang >= 4.0)

### Architechture of the project

FIXME

### Build the project

You can build the project with the simple Makefile provided at the root of the
repository. There are three rules in the Makefile:

* all: builds the project
* debug: compiles with debug flags
* clean: clean everything created by the rules above.

### Test it with provided samples

After building the project the binary is in the src folder and is called:
- **bson-parser**

The usage is:
```bash
./bson-parser file.bson
```

Some bson files are provided in the ``samples`` folder. You can use them to test
the program.

### Todo

* [ ] Synthetize all types in a global header to make them easily adaptable
* [ ] Use a real build system (cmake)
* [ ] Refactor into multiple folders (ast, parser, utils)

## Improvements

### Make the bson parser portable

This bson parser was implemented on an x86-64 architechture. It won't work
on an other architechture because of the size of basic types and the way
the bytes are stored (endianess).
To solve this issue an improvement could be to have an adaptable header with
the corresponding ``using`` to the data types. To make it work on other
architechture the only thing to do would be to replace with the adequate types
 in this header.

### Improve memory management

Most of the complex data types parsed are stored in a std::shared_ptr. An
improvement could be to store them in the more restricive std::unique_ptr.
This improvement however has to take into account the moment when the memory
is allocated. The code has to be refactored to allocate in the class
constructors.

## Author

* Loic Banet [loic.banet@gmail.com]
