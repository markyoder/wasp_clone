# Standard Object Notation (SON)
The standard object notation is a lightweight data entry syntax intended to facilitate application input acquisition.

The supported constructs are Objects, Arrays, and Keyed values. Additionally, Objects, Arrays, and Keyed values can be further disambiguated using identifiers.

SON can facilitate simple constructs such as property or configuration files using keyed-values. 
## Keyed-Value 

The Keyed-Value is the simplest construct for representing information. 

`name = value` 

Where _name_ is a string, _=_ indicates assignment, and _value_ can be a string, or number.

Alternatively, the colon ':' can be used to indicate assignemt.

`name : value`

An example property store file follows:

```
x=544 y=100
width = 1920
height = 1080
```