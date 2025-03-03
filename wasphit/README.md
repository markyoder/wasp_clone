# Hierarchical Input Text - HIT
The Hierarchical input text provides an input syntax used by the MOOSE framework

## Input Syntax
The syntax pattern is as follows:

```
file := block*|key_value*|file_include*
block := '[' name ']' block_members '[]'
block_members := (block_member | file_include)*
block_member := block | key_value
file_include := '!include' string
key_value := name :?'=' value
name := string
value := (number|string|array)
array := "'" (number|string) "'"
comment := "#" .* \n
```
where the block `name` must adhere to the pattern `([A-Za-z0-9_\.])+`. A `value` can be an integer, real, string, or array (as indicated by single quotes).
A file can have zero or more blocks and arbritrarily include files. 

Note that an optional ':' may precede the '=' in a key_value as shown in the following example.
```
# Comments look like this
[block1]
   # This is a comment
   name  = 1
   name := 3.14159
   name  = "string value"
   name  = '1 2 3'
   name := '4 5 6'
  [nested_block]
    ...
  []
[]    
!include parts_file.i
```

The above example illustrates arbitrary hierarchy. 

Note that the block indentation is recommended for clarity but is not required.


