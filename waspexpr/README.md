# Expression Engine
The expression engine facilitate numerical and string expression evaluations that are integrated into other Workbench Analysis Sequence Processor components.


### Arithmetic and Algabraic Operators
The Expr engine supports regular arithmetic and algabraic operations.

| Operation      | Result              | 
|----------------|---------------------|
| Subtraction    | $`3 - 4 \equiv -1`$ | 
| Addition       | $`5 + 3 \equiv  8`$ | 
| Division       | $`8 / 2 \equiv  4`$ | 
| Multiplication | $`3 * 3 \equiv  9`$ | 
| Exponentiation | $`2 ^ 3 \equiv  8`$ | 
| Parenthesis    | $`(3 - 4) * -1 \equiv 1`$ | 

### Relational Operators
Relational operations are also supported.

| Operation      | Result              | 
|----------------|---------------------|
| Equal    | $`3==3 \equiv true`$| 
| Not Equal    | $`3!=3 \equiv false`$| 
| Less Than       | $`8 < 9 \equiv  true`$ | 
| Less Than or Equal      | $`8 \leq 9 \equiv  true`$ | 
| Greater Than       | $`9 > 8 \equiv  true`$ | 
| Greater Than or Equal      | $`9 \geq 8 \equiv  true`$ | 

Syntactic alternatives exist.

| Operation      | Result              | 
|----------------|---------------------|
| Equal    | $`3 .eq. 3 \equiv true`$| 
| Not Equal    | $`3 .neq. 3 \equiv false`$| 
| Less Than       | $`8 .lt. 9 \equiv  true`$ | 
| Less Than or Equal      | $`8 .lte. 9 \equiv  true`$ | 
| Greater Than       | $`9 .gt. 8 \equiv  true`$ | 
| Greater Than or Equal      | $`9 .gte. 8 \equiv  true`$ | 

### Boolean Operators

| Operation      | Result              | 
|----------------|---------------------|
| Not    | $` !(3==3) \equiv false `$ | 
| Or     | $` !(1==1) \mid\mid 1==1 \equiv true `$ | 
| And       | $` !(1==1) {\&}{\&} 1==1 \equiv false `$ | 


### Default Variables
The default variables are available for use in expression evaluations:

| Name      | Value              | 
|----------------|---------------------|
| `pi`    | $`3.14159265359 \approx \pi`$| 
| `e`    | $`2.7182818284590452353602874713527 \approx e`$| 
| `nl`       | '\n' | 


### Default Functions
The Expr engine also has the following functions available for use in expression evaluations:

| Function      | Description              | 
|----------------|---------------------|
| $`sin(theta)`$    | sine of theta : $` \frac{opposite}{hypotenuse} `$ |
| $`sinh(x)`$    | hyperbolic sine of x |
| $`asin(x)`$    | arc sine of x |
| $`asinh(x)`$    | inverse hyperbolic sine of x |
| $`cos(theta)`$    | cosine of theta : $` \frac{adjecent}{hypotenuse} `$ |
| $`cosh(x)`$    | hyperbolic cosine of x |
| $`acos(x)`$    | arc cosine of x |
| $`acosh(x)`$    | inverse hyperbolic cosine of x |
| $`tan(theta)`$    | tangent of theta : $` \frac{opposite}{adjecent} `$ |
| $`tanh(x)`$    | hyperbolic tangent of x |
| $`atan(x)`$    | arc tangent of x |
| $`atan2(x,y)`$    | arc tangent of x/y |
| $`atanh(x)`$    | inverse hyperbolic tangent of x |
| $`sec(theta)`$    | secant of theta : $` \frac{hypotenuse}{adjecent} `$ |
| $`csc(theta)`$    | cosecant of theta : $` \frac{hypotenuse}{opposite} `$ |
| $`cot(theta)`$    | cotangent of theta : $` \frac{adjecent}{hypotenuse} `$ |
| $`floor(x)`$    | closest integer value below x |
| $`ceil(x)`$    | closest integer value above x |
| $`exp(x)`$    | e raised to x |
| $`log(x)`$    | natural log (base e) of x |
| $`lg(x)`$    | binary log (base 2) of x |
| $`log10(x)`$    | common log (base 10) of x |
| $`sqrt(x)`$    | square root of x |
| $`deg2rad(x)`$    | converts x degrees into radians |
| $`rad2deg(x)`$    | converts x radians into degrees |
| $`deg2grad(x)`$    | converts x degrees into gradians |
| $`grad2deg(x)`$    | converts x gradians into degrees |
| $`deg2rad(x)`$    | converts x degrees into radians |
| $`round(x)`$    | rounds x to the closest integer |
| $`round(x,p)`$    | rounds x to the p decimal point |
| $`abs(x)`$    | absolute value of x |
| $`pow(x,y)`$    | x raised to the power of y : $`x^y`$ |
| $`mod(x,y)`$    | modulo of x given y |
| $`fmt(x,format)`$    | format the variable x with the desired [format](/wasphalite/README.md#formatting) |


### Special Functions
The Expr engine has a few special functions that are always available. 


| Function                              | Description                                | 
|---------------------------------------|---------------------|
| $`if(condition,if true,if false)`$   | if the `condition` evaluates to true, the `if true` value is returned, else `if false` is returned | 
| $`defined('name')`$       | return true, if and only if a variable with name `name` exists. Note the argument is quoted | 
| $`size(array)`$       | acquires the size (element count) of the given array | 


### Array Access
The Expr engine supports accessing array elements by recognizing `array[index]` patterns. Only rank 1 arrays are supported.
