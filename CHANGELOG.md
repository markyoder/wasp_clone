# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

### Changed 
 - GetPot block and subblock to be equivalent
 - GetPot comma is no longer a valid array separator
 - GetPot semicolon is now an allowed array separator
 - Gtest dependence from TriBITS to vanilla version
 - Extra repository logic from TriBITS to Git submodule 
 - FlexLexer version from 2.5.37 to 2.6.4
 - GNU BISON version from 3.0.4 to 3.7.6
 - VERA input parser to cache staged non decorative nodes to avoid expensive node-count loop  

### Added
 - waspdrive scheduler capability.
 - support for GetPot shorthand object notation '[x/y/z]'
 - support for commas in GetPot strings
 - support for double-quoted strings in GetPot documents
 - support for more than one input and template file in waspdrive input 
 - support for VERA input section naming and validation
 - support for parsing VERA input list syntax `<n..m x i> 193*10` etc.


### Fixed
- wasplsp compile error in certain configurations caused by missing include of `functional`.


## [1.0.3] - 10-07-2019
### Added
- GCC 5.4 compiler compatibility CI job.
- wasplsp - Language Server Protocol package with WaspServer and LSPInterpreter. See WASPLSP readme for details.
- waspdakota: a package for the Dakota UQ coupling. Specifically, support for the Dakota Parameter file format
- wasputils/substitute: a utility that allows direct use of the Dakota parameter file for template attribute substitution
- HIVE UNKNOWN input node validation capability (See HIVE readme for details).

### Changed
- waspvii hanging comment (comment 1 or more lines below last parameter) logic to reparent to the block

### Fixed
- wasppy inability to handle file paths with whitespaces.
- CMake package logic to allow for incorporation into a Fortran project.
- Missing support for apostrophe in xml element name effecting the getpotxml utility.


## [1.0.2] - 07-16-2018
### Added
- DocPrint utility that consumes an input schema and produces GitLab compatible Markdown. The Markdown can be converted to html using Pandoc.

## [1.0.1] - 07-05-2018
### Added
- wasppy/driver capability that allows execution of an external application and results extraction.

## [1.0.0] - 05-11-2018
### Added
- Typedefs for Default TokenPool,TreeNodePool, and Interpreters.
- Hierarchical data attribute references in HALITE. I.e., `<object.key.value>`

### Changed
- The TreeNodeView has been refactored to be NodeView and free of template parameters. This breaks backwards compatibility

### Fixed
- inoperable wasp2py when using wasp2py module from a regular wasp installation (i.e., wasp/wasppy/son2py and wasp/bin)
- missing support for `%` in expression engine strings
- missing support for `+` in ddi integer token lex pattern

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
