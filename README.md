## About
This is prototype version of educational project on C++ for enumeration combinations on square 2d-grid.

Combinations can restricted by 
- grid size **N** and number of items **M**
- minimum distance between items **r**
- maximum distance to the nearest item (connectivity) **R**
- uniqueness relatively rotations, reflections and shifts
- fixed arbitrary subset of items **template**

Can be used for building custom scenarios in C++ code (check out tests_OEIS() function for working example)

## Requirements
g++, CMake

## Template file
2*n integer numbers for coordinates of fixed items, can be left empty

## Usage
- Compile code with **CMake**:
```
cmake -G "Unix Makefiles" .
```

- Run:
```sh
 combs_on_grid /path_to_template
``  

