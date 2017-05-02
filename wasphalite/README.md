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
 
#### Format Specifiers 
 The available specifiers are :
 
| Specifier | Description                                        | Example   |
|-----------|----------------------------------------------------|-----------|
| f         | Decimal floating point                             | 3.14159   |
| e         | Scientific notation (mantissa/exponent), lowercase | 3.9265e+2 |
| s         | String of characters                               | sample    |
| d         | Signed decimal value                               | 300       |
 
The format declarator percent `%` can be escaped with a double  percent specified, `%%`

#### Format Flags
The available flags are :

| flag | Description                                                 | Example             |
|------|-------------------------------------------------------------|---------------------|
| -    | The result will be left-justified                           | 'left       '       |
| +    | The result will always include a sign                       | '+result'           |
| ' '  | The result will include a leading space for positive values | ' result'           |
| 0    | The result will be zero-padded                              | '0result'           |
| (    | The result will enclose negative numbers in parentheses     | '(negative result)' |

#### Format Width
The width is the minimum number of characters to be written to the output. Most frequently used for padding.

#### Format Precision
For general argument types the precision is the maximum number of characters to be written to the output. 
For floating-point types (specifier = 'e','f') the precision is the number of digits after the decimal point. 
 

#### Format Examples

String examples:

| Format                    | Result         | Description                                                                                            |
|---------------------------|----------------|--------------------------------------------------------------------------------------------------------|
| '<"str":fmt=%s>'          | `'str'`          | Print the raw string "str" as a string                                                                 |
| '<"str":fmt=%4s>'         | `' str'`         | Print the raw string "str" with a width of 4 as a string                                               |
| '<"str":fmt=%05s>'        | `'00str'`        | Print the raw string "str" with a width of 5 as a string padded with zeros                             |
| '<"-30":fmt=%05s>'        | `'00-30'`        | Print the raw string "-30" with a width of 5 as a string padded with zeros                             |
| '<"-30":fmt=%%05s="%05s"> | `'%05s="00-30"'` | Print the raw string "-30" with a format prefix of '%05s', a width of 5 as a string padded with zeros  |
| '<"str":fmt=%-10s>'       | `'str`         ' | Print the raw string "str" left justified with a minimum width of 10                                  |

Integer examples:

| Format                    | Result         | Description                                                                                            |
|---------------------------|----------------|--------------------------------------------------------------------------------------------------------|
| '\<3:fmt=%d\>'            | `'3'`            | Print the integer 3 as an integer                                                                 |
| '\<30:fmt=%4d\>'          | `'  30'`         | Print the integer 30 with a width of 4 as an integer                                               |
| '\<-30:fmt=%-5d\>'        | `'30   '`        | Print the integer 30 left justified with a width of 5 as an integer                           |
| '\<-30:fmt=%05d\>'        | `'-0030'`        | Print the integer -30 with a width of 5 as an integer padded with zeros                             |
| '\<30:fmt=% d\>'          | `' 30'`          | Print the integer 30 with a leading space due to positive value  |
| '\<x=-30:fmt=% d\>'       | `'-30'`          | Print the variable x (-30) and if x > 0 include a leading space |
| '\<30:fmt=%+d\>'          | `'+30'`          | Print the integer 30 with its sign |
| '\<x=-30:fmt=%(d\>'       | `'(30)'`         | Print the varaible x (-30) with parenthesis if x < 0 |
| '\<3.14159:fmt=%d\>'      | `'3'`            | Print the floating point value as an integer |

Float-Point examples:

| Format                    | Result         | Description                                                                                            |
|---------------------------|----------------|--------------------------------------------------------------------------------------------------------|
| '\<3.14159265:fmt=%f\>'   | `'3.141593'`     | Print the floating-point value 3.14159265 as a floating point value with default precision of 6 |
|'\<3.14159265:fmt=%7f\>'|`'3.141593'`|
|'\<3.14159265:fmt=%8f\>'|`'3.141593'`|
|'\<3.14159265:fmt=%9f\>'|`' 3.141593'`|
|'\<3.14159265:fmt=%10f\>'|`'  3.141593'`|
|'\<3.14159265:fmt=%.0f\>'|`'3'`|
|'\<3.14159265:fmt=%.1f\>'|`'3.1'`|
|'\<3.14159265:fmt=%.2f\>'|`'3.14'`|
|'\<3.14159265:fmt=%.3f\>'|`'3.142'`|
|'\<3.14159265:fmt=%1.0f\>'|`'3'`|
|'\<3.14159265:fmt=%4.1f\>'|`' 3.1'`|
|'\<3.14159265:fmt=%4.8f\>'|`'3.14159265'`|
|'\<3.14159265:fmt=%8.2f\>'|`'    3.14'`|
|'\<3.14159265:fmt=%10.3f\>'|`'     3.142'`|
|'\<3.14159265:fmt=%01.0f\>'|`'3'`|
|'\<3.14159265:fmt=%04.1f\>'|`'03.1'`|
|'\<3.14159265:fmt=%04.8f\>'|`'3.14159265'`|
|'\<3.14159265:fmt=%08.2f\>'|`'00003.14'`|
|'\<3.14159265:fmt=%010.3f\>'|`'000003.142'`|
|'\<3.14159265:fmt=%g\>'|`'3.14159'`|
|'\<3.14159265:fmt=%.0g\>'|`'3'`|
|'\<3.14159265:fmt=%.1g\>'|`'3'`|
|'\<3.14159265:fmt=%.2g\>'|`'3.1'`|
|'\<3.14159265:fmt=%.3g\>'|`'3.14'`|
|'\<3.14159265:fmt=%1.0g\>'|`'3'`|
|'\<3.14159265:fmt=%4.1g\>'|`'   3'`|
|'\<3.14159265:fmt=%4.8g\>'|`'3.1415927'`|
|'\<3.14159265:fmt=%8.2g\>'|`'     3.1'`|
|'\<3.14159265:fmt=%10.3g\>'|`'      3.14'`|
|'\<3.14159265:fmt=%01.0g\>'|`'3'`|
|'\<3.14159265:fmt=%04.1g\>'|`'0003'`|
|'\<3.14159265:fmt=%04.8g\>'|`'3.1415927'`|
|'\<3.14159265:fmt=%08.2g\>'|`'000003.1'`|
|'\<3.14159265:fmt=%010.3g\>'|`'0000003.14'`|
|'\<1e-4:fmt=%.4g\>'|`'0.0001000'`|
|'\<1e-4:fmt=%10.4g\>'|`' 0.0001000'`|
|'\<1e-4:fmt=%.5g\>'|`'0.00010000'`|
|'\<1e-5:fmt=%.5g\>'|`'1.0000e-05'`|
|'\<1e-6:fmt=%.6g\>'|`'1.00000e-06'`|
|'\<1e-2:fmt=%.7g\>'|`'0.01000000'`|
|'\<1e2:fmt=%10.7g\>'|`'  100.0000'`|
|'\<3.14159265:fmt=%e\>'|`'3.141593e+00'`|
|'\<3.14159265:fmt=%.0e\>'|`'3e+00'`|
|'\<3.14159265:fmt=%.1e\>'|`'3.1e+00'`|
|'\<3.14159265:fmt=%.2e\>'|`'3.14e+00'`|
|'\<3.14159265:fmt=%.3e\>'|`'3.142e+00'`|
|'\<3.14159265:fmt=%1.0e\>'|`'3e+00'`|
|'\<3.14159265:fmt=%4.1e\>'|`'3.1e+00'`|
|'\<3.14159265:fmt=%4.8e\>'|`'3.14159265e+00'`|
|'\<3.14159265:fmt=%8.2e\>'|`'3.14e+00'`|
|'\<3.14159265:fmt=%10.3e\>'|`' 3.142e+00'`|
|'\<3.14159265:fmt=%01.0e\>'|`'3e+00'`|
|'\<3.14159265:fmt=%04.1e\>'|`'3.1e+00'`|
|'\<3.14159265:fmt=%04.8e\>'|`'3.14159265e+00'`|
|'\<3.14159265:fmt=%08.2e\>'|`'3.14e+00'`|
|'\<3.14159265:fmt=%010.3e\>'|`'03.142e+00'`|
|'\<1e-4:fmt=%.4e\>'|`'1.0000e-04'`|
|'\<1e-4:fmt=%10.4e\>'|`'1.0000e-04'`|
|'\<1e-4:fmt=%.5e\>'|`'1.00000e-04'`|
|'\<1e-5:fmt=%.5e\>'|`'1.00000e-05'`|
|'\<1e-6:fmt=%.6e\>'|`'1.000000e-06'`|
|'\<1e-2:fmt=%.7e\>'|`'1.0000000e-02'`|
|'\<1e-2:fmt=%10.7e\>'|`'1.0000000e-02'`|
|'\<1e2:fmt=%10.7e\>'|`'1.0000000e+02'`|


## Scoped Attribute
Because the data is hierarchical access to lower levels of the data hierarchy can be needed. 
Access to the can be facilitated by scoping an attribute access via a 'use' statement.

Given hierarchical data of :

```
{
   'fox' : { 'color' : 'red', 'speed' : 'quick' }
   ,'dog color' : 'brown'
}
``` 
the following template uses a scoped attributes of `fox` `color` and `speed` to emit the desired result:

```
the <speed:use=fox> <color:use=fox> fox jumped over the <'dog color'> dog. 
```
or
```
<"the "+speed+" "+color:use=fox> fox jumped over the <'dog color'> dog. 
```



## File Imports
TODO - describe file imports...
