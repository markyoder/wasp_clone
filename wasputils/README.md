# Command Line Utilities 
The Workbench Analysis Sequence Processor package provides a set of command line utilities to aid in sequence processing and processor development.

The sequence processor construct parse trees from which two primary functions are typically desired:

1. the listing of the parse tree
2. the selection of input given a select statement.

## File Listing Utilities
Available Interpreters have corresponding *list utilities. 

SON, GetPot, DDI, and JSON have corresponding sonlist, getpotlist, ddilist, and jsonlist. 

These utilities produce an ordered directory-style listing of each parsed input component.

For the given example SON data file `example.son`:

```
object(identifier){
   key = value
   child ( name ) {
      x = 1
   }
}
array [ 1 2 3 ]
```

an invocation of the `sonlist` utility:

```
sonlist example.son
```
produces a directory-style listing of each component in the file:

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

These lists describe the interpreted hierachy and value.


Note that the Definition-Driven Interpreter (DDI) is different from the others as it requires a schema (definition) in order to parse.

```
ddilist /path/to/schema.sch /path/to/input.inp
```

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
The first node selected is the `/object/child/x` node, which has the text `x = 1`. 
Subsequently, the relative path `../../../array` is used from `/object/child/x` to select three levels up `../../../`, and subsequently the `array` node.
Notice that the exact user input is reproduced. 

## XML Utilities
The XML standard is readily accessible in most programming languages where SON, GetPot, DDI, etc. are not. 
As such, the *xml utilities provide a bridge for prototyping or coupling with higher-level scripts, etc.

```
sonxml example.son
```
produces

```xml
<document>
  <object>
    <decl loc="1.1" dec="true">object</decl>
    <LP loc="1.7" dec="true">(</LP>
    <id loc="1.8" dec="true">identifier</id>
    <RP loc="1.18" dec="true">)</RP>
    <LBC loc="1.19" dec="true">{</LBC>
    <key>
      <decl loc="2.4" dec="true">key</decl>
      <ASSIGN loc="2.8" dec="true">=</ASSIGN>
      <value loc="2.10">value</value>
    </key>
    <child>
      <decl loc="3.4" dec="true">child</decl>
      <LP loc="3.10" dec="true">(</LP>
      <id loc="3.12" dec="true">name</id>
      <RP loc="3.17" dec="true">)</RP>
      <LBC loc="3.19" dec="true">{</LBC>
      <x>
        <decl loc="4.7" dec="true">x</decl>
        <ASSIGN loc="4.9" dec="true">=</ASSIGN>
        <value loc="4.11">1</value>
      </x>
      <RBC loc="5.4" dec="true">}</RBC>
    </child>
    <RBC loc="6.1" dec="true">}</RBC>
  </object>
  <array>
    <decl loc="7.1" dec="true">array</decl>
    <LBK loc="7.7" dec="true">[</LBK>
    <value loc="7.9">1</value>
    <value loc="7.11">2</value>
    <value loc="7.13">3</value>
    <RBK loc="7.15" dec="true">]</RBK>
  </array>
</document>
```
Any xml element with the attribute `dec="true"`  indicates a 'decorative' input component, required syntax and could be ignored by most higher level interpreters. 

The attribute `loc="line.column"` indicates the input components location in the file. 

The element's name indicates the name of the input component. The leaf element's data are the data of interest stored in the parse tree.

## File Validation Utilities
The SON, DDI, and GetPot interpreters have Hierarchical Input Validation Engine ([HIVE](/wasphive/README.md#hierarchical-input-validation-engine-hive)) adapters allowing them to be validated. 
As such, there are sonvalid, ddivalid, and getpotvalid utilities. 

Invocation of the validation utilities requires a schema, and an input:

```
sonvalid /path/to/schema.sch /path/to/input.inp
```

The schema's contents are beyond the scope of this document. The product of *valid will be a return code of 0 only if no validation errors occur in the input. 
If an error occurs, a non-zero return code is produced and validation errors emitted. See the [HIVE](/wasphive/README.md#hierarchical-input-validation-engine-hive) documentation of types of validation errors.

 
## The HierarchAL Input Template Expansion (HALITE) Engine 
The [HALITE](/wasphalite/README.md#hierarchial-input-template-expansion-engine-halite) engine has the corresponding `halite` command line utility. 

HALITE provides a data-driven template expansion capability and has sizable feature set for templating text data for input or other needs. 

The `halite` command line utility can be invoked with a template and optional [JSON](http://www.json.org/)-formatted data parameter set:

```
halite /path/to/template.tmpl
```
or with JSON parameter set:

```
halite /path/to/template.tmpl /path/to/data.json
```

The expanded template emitted on stdout, and errors/log information is emitted on stderr.


## Schema Skeleton Creation Utility

The ability to take multiple input files known to be valid and to create a schema skeleton from these can be a very useful starting point for schema creation.  Currently, a utility exists that allows this to be done with a series of SON input files.

Therefore, if a user has multiple SON formatted input files that are known to be valid, and the objectibve is to begin creating a schema for these files, the first step is to run

    sonschemaskel path/to/valid/input1.son path/to/valid/input2.son ...

and the resulting output will be a schema skeleton that can be used with the Hierarchical Input Validation Engine to validate the inputs.  These schema skeletons have actual rule stubs for each input node commented out.  These rules can reviewed in more detail in the [HIVE section](/wasphive/README.md#hierarchical-input-validation-engine-hive) and should be modified for each piece of input.


