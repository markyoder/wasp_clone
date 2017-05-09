# Command Line Utilities 
The Workbench Analysis Sequence Processor package provides a set of command line utilities to aid in sequence processing and processor development.

The sequence processor construct parse trees from which two primary functions are typically desired.

1. the listing of the parse tree
2. the selection of input given a select statment.

## File Listing Utilities
Available Interpreters have corresponding *list utilities. 

SON, GetPot, DDI, and JSON have corresponding sonlist, getpotlist, ddilist, and jsonlist. 

These utilities produce a ordered directory-style listing of each parsed input component.

E.g., for the given example SON data file `example.son`:

```
object(identifier){
   key = value
   child ( name ) {
      x = 1
   }
}
array [ 1 2 3 ]
```

An invocation of the `sonlist` utility:

```
sonlist example.son
```
Produces a directory-style listing of each component in the file:

```
/
/object
/object/decl (object)
/object/( (()
/object/id (identifier)
/object/) ())
/object/{ ({)
/object/key
/object/key/decl (key)
/object/key/= (=)
/object/key/value (value)
/object/child
/object/child/decl (child)
/object/child/( (()
/object/child/id (name)
/object/child/) ())
/object/child/{ ({)
/object/child/x
/object/child/x/decl (x)
/object/child/x/= (=)
/object/child/x/value (1)
/object/child/} (})
/object/} (})
/array
/array/decl (array)
/array/[ ([)
/array/value (1)
/array/value (2)
/array/value (3)
/array/] (])

```

These listings describe the interpreted hierachy and value.

## File Component Selection Utilities
The ability to select specific parts of the input can be useful in schema creation. All supported interpreters have corresponding select utilities.

Using the example.son file earlier a select statement of `sonselect example.son /array/value[1:3]` produces the following output:

```
Selecting /array/value[1:3]
---- 3 nodes selected with statement '/array/value[1:3]' ----
1) /array/value
1
2) /array/value
2
3) /array/value
3
```

Alternatively, `sonselect example.son /object/child/x` produces the following output:

```
Selecting /object/child/x
---- 1 nodes selected with statement '/object/child/x' ----
1) /object/child/x
x = 1
```

Subsequent selections select from prior selection sets, so `sonselect example.son /object/child/x ../key/value` produces:

```
Selecting /object/child/x
---- 1 nodes selected with statement '/object/child/x' ----
1) /object/child/x
x = 1
Selecting ../../../array
---- 1 nodes selected with statement '../../../array' ----
1) /array
array [ 1 2 3 ]
```