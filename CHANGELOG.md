# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Additions
- Typedefs for Default TokenPool,TreeNodePool, and Interpreters.

### Changes
- The TreeNodeView has been refactored to be NodeView and free of template parameters. This breaks backwards compatibility

### Fixes
None
- inoperable wasp2py when using wasp2py module from a regular wasp installation (i.e., wasp/wasppy/son2py and wasp/bin)

## [0.1.2] - 01-22-2018
### Added
- The SON syntax now supports a 'block', ([blockname]) syntax which acts the same
as a SON object, but can be visually more appealing to users. It also allows for
compatibility with INI/Config and the NEK5000 PAR input formats.
- A clang-format style standard and updated code accordingly
- A SON2JSON routine and utility that allows conversion and validation 
of SON input to JSON. This allows for validated input use in Python.
- HALITE attribute delimiter intrinsic variables for use in rendering 
the literal delimiter.

### Fixed 
- MVSC 2015 and Intel compile error involving _set_output_format in waspcore/Format.h


## [0.1.1] - 10-22-2017
### Added
- HALITE configurable iterative delimiter emission capability that 
allows a delimiter to be emitted based on given iteration stide.
- HALITEWorkflow convenience class.
- Support for shared library builds on Windows
- Substantial improvements in README documentation
- Missing min/max functions to Expr/HALITE packages

### Changed
- HIVE ChildUniqueness and NotExistsIn to be case-insensitive

### Fixed 
- An issue where HALITE indirect attribute substitution produced a parse
error.
- A compiler error when when compiling in a Qt project the 'emit' macro and
the HALITE emit method collided.
- An issue where Expr lexer's REAL token regex consumed part of 
the alternative boolean operator (7.gt.8=> 7.ERROR, instead of 7.gt.8=> 7 > 8)
- A segfault when HALITE processes empty attribute


## [0.1.0] - 06-02-2017
### Added 
- SON input format support
- DDI input format support
- JSON data format support
- Expr math expression evaluation capability
- HIVE validation engine capability
- HALITE template engine capability
- GetPot input format 
- utilities for listing input formats
- utilities for validating input data
- utilities for input format conversion
