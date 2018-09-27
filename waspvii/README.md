# VERA Input Interpreter 
The vera input interpreter (VII) provides a input processing capability which requires very little syntax.

Specifically, VII supports comments, data blocks, arrays, and scalar values. 


The pattern is as follows:

```
file := block*
block := '[' name ']' commands
commands := named_command | unnamed_command
unnamed_command := (name value+ (key_value)*)+ 
named_command := (name _name value+ (key_value)*)+ 
key_value := name =? value
name := string
_name := anything
```
where the block `name` must adhere to the pattern `([A-Za-z0-9_\.])+`. A `value` can be an integer, real, string, or quoted string.
A file can have zero or more blocks. 

An example is as follows:
```
# Comments look like this
[block_name1]
   # keys have optional '=' 
   name = 1
   name = 3.14159
   name = "string value"
   
   array 1 2 3 4
   
[block2] 
   command 1.2 1 2 3 3 4
       command_key1 "value"
           command_key2 = 2.71
```          

The above example illustrates arbitrary hierarchy. 

Note that the block indentation is recommended for clarity but is not required.

If a collision occurs between a command value and name, the command value must be quoted to disambiguate it.

```
[block_name1]
  command1 string
  command2_named_string 
```
must be 


```
[block_name1]
  command1 'string'
  command2_named_string 
```
