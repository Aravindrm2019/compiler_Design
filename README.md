# Predictive Parsing Compiler Lab

A comprehensive compiler implementation demonstrating all phases of compilation: lexical analysis, syntax analysis, semantic analysis, intermediate code generation, optimization, and target code generation.




### Example Program

```c
int x;
int y;
x = 10;
y = x * 2;
int z;
z = x + y;
```

## Compilation Output Example

When you run the compiler with the above program, you'll see:

```
Enter program (Ctrl+D to finish):

========== 1. LEXICAL ANALYSIS ==========
KEYWORD int
IDENTIFIER x
DELIM ;
KEYWORD int
IDENTIFIER y
DELIM ;
IDENTIFIER x
OP =
INTEGER 10
DELIM ;
IDENTIFIER y
OP =
IDENTIFIER x
OP *
INTEGER 2
DELIM ;
KEYWORD int
IDENTIFIER z
DELIM ;
IDENTIFIER z
OP =
IDENTIFIER x
OP +
IDENTIFIER y
DELIM ;

========== 2. SYNTAX ANALYSIS ==========
KEYWORD int
IDENTIFIER x
DELIM ;
KEYWORD int
IDENTIFIER y
DELIM ;
IDENTIFIER x
OP =
INTEGER 10
DELIM ;
x = 10
IDENTIFIER y
OP =
IDENTIFIER x
OP *
INTEGER 2
DELIM ;
t0 = x * 2
y = t0
KEYWORD int
IDENTIFIER z
DELIM ;
IDENTIFIER z
OP =
IDENTIFIER x
OP +
IDENTIFIER y
DELIM ;
t1 = x + y
z = t1
Syntax is valid

========== 3. SEMANTIC ANALYSIS ==========
Semantic checks passed

========== 4. INTERMEDIATE CODE ==========
KEYWORD int
IDENTIFIER x
DELIM ;
KEYWORD int
IDENTIFIER y
DELIM ;
IDENTIFIER x
OP =
INTEGER 10
DELIM ;
x = 10
IDENTIFIER y
OP =
IDENTIFIER x
OP *
INTEGER 2
DELIM ;
t2 = x * 2
y = t2
KEYWORD int
IDENTIFIER z
DELIM ;
IDENTIFIER z
OP =
IDENTIFIER x
OP +
IDENTIFIER y
DELIM ;
t3 = x + y
z = t3

========== 5. OPTIMIZATION ==========
Constant folding applied

========== 6. TARGET CODE ==========
MOV R1, result
```

## Compilation Phases Explained

### Phase 1: Lexical Analysis
Converts input stream into tokens (keywords, identifiers, operators, delimiters).

### Phase 2: Syntax Analysis
Parses tokens according to grammar rules and generates intermediate code with temp variables for expressions.

### Phase 3: Semantic Analysis
Performs semantic checks such as:
- Variable declaration validation
- Type compatibility (when applicable)

### Phase 4: Intermediate Code Generation
Generates 3-address code using temp variables (t0, t1, t2, ...).

### Phase 5: Optimization
Applies optimizations such as:
- Constant folding
- Dead code elimination

### Phase 6: Target Code Generation
Converts intermediate code to target assembly-like code.

## Grammar Utilities

### Run FIRST/FOLLOW Computation

```bash
cd "predictive parsing"
python first_follow.py
```

Output:
```
FIRST Sets:

S : {'b'}
A : {'b'}
B : {'b'}

FOLLOW Sets:

S : {'$'}
A : {'b', 'a'}
B : {'$'}
```

### Remove Left Recursion

```bash
cd "predictive parsing"
python left_recursion.py
```

Output:
```
Grammar after removing Left Recursion:

S -> A B
A -> b A'
A' -> a A' | #
B -> b
```

### Apply Left Factoring

```bash
cd "predictive parsing"
python left_factoring.py
```

Output:
```
Grammar after Left Factoring:

S -> A B
A -> A a | b
B -> b
```

