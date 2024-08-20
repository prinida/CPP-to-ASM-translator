# C++ to assembler translator

This project intended for translation (conversation) subset of **C++** language to **assembler** program.

## Supported subset of C++ language 
+ data type **int** (at the moment only positive numbers are supported)
+ variable description instructions
+ assignment operators **=**, **if**, **if-else** of any nesting and in any sequence
+ operations **+, –, \*, ==, !=, <**

## Brief description of the work

**Phases of translation:**
1. Lexical analysis
2. Syntax analysis (parsing)
3. Assembler code generation

Lexical analysis - the work is based on a **finite state machine**.\
The parser is implemented using the **LL(1)** table method.\
Assembler code generator uses postfix notation.

## Project structure

+ *examples* folder contains examples with resources in *res* folder, *results* folder with *assembler.txt* and *postfix.txt* or *errors.txt* files, exe file to run program ourselves.

+ *res* folder contains resources required for the translator to work:
  + *alphabet.txt* - contains all symbols in language
  + *keywords.txt* - contains all keywords in language
  + *operators.txt* - contains all operators in language
  + *operatorsOperandsNumber.txt* - contains the number of operands for operators and keywords
  + *parseTable.txt* - contains parse table intended for syntax analysis
  + *priorities.txt* - contains operator and keyword priorities
  + **program.txt** - contains source program on **C++** language
  + *separators.txt* - contains all separators in language

+ *src* folder contains all source code files("*.h", "*.cpp")

+ *CMakeLists.txt* contains code on cmake language to build project

Also *results* folder that generated after executation *exe* file contains:
+ *assembler.txt* - contains assembler program to run on **MASM** (generated if the program is successfully executed)
+ *postfix.txt* - contains postfix notation of program (generated if the program is successfully executed)
+ *errors.txt* - contains syntax and lexical errors (generated in case of program execution failure)

## Build solution with CMake on Windows

*You need install cmake on your machine to build solution.*

1. Create folder for solution (for example *build* folder in repository folder) using the command `mkdir build`
2. Go to the *build* folder `cd build`
3. Use this command `cmake -G "Visual Studio 17 2022" ..` to generate project and needed cmake files in *build* folder. You can use other compilers instead of "Visual Studio 17 2022", detailed list of compilers you can observe after entering command `cmake --help` in section "Generators"
4. To build project you need enter command `cmake --build .` or use your integrated development environment(IDE) or use selected compiler
5. *exe* file located in path "build\bin\Debug\"
6. The results of the program can be found in the *results* folder

## Simple example

**More complex examples can be found in the folder *examples*.**

**Source program** (located in *res* folder in *program.txt* file):

``` cpp
int main()
{
    int g = 11 * 20;
    
    if (g == 11 * 20 + 1 - 1)
    {
        int b = 15 - 14;
    }
    else
    {
        int a = 172;
    }
	

    return 0;
}
```

**Postfix notation** (located in *results* folder in *postfix.txt* file):
```
g 11 20 * = int g 11 20 * 1 + 1 - == m1 if b 15 14 - = int m2 else m1: a 172 = int m2: 0 return [int main()] 
```

**Assembler code** (located in *results* folder in *assembler.txt* file):
```asm
.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
EXTERN  ExitProcess@4: PROC

.DATA
g DD ?
b DD ?
a DD ?
r1 DD ?
r2 DD ?

.CODE
MAIN PROC

mov EAX, 11
mov EBX, 20
mul EBX
mov r1, EAX

mov EAX, r1
mov g, EAX

mov EAX, 11
mov EBX, 20
mul EBX
mov r1, EAX

mov EAX, r1
mov EBX, 1
add EAX, EBX
mov r1, EAX

mov EAX, r1
mov EBX, 1
sub EAX, EBX
mov r1, EAX

mov EAX, g
mov EBX, r1
cmp EAX, EBX
jne m1
mov EAX, 15
mov EBX, 14
sub EAX, EBX
mov r1, EAX

mov EAX, r1
mov b, EAX

jmp m2
m1:
mov EAX, 172
mov a, EAX

m2:
PUSH 0
CALL ExitProcess@4

MAIN ENDP
END MAIN

```