# Cmake

Hera is to talk about the c++ compile tools cmake
this is my understanding of the cmake and the process that needs to be solved to compile or more clear to run c++ code

## [chaper 1](./chapter%201/) Add Excutable Procedure

is begin a excutable procedure with c++ code. how to start the basic cpp procedure with cmakelists

## [chapter 2](./chapter%202/) Include the Header File

is to add a header file in c++. and the library with the header line in cpp procedure.

## [chapter 3](./chapter%203/) Add Subdirectory

chapter 3 is to learn how to structure the code , for example the header file should in the **include**, header file is to declare the function or class or member. and the source code will be put in the **src** folder.

```
$ tree
.
├── CMakeLists.txt
├── sub
│   ├── CMakeLists.txt
│   └── hello_slam.cpp
── sub1
   ├── CMakeLists.txt
   ├── include
   │   └── hello.h
   │      
   └── src
       └── sayhello.cpp


```

## [chapter 4](./chapter%204/) Generate the Code

some situations needs to transmit the parameters from CMakeLists.txt to the cpp file, so in the chapter 4, use the ***configure_file*** to realize this, the principle is to use the for example the version, *.h.in can be transformed to the header file by the command ***configure_file***.And then needs two arguments, first is the file second is output path of the header file.

## [chapter 5](./chapter%205/)

Static analysis is the analysis of code without executing it. It can be used to find common programming errors and enforce coding guidelines. Examples of errors that can be found using static analysis tools include:

- Out of bounds errors
- Memory leaks
- Usage of uninitialized variables
- Use of unsafe functions
