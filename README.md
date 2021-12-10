# Caroline
**Caroline** is a procedural mini programming language that utilizes the conventions and principles of pseudocodes in designing and writing executable programs. The name Caroline is inspired by its French origin that means *“Strong”* and *“Free Woman”*. As the name suggests, Caroline aims to give novice programmers freedom to express their ideas regardless of their experience, and nurture them to create strong and creative solutions that they can easily use and comprehend.

As mentioned before, Caroline will be following the principles and conventions of writing a pseudocode. Meaning, its syntactic elements will be mainly based on common writing practices that a pseudocode follows. All the basic programming concepts like conditionals and iterations will also follow a pseudocode type of writing. The only difference of Caroline from a pseudocode is that it will follow a specific language syntax for it to be compiled and executed correctly. But the basic readability and writing practices of a pseudocode will remain.

## How to Run Caroline Programming Language
Dependencies:
    - Flex and Bison
    - GCC Compiler
Run the Following Steps:
```
flex lexer.l // this will generate lex.yy.c
gcc lex.yy.c // this will generate an .exe file
./a.exe
```

## Current Functionalities
Currently Caroline is at the stage of Having a Lexer file. The parser is a work in progress since we need to implement the Descent Parser Algorithm.