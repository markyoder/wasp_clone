# Heirarchical Input Validation Engine (HIVE) 
HIVE uses a set of restrictions or rules to describe the definition or schema of an application input. 
These rules describe scalar and relational restrictions. These rules can user [_SIREN_](/waspsiren/README.md)
to define restrictions related to sets of elements. E.g., an identifier reference but refer to an existing
element's identifier.

The input definition can be used by other applications (user interfaces) to facilitate interactive validation,
creation, and navigation.


## Restriction Descriptions


* MinOccurs - describes the minimum occurrences that an input element is allowed to occur under its parent context
* MaxOccurs - describes the maximum occurrences that an input element can occur under its parent context
* ValType - describes the allowed value type for the element (Int, Real, etc.)
* ValEnums - describes a list of allowed values for the element 
* MinValInc - describes the minimum inclusive value that this element is allowed to have if it is a number (float or integer)
* MaxValInc 
* MinValExc 
* MaxValExc 
* ExistsIn 
* NotExistsIn 
* SumOver 
* SumOverGroup 
* IncreaseOver 
* DecreaseOver 
* ChildAtMostOne 
* ChildExactlyOne 
* ChildAtLeastOne 
* ChildCountEqual 
* ChildUniqueness 
 


1. __MinOccurs__ It is used mostly to denote if a piece of input is required or not.
Most often, this rule will have a literal constant for minimum allowances.  The value 
must be an integer. For example, `MinOccurs=0` denotes that this element is optional 
under its parent context, and `MinOccurs=1` denotes that this element is required to
occur at least once under its parent. Rarely, this rule may have a lookup path that 
contains a relative path from the current element into the parse tree.  If the lookup
path describes a set containing a single value, and if that value is an integer, then
that value will be used to determine the minimum allowed occurrences of the element being validated.
TODO - give example situations
 

2. __MaxOccurs__ Most often, this element will have a literal constant value to describe
a  number of maximum allowances.  The value  must be integer or '+INF' (indicating that
there is no upper limit on the number of time this element can occur). This rule may have
a  lookup path that contains a relative path from the current element into the parse tree.
If the lookup path describes a set containing a single value, and if that value is an integer,
then that value will be used to determine the maximum allowed occurrences of the element being
validated.

 

3. __ValType__  Checks the type of the element. This can be one of the following: 
	* _Int_ - meaning a negative or positive integer
	* _Real_- meaning a negative or positive floating point value (or integer)
	* _String_ meaning a literal string of text
	* _RealOrQuestion_ meaning a negative or positive floating point value or the literal "?"
	* _IntOrYesOrNo_ meaning a negative or positive integer or the literals "yes" or "no" (case insensitive)
	* _IntOrAsterisk_ meaning a negative or positive integer or the literal "*"
TODO - give example situations 

4. __ValEnums__ Compares the element's value with once of the provided. If the element's
value is anything other than the listed allowed enumerations, then this check will fail.  
Note : This check is case insensitive and if the value being checked is an integer, 
then leading zeros are ignored.
TODO - give example situation

5. __MinValInc__ Most often, this restriction will have a constant defines the minimum 
value that this element is allowed to be.  For example, 0.0 denotes that this element
is allowed to be zero or greater.  Rarely, this rule may have a lookup path that contains
a relative path into the parse tree.  If the set represented by the relative path is a single
value, and if that value is a number, then that value will be used to determine the lowest
allowed value for the node being validated.

6. __MaxValInc__  If this element exists in the input and it does not have
a value that is a number, then it will fail this check.  However, if this element does not
exist at all in the input, then this validation check will not fail - that is delegated
to the MinOccurs check.  Most often, this restriction node will have a constant that will 
define the largest value that this element is allowed to be.  For example, 0.0 denotes that
this element is allowed to be zero or less. Rarely, this rule may have a lookup path that 
contains a relative path into the parse tree from the current element.  If there is a single
value in the set described by the relative path, and if that value is a number, then that
value will be used to determine the largest allowed value for the element being validated.


