# Definition Driven Interpreter 
The definition driven interperter (DDI) provides a capability with very little syntax.

Specifically, DDI supports data hierarchy, arrays, and scalar values. 


The pattern is as follows:

```
file := section*
section := (name value* [section])*
```
where the section `name` must adhere to the pattern `[A-Za-z_]([A-Za-z0-9_\.])*`. A `value` can be an integer, real, or quoted string.
A file can have zero or more sections. 

An example is as follows:
```
# Comments look like this
section_name1
   # keys have optional '=' 
   key = 1
   key = 3.14159
   key = "string value"
   
   array 1 2 3 4
   
   subsection1.1 
   subsection1.2 1 2 3 3 4
       subsection1.2.1 "value"
          key = 2.71
```          

The above example illustrates arbitrary hierarchy. 

Note that the indentation is recommended for clarity, but is not required. All content, except comments, could occur on the same line.