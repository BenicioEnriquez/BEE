## Inspiration
When introduced to the world of programming, most young coders are taught a dynamically-typed, interpreted language such as JavaScript or Python, which are highly flexible and provide heavy abstractions on top of low-level systems. These attributes makes those languages an obvious choice for starting out, since programming historically has a high learning curve. However, things quickly become problematic when attempting to transition to a harder language, such as C. All of a sudden one has to deal with memory access, hard types, and far less forgiving compilers. It's easy to see why someone might become overwhelmed. That's where **BEE** comes in. 

## What it does
**BEE**'s main goal is to make the transition  from languages like Python to languages like C _much_ easier. It's not particularly better at doing any specific job than languages that have already been made, but is instead designed to be a solid middle ground for those looking to level up their programming. **BEE** is a compiled language, but also comes with a JIT compiler for those who are used to interpreted languages. **BEE** is statically typed, but doesn't give direct memory access or require pointers. **BEE**'s syntax is similar to that of C, but also comes with options to used Python-like code ("and" instead of "&&"). Here are some examples:
```C
// The traditional hello world program
printf('Hello, World!\n');
```
You'll find a lot of the basic syntax to be quite familar, including the iconic **printf**
```C
// Simple greeting program
string name = 'Benny';
string greeting = "%s says hi\n";
printf(greeting, name);
```
Strings can be defined with either single or double quotes, as in the style of Python/JS
```C
// Doing some stuff with numbers
double pi = 3.1415;
if (pi > 1.2) {
    printf("big");
} else {
    printf("small");
}
int count = 0;
while (count < 10) {
    printf('count = %d', count);
    count++;
}
```
Control flow and math works exactly as you would expect it to
```C
// Working with arrays
int~ ages = [9, 8, 7, 6, 5];
ages[2] += 1;
printf("Billy just turned %d!\n", ages[2]);
```
This is one bigger area in which things differ; array types are designated with a tilde (~) at the end of a primitive, and are constructed using square brackets. Also unlike C, arrays can be defined without a variable (i.e. pass-by-value) as show below
```C
// Fancy functions
int foo(int~ data) {
    return data[0];
}
int x = foo([1, 2, 3]);
```
All of the above code can be ran or compiled with ease using the BEE binary, which has example uses shown below
```Bash
# To build the project
make
# To use JIT compilation on code.b
./bee run code.b
# To compile code.b into it's own binary
./bee code.b
```

## How I built it
**BEE** is built primarily using LLVM's C++ api for control flow and machine code generation. Lexical analysis is done using Flex, which is then fed into Bison, the parser. The AST produced by Bison is then compiled one node at a time by the LLVM IR creation tools, and then grouped together into a "module". Finally, the module is either passed to Clang to generate native machine code, or back into LLVM for JIT compilation and execution.

## Challenges I ran into
Arrays were a big problem. I was under the impression that once I had successfully figured out strings, arrays would be a piece of cake. I was wrong. Arrays need to be modifiable in real time, meaning they can't simply be defined as a portion of memory in the ".data" section with a global pointer like a string can. To resolve this, I had to figure out how to dynamically allocate a portion of memory in LLVM IR and keep track of the types, which took quite a bit of time.

## Accomplishments that I'm proud of
I am proud to say that **BEE** fully supports constant string types and dynamic access to arrays. Along with this, **BEE** also has support for integers, doubles, and booleans, along with their corresponding operations and control flow (such as while loops, if/else, and functions). Additionally, **BEE** has hesitant support for externally linked C libraries,  though the libraries must be compiled and linked separately.

## What I learned
Making a fully featured language is not as easy as it seems. There is a ton of work going on behind the scenes of even the most basic compilers that we may never notice. Memory is a very tricky thing, and can cause absolute failure if not handled correctly. In the future, if I were to attempt to make another language, I would want to plan out in detail beforehand how I'm going to handle memory access, addressing, and typing.

## What's next for BEE: Benny's Extraordinary Executor
For loops, Object Orientation, Better C interoperability, Cross Platform Compilation, String modification and utils (concatenation, substring, regex, etc.), Type casting (int <-> double, string <-> int, etc.)
