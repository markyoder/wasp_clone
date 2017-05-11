# Definition Driven Interpreter 
The definition driven interperter (DDI) provides a capability with very little syntax.

Specifically, DDI supports data hierarchy, arrays, and scalar values. 


The pattern is as follows:

```
file := section*
section := name value* section*
```
where the section `name` must adhere to the pattern `[A-Za-z_]([A-Za-z0-9_\.])*`. A `value` can be an integer, real, or quoted string.
A file can have zero or more sections. 

An example is as follows:
```
# Comments look like this
section_name1
   # keys have optional '=' 
   name = 1
   name = 3.14159
   name = "string value"
   
   array 1 2 3 4
   
   subsection1.1 
   subsection1.2 1 2 3 3 4
       subsection1.2.1 "value"
          name = 2.71
```          

The above example illustrates arbitrary hierarchy. 

Note that the section indentation is recommended for clarity, but is not required. All content, except comments, could occur on the same line.

It is also clear to see that there is an ambiguity in the grammar. Specifically, how does one know whether a subsequent section is a subsection or sibling section?

```
section1
section2
```
syntactially look the same as

```
section1
section1.1
```

This is where and why the definition is important and required in driving the interpretation of these files. 

The definition driven algorithm is straight forward.


1. Read a section name and perform the follow
2. If the section name is legal for existing context, capture section name and push section context. Repeat steps.
3. If the section name is not legal, pop current context and repeat steps 2,3,4 inquiries on new/parent context. 
4. If no context available, i.e. exhausted, ERROR.

The result is a parse tree where node names are section names. 

