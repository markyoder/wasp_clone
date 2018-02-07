# 0.1.2
* The SON syntax now supports a 'block', ([blockname]) syntax which acts the same
as a SON object, but can be visually more appealing to users. It also allows for
compatibility with INI/Config and the NEK5000 PAR input formats.
* Introduced a clang-format style standard and updated code accordingly
* Introduced SON2JSON routine and utility that allows conversion and validation 
of SON input to JSON. This allows for validated input use in Python.
* Introduced HALITE attribute delimiter intrinsic variables for use in rendering 
the literal delimiter.
* Fixed a MVSC 2015 and Intel compile error involving _set_output_format in waspcore/Format.h


# 0.1.1 10-22-2017
* Added HALITE configurable iterative delimiter emission capability that 
allows a delimiter to be emitted based on given iteration stide.
* Added HALITEWorkflow convenience class.
* Added support for shared library builds on Windows
* Substantial improvements in README documentation
* Added missing min/max functions to Expr/HALITE packages
* Fixed a issue where HALITE indirect attribute substitution produced a parse
error.
* Fixed a compiler error when when compiling in a Qt project the 'emit' macro and
the HALITE emit method collided.
* Fixed issue where Expr lexer's REAL token regex consumed part of 
the alternative boolean operator (7.gt.8=> 7.ERROR, instead of 7.gt.8=> 7 > 8)

* Fixed


# 0.1.0 06-02-2017
* Added SON input format support
* Added DDI input format support
* Added JSON data format support
* Added Expr math expression evaluation capability
* Added HIVE validation engine capability
* Added HALITE template engine capability
* Added GetPot input format 
* Added utilities for listing input formats
* Added utilities for validating input data
* Added utilities for input format conversion
