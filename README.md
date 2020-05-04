# Ram-machine
Program is a simple implementation of [RAM machine](https://en.wikipedia.org/wiki/Random-access_machine).

# Program
Program should be written with lines of code described as below:

`[JUMP label], instruction, access modifier, argument, [comment];`

Example program for `abs` is listed below:
```
     , READ ,  , 0    , Read value to accumulator;
     , JGTZ ,  , NOABS, If accumulator is greather than 0 jump to NOABS;
     , STORE,  , 1    , Store accumulator to register 1;
     , LOAD , =, 0    , Load 0 to accumulator;
     , SUB  ,  , 1    , Subtract value in register 1 from accumulator;
NOABS, WRITE,  , 0    , Write accumulator;
     , HALT ,  ,      , Stop;
 ```

More example programs are in `instructions` folder.

# Input tape
Input tape is text file with values named: `input.txt`.

# Registers
Memory is made of registers. Register `0` is accumulator. Other registers can be freely accessed. Registers are integers from `0` to `count - 1`. Current register count is: 100.

# Access modifier
The access modifier is used to specify how to handle the instruction argument. The instruction argument should be treated as follows:
* ` ` - (nothing) register
* `=` - literal
* `*` - register's value is pointer to other register

# Supported instructions
List of supported instructions:
|Instruction|Description|
|---|---|
| `JUMP, , argument` | jump to label `argument` |
| `JZERO, , argument` | jump to label `argument` if accumulator is zero |
| `JGTZ, , argument` | jump to label `argument` if accumulator is greather than zero | |
| `LOAD, (<nothing> or = or *), argument` | load value to accumulator from `argument` |
| `STORE, (<nothing> or *), argument` | store value from accumulator from `argument` |
| `ADD, (<nothing> or = or *), argument` | add `argument` to accumulator value |
| `SUB, (<nothing> or = or *), argument` | subtract `argument` from accumulator |
| `MULT,(<nothing> or = or *), argument` | multiply accumulator by `argument` |
| `DIV, (<nothing> or = or *), argument` | divide accumulator by `argument` |
| `READ, (<nothing> or *), argument` | read from input tape |
| `WRITE, (<nothing> or = or *), argument` | write to output tape |
| `HALT` | ends program |