# HierarchiAL Input Template Expansion engine (HALITE)
The HALITE engine is a data-driven input template expansion engine intended to facilitate application input or data generation. 

When it comes to text creation there are typically two approaches, 
1) write a program to generate the needed text, 
or 2) create templates and some program glue logic to read the templates and substitute attributes. 


The HALITE engine attempts to bridge these approaches by providing standard glue logic. In this way, 
1) the templates preserve clarity of intended text, 
2) templates facilitate reuse,
3) development is streamlined by eliminating the developer and only requiring a template designer, and most importantly
4) templates are interchangeable allowing using the same data to create a different 'look', perhaps, for a different application to consume.

In addition to the above, the HALITE engine provides a single point, data-driven, expansion capability that removes the need for application-specific glue logic.

A template and an optional hierarchical data set is all that is needed to expand templates into text usable by the end consumer.

The supported data constructs are provide by JSON and are Objects, Arrays, and Keyed values. For more about JSON syntax see www.json.org.

The expression evaluation support scalar and vector variable reference and mathematical expression evaluations. 



Template constructs available are:
1. Static text - plain text to be emitted to the expanded result. Contains no attributes or expression evaluation.
2. Attributes - parameters or expressions to be evaluated, optionally formatted, and substituted into the expanded result.
3. Optional Attributes - parameters expressions that when only present are emitted to the expanded result.
4. Silent Attributes - parameters or expressions that when evaluated are NOT emitted to the expanded result. Useful for intermediate or cached attribute evaluations to be used later.
5. Iterative Attributes - expressions which are evaluated iteratively for a specified range(s) with optional separator and format.
6. Template imports - import a template into the existing template with optional use of data object.
7. Iterative template imports - import a template for each element of an array via 'using' an array or repeatedly via range variables.
8. Conditional action blocks - support pre-processor style #if/ifdef/ifndef - #elseif/else - #endif conditional blocks which will only be emitted when the appropriate condition is true.


TODO describe general HALITE logic flow

## Attributes and Expressions
TODO - describe attributes and expressions...

### Formatting 
TODO - describe formatting options...
 
## File Imports
TODO - describe file imports...
