# HierarchiAL Input Template Expansion engine (HALITE)
The HALITE engine is a data-driven input template expansion engine intended to facilitate application input or data generation. 

When it comes to text creation there are typically two approaches, 
1) write a program to generate the needed text, 
or 2) create templates and some program glue logic to read the templates and substitute attributes. 


The HALITE engine attempts to bridge these approaches by providing standard glue logic. In this way, 
1) the templates preserve clarity of intended text, 
2) templates facilitate reuse,
3) development is streamlined by eliminating the developer and only requiring a template designer, and most importantly
4) templates are interchangeable which allows using the same data to create a different 'look', perhaps, for a different application to consume.

In addition to the above, the HALITE engine provides a single point, data-driven, expansion capability that removes the need for application-specific glue logic.

A template and an optional hierarchical data set is all that is needed to expand templates into text usable by the end consumer.

The supported data constructs are provide by JSON and are Objects, Arrays, and Keyed values. For more about JSON syntax see www.json.org.

The expression evaluation support scalar and vector variable reference and mathematical expression evaluations. 

## Template Evaluation Summary
This section describes the general approach used by the HALITE engine when evaluating a template and constructing the resulting text. 

There are 3 primary components:
1) The template, consisting of constructs discussed below.
2) The optional data, described in hierarchal object notation.
3) The evaluation stream which is the destination of evaluating template constructs.



Template constructs available are:
1. Static text - plain text to be emitted to the expanded result. Contains no attributes or expression evaluation.
2. Attributes - parameters or expressions to be evaluated, optionally formatted, and substituted into the expanded result.
3. Optional Attributes - parameters expressions that when only present are emitted to the expanded result.
4. Silent Attributes - parameters or expressions that when evaluated are NOT emitted to the expanded result. Useful for intermediate or cached attribute evaluations to be used later.
5. Iterative Attributes - expressions which are evaluated iteratively for a specified range(s) with optional separator and format.
6. Template imports - import a template into the existing template with optional use of data object.
7. Iterative template imports - import a template for each element of an array via 'using' an array or repeatedly via range variables.
8. Conditional action blocks - support pre-processor style #if/ifdef/ifndef - #elseif/else - #endif conditional blocks which will only be emitted when the appropriate condition is true.

Each construct is evaluated and emitted into the evaluation stream which can be redirected to a file when using the HALITE utility, or c++ std::ostream when using the wasphalite api.

## Attributes and Expressions
Attributes and expressions are delimited by an opening and closing delimiter. By default these delimiters are '<' and '>' respectively. 

### Attribute Patterns
Attribute names are defined as the regular expression `[A-Za-z_]([A-Za-z0-9\._])*`. Examples of these are: 
1. `var`
2. `var_name`
3. `var.name`
4. `var1`
5. `var1.real`
6. etc.

If an attribute name contains character(s) that violate the regular expression, the variable name can be quoted. Examples of these are:
1. `'var(name)'`
2. `'my var(name)'`
3. etc.

### Example Attribute Pattern
An example attribute substitution looks like:
```
the <FoxSpeed> <FoxColor> fox jumped over the <DogColor> dog.
```
or
```
the <'fox speed'> <'fox color'> fox jumped over the <'dog color'> dog.
```
Here the `FoxSpeed` or `'fox speed'` attributes might be 'quick' or 'fast', the `FoxColor` be 'red', and the `DogColor` or `'dog color'` be 'brown' or 'black.'

### Expressions
The HALITE Engine uses the WASP [expression engine](/waspexpr) for expression evaluation which supports all regular math operators of 
multiplication '*', division '/', addition '+', subtraction '-', and precedence '(',')'

* regular trig functions - sin(x),cos(x),tan(x),asin(x),acos(x),atan(x)
        ,atan2(y, x),sec(x),cosec(x),cot(x),sinh(x),cosh(x),tanh(x),asinh(x),acosh(x),atanh(x)
* logarithmic functions - ln(x),log(x),lg(x)
* exp(x)
* pow(x)
* round(x),round(x, p)
* floor(x),ceil(x)
* if(cond, trueval, falseval)
* abs(x)
* modulo - mod(x,y),
* sqrt(x)
* defined('x') - indicates if the variable named x is defined


### Example Expression Patterns
An example attribute substitution looks like:
```
the quick red fox jumped over the brown dog going <miles/hour>mph fast.
```
or
```
the quick red fox jumped over the brown dog going <velocity_mph*1.60934>kph fast.
```

In addition to integer and double precision math operations, string concatenation is also available.

E.g., 
```
<"My result is "+numeric_result>
```
Here the `numeric_result` is concatenated to the string `My result is ` producing a final result that is string typed.

## Formatting 
Attribute and expressions can be formatted prior to insertion into the evaluation stream. This is influenced by the [C printf](http://www.cplusplus.com/reference/cstdio/printf) and  [Java.Format](https://docs.oracle.com/javase/7/docs/api/java/util/Formatter.html) capability.

Specifically, the following constructs are provided:
`%[flags][width][.precision]specifier` 
 
 The available specifiers are :
 
| Specifier | Description                                        | Example   |
|-----------|----------------------------------------------------|-----------|
| f         | Decimal floating point                             | 3.14159   |
| e         | Scientific notation (mantissa/exponent), lowercase | 3.9265e+2 |
| s         | String of characters                               | sample    |
| d         | Signed decimal value                               | 300       |
 
The format declarator percent `%` can be escaped with a double  percent specified, `%%`

TODO document flags, width, and precision.
 
## File Imports
TODO - describe file imports...
