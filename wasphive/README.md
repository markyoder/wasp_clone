# ***Hierarchical Input Validation Engine (HIVE)***

## **Table of Contents**
1. [Introduction](#introduction)

2. [Input Validation Rules Summary](#input-validation-rules-summary)
3. [Input Validation Rules Details](#input-validation-rules-details)
 - [Miscellaneous Validation Details](#miscellaneous-validation-details)
 - [MinOccurs Validation Details](#minoccurs-validation-details)
 - [MaxOccurs Validation Details](#maxoccurs-validation-details)
 - [ValType Validation Details](#valtype-validation-details)
 - [ValEnums Validation Details](#valenums-validation-details)
 - [MinValInc Validation Details](#minvalInc-validation-details)
 - [MaxValInc Validation Details](#maxvalinc-validation-details)
 - [MinValExc Validation Details](#minvalexc-validation-details)
 - [MaxValExc Validation Details](#maxvalexc-validation-details)
 - [ExistsIn Validation Details](#existsin-validation-details)
 - [NotExistsIn Validation Details](#notexistsin-validation-details)
 - [SumOver Validation Details](#sumover-validation-details)
 - [SumOverGroup Validation Details](#sumovergroup-validation-details)
 - [IncreaseOver Validation Details](#increaseover-validation-details)
 - [DecreaseOver Validation Details](#decreaseover-validation-details)
 - [ChildAtMostOne Validation Details](#childatmostone-validation-details)
 - [ChildExactlyOne Validation Details](#childexactlyone-validation-details)
 - [ChildAtLeastOne Validation Details](#childatLeastone-validation-details)
 - [ChildCountEqual Validation Details](#childcountequal-validation-details)
 - [ChildUniqueness Validation Details](#childuniqueness-validation-details)
4. [Input Assistance Rules Details](#input-assistance-rules-details)
 - [MinOccurs Assistance Details](#minoccurs-assistance-details)
 - [ChildAtMostOne Assistance Details](#childatmostone-assistance-details)
 - [ChildExactlyOne Assistance Details](#childexactlyone-assistance-details)
 - [ValEnums Assistance Details](#valenums-assistance-details)
 - [ValType Assistance Details](#valtype-assistance-details)
 - [ExistsIn Assistance Details](#existsin-assistance-details)
 - [InputTmpl Assistance Details](#inputtmpl-assistance-details)
 - [InputName Assistance Details](#inputname-assistance-details)
 - [InputType Assistance Details](#inputtype-assistance-details)
 - [InputVariants Assistance Details](#inputvariants-assistance-details)
 - [InputDefault Assistance Details](#inputdefault-assistance-details)
 - [Description Assistance Details](#description-assistance-details)
5. [Input Validation Rules Examples](#input-validation-rules-examples)
 - [Miscellaneous Validation Examples](#miscellaneous-validation-examples)
 - [MinOccurs Validation Examples](#minoccurs-validation-examples)
 - [MaxOccurs Validation Examples](#maxoccurs-validation-examples)
 - [ValType Validation Examples](#valtype-validation-examples)
 - [ValEnums Validation Examples](#valenums-validation-examples)
 - [MinValInc Validation Examples](#minvalInc-validation-examples)
 - [MaxValInc Validation Examples](#maxvalinc-validation-examples)
 - [MinValExc Validation Examples](#minvalexc-validation-examples)
 - [MaxValExc Validation Examples](#maxvalexc-validation-examples)
 - [ExistsIn Validation Examples](#existsin-validation-examples)
 - [NotExistsIn Validation Examples](#notexistsin-validation-examples)
 - [SumOver Validation Examples](#sumover-validation-examples)
 - [SumOverGroup Validation Examples](#sumovergroup-validation-examples)
 - [IncreaseOver Validation Examples](#increaseover-validation-examples)
 - [DecreaseOver Validation Examples](#decreaseover-validation-examples)
 - [ChildAtMostOne Validation Examples](#childatmostone-validation-examples)
 - [ChildExactlyOne Validation Examples](#childexactlyone-validation-examples)
 - [ChildAtLeastOne Validation Examples](#childatLeastone-validation-examples)
 - [ChildCountEqual Validation Examples](#childcountequal-validation-examples)
 - [ChildUniqueness Validation Examples](#childuniqueness-validation-examples)

---
## **Introduction**

The Hierarchical Input Validation Engine (**HIVE**) uses a set of rules to describe the schema of an application's input. These rules describe scalar and relational input restrictions. They can use ***Sequence Input Retrieval ENgine (SIREN) Expression*** paths to define restrictions related to relative sets of input elements. Schema files for HIVE are written using the ***Standard Object Notation (SON) Syntax***.  Applications, such as the **NEAMS Workbench**, use HIVE and schema files to facilitate input validation, introspection, and assistance by using ***Grammar Files*** to associate an application with a schema file and a directory containing ***Template Files***. ***SIREN Expressions***, ***SON Syntax***, ***Grammar Files***, and ***Template Files*** are beyond the scope of this document, but they can all be referenced in their own documentation.

The document layout is as follows:

- The [Input Validation Rules Summary](#input-validation-rules-summary) section provides a very brief description of each input validation rule.

- The [Input Validation Rules Details](#input-validation-rules-details) section provides a more detailed description of each input validation rule with verbal examples of how the rules may be applied.

- The [Input Assistance Rules Details](#input-assistance-rules-details) section provides descriptions and details of the rules that can be used by NEAMS Workbench for input assistance and autocompletion.

- The [Input Validation Rules Examples](#input-validation-rules-examples) provides very detailed examples and exact syntax of every validation rule.  This section supplies an example schema, an example input that will pass validation against the schema, an example input that will fail validation against the schema, and the validation messages that HIVE produces when validating the failing input against the provided schema. If incorporating a specific rule in the integration of an application into the NEAMS Workbench, then the examples section for that particular rule should be fully understood syntactically and semantically.

- In this document, the term ***input*** is used when referring to a file is to be validated, and ***schema*** is used when referring to the file that describes the definition and rules against which the input is validated. Currently, schema files must be written in the SON syntax.  We will be using the SON syntax for example input files in this document as well.

---
## **Input Validation Rules Summary**

* ***MinOccurs***  - describes the minimum number of times that an element is allowed to appear under its parent context.
* ***MaxOccurs*** - describes the maximum number of times that an element is allowed to appear under its parent context.
* ***ValType*** - describes the allowed value type for the element (Int, Real, String).
* ***ValEnums*** - describes a list of allowed value choices for the element.
* ***MinValInc*** - describes the minimum inclusive value that this element is allowed to have if it is a number (i.e. the provided input value must be greater than or equal to this).
* ***MaxValInc*** - describes the maximum inclusive value that this element is allowed to have if it is a number (i.e. the provided input value must be less than or equal to this).
* ***MinValExc*** - describes the minimum exclusive value of the element in the input if it is a number (i.e. the provided input value must be greater than this).
* ***MaxValExc*** - describes the maximum exclusive value of the element in the input if it is a number (i.e. the provided input value must be less than this).
* ***ExistsIn*** - describes a set of lookup paths into relative sections of the input file and possible constant values where the value of the element being validated must exist.
* ***NotExistsIn*** - describes a set of lookup paths into relative sections of the input file where the value of the element being validated must not exist.
* ***SumOver***  - describes what sum the values must add to under a given context.
* ***SumOverGroup*** - describes what sum the values must add to under a given context when grouped by dividing another input element's value by a given value.
* ***IncreaseOver*** - describes that the values under the element must be increasing in the order that they are read.
* ***DecreaseOver*** - describes that the values under the element must be decreasing in the order that they are read.
* ***ChildAtMostOne*** - describes one or more lists of lookup paths into relative sections of the input file (and possible values) where at most one is allowed to exist.
* ***ChildExactlyOne*** - describes one or more lists of lookup paths into relative sections of the input file (and possible values) where at exactly one is allowed to exist.
* ***ChildAtLeastOne*** - describes one or more lists of lookup paths into relative sections of the input file (and possible values) where at least one must exist.
* ***ChildCountEqual*** - describes one or more lists of lookup paths into relative sections of the input file where the number of values must be equal.
* ***ChildUniqueness*** - describes one or more lists of lookup paths into relative sections of the input file where the values at all of these paths must be unique.

---
## **Input Validation Rules Details**

### Miscellaneous Validation Details

- Before exploring the details of all of the validation rules, the first thing to note is that a schema file must represent a superset of the hierarchy of all possible inputs.  This is just to say that every hierarchical node in an input file that is to be validated, must have an exact mapping to a node at the same hierarchical path in the schema. If there is an element in an input file that does not have an exact mapping to an associated node in the schema, then that element is said to be invalid. Once the hierarchy of the schema is built, then rules can be added to every element for validation.

- At the basic level, there are two types of validation messages that may be reported by HIVE.

1. Problems with the ***input*** file are reported in the form:
        
        line:X column:Y - Validation Error: MESSAGE


	*The NEAMS Workbench captures the line and column reported so that the offending input elements can be navigated to simply by clicking on the message.*
	
            
2. Problems with the ***schema*** file are reported in the form:
        
        Validation Error: Invalid Schema Rule: MESSAGE line:X column:Y


	*These messages denote an actual error in the schema file (not the input) at the provided line and column number.*
 
For examples of these ***Miscellaneous Validation Details*** (including schemas, inputs, and expected validation messages), please see [Miscellaneous Validation Examples](#miscellaneous-validation-examples).

### MinOccurs Validation Details

- The ***Minimum Occurrence*** rule describes the minimum number of times that an element must occur under its parent context. It is used mostly to denote if a piece of input is required or optional. Most often, this rule will have a literal constant for minimum allowances.  The value must be an integer. For example, `MinOccurs = 0` denotes that this element is optional under its parent context, and `MinOccurs = 1` denotes that this element is required to occur at least once under its parent. This rule may also have a relative input lookup path from the element being validated. If the lookup path describes a set containing a single value, and if that value is an integer, then that value will be used to determine the minimum allowed occurrences of the element being validated.
 
For detailed usage examples and syntax of the ***Minimum Occurrence*** rule (including schemas, inputs, and expected validation messages), please see [MinOccurs Validation Examples](#minoccurs-validation-examples).

### MaxOccurs Validation Details

The ***Maximum Occurrence*** rule describes the maximum number of times that an element is allowed to occur under its parent context. Most often, this element will have a literal constant value to describe a  number of maximum allowances.  The value  must be integer or '**NoLimit**' (indicating that there is no upper limit on the number of times this element can occur). This rule may also have a relative input lookup path from the element being validated. If the lookup path describes a set containing a single value, and if that value is an integer, then that value will be used to determine the maximum allowed occurrences of the element being validated.

For detailed usage examples and syntax of the ***Maximum Occurrence*** rule (including schemas, inputs, and expected validation messages), please see [MaxOccurs Validation Examples](#maxoccurs-validation-examples).

### ValType Validation Details

 - The ***Value Type*** rule checks the type of the element value in the input. This can be one of the following: 
* `Int` - meaning a negative or positive integer
* `Real` - meaning a negative or positive floating point value (or integer)
* `String` - meaning a literal string of text

For detailed usage examples and syntax of the ***Value Type*** rule (including schemas, inputs, and expected validation messages), please see [ValType Validation Examples](#valtype-validation-examples).

### ValEnums Validation Details

- The ***Value Enumerations*** rule contains a static list of values choices.  It compares the element's input value with the provided choices. If the element's value is not in the schema's list of allowed enumerations, then this check will fail. Note: This check is case insensitive and if the value being checked is an integer, then leading zeros are ignored.

For detailed usage examples and syntax of the ***Value Enumerations*** rule (including schemas, inputs, and expected validation messages), please see [ValEnums Validation Examples](#valenums-validation-examples).

### MinValInc Validation Details

- The ***Minimum Value Inclusive*** rule provides a number (real or integer) to which the associated input value must be greater than or equal. Most often, this rule will contain a constant number defining the minimum value that this element is allowed to be.  For example, *MinValInc = 0.0* denotes that this element's value must be zero or greater. This rule may also have a relative input lookup path from the element being validated.  If the set in the input represented by the relative path is a single value, and if that value is a number, then that value will be used to determine the lowest allowed value for the element being validated. If an element at this relative lookup path exists in the input and it is not a number, then it will fail this check.  However, if this element does not exist at all in the input, then this validation check will not fail - that is delegated to the `MinOccurs` check.

For detailed usage examples and syntax of the ***Minimum Value Inclusive*** rule (including schemas, inputs, and expected validation messages), please see [MinValInc Validation Examples](#minvalinc-validation-examples).

### MaxValInc Validation Details

- The ***Maximum Value Inclusive*** rule provides a number (real or integer) to which the associated input value must be less than or equal. Most often, this rule will contain a constant number defining the maximum value that this element is allowed to be.  For example, *MaxValInc = 0.0* denotes that this element's value must be zero or less.  This rule may also have a relative input lookup path from the element being validated.  If the set in the input represented by the relative path is a single value, and if that value is a number, then that value will be used to determine the highest allowed value for the element being validated. If an element at this relative lookup path exists in the input and it is not a number, then it will fail this check.  However, if this element does not exist at all in the input, then this validation check will not fail - that is delegated to the `MinOccurs` check.

For detailed usage examples and syntax of the ***Maximum Value Inclusive*** rule (including schemas, inputs, and expected validation messages), please see [MaxValInc Validation Examples](#maxvalinc-validation-examples).

### MinValExc Validation Details

- The ***Minimum Value Exclusive*** rule provides a number (real or integer) to which the associated input value must be greater. Most often, this rule will contain a constant number, and the associated input value must be greater than this number.  For example, *MinValExc = 0.0* denotes that this element value must be greater than zero (not equal). This rule may also have a relative input lookup path from the element being validated.  If the set in the input represented by the relative path is a single value, and if that value is a number, then that value will be used to determine the minimum exclusive allowed input value. If an element at this relative lookup path exists in the input and it is not a number, then it will fail this check.  However, if this element does not exist at all in the input, then this validation check will not fail - that is delegated to the `MinOccurs` check.

For detailed usage examples and syntax of the ***Minimum Value Exclusive*** rule (including schemas, inputs, and expected validation messages), please see [MinValExc Validation Examples](#minvalexc-validation-examples).

### MaxValExc Validation Details

- The ***Maximum Value Exclusive*** rule provides a number (real or integer) to which the associated input value must be less. Most often, this rule will contain a constant number, and the associated input value must be less than this number.  For example, *MaxValExc = 0.0* denotes that this element value must be less than zero (not equal). This rule may also have a relative input lookup path from the element being validated.  If the set in the input represented by the relative path is a single value, and if that value is a number, then that value will be used to determine the maximum exclusive allowed input value. If an element at this relative lookup path exists in the input and it is not a number, then it will fail this check.  However, if this element does not exist at all in the input, then this validation check will not fail - that is delegated to the `MinOccurs` check.

For detailed usage examples and syntax of the ***Maximum Value Exclusive*** rule (including schemas, inputs, and expected validation messages), please see [MaxValExc Validation Examples](#maxvalexc-validation-examples).

### ExistsIn Validation Details

- The ***Exists In*** rule is used as a key to say that an element in the input must be defined somewhere else in the input.  This rule will always contain one or more relative input lookup paths from the element being validated.  The pieces of input at these paths will be collected into a set.  This rule also may contain one or more optional constant values. If these exist, then the constant values will also be added to the set.  Then, all of the values in the input being validated by this rule must exist in the set built from the lookup paths and the constant values in order to pass the validation.  If any element does not exist in this set, then the validation check fails.  This rule may use an optional `Abs` modifier flag that can occur as a parenthetical identifier. The `Abs` modifier flag indicates that the absolute value of all numbers added to the set checked for existence are used.  Then, even if the value of the element being validated is negative and a value at one of the rule's relative input lookup paths is positive, but they have the same absolute value, this validation check will pass. Note: this check is case insensitive, and if the value being checked is an integer, then leading zeros are ignored.

For detailed usage examples and syntax of the ***Exists In*** rule (including schemas, inputs, and expected validation messages), please see [ExistsIn Validation Examples](#existsin-validation-examples).

### NotExistsIn Validation Details

- The ***Not Exists In*** rule will always contain one or more relative input lookup paths from the element being validated. The pieces of input at these paths will be collected into a set.  If the value of the element being validated exists in this set, then this validation check fails.  If it does not exist, then the validation check passes. This rule may use an optional `Abs` modifier flag that can occur as a parenthetical identifier. The `Abs` modifier flag indicates that the absolute value of all numbers added to the set checked for existence are used.  Then, even if the value of the element being validated is negative and a value at one of the rule's relative input lookup paths is positive, but they have the same absolute value, this validation check will fail. Note: this check is case insensitive, and if the value being checked is an integer, then leading zeros are ignored.

For detailed usage examples and syntax of the ***Not Exists In*** rule (including schemas, inputs, and expected validation messages), please see [NotExistsIn Validation Examples](#notexistsin-validation-examples).

### SumOver Validation Details

 - The ***Sum Over*** rule must always contain a **context expression** and an **expected sum value**. The expected sum value is the desired sum when all of the the  elements in the given context are summed. The context contains a relative ancestry path in the input hierarchy that the values will be summed over. For a simple array, this will usually be "**..**", however it may go back further in lineage if needed (e.g. "**../../..**").

For detailed usage examples and syntax of the ***Sum Over*** rule (including schemas, inputs, and expected validation messages), please see [SumOver Validation Examples](#sumover-validation-examples).

### SumOverGroup Validation Details

- The ***Sum Over Group*** rule must always contain a **context path**, a **group sum value**, a **compare path**, and a **group divide value**.  The compare path is used to acquire another element in the input hierarchy relative to the current element being validated.  This value must exist in the input and be a number.  Then, this value is divided by the group divide value.  This does integer division to split the input element that will be added into groups.  Then, each group must successfully add to the group sum value.  If any group does not add to the group sum value, then this validation check fails.  If every group (when split by performing an integer division on the value at the compare path relative location by the group divide value) adds to the same desired group sum, then this validation check passes.

For detailed usage examples and syntax of the ***Sum Over Group*** rule (including schemas, inputs, and expected validation messages), please see [SumOverGroup Validation Examples](#sumovergroup-validation-examples).

### IncreaseOver Validation Details

- The ***Increase Over*** rule must contain a required modifier flag that occurs as a parenthetical identifier and indicates the monotonicity. The flag must either be `Strict`, meaning that the values must be strictly increasing in the order that they are read (no two values are the same), or `Mono`, meaning that multiple value are allowed to be the same as long as they never decrease.  For example *3 4 5 5 6 7* would pass a `Mono` check, but fail a `Strict` check due to two value being the same.  This rule also contains a context path that describes the relative ancestry in the input hierarchy under which the values must increase.  For a simple array, this will usually be "**..**". However, it may go back further in lineage if needed (e.g. "**../../..**").

For detailed usage examples and syntax of the ***Increase Over*** rule (including schemas, inputs, and expected validation messages), please see [IncreaseOver Validation Examples](#increaseover-validation-examples).

### DecreaseOver Validation Details

- The ***Decrease Over*** rule must contain a required modifier flag that occurs as a parenthetical identifier and indicates the monotonicity. The flag must either be `Strict`, meaning that the values must be strictly decreasing in the order that they are read (no two values are the same), or `Mono`, meaning that multiple value are allowed to be the same as long as they never increase.  For example *7 6 5 5 4 3* would pass a `Mono` check, but fail a `Strict` check due to two value being the same.  This rule also contains a context path that describes the relative ancestry in the input hierarchy under which the values must decrease.  For a simple array, this will usually be "**..**". However, it may go back further in lineage if needed (e.g. "**../../..**").

For detailed usage examples and syntax of the ***Decrease Over*** rule (including schemas, inputs, and expected validation messages), please see [DecreaseOver Validation Examples](#decreaseover-validation-examples).

### ChildAtMostOne Validation Details

- The ***Child At Most One*** rule contains multiple relative input lookup paths. Each of these lookup paths can optionally have an assigned lookup value. There may be multiple of these rules for any given element in the schema. Of the given list of elements, *at most one* must exist in the input in order for this rule to pass. If there is a lookup value associated with the lookup path, then that path's value in the input must be equal to what is provided in the schema in order for that element to count towards existence.

For detailed usage examples and syntax of the ***Child At Most One*** rule (including schemas, inputs, and expected validation messages), please see [ChildAtMostOne Validation Examples](#childatmostone-validation-examples).

### ChildExactlyOne Validation Details

- The ***Child Exactly One*** rule contains multiple relative input lookup paths. Each of these lookup paths can optionally have an assigned lookup value. There may be multiple of these rules for any given element in the schema. Of the given list of elements, *exactly one* must exist in the input in order for this rule to pass. If there is a lookup value associated with the lookup path, then that path's value in the input must be equal to what is provided in the schema in order for that element to count towards existence.

For detailed usage examples and syntax of the ***Child Exactly One*** rule (including schemas, inputs, and expected validation messages), please see [ChildExactlyOne Validation Examples](#childexactlyone-validation-examples).

### ChildAtLeastOne Validation Details

- The ***Child At Least One*** rule contains multiple relative input lookup paths.  Each of these lookup paths can optionally have an assigned lookup value. There may be multiple of these rules for any given element in the schema. Of the given list of elements, *at least one* must exist in the input in order for this rule to pass.  If there is a lookup value associated with the lookup path, then that path's value in the input must be equal to what is provided in the schema in order for that element to count towards existence.

For detailed usage examples and syntax of the ***Child At Least One*** rule (including schemas, inputs, and expected validation messages), please see [ChildAtLeastOne Validation Examples](#childatleastone-validation-examples).

### ChildCountEqual Validation Details

- The ***Child Count Equal*** rule is usually used to ensure that arrays in the input have an equal number of value members.  There may be multiple of these rules on any given element.  This rule contains multiple relative input look paths and a required modifier flag that occurs as a parenthetical identifier.  This modifier flag can be either `IfExists` or `EvenNone`.  If the modifier flag is `IfExists`, then it means that the pieces of input in the relative lookup paths must be equal only if they actually exist.  However, If the modifier flag is `EvenNone`, then this is a stricter rule that denotes that the relative input lookup path nodes in the input must be equal regardless if they exist or not.

For detailed usage examples and syntax of the ***Child Count Equal*** rule (including schemas, inputs, and expected validation messages), please see [ChildCountEqual Validation Examples](#childcountequal-validation-examples).

### ChildUniqueness Validation Details

- The ***Child Uniqueness*** rule is used quite often. Every value in this set has to occur once and only once among all other values, at all other paths. There may be multiple of these rules on any given element. This rule may use an optional `Abs` modifier flag that can occur as a parenthetical identifier. The `Abs` modifier flag indicates that the absolute value of all numbers added to the set checked for uniqueness are used.  Then, even if one value is negative and the other is positive, but they have the same absolute value, this validation check will fail.  For example, if one ChildUniqueness relative input lookup path contains "*-5*" and another relative lookup input path contains "*5*", this validation check will fail if the `Abs` modifier flag is used.

For detailed usage examples and syntax of the ***Child Uniqueness*** rule (including schemas, inputs, and expected validation messages), please see [ChildUniqueness Validation Examples](#childuniqueness-validation-examples).

---
## **Input Assistance Rules Details**

### MaxOccurs Assistance Details

- The ***Maximum Occurrence*** rule is used by the NEAMS Workbench logic for filtering options as needed from the autocompletion list.  An element can only be added up to MaxOccurs times via autocomplete.  For example, if an element has `MaxOccurs = 1`, it can only be added once to the document.  After is it added once, it is filtered from the autocompletion list.

### ChildAtMostOne Assistance Details

- The ***Child At Most One*** rule is used by the NEAMS Workbench logic for filtering options as needed from the autocompletion list.  If at most one of multiple choices are allowed at any context, then as soon as one of those choices are added to the document, the others are filtered from the autocompletion list.  For example, if an element has `ChildAtMostOne = [ choice1 choice2 choice3]`, and `choice2` is added, then `choice1` and `choice3` will not be available on the next autocomplete.

### ChildExactlyOne Assistance Details

- The ***Child Exactly One*** rule is used by the NEAMS Workbench logic for filtering options as needed from the autocompletion list.  If exactly one of multiple choices are allowed at any context, then as soon as one of those choices are added to the document, the others are filtered from the autocompletion list.  For example, if an element has `ChildExactlyOne = [ choice1 choice2 choice3]`, and `choice2` is added, then `choice1` and `choice3` will not be available on the next autocomplete.

### ValEnums Assistance Details

- The ***Value Enumerations*** rule is used by the NEAMS Workbench autocompletion logic to provide a set of choices that are legal at a given context based on a static set of values supplied in the schema.  For example, if an element has `ValEnums = [ "a" "b" "c" "d" ]`,  then those values will be provided as autocompletion options.

### ExistsIn Assistance Details

- The ***Exists In*** rule is used by the NEAMS Workbench autocompletion logic to provide a set of choices that are legal at a given context based on values supplied elsewhere in the input.  For example, if an element has `ExistsIn = [ "../../some/context1" "../../some/context2" ]`, and the values `1`, `2`, `3`, and `4` exist in the input at that relative context, then those values will be provided as autocompletion options.

### ValType Assistance Details

- The ***Value Type*** rule is used by the NEAMS Workbench autocompletion logic to drop in a legitimate default value of the correct type for flag-values and flag-arrays if no `InputDefault` is provided in the schema.

 - For an element with a `ValType = Int` rule, `1` will be inserted.
 - For an element with a `ValType = Real` rule, `0.0` will be inserted.
 - For an element with a `ValType = String` rule, `'insert-string-here'` will be inserted.
 
- To override this behavior, please see [InputDefault Assistance Details](#inputdefault-assistance-details).

### InputTmpl Assistance Details

- The ***Input Template*** rule is used by the NEAMS Workbench to pick which ***Template File*** to use for autocompletion.  For example, if a context has `InputTmpl = MyCustomTemplate` then a template named `MyCustomTemplate.tmpl` in the template directory provided by a NEAMS Workbench ***Grammar File*** will be used for autocompletion. ***Template Files*** and ***Grammars Files*** are beyond the scope of this document, but they can be referenced in their own documentation.

### InputName Assistance Details

- The ***Input Name*** rule is used by the NEAMS Workbench to override the name of the actual node that the template provided by `InputTmpl` uses for autocompletion, if desired. For example, if the name of an element in the input hierarchy is `something_one` (therefore the name in the schema must be the same), but a template named `MySomething.tmpl` should use the name `something_two` instead for autocompletion, then `something_one` can be overridden with  via:

	    something_one{
	        InputName = "something_two"
	        InputTmpl = "MySomething"
	    }

### InputType Assistance Details

- The ***Input Type*** rule is used by the NEAMS Workbench to let the template provided by `InputTmpl` for autocompletion know what type to switch on, if desired. If a template can handle multiple situations in different ways depending on what type it is dealing with, then Workbench will let the template know the type of the current autocompletion context is with this rule.  For example, if there is a template named `FlagTypes.tmpl` that can handle the types `FlagValue` and `FlagArray` differently, then Workbench can let the template know it is dealing with a `FlagValue` via:

        flag_value_node{
            InputType = "FlagValue"
            InputTmpl = "FlagTypes"
        }

- Or, Workbench can let the same template know it is dealing, instead, with a `FlagArray` via:

	    flag_array_node{
	        InputType = "FlagArray"
	        InputTmple = "FlagType"
	    }

### InputVariants Assistance Details

- The ***Input Variants*** rule is used by the NEAMS Workbench to provide multiple choices of autocompletion templates for a single context.  For example, if an element has `InputVariants = [ 'simple_version' 'middle_version' 'complex_version' ]` **AND** `simple_version.tmpl`, `middle_version.tmpl,` and `complex_version.tmpl` exist in the template directory provided by application's grammar, then all three of those choices will be available at that context via autocomplete and use their associate templates.

### InputDefault Assistance Details

- The ***Input Default*** rule is used by the NEAMS Workbench to explicitly tell a template what value should be dropped in for flag-values and flag-arrays via `InputDefault = 'explicit_default_value'`.   This overrides the `ValType` logic described in [ValType Assistance Details](#valtype-assistance-details).

### Description Assistance Details

-  The ***Input Description*** rule is just used by the NEAMS Workbench to give a short one line description in the autocompletion dropdown list via `Description = 'autocomplete dropdown description'` .  These descriptions can be very useful to novice users unfamiliar with all of the parameters at a given context.  These descriptions are not used by the templates for any further autocompletion logic.

---

## **Input Validation Rules Examples**

### Miscellaneous Validation Examples

For a verbal description of these ***Miscellaneous Validation Details***, please see [Miscellaneous Validation Details](#miscellaneous-validation-details).

 - Schema example:

        test{
        
            should_exist_one{
            }
            should_exist_two{
                value{
                }
            }
            invalid_rule{
                inside{
                    BadRuleName=10
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            should_exist_one   = 1
            should_exist_two   = [ 2 3 4 5 ]
        
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            should_not_exist_one   = 21
            should_not_exist_two   = [ 22 23 24 25 ]
            invalid_rule{
                inside=5
            }
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: "BadRuleName" line:11 column:13
        
        line:3 column:5 - Validation Error: /test/should_not_exist_one is not a valid piece of input
        
        line:4 column:5 - Validation Error: /test/should_not_exist_two is not a valid piece of input

### MinOccurs Validation Examples        

For a verbal description of the ***Minimum Occurrence*** validation rule, please see [MinOccurs Validation Details](#minoccurs-validation-details).

 - Schema example:

        test{
        
            control{
            }
            bad_two_numbers{
            }
            bad_real{
            }
            bad_string{
            }
            valueone{
                MinOccurs=10
            }
            valuetwo{
                MinOccurs="../control"
            }
            valuethree{
                inside{
                    MinOccurs=-5
                }
            }
            value_bad_one{
                inside{
                    MinOccurs="../../bad_two_numbers"
                }
            }
            value_bad_two{
                inside{
                    MinOccurs="../../bad_real"
                }
            }
            value_bad_three{
                inside{
                    MinOccurs="../../bad_string"
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            control=15
        
            valueone=1
            valueone=2
            valueone=3
            valueone=4
            valueone=5
            valueone=6
            valueone=7
            valueone=8
            valueone=9
            valueone=10
        
            valuetwo=1
            valuetwo=2
            valuetwo=3
            valuetwo=4
            valuetwo=5
            valuetwo=6
            valuetwo=7
            valuetwo=8
            valuetwo=9
            valuetwo=10
            valuetwo=11
            valuetwo=12
            valuetwo=13
            valuetwo=14
            valuetwo=15
        
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            control=15
        
            valueone=1
            valueone=2
            valueone=3
            valueone=4
            valueone=5
            valueone=6
            valueone=7
            valueone=8
            valueone=9
        
            valuetwo=1
            valuetwo=2
            valuetwo=3
            valuetwo=4
            valuetwo=5
            valuetwo=6
            valuetwo=7
            valuetwo=8
            valuetwo=9
            valuetwo=10
            valuetwo=11
            valuetwo=12
            valuetwo=13
            valuetwo=14
        
        }
        
        test{
            bad_two_numbers=6
            bad_two_numbers=7
            bad_real=8.2
            bad_string='some_string'
            valuethree{
            }
            value_bad_one{
            }
            value_bad_two{
            }
            value_bad_three{
            }
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:1 column:1 - Validation Error: test has 9 "valueone" occurrences - when there should be a minimum occurrence of 10

        line:1 column:1 - Validation Error: test has 14 "valuetwo" occurrences - when there should be a minimum occurrence of "15" from "../control"

        line:32 column:1 - Validation Error: test has 0 "valueone" occurrences - when there should be a minimum occurrence of 10

        line:37 column:5 - Validation Error: valuethree has 0 "inside" occurrences - when there should be a minimum occurrence of -5

        line:39 column:5 - Validation Error: inside minimum occurrence checks against "../../bad_two_numbers" which returns more than one value

        line:41 column:5 - Validation Error: inside minimum occurrence checks against "../../bad_real" which does not return a valid number

        line:43 column:5 - Validation Error: inside minimum occurrence checks against "../../bad_string" which does not return a valid number


### MaxOccurs Validation Examples        

For a verbal description of the ***Maximum Occurrence*** validation rule, please see [MaxOccurs Validation Details](#maxoccurs-validation-details).

 - Schema example:

        test{
        
            MaxOccurs=NoLimit
            control{
            }
            bad_two_numbers{
            }
            bad_real{
            }
            bad_string{
            }
            valueone{
                MaxOccurs=10
            }
            valuetwo{
                MaxOccurs="../control"
            }
            value_bad_one{
                inside{
                    MinOccurs="../../bad_two_numbers"
                }
            }
            value_bad_two{
                inside{
                    MinOccurs="../../bad_real"
                }
            }
            value_bad_three{
                inside{
                    MinOccurs="../../bad_string"
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            control=15
        
            valueone=1
            valueone=2
            valueone=3
            valueone=4
            valueone=5
            valueone=6
            valueone=7
            valueone=8
            valueone=9
            valueone=10
        
            valuetwo=1
            valuetwo=2
            valuetwo=3
            valuetwo=4
            valuetwo=5
            valuetwo=6
            valuetwo=7
            valuetwo=8
            valuetwo=9
            valuetwo=10
            valuetwo=11
            valuetwo=12
            valuetwo=13
            valuetwo=14
            valuetwo=15
        
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            control=15
        
            valueone=1
            valueone=2
            valueone=3
            valueone=4
            valueone=5
            valueone=6
            valueone=7
            valueone=8
            valueone=9
            valueone=10
            valueone=11
        
            valuetwo=1
            valuetwo=2
            valuetwo=3
            valuetwo=4
            valuetwo=5
            valuetwo=6
            valuetwo=7
            valuetwo=8
            valuetwo=9
            valuetwo=10
            valuetwo=11
            valuetwo=12
            valuetwo=13
            valuetwo=14
            valuetwo=15
            valuetwo=16
        
        }
        
        test{
            valueone=1
            valueone=2
            valueone=3
            valueone=4
            valueone=5
            valueone=6
            valueone=7
            valueone=8
            valueone=9
            valueone=10
            valueone=11
            valueone=12
            valueone=13
            valueone=14
        }
        test{
            control=2
            bad_two_numbers=6
            bad_two_numbers=7
            bad_real=8.2
            bad_string='some_string'
            valueone=1
            valuetwo=1
            valuetwo=2
            valuetwo=3
            valuetwo=4
            value_bad_one{
            }
            value_bad_two{
            }
            value_bad_three{
            }
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:1 column:1 - Validation Error: test has 11 "valueone" occurrences - when there should be a maximum occurrence of 10

        line:1 column:1 - Validation Error: test has 16 "valuetwo" occurrences - when there should be a maximum occurrence of "15" from "../control"

        line:36 column:1 - Validation Error: test has 14 "valueone" occurrences - when there should be a maximum occurrence of 10

        line:52 column:1 - Validation Error: test has 4 "valuetwo" occurrences - when there should be a maximum occurrence of "2" from "../control"

        line:63 column:5 - Validation Error: inside minimum occurrence checks against "../../bad_two_numbers" which returns more than one value

        line:65 column:5 - Validation Error: inside minimum occurrence checks against "../../bad_real" which does not return a valid number

        line:67 column:5 - Validation Error: inside minimum occurrence checks against "../../bad_string" which does not return a valid number


### ValType Validation Examples        

For a verbal description of the ***Value Type*** validation rule, please see [ValType Validation Details](#valtype-validation-details).

 - Schema example:

        test{
        
            one{
                ValType=Int
            }
            two{
                ValType=Int
            }
            three{
                ValType=Int
            }
            four{
                ValType=Real
            }
            five{
                ValType=Real
            }
            six{
                ValType=Real
            }
            seven{
                ValType=String
            }
            eight{
                ValType=String
            }
            nine{
                inside{
                    ValType=BadType
                }
            }
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
            one=-8
            two=0
            three=83
            four=-9.4
            five=3
            six='+9e-3'
            seven=ThisIsAString
            eight="This Is Also A String"
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
            one=-8.3
            two=0.3
            three="+8e-3"
            four='*'
            five=StringHere
            six='another string here'
            seven=4.5
            eight=5E-4
            nine='hello world'
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: Bad ValType Option "BadType" at line:29 column:21 - Expected [ Int Real String ]

        line:2 column:5 - Validation Error: one value "-8.3" is not of type Int

        line:3 column:5 - Validation Error: two value "0.3" is not of type Int

        line:4 column:5 - Validation Error: three value "+8e-3" is not of type Int

        line:5 column:5 - Validation Error: four value "*" is not of type Real

        line:6 column:5 - Validation Error: five value "StringHere" is not of type Real

        line:7 column:5 - Validation Error: six value "another string here" is not of type Real
        

### ValEnums Validation Examples        

For a verbal description of the ***Value Enumerations*** validation rule, please see [ValEnums Validation Details](#valenums-validation-details).

 - Schema example:

        test{
        
            one{
                ValEnums=[ yes no maybe ]
            }
            two{
                ValEnums=[ yes no maybe ]
            }
            three{
                ValEnums=[ REF:ReferencedColors ]
            }
            four{
                ValEnums=[ REF:ReferencedNumbers ]
            }
            five{
                ValEnums=[ REF:ReferencedNumbers REF:ReferencedColors ]
            }
            six{
                ValEnums=[ REF:BadReference REF:ReferencedNumbers ]
            }
        
        }
        
        EndOfSchema{}
        
        ReferencedColors=[ red orange yellow green blue indigo violet ]
        ReferencedNumbers=[ 1 2 3 4 5 ]

 - Input example that **PASSES** validation on schema above:

        
        test{
            one="yes"
            two='Maybe'
            three=blue
            four=4
            five=oRanGe
            five=0002
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
            one=red
            two="Green"
            three=yes
            four=-4
            five=007
            six=something
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: Enum Reference "BadReference" at line:19 column:20 not found in schema

        line:2 column:5 - Validation Error: one value "red" is not one of the allowed values: [ "maybe" "no" "yes" ]

        line:3 column:5 - Validation Error: two value "green" is not one of the allowed values: [ "maybe" "no" "yes" ]

        line:4 column:5 - Validation Error: three value "yes" is not one of the allowed values: [ ... "green" "indigo" "orange" "red" "violet" "yellow" ]

        line:5 column:5 - Validation Error: four value "-4" is not one of the allowed values: [ "1" "2" "3" "4" "5" ]

        line:6 column:5 - Validation Error: five value "7" is not one of the allowed values: [ ... "3" "4" "5" "blue" "green" "indigo" ... ]


### MinValInc Validation Examples        

For a verbal description of the ***Minimum Value Inclusive*** validation rule, please see [MinValInc Validation Details](#minvalinc-validation-details).

 - Schema example:

        test{
        
            controlone{
            }
            controltwo{
            }
            bad_two_numbers{
            }
            bad_string{
            }
            valueone{
                MinValInc=58.7
            }
            valuetwo{
                value{
                    MinValInc=58.7
                }
            }
            valuethree{
                MinValInc=23
            }
            valuefour{
                value{
                    MinValInc=23
                }
            }
            valuefive{
                MinValInc="../controlone"
            }
            valuesix{
                value{
                    MinValInc="../../controlone"
                }
            }
            valueseven{
                MinValInc="../controltwo"
            }
            valueeight{
                value{
                    MinValInc="../../controltwo"
                }
            }
            value_bad_one{
                inside{
                    MinValInc="../../bad_two_numbers"
                }
            }
            value_bad_two{
                inside{
                    MinValInc="../../bad_string"
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
            controlone=15
            controltwo=-45.3
            valueone=58.7
            valuetwo=[ 65 66 67 68 58.7 ]
            valuethree=23
            valuefour=[ 38.3 30.3 23 32.34 ]
            valuefive=15
            valuesix=[ 21 22 23 24 15 ]
            valueseven=-45.3
            valueeight=[ -32.4 31.9 -30.3 -45.3 ]
        }
        

 - Input example that **FAILS** validation on schema above:
        
        test{
            controlone=15
            controltwo=-45.3
            bad_two_numbers=6
            bad_two_numbers=7
            bad_string='some_string'
            valueone=58.6
            valuetwo=[ 65 56 58.6 58 88.7 ]
            valuethree=22.9
            valuefour=[ 28.3 20.3 22.9 12.34 2e2 ]
            valuefive=14
            valuesix=[ 11 12 15 14 15.1 ]
            valueseven=-45.4
            valueeight=[ -45.4 -41.9 -100.3 -45.3 -4E-8 -7e+3 ]
            value_bad_one{
                inside=47
            }
            value_bad_two{
                inside=48
            }
            valueone='a-string'
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:7 column:5 - Validation Error: valueone value "58.6" is less than the allowed minimum inclusive value of 58.7

        line:8 column:19 - Validation Error: valuetwo value "56" is less than the allowed minimum inclusive value of 58.7

        line:8 column:22 - Validation Error: valuetwo value "58.6" is less than the allowed minimum inclusive value of 58.7

        line:8 column:27 - Validation Error: valuetwo value "58" is less than the allowed minimum inclusive value of 58.7

        line:9 column:5 - Validation Error: valuethree value "22.9" is less than the allowed minimum inclusive value of 23

        line:10 column:22 - Validation Error: valuefour value "20.3" is less than the allowed minimum inclusive value of 23

        line:10 column:27 - Validation Error: valuefour value "22.9" is less than the allowed minimum inclusive value of 23

        line:10 column:32 - Validation Error: valuefour value "12.34" is less than the allowed minimum inclusive value of 23

        line:11 column:5 - Validation Error: valuefive value "14" is less than the allowed minimum inclusive value of "15" from "../controlone"

        line:12 column:16 - Validation Error: valuesix value "11" is less than the allowed minimum inclusive value of "15" from "../../controlone"

        line:12 column:19 - Validation Error: valuesix value "12" is less than the allowed minimum inclusive value of "15" from "../../controlone"

        line:12 column:25 - Validation Error: valuesix value "14" is less than the allowed minimum inclusive value of "15" from "../../controlone"

        line:13 column:5 - Validation Error: valueseven value "-45.4" is less than the allowed minimum inclusive value of "-45.3" from "../controltwo"

        line:14 column:18 - Validation Error: valueeight value "-45.4" is less than the allowed minimum inclusive value of "-45.3" from "../../controltwo"

        line:14 column:30 - Validation Error: valueeight value "-100.3" is less than the allowed minimum inclusive value of "-45.3" from "../../controltwo"

        line:14 column:49 - Validation Error: valueeight value "-7e+3" is less than the allowed minimum inclusive value of "-45.3" from "../../controltwo"

        line:16 column:9 - Validation Error: inside minimum inclusive value checks against "../../bad_two_numbers" which returns more than one value

        line:19 column:9 - Validation Error: inside minimum inclusive value checks against "../../bad_string" which does not return a valid number

        line:21 column:5 - Validation Error: valueone value "a-string" is wrong value type for minimum inclusive value


### MaxValInc Validation Examples        

For a verbal description of the ***Maximum Value Inclusive*** validation rule, please see [MaxValInc Validation Details](#maxvalinc-validation-details).

 - Schema example:

        test{
        
            controlone{
            }
            controltwo{
            }
            bad_two_numbers{
            }
            bad_string{
            }
            valueone{
                MaxValInc=58.7
            }
            valuetwo{
                value{
                    MaxValInc=58.7
                }
            }
            valuethree{
                MaxValInc=23
            }
            valuefour{
                value{
                    MaxValInc=23
                }
            }
            valuefive{
                MaxValInc="../controlone"
            }
            valuesix{
                value{
                    MaxValInc="../../controlone"
                }
            }
            valueseven{
                MaxValInc="../controltwo"
            }
            valueeight{
                value{
                    MaxValInc="../../controltwo"
                }
            }
            value_bad_one{
                inside{
                    MaxValInc="../../bad_two_numbers"
                }
            }
            value_bad_two{
                inside{
                    MaxValInc="../../bad_string"
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
            controlone=15
            controltwo=-45.3
            valueone=58.7
            valuetwo=[ 55 56 57 58 58.7 ]
            valuethree=23
            valuefour=[ 18.3 20.3 23 12.34 ]
            valuefive=15
            valuesix=[ 11 12 13 14 15 ]
            valueseven=-45.3
            valueeight=[ -52.4 -51.9 -100.3 -45.3 ]
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
            controlone=15
            controltwo=-45.3
            bad_two_numbers=6
            bad_two_numbers=7
            bad_string='some_string'
            valueone=58.8
            valuetwo=[ 65 56 58.8 58 88.7 ]
            valuethree=23.9
            valuefour=[ 18.3 20.3 23.1 12.34 2e2 ]
            valuefive=19
            valuesix=[ 11 12 18.2 14 15.1 ]
            valueseven=-45.1
            valueeight=[ -52.4 -41.9 -100.3 -45.3 -4E-8 -7e+3 ]
            value_bad_one{
                inside=47
            }
            value_bad_two{
                inside=48
            }
            valueone='a-string'
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:7 column:5 - Validation Error: valueone value "58.8" is greater than the allowed maximum inclusive value of 58.7

        line:8 column:16 - Validation Error: valuetwo value "65" is greater than the allowed maximum inclusive value of 58.7

        line:8 column:22 - Validation Error: valuetwo value "58.8" is greater than the allowed maximum inclusive value of 58.7

        line:8 column:30 - Validation Error: valuetwo value "88.7" is greater than the allowed maximum inclusive value of 58.7

        line:9 column:5 - Validation Error: valuethree value "23.9" is greater than the allowed maximum inclusive value of 23

        line:10 column:27 - Validation Error: valuefour value "23.1" is greater than the allowed maximum inclusive value of 23

        line:10 column:38 - Validation Error: valuefour value "2e2" is greater than the allowed maximum inclusive value of 23

        line:11 column:5 - Validation Error: valuefive value "19" is greater than the allowed maximum inclusive value of "15" from "../controlone"

        line:12 column:22 - Validation Error: valuesix value "18.2" is greater than the allowed maximum inclusive value of "15" from "../../controlone"

        line:12 column:30 - Validation Error: valuesix value "15.1" is greater than the allowed maximum inclusive value of "15" from "../../controlone"

        line:13 column:5 - Validation Error: valueseven value "-45.1" is greater than the allowed maximum inclusive value of "-45.3" from "../controltwo"

        line:14 column:24 - Validation Error: valueeight value "-41.9" is greater than the allowed maximum inclusive value of "-45.3" from "../../controltwo"

        line:14 column:43 - Validation Error: valueeight value "-4E-8" is greater than the allowed maximum inclusive value of "-45.3" from "../../controltwo"

        line:16 column:9 - Validation Error: inside maximum inclusive value checks against "../../bad_two_numbers" which returns more than one value

        line:19 column:9 - Validation Error: inside maximum inclusive value checks against "../../bad_string" which does not return a valid number

        line:21 column:5 - Validation Error: valueone value "a-string" is wrong value type for maximum inclusive value


### MinValExc Validation Examples        

For a verbal description of the ***Minimum Value Exclusive*** validation rule, please see [MinValExc Validation Details](#minvalexc-validation-details).

 - Schema example:

        test{
        
            controlone{
            }
            controltwo{
            }
            bad_two_numbers{
            }
            bad_string{
            }
            valueone{
                MinValExc=58.7
            }
            valuetwo{
                value{
                    MinValExc=58.7
                }
            }
            valuethree{
                MinValExc=23
            }
            valuefour{
                value{
                    MinValExc=23
                }
            }
            valuefive{
                MinValExc="../controlone"
            }
            valuesix{
                value{
                    MinValExc="../../controlone"
                }
            }
            valueseven{
                MinValExc="../controltwo"
            }
            valueeight{
                value{
                    MinValExc="../../controltwo"
                }
            }
            valuenine{
                MinValExc=NoLimit
            }
            value_bad_one{
                inside{
                    MinValExc="../../bad_two_numbers"
                }
            }
            value_bad_two{
                inside{
                    MinValExc="../../bad_string"
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
            controlone=15
            controltwo=-45.3
            valueone=58.8
            valuetwo=[ 65 66 67 68 58.8 ]
            valuethree=23.1
            valuefour=[ 38.3 30.3 23.1 32.34 ]
            valuefive=16
            valuesix=[ 21 22 23 24 16 ]
            valueseven=-45.2
            valueeight=[ -32.4 31.9 -30.3 -45.2 ]
            valuenine=-2000.90
        }
        

 - Input example that **FAILS** validation on schema above:
        
        test{
            controlone=15
            controltwo=-453E-1
            bad_two_numbers=6
            bad_two_numbers=7
            bad_string='some_string'
            valueone=58.7
            valuetwo=[ 65E-1 66 7 68 58.7 ]
            valuethree=23
            valuefour=[ 383E-2 3.3 23 32.34 ]
            valuefive=15
            valuesix=[ -21 22 2.3E-4 24 15 ]
            valueseven=-45.3
            valueeight=[ -132.4 -3.19E5 -30.3 -45.3 ]
            valuenine=-2000.90
            value_bad_one{
                inside=47
            }
            value_bad_two{
                inside=48
            }
            valueone='a-string'
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:7 column:5 - Validation Error: valueone value "58.7" is less than or equal to the allowed minimum exclusive value of 58.7

        line:8 column:16 - Validation Error: valuetwo value "65E-1" is less than or equal to the allowed minimum exclusive value of 58.7

        line:8 column:25 - Validation Error: valuetwo value "7" is less than or equal to the allowed minimum exclusive value of 58.7

        line:8 column:30 - Validation Error: valuetwo value "58.7" is less than or equal to the allowed minimum exclusive value of 58.7

        line:9 column:5 - Validation Error: valuethree value "23" is less than or equal to the allowed minimum exclusive value of 23

        line:10 column:17 - Validation Error: valuefour value "383E-2" is less than or equal to the allowed minimum exclusive value of 23

        line:10 column:24 - Validation Error: valuefour value "3.3" is less than or equal to the allowed minimum exclusive value of 23

        line:10 column:28 - Validation Error: valuefour value "23" is less than or equal to the allowed minimum exclusive value of 23

        line:11 column:5 - Validation Error: valuefive value "15" is less than or equal to the allowed minimum exclusive value of "15" from "../controlone"

        line:12 column:16 - Validation Error: valuesix value "-21" is less than or equal to the allowed minimum exclusive value of "15" from "../../controlone"

        line:12 column:23 - Validation Error: valuesix value "2.3E-4" is less than or equal to the allowed minimum exclusive value of "15" from "../../controlone"

        line:12 column:33 - Validation Error: valuesix value "15" is less than or equal to the allowed minimum exclusive value of "15" from "../../controlone"

        line:13 column:5 - Validation Error: valueseven value "-45.3" is less than or equal to the allowed minimum exclusive value of "-453E-1" from "../controltwo"

        line:14 column:18 - Validation Error: valueeight value "-132.4" is less than or equal to the allowed minimum exclusive value of "-453E-1" from "../../controltwo"

        line:14 column:25 - Validation Error: valueeight value "-3.19E5" is less than or equal to the allowed minimum exclusive value of "-453E-1" from "../../controltwo"

        line:14 column:39 - Validation Error: valueeight value "-45.3" is less than or equal to the allowed minimum exclusive value of "-453E-1" from "../../controltwo"

        line:17 column:9 - Validation Error: inside minimum exclusive value checks against "../../bad_two_numbers" which returns more than one value

        line:20 column:9 - Validation Error: inside minimum exclusive value checks against "../../bad_string" which does not return a valid number

        line:22 column:5 - Validation Error: valueone value "a-string" is wrong value type for minimum exclusive value


### MaxValExc Validation Examples        

For a verbal description of the ***Maximum Value Exclusive*** validation rule, please see [MaxValExc Validation Details](#maxvalexc-validation-details).

 - Schema example:

        test{
        
            controlone{
            }
            controltwo{
            }
            bad_two_numbers{
            }
            bad_string{
            }
            valueone{
                MaxValExc=58.7
            }
            valuetwo{
                value{
                    MaxValExc=58.7
                }
            }
            valuethree{
                MaxValExc=23
            }
            valuefour{
                value{
                    MaxValExc=23
                }
            }
            valuefive{
                MaxValExc="../controlone"
            }
            valuesix{
                value{
                    MaxValExc="../../controlone"
                }
            }
            valueseven{
                MaxValExc="../controltwo"
            }
            valueeight{
                value{
                    MaxValExc="../../controltwo"
                }
            }
            valuenine{
                MaxValExc=NoLimit
            }
            value_bad_one{
                inside{
                    MaxValExc="../../bad_two_numbers"
                }
            }
            value_bad_two{
                inside{
                    MaxValExc="../../bad_string"
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
            controlone=15.1
            controltwo=-452E-1
            valueone=58.6
            valuetwo=[ 55 56 57 58 58.6 ]
            valuethree=22.9
            valuefour=[ 18.3 20.3 22.9 12.34 ]
            valuefive=15
            valuesix=[ 11 12 13 14 15 ]
            valueseven=-45.3
            valueeight=[ -52.4 -51.9 -100.3 -45.3 ]
            valuenine=2000.90
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
            controlone=15
            controltwo=-453e-1
            bad_two_numbers=6
            bad_two_numbers=7
            bad_string='some_string'
            valueone=58.7
            valuetwo=[ 65 59 57 58 58.7 ]
            valuethree=23
            valuefour=[ 18.3 29.3 23 12.34 ]
            valuefive=15
            valuesix=[ 11 12 13 14 15 17.3 ]
            valueseven=-45.3
            valueeight=[ -52.4 -51.9 -10.3 -45.3 ]
            valuenine=2000.90
            value_bad_one{
                inside=47
            }
            value_bad_two{
                inside=48
            }
            valueone='a-string'
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:7 column:5 - Validation Error: valueone value "58.7" is greater than or equal to the allowed maximum exclusive value of 58.7

        line:8 column:16 - Validation Error: valuetwo value "65" is greater than or equal to the allowed maximum exclusive value of 58.7

        line:8 column:19 - Validation Error: valuetwo value "59" is greater than or equal to the allowed maximum exclusive value of 58.7

        line:8 column:28 - Validation Error: valuetwo value "58.7" is greater than or equal to the allowed maximum exclusive value of 58.7

        line:9 column:5 - Validation Error: valuethree value "23" is greater than or equal to the allowed maximum exclusive value of 23

        line:10 column:22 - Validation Error: valuefour value "29.3" is greater than or equal to the allowed maximum exclusive value of 23

        line:10 column:27 - Validation Error: valuefour value "23" is greater than or equal to the allowed maximum exclusive value of 23

        line:11 column:5 - Validation Error: valuefive value "15" is greater than or equal to the allowed maximum exclusive value of "15" from "../controlone"

        line:12 column:28 - Validation Error: valuesix value "15" is greater than or equal to the allowed maximum exclusive value of "15" from "../../controlone"

        line:12 column:31 - Validation Error: valuesix value "17.3" is greater than or equal to the allowed maximum exclusive value of "15" from "../../controlone"

        line:13 column:5 - Validation Error: valueseven value "-45.3" is greater than or equal to the allowed maximum exclusive value of "-453e-1" from "../controltwo"

        line:14 column:30 - Validation Error: valueeight value "-10.3" is greater than or equal to the allowed maximum exclusive value of "-453e-1" from "../../controltwo"

        line:14 column:36 - Validation Error: valueeight value "-45.3" is greater than or equal to the allowed maximum exclusive value of "-453e-1" from "../../controltwo"

        line:17 column:9 - Validation Error: inside maximum exclusive value checks against "../../bad_two_numbers" which returns more than one value

        line:20 column:9 - Validation Error: inside maximum exclusive value checks against "../../bad_string" which does not return a valid number

        line:22 column:5 - Validation Error: valueone value "a-string" is wrong value type for maximum exclusive value


### ExistsIn Validation Examples        

For a verbal description of the ***Exists In*** validation rule, please see [ExistsIn Validation Details](#existsin-validation-details).

 - Schema example:

        test{
        
            defineone{
            }
            definetwo{
            }
            definethree{
            }
            useone{
                value{
                    ExistsIn=[ "../../defineone/value"
                               "../../definetwo/value"
                               "../../definethree/value" ]
                }
            }
            usetwo{
                value{
                    ExistsIn=[ EXTRA:"ford"
                               EXTRA:"chevy"
                               EXTRA:"bmw"
                               EXTRAREF:ReferencedColors
                               EXTRAREF:ReferencedNumbers
                               "../../defineone/value"
                               "../../definetwo/value"
                               "../../definethree/value" ]
                }
            }
            usethree{
                value{
                    ExistsIn(Abs)=[ EXTRAREF:ReferencedNumbers
                                    "../../definetwo/value" ]
                }
            }
            usefour_reg{
                value{
                    ExistsIn=[ EXTRA:"hamburger"
                               EXTRA:"hotdog"
                               EXTRA:800
                               EXTRA:900
                               "../../defineone/value"
                               "../../definethree/value" ]
                }
            }
            usefive_reg{
                value{
                    ExistsIn=[ EXTRAREF:ReferencedColors
                               "../../definetwo/value"
                               "../../definethree/value"
                                EXTRA:0
                                RANGE:[ 1200 1300 ]
                                RANGE:[ 1400 1500 ]
                                RANGE:[ 1600 1700 ]
                                RANGE:[ 1800 1900 ] ]
                }
            }
            usefour_abs{
                value{
                    ExistsIn(Abs)=[ EXTRA:"hamburger"
                               EXTRA:"hotdog"
                               EXTRA:800
                               EXTRA:900
                               "../../defineone/value"
                               "../../definethree/value" ]
                }
            }
            usefive_abs{
                value{
                    ExistsIn(Abs)=[ EXTRAREF:ReferencedColors
                               "../../definetwo/value"
                               "../../definethree/value"
                                EXTRA:0
                                RANGE:[ 1200 1300 ]
                                RANGE:[ 1400 1500 ]
                                RANGE:[ 1600 1700 ]
                                RANGE:[ 1800 1900 ] ]
                }
            }
            usesix{
                value{
                    ExistsIn(BadFlag)=[ "../../defineone/value" ]
                }
            }
            useseven{
                value{
                    ExistsIn=[ "../../defineone/value"
                               RANGE:[ 25 fifty ] ]
                }
            }
            useeight{
                value{
                    ExistsIn=[ "../../defineone/value"
                               RANGE:[ 50 25 ] ]
                }
            }
            usenine{
                value{
                    ExistsIn=[ "../../defineone/value"
                               RANGE:[ 25 50 100 ] ]
                }
            }
            useten{
                value{
                    ExistsIn=[ EXTRAREF:BadReference
                               "../../defineone/value" ]
                }
            }
            useeleven{
                value{
                    ExistsIn=[ "../../../../defineone/value" ]
                }
            }
        
        }
        EndOfSchema{}
        ReferencedColors=[ red orange yellow green blue indigo violet ]
        ReferencedNumbers=[ 1 2 3 4 5 ]

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            defineone=one
            defineone=two
            defineone=three
            defineone=four
        
            definetwo=[ england spain germany italy canada ]
            definetwo=-200
            definetwo=300
            definetwo=[ 500 -600 ]
        
            definethree=science
            definethree=math
            definethree=[ geography economics recess lunch ]
        
            useone=two
            useone=germany
            useone=[ three recess lunch italy canada ]
        
            usetwo=[ ford bmw red 1 4 math ]
            usetwo=3
            usetwo=blue
        
            usethree=england
            usethree=italy
            usethree=[ 5 "3" -2 canada "1" ]
            usethree=-4
        
            usefour_abs=geography
            usefour_abs=[ hamburger 900 math hotdog "four" ]
            usefour_abs=three
            usefour_abs=[ 800 -800 ]
            usefour_abs=-900
        
            usefive_abs=orange
            usefive_abs=economics
            usefive_abs=[ "indigo" violet "geography" ]
            usefive_abs=science
            usefive_abs=[ 600 -600 300 -300 1200 1300 ]
            usefive_abs=200
            usefive_abs=[ -500 500 -200 -1850 ]
            usefive_abs=-1675
        
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            defineone=one
            defineone=two
            defineone=three
            defineone=four
        
            definetwo=[ england spain germany italy canada ]
            definetwo=-200
            definetwo=300
            definetwo=[ 500 -600 ]
        
            definethree=science
            definethree=math
            definethree=[ geography economics recess lunch ]
        
            useone=seven
            useone=japan
            useone=[ three spelling yellow italy canada 2 ]
        
            usetwo=[ ford honda red -1 4 math ]
            usetwo=-3
            usetwo=purple
        
            usethree=red
            usethree=three
            usethree=[ 5 "3" -2.3 blue "1" ]
            usethree=lunch
        
            usefour_reg=geography
            usefour_reg=[ hamburger 900 spain hotdog fries ]
            usefour_reg=orange
            usefour_reg=[ 800 -800 ]
            usefour_reg=-900
        
            usefive_reg=orange
            usefive_reg=economics
            usefive_reg=[ "indigo" violet "geography" ]
            usefive_reg=science
            usefive_reg=[ 600 2 300 five ]
            usefive_reg=200
            usefive_reg=[ -500 -3 -200 ]
        
            usesix=one
            useseven=two
            useeight=three
            usenine=four
            useten=one
            useeleven=two
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: "50" start of range is greater than or equal to "25" end of range at line:92 column:32

        Validation Error: Invalid Schema Rule: Bad ExistsIn Option "BadFlag" at line:80 column:22 - Expected [ Abs ]

        Validation Error: Invalid Schema Rule: Bad ExistsIn Path "../../../../defineone/value" at line:109 column:24

        Validation Error: Invalid Schema Rule: Enum Reference "BadReference" at line:103 column:24 not found in schema

        Validation Error: Invalid Schema Rule: Range does not have exactly two values at line:98 column:24

        Validation Error: Invalid Schema Rule: fifty range value not a valid number at line:86 column:35

        line:17 column:12 - Validation Error: useone value "seven" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:18 column:12 - Validation Error: useone value "japan" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:19 column:20 - Validation Error: useone value "spelling" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:19 column:29 - Validation Error: useone value "yellow" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:19 column:49 - Validation Error: useone value "2" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:21 column:19 - Validation Error: usetwo value "honda" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:21 column:29 - Validation Error: usetwo value "-1" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:22 column:12 - Validation Error: usetwo value "-3" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:23 column:12 - Validation Error: usetwo value "purple" does not exist in set: [ ../../defineone/value ../../definetwo/value ../../definethree/value ]

        line:25 column:14 - Validation Error: usethree value "red" does not exist in set: [ ../../definetwo/value ]

        line:26 column:14 - Validation Error: usethree value "three" does not exist in set: [ ../../definetwo/value ]

        line:27 column:22 - Validation Error: usethree value "2.3" does not exist in set: [ ../../definetwo/value ]

        line:27 column:27 - Validation Error: usethree value "blue" does not exist in set: [ ../../definetwo/value ]

        line:28 column:14 - Validation Error: usethree value "lunch" does not exist in set: [ ../../definetwo/value ]

        line:31 column:33 - Validation Error: usefour_reg value "spain" does not exist in set: [ ../../defineone/value ../../definethree/value ]

        line:31 column:46 - Validation Error: usefour_reg value "fries" does not exist in set: [ ../../defineone/value ../../definethree/value ]

        line:32 column:17 - Validation Error: usefour_reg value "orange" does not exist in set: [ ../../defineone/value ../../definethree/value ]

        line:33 column:23 - Validation Error: usefour_reg value "-800" does not exist in set: [ ../../defineone/value ../../definethree/value ]

        line:34 column:17 - Validation Error: usefour_reg value "-900" does not exist in set: [ ../../defineone/value ../../definethree/value ]

        line:40 column:19 - Validation Error: usefive_reg value "600" does not exist in set: [ ../../definetwo/value ./../definethree/value ]

        line:40 column:23 - Validation Error: usefive_reg value "2" does not exist in set: [ ../../definetwo/value ./../definethree/value ]

        line:40 column:29 - Validation Error: usefive_reg value "five" does not exist in set: [ ../../definetwo/value ../../definethree/value ]

        line:41 column:17 - Validation Error: usefive_reg value "200" does not exist in set: [ ../../definetwo/value ../../definethree/value ]

        line:42 column:19 - Validation Error: usefive_reg value "-500" does not exist in set: [ ../../definetwo/value ../../definethree/value ]

        line:42 column:24 - Validation Error: usefive_reg value "-3" does not exist in set: [ ../../definetwo/value ../../definethree/value ]


### NotExistsIn Validation Examples        

For a verbal description of the ***Not Exists In*** validation rule, please see [NotExistsIn Validation Details](#notexistsin-validation-details).

 - Schema example:

        test{
        
            defineone{
            }
            definetwo{
            }
            definethree{
            }
            useone{
                value{
                    NotExistsIn=[ "../../defineone/value"
                                  "../../definetwo/value"
                                  "../../definethree/value" ]
                }
            }
            usetwo{
                value{
                    NotExistsIn(Abs)=[ "../../defineone/value"
                                       "../../definetwo/value" ]
                }
            }
            usethree{
                value{
                    NotExistsIn=[ "../../defineone/value"
                                  "../../definethree/value" ]
                }
            }
            usefour{
                value{
                    NotExistsIn=[ "../../definetwo/value"
                                  "../../definethree/value" ]
                }
            }
            usefive{
                value{
                    NotExistsIn=[ "../../definethree/value" ]
                }
            }
            usesix{
                value{
                    NotExistsIn(BadFlag)=[ "../../defineone/value" ]
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            defineone=one
            defineone=two
            defineone=three
            defineone=four
            defineone=0
        
            definetwo=[ england spain germany italy canada ]
            definetwo=-200
            definetwo=300
            definetwo=[ 500 0 -600 ]
        
            definethree=science
            definethree=math
            definethree=[ geography economics 0 recess lunch ]
        
            useone=200
            useone=japan
            useone=[ -500 600 seven -300 art ]
        
            usetwo=[ science "recess" ]
            usetwo="lunch"
            usetwo=economics
            usetwo=[ "math" geography ]
        
            usethree=canada
            usethree=england
            usethree=[ -200 "italy" 300 ]
            usethree="-600"
        
            usefour="one"
            usefour=[ "two" one ]
            usefour="four"
            usefour=[ "four" three ]
            usefour="three"
       
            usefive=[ 300 -600 ]
            usefive="one"
            usefive=[ three italy "england" ]
        
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            defineone=one
            defineone=two
            defineone=three
            defineone=four
        
            definetwo=[ england spain germany italy canada ]
            definetwo=-200
            definetwo=300
            definetwo=[ 500 0 -600 ]
        
            definethree=science
            definethree=math
            definethree=[ geography economics 0 recess lunch ]
        
            useone=two
            useone=germany
            useone=[ three recess lunch italy canada ]
        
            usetwo=[ two germany -600 ]
            usetwo="four"
            usetwo="600"
            usetwo=[ -200 200 one ]
        
            usethree=four
            usethree=lunch
            usethree=[ two "three" ]
            usethree="science"
        
            usefour=300
            usefour=[ -600 economics ]
            usefour=recess
            usefour=[ lunch -200 ]
            usefour=math
        
            usefive=[ recess "math" ]
            usefive="science"
            usefive=[ math economics "geography" ]
        
            usesix=one
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: Bad NotExistsIn Option "BadFlag" at line:41 column:25 - Expected [ Abs ]
        
        line:17 column:12 - Validation Error: useone value "two" also exists at "../../defineone/value" on line:4 column:15
        
        line:18 column:12 - Validation Error: useone value "germany" also exists at "../../definetwo/value" on line:8 column:31
        
        line:19 column:14 - Validation Error: useone value "three" also exists at "../../defineone/value" on line:5 column:15
        
        line:19 column:20 - Validation Error: useone value "recess" also exists at "../../definethree/value" on line:15 column:41
        
        line:19 column:27 - Validation Error: useone value "lunch" also exists at "../../definethree/value" on line:15 column:48
        
        line:19 column:33 - Validation Error: useone value "italy" also exists at "../../definetwo/value" on line:8 column:39
        
        line:19 column:39 - Validation Error: useone value "canada" also exists at "../../definetwo/value" on line:8 column:45
        
        line:21 column:14 - Validation Error: usetwo value "two" also exists at "../../defineone/value" on line:4 column:15
        
        line:21 column:18 - Validation Error: usetwo value "germany" also exists at "../../definetwo/value" on line:8 column:31
        
        line:21 column:26 - Validation Error: usetwo value "600" also exists at "../../definetwo/value" on line:11 column:23
        
        line:22 column:12 - Validation Error: usetwo value "four" also exists at "../../defineone/value" on line:6 column:15
        
        line:23 column:12 - Validation Error: usetwo value "600" also exists at "../../definetwo/value" on line:11 column:23
        
        line:24 column:14 - Validation Error: usetwo value "200" also exists at "../../definetwo/value" on line:9 column:15
        
        line:24 column:19 - Validation Error: usetwo value "200" also exists at "../../definetwo/value" on line:9 column:15
        
        line:24 column:23 - Validation Error: usetwo value "one" also exists at "../../defineone/value" on line:3 column:15
        
        line:26 column:14 - Validation Error: usethree value "four" also exists at "../../defineone/value" on line:6 column:15
        
        line:27 column:14 - Validation Error: usethree value "lunch" also exists at "../../definethree/value" on line:15 column:48
        
        line:28 column:16 - Validation Error: usethree value "two" also exists at "../../defineone/value" on line:4 column:15
        
        line:28 column:20 - Validation Error: usethree value "three" also exists at "../../defineone/value" on line:5 column:15
        
        line:29 column:14 - Validation Error: usethree value "science" also exists at "../../definethree/value" on line:13 column:17
        
        line:31 column:13 - Validation Error: usefour value "300" also exists at "../../definetwo/value" on line:10 column:15
        
        line:32 column:15 - Validation Error: usefour value "-600" also exists at "../../definetwo/value" on line:11 column:23
        
        line:32 column:20 - Validation Error: usefour value "economics" also exists at "../../definethree/value" on line:15 column:29
        
        line:33 column:13 - Validation Error: usefour value "recess" also exists at "../../definethree/value" on line:15 column:41
        
        line:34 column:15 - Validation Error: usefour value "lunch" also exists at "../../definethree/value" on line:15 column:48
        
        line:34 column:21 - Validation Error: usefour value "-200" also exists at "../../definetwo/value" on line:9 column:15
        
        line:35 column:13 - Validation Error: usefour value "math" also exists at "../../definethree/value" on line:14 column:17
        
        line:37 column:15 - Validation Error: usefive value "recess" also exists at "../../definethree/value" on line:15 column:41
        
        line:37 column:22 - Validation Error: usefive value "math" also exists at "../../definethree/value" on line:14 column:17
        
        line:38 column:13 - Validation Error: usefive value "science" also exists at "../../definethree/value" on line:13 column:17
        
        line:39 column:15 - Validation Error: usefive value "math" also exists at "../../definethree/value" on line:14 column:17
        
        line:39 column:20 - Validation Error: usefive value "economics" also exists at "../../definethree/value" on line:15 column:29
        
        line:39 column:30 - Validation Error: usefive value "geography" also exists at "../../definethree/value" on line:15 column:19


### SumOver Validation Examples        

For a verbal description of the ***Sum Over*** validation rule, please see [SumOver Validation Details](#sumover-validation-details).

 - Schema example:

        test{
        
            container{
                inside{
                    SumOver("../..")=107.6
                }
            }
            array{
                value{
                    SumOver("..")=209.4
                }
            }
            invalid_array{
                value{
                    SumOver("..")=123.4
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            container{
                inside=59.4
            }
            container{
                inside=24.9
            }
            container{
                inside=23.3
            }
            array=[ 4.5 87.3 83.2 34.4 ]
        
        }
        

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            container{
                inside=59.4
            }
            container{
                inside=28.9
            }
            container{
                inside=23.3
            }
            array=[ 4.5 87.3 83.5 34.4 ]
            invalid_array= [ 1.2 4.5 something 8.8 ]
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:1 column:1 - Validation Error: test children "inside" sum to 111.6 - instead of the required sum of 107.6

        line:12 column:5 - Validation Error: array children "value" sum to 209.7 - instead of the required sum of 209.4

        line:13 column:30 - Validation Error: invalid_array value "something" is wrong value type for sum over


### SumOverGroup Validation Examples        

For a verbal description of the ***Sum Over Group*** validation rule, please see [SumOverGroup Validation Details](#sumovergroup-validation-details).

 - Schema example:

        test{
            inside{
                id{
                }
                container{
                    id{
                    }
                    inside{
                        SumOverGroup("../..")=[ ComparePath="../id"
                                                GroupDivide=1000
                                                GroupSum=107.6 ]
                    }
                    badoptions{
                        badruleone{
                            SumOverGroup("../..")=[ 
                                                    GroupDivide=1000
                                                    GroupSum=107.6 ]
                        }
                        badruletwo{
                            SumOverGroup("../..")=[ ComparePath="../id"
        
                                                    GroupSum=107.6 ]
                        }
                        badrulethree{
                            SumOverGroup("../..")=[ ComparePath="../id"
                                                    GroupDivide=1000
                                                   ]
                        }
                    }
                }
                array{
                    value{
                        SumOverGroup("../../..")=[ ComparePath="../../id"
                                                   GroupDivide=10
                                                   GroupSum=418.8 ]
                    }
                }
                invalid_array{
                    value{
                        SumOverGroup("../../..")=[ ComparePath="../../id"
                                                   GroupDivide=100
                                                   GroupSum=123.4 ]
                    }
                }
            }
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            inside{
        
                id=121
        
                container{
                    id=72123
                    inside=59.4
                }
                container{
                    id=72456
                    inside=24.9
                }
                container{
                    id=72789
                    inside=23.3
                }
                container{
                    id=82123
                    inside=59.6
                }
                container{
                    id=82456
                    inside=44.7
                }
                container{
                    id=82789
                    inside=3.3
                }
                container{
                    id=92123
                    inside=0.4
                }
                container{
                    id=92456
                    inside=107.1
                }
                container{
                    id=92789
                    inside=0.1
                }
        
                array=[ 4.5 87.3 83.2 54.4 ]
        
            }
        
            inside{
                id=124
                array=[ 4.5 67.3 83.2 34.4 ]
            }
        
            inside{
                id=1324
                array=[ 4.5 87.3 83.2 14.4 ]
            }
        
            inside{
                id=1322
                array=[ 24.5 87.3 83.2 34.4 ]
            }
        
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            inside{
        
                id=121
        
                container{
                    id=72123
                    inside=59.4
                }
                container{
                    id=72456
                    inside=14.9
                }
                container{
                    id=72789
                    inside=23.3
                }
                container{
                    id=82123
                    inside=59.6
                }
                container{
                    id=82456
                    inside=54.7
                }
                container{
                    id=82789
                    inside=83.3
                }
                container{
                    id=92123
                    inside=9.4
                }
                container{
                    id=92456
                    inside=107.1
                }
                container{
                    id=92789
                    inside=0.8
                    badoptions{
                    }
                }
        
                array=[ 4.9 87.3 3.2 54.4 ]
        
            }
        
            inside{
                id=124
                array=[ 4.5 67.3 83.2 134.4 ]
            }
        
            inside{
                id=1324
                array=[ 4.5 97.3 83.2 14.1 ]
            }
        
            inside{
                id=1322
                array=[ 24.5 87.3 83.2 14.4 ]
                invalid_array= [ 1.2 4.5 something 8.8 ]
            }
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: SumOverGroup missing ComparePath at line:15 column:21

        Validation Error: Invalid Schema Rule: SumOverGroup missing GroupDivide at line:20 column:21

        Validation Error: Invalid Schema Rule: SumOverGroup missing GroupSum at line:25 column:21

        line:1 column:1 - Validation Error: test children "value" sum to 408.5 for 1320 group - instead of the required sum of 418.8

        line:1 column:1 - Validation Error: test children "value" sum to 439.2 for 120 group - instead of the required sum of 418.8

        line:3 column:5 - Validation Error: inside children "inside" sum to 97.6 for 72000 group - instead of the required sum of 107.6

        line:3 column:5 - Validation Error: inside children "inside" sum to 117.3 for 92000 group - instead of the required sum of 107.6

        line:3 column:5 - Validation Error: inside children "inside" sum to 197.6 for 82000 group - instead of the required sum of 107.6

        line:63 column:34 - Validation Error: invalid_array value "something" is wrong value type for sum over group


### IncreaseOver Validation Examples        

For a verbal description of the ***Increase Over*** validation rule, please see [IncreaseOver Validation Details](#increaseover-validation-details).

 - Schema example:

        test{
        
            container{
                inside{
                    IncreaseOver("../..")=Strict
                }
                badrule{
                    inside{
                        IncreaseOver("../..")=Neither
                    }
                }
            }
            array{
                value{
                    IncreaseOver("..")=Mono
                }
            }
            another_array{
                value{
                    IncreaseOver("..")=Strict
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            container{
                inside=19.4
            }
            container{
                inside=24.9
            }
            container{
                inside=93.3
            }
            container{
                inside=193.3
            }
            array=[ 4.5 87.3 87.3 87.3 98.2 100.2 100.2 163.2 ]
        
        }
        

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            container{
                inside=19.4
            }
            container{
                inside=24.9
            }
            container{
                inside=24.9
            }
            container{
                inside=93.3
                badrule{
                }
            }
            array=[ 4.5 87.3 87.3 87.3 48.2 100.2 100.2 63.2 ]
            array=[ 4.5 87.3 87.3 something 48.2 100.2 100.2 63.2 ]
            another_array=[ 4.5 87.3 something 87.3 48.2 100.2 100.2 63.2 ]
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: Bad IncreaseOver Option "Neither" at line:9 column:39 - Expected [ Mono Strict ]

        line:1 column:1 - Validation Error: test children "inside" are not strictly increasing at line:10 column:9

        line:17 column:5 - Validation Error: array children "value" are not monotonically increasing at line:17 column:32

        line:17 column:5 - Validation Error: array children "value" are not monotonically increasing at line:17 column:49

        line:18 column:27 - Validation Error: array value "something" is wrong value type for increasing

        line:19 column:30 - Validation Error: another_array value "something" is wrong value type for increasing


### DecreaseOver Validation Examples        

For a verbal description of the ***Decrease Over*** validation rule, please see [DecreaseOver Validation Details](#decreaseover-validation-details).

 - Schema example:

        test{
        
            container{
                inside{
                    DecreaseOver("../..")=Strict
                }
                badrule{
                    inside{
                        DecreaseOver("../..")=Neither
                    }
                }
            }
            array{
                value{
                    DecreaseOver("..")=Mono
                }
            }
            another_array{
                value{
                    DecreaseOver("..")=Strict
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            container{
                inside=193.3
            }
            container{
                inside=93.3
            }
            container{
                inside=24.9
            }
            container{
                inside=19.4
            }
            array=[ 163.2 100.2 100.2 98.2 87.3 87.3 87.3 4.5 ]
        
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            container{
                inside=93.3
            }
            container{
                inside=24.9
            }
            container{
                inside=24.9
            }
            container{
                inside=19.4
                badrule{
                }
            }
            array=[ 63.2 100.2 100.2 48.2 87.3 87.3 87.3 4.5 ]
            array=[ 163.2 100.2 100.2 something 87.3 87.3 87.3 4.5 ]
            another_array=[ 163.2 100.2 something 100.2 87.3 87.3 87.3 4.5 ]
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: Bad DecreaseOver Option "Neither" at line:9 column:39 - Expected [ Mono Strict ]

        line:1 column:1 - Validation Error: test children "inside" are not strictly decreasing at line:10 column:9

        line:17 column:5 - Validation Error: array children "value" are not monotonically decreasing at line:17 column:18

        line:17 column:5 - Validation Error: array children "value" are not monotonically decreasing at line:17 column:35

        line:18 column:31 - Validation Error: array value "something" is wrong value type for decreasing

        line:19 column:33 - Validation Error: another_array value "something" is wrong value type for decreasing


### ChildAtMostOne Validation Examples        

For a verbal description of the ***Child At Most One*** validation rule, please see [ChildAtMostOne Validation Details](#childatmostone-validation-details).

 - Schema example:

        test{
        
            ChildAtMostOne = [ one two three ]
        
            one{
            }
            two{
            }
            three{
            }
            four{
            }
            five{
                ChildAtMostOne=[ "../four" "../two" ]
            }
            six{
            }
            seven{
                ChildAtMostOne=[ "../six" ]
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
            one=1
            four=4
            six=6
        }
        test{
            four=4
        }
        test{
            two=3
        }
        test{
            five=5
        }
        test{
            seven=7
        }
        test{
            three=[ 2 3 4 ]
            four=5
            five=6
        }
        test{
            two=[ 2 3 4 ]
            five=6
        }
        test{
            five=6
            four=5
        }
        test{
            one=[ 2 3 4 ]
            seven=5
        }
        test{
            one=[ 2 3 4 ]
            six=6
            seven=5
        }
        test{
            one=[ 2 3 4 ]
            five=5
        }
        test{
            two=2
            six=[ 8 9 10 ]
            seven=[ 11 12 ]
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
            one=1
            three=2
        }
        test{
            one=1
            two=[ 6 7 8 9 ]
            three=3
        }
        test{
            two=[ 1 2 3 4 ]
            three=5
        }
        test{
            four=[ 6 7 8 9 ]
            two=5
            five=4
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:1 column:1 - Validation Error: test has more than one of: [ one two three ] - at most one must occur

        line:5 column:1 - Validation Error: test has more than one of: [ one two three ] - at most one must occur

        line:10 column:1 - Validation Error: test has more than one of: [ one two three ] - at most one must occur

        line:17 column:5 - Validation Error: five has more than one of: [ "../four" "../two" ] - at most one must occur


### ChildExactlyOne Validation Examples        

For a verbal description of the ***Child Exactly One*** validation rule, please see [ChildExactlyOne Validation Details](#childexactlyone-validation-details).

 - Schema example:

        test{
        
            ChildExactlyOne = [ one two three ]
        
            one{
            }
            two{
            }
            three{
            }
            four{
            }
            five{
                ChildExactlyOne=[ "../four" "../two" ]
            }
            six{
            }
            seven{
                ChildExactlyOne=[ "../six" ]
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
            one=1
            four=4
            six=6
        }
        test{
            three=[ 2 3 4 ]
            four=5
            five=6
        }
        test{
            two=[ 2 3 4 ]
            five=6
        }
        test{
            one=[ 7 8 9 ]
            four=2
            five=6
        }
        test{
            two=2
            six=[ 8 9 10 ]
            seven=[ 11 12 ]
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
            four=5
            five=6
        }
        test{
            one=1
            three=2
        }
        test{
            one=1
            two=[ 6 7 8 9 ]
            three=3
        }
        test{
            one=[ 6 7 8 9 ]
            five=9
        }
        test{
            two=[ 6 7 8 9 ]
            five=9
            four=7
        }
        test{
            three=[ 6 7 8 9 ]
            seven=9
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:1 column:1 - Validation Error: test has zero of: [ one two three ] - exactly one must occur

        line:5 column:1 - Validation Error: test has more than one of: [ one two three ] - exactly one must occur

        line:9 column:1 - Validation Error: test has more than one of: [ one two three ] - exactly one must occur

        line:16 column:5 - Validation Error: five has zero of: [ "../four" "../two" ] - exactly one must occur

        line:20 column:5 - Validation Error: five has more than one of: [ "../four" "../two" ] - exactly one must occur

        line:25 column:5 - Validation Error: seven has zero of: [ "../six" ] - exactly one must occur


### ChildAtLeastOne Validation Examples        

For a verbal description of the ***Child At Least One*** validation rule, please see [ChildAtLeastOne Validation Details](#childatleastone-validation-details).

 - Schema example:

        test{
        
            ChildAtLeastOne = [ one 'two/value' 'three/value' ]
        
            one{
            }
            two{
                value{
                }
            }
            three{
                value{
                }
            }
            four{
            }
            five{
                ChildAtLeastOne=[ "../four" "../two/value" ]
            }
            six{
                value{
                }
            }
            seven{
                ChildAtLeastOne=[ "../six/value" ]
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
            one=1
            four=4
            six=6
        }
        test{
            three=[ 2 3 4 ]
            four=5
            five=6
        }
        test{
            two=[ 2 3 4 ]
            four=5
            five=6
        }
        test{
            two=2
            five=6
        }
        test{
            two=2
            three=[ 5 6 7 ]
            six=[ 8 9 10 ]
            seven=[ 11 12 ]
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
            four=5
            five=6
        }
        test{
            three=2
            five=5
        }
        test{
            one=1
            three=[ 5 6 7 ]
            seven=[ 11 12 ]
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        line:1 column:1 - Validation Error: test has zero of: [ one 'two/value' 'three/value' ] - at least one must occur

        line:7 column:5 - Validation Error: five has zero of: [ "../four" "../two/value" ] - at least one must occur

        line:12 column:5 - Validation Error: seven has zero of: [ "../six/value" ] - at least one must occur


### ChildCountEqual Validation Examples        

For a verbal description of the ***Child Count Equal*** validation rule, please see [ChildCountEqual Validation Details](#childcountequal-validation-details).

 - Schema example:

        test{
        
            ChildCountEqual(IfExists) = [ one/value   two/value  three/value ]
            ChildCountEqual(EvenNone) = [ four/value  five/value six/value   ]
        
            badflags{
                inside{
                    ChildCountEqual           = [ three/value six/value ]
                    ChildCountEqual(BadFlag)  = [ one/value   four/value ]
                }
            }
        
            one{
                value{
                }
            }
            two{
                value{
                }
            }
            three{
                value{
                }
            }
            four{
                value{
                }
            }
            five{
                value{
                }
            }
            six{
                value{
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            one=[ a b c ]
            one=d
            one=[ e f ]
        
            three=[ "!" "@" "#" ]
            three="$"
            three=[ "%" "^" ]
        
            four=[ red orange yellow ]
            four=green
            four=[ blue indigo ]
        
            five=[ canada poland england ]
            five=mexico
            five=[ italy france ]
        
            six=[ algebra chemistry history ]
            six=calculus
            six=[ physics geometry ]
        
        }

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            one=[ a b c ]
            one=d
            one=[ e f ]
        
            two=[ 1 2 3 ]
            two=4
            two=[ 5 6 7 ]
        
            three=[ "!" "@" "#" ]
            three="$"
            three=[ "%" "^" ]
        
            four=[ red orange yellow ]
            four=green
            four=[ blue indigo ]
        
            six=[ algebra chemistry history ]
            six=calculus
            six=[ physics geometry ]
        
            badflags{
            }
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: Bad ChildCountEqual Option "" at line:8 column:43 - Expected [ IfExists EvenNone ]

        Validation Error: Invalid Schema Rule: Bad ChildCountEqual Option "BadFlag" at line:9 column:43 - Expected [ IfExists EvenNone ]

        line:1 column:1 - Validation Error: test does not have an equal number of existing: [ one/value two/value three/value ]

        line:1 column:1 - Validation Error: test does not have an equal number of: [ four/value five/value six/value ]


### ChildUniqueness Validation Examples        

For a verbal description of the ***Child Uniqueness*** validation rule, please see [ChildUniqueness Validation Details](#childuniqueness-validation-details).

 - Schema example:

        test{
        
            ChildUniqueness          = [ one/value                       ]
            ChildUniqueness          = [ one/value two/value             ]
            ChildUniqueness(Abs)     = [           two/value three/value ]
            badflags{
                inside{
                    ChildUniqueness(BadFlag) = [ four/value              ]
                }
            }
        
            one{
                value{
                }
            }
            two{
                value{
                }
            }
            three{
                value{
                }
            }
            four{
                value{
                }
            }
        
        }

 - Input example that **PASSES** validation on schema above:

        
        test{
        
            one=[ 12 a b 11 c 0 -4 ]
            one=d
            one=e
            one=[ f -12 g h ]
        
            two=[ 1 2 3 -11 ]
            two=4
            two=5
            two=[ 6 7 8 ]
        
            three=[ "!" "@" "#" ]
            three="$"
            three="%"
            three=[ "^" "&" 0 "*" ]
        
        }
        

 - Input example that **FAILS** validation on schema above:
        
        test{
        
            one=[ a b c ]
            one=d
            one="%"
            one=[ 8 b h ]
        
            two=[ 1 b 3 0 ]
            two="%"
            two="*"
            two=[ 6 7 8 -3 ]
        
            three=[ 8 "@" c ]
            three="$"
            three="%"
            three=[ "^" b 0 -7 "*" ]
        
            badflags{
            }
        
        }

 - HIVE validation messages when validating the failing input shown above against the schema above:

        Validation Error: Invalid Schema Rule: Bad ChildUniqueness Option "BadFlag" at line:8 column:29 - Expected [ Abs ]
        
        line:3 column:13 - Validation Error: one/value value "b" also exists at "one/value" on line:6 column:13
        
        line:3 column:13 - Validation Error: one/value value "b" also exists at "one/value" on line:6 column:13
        
        line:5 column:9 - Validation Error: one/value value "%" also exists at "two/value" on line:9 column:9
        
        line:6 column:11 - Validation Error: one/value value "8" also exists at "two/value" on line:11 column:15
        
        line:6 column:13 - Validation Error: one/value value "b" also exists at "one/value" on line:3 column:13
        
        line:6 column:13 - Validation Error: one/value value "b" also exists at "one/value" on line:3 column:13
        
        line:8 column:13 - Validation Error: two/value value "b" also exists at "one/value" on line:3 column:13
        
        line:8 column:13 - Validation Error: two/value value "b" also exists at "three/value" on line:16 column:17
        
        line:8 column:15 - Validation Error: two/value value "3" also exists at "two/value" on line:11 column:17
        
        line:8 column:17 - Validation Error: two/value value "0" also exists at "three/value" on line:16 column:19
        
        line:9 column:9 - Validation Error: two/value value "%" also exists at "one/value" on line:5 column:9
        
        line:9 column:9 - Validation Error: two/value value "%" also exists at "three/value" on line:15 column:11
        
        line:10 column:9 - Validation Error: two/value value "*" also exists at "three/value" on line:16 column:24
        
        line:11 column:13 - Validation Error: two/value value "7" also exists at "three/value" on line:16 column:21
        
        line:11 column:15 - Validation Error: two/value value "8" also exists at "one/value" on line:6 column:11
        
        line:11 column:15 - Validation Error: two/value value "8" also exists at "three/value" on line:13 column:13
        
        line:11 column:17 - Validation Error: two/value value "3" also exists at "two/value" on line:8 column:15
        
        line:13 column:13 - Validation Error: three/value value "8" also exists at "two/value" on line:11 column:15
        
        line:15 column:11 - Validation Error: three/value value "%" also exists at "two/value" on line:9 column:9
        
        line:16 column:17 - Validation Error: three/value value "b" also exists at "two/value" on line:8 column:13
        
        line:16 column:19 - Validation Error: three/value value "0" also exists at "two/value" on line:8 column:17
        
        line:16 column:21 - Validation Error: three/value value "7" also exists at "two/value" on line:11 column:13
        
        line:16 column:24 - Validation Error: three/value value "*" also exists at "two/value" on line:10 column:9

---
