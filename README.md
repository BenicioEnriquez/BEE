# BEE
BEE is a statically typed C-style language focused on simplicity and ease of use. It is designed to be an intermediary language between C and python to help ease the transition for young programmers.

## Inspiration
When introduced to the world of programming, most young coders are taught a dynamically-typed, interpreted language such as JavaScript or Python, which are highly flexible and provide heavy abstractions on top of low-level systems. This makes them an obvious choice for starting out, since programming historically has a high learning curve. However, things quickly become problematic when attempting to transition to harder language, such as C. All of a sudden one has to deal with memory access, hard types, and far less forgiving compilers. It's easy to see why someone might become overwhelmed. That's where **BEE** comes in. 

## What it does
**BEE**'s main goal is to make the transition  from languages like Python to languages like C _much_ easier. It's not particularly better at doing any specific job than languages that have already been made, but is instead designed to be a perfect middle ground for those looking to level up their programming. **BEE** is a compiled language, but also comes with a JIT compiler for those used to interpreted languages. **BEE** is statically typed, but doesn't give direct memory access to the the variables or their pointers. **BEE**'s syntax is similar to that of C, but also comes with options to used Python-like code ("and" instead of "&&")

## How we built it
**BEE** is built primarily using LLVM's C++ api for control flow and machine code generation. Lexical analysis is done using Flex, which is then fed into the parser, which is made using Bison. The AST produced by Bison is then compiled one node at a time by the LLVM IR creation tools, and grouped together into a module. From this point, the module is either passed to Clang to generate native machine code, or back into LLVM for JIT compilation and execution.

## Challenges we ran into
Arrays were a big problem. I was under the impression that once I had successfully figured out strings, arrays would be a piece of cake. I was wrong. Arrays need to be modifiable in real time, meaning they can't simply be defined as a portion of memory in the ".data" section with a global pointer like string can. To resolve this, I had to figure out how to dynamically allocate a portion of memory in LLVM IR and keep track of the types, which took quite a chunk of time.

## Accomplishments that we're proud of
I am proud to say that **BEE** fully supports constant string types and dynamic access to arrays. Along with this, **BEE** also has support for integers, doubles, and booleans, along with their corresponding operations and control flow. Additionally, **BEE** has hesitant support for externally linked C libraries,  though the libraries must be compiled and link separately.

## What we learned
Making a fully featured language is not as easy as it seems. There is a ton of work going on behind the scenes of even the most basic compilers that we may never notice. Memory is a very tricky thing, and can cause absolute failure if not handled correctly. In the future, if I were to attempt another language, I would want to plan out in detail beforehand how I'm going to handle memory access, addressing, and typing.

## What's next for BEE: Benny's Extraordinary Executor
Object Orientation, Better C interoperability, Cross Platform Compilation, String modification and utils (concatenation, substring, regex, etc.), Type casting (int <-> double, string <-> int, etc.)
