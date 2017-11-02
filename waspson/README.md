# Standard Object Notation (SON)
The standard object notation is a lightweight data entry syntax intended to facilitate application input acquisition.

The supported constructs are Objects, Arrays, and Keyed values. Additionally, Objects, Arrays, and Keyed values can be further disambiguated using identifiers.

SON can facilitate simple constructs such as property or configuration files using keyed-values. 

## Keyed-Value 

The Keyed-Value is the simplest construct for representing information. 

`name = value` 

Where _name_ is a string, _=_ indicates assignment, and _value_ can be a string, or number.

Alternatively, the colon ':' can be used to indicate assignment.

`name : value`

An example property store file that illustrates an application window attribute follows:

```
x=544 y=100
width = 1920
height = 1080
```

Lastly, if the keyed-value needs to be further disambiguated an identifier can be added.

`name ( id ) = value`

An example property store file that illustrates an application with attributes of two windows (main, settings) follows:

```
x(main)=544 y(main)=100
width(main) = 1920
height(main) = 1080

x(settings) = 520 y(settings) = 800
width (settings) = 120 height(settings) = 120
```

## Hierarchy via Objects
Hierarchy or grouping can be added using the Object construct. Objects are useful in exhuming common context with a succinct handle. 

Objects can have nested objects, keyed-values, and arrays in any order. 

Objects have the following syntax.

```
object_name { ... }
```

```
object_name { 
... 
}
```

```
object_name 
{ 
... 
}
```
 
The example property store file above illustrates potential object use as follows.
 
```
main{
    x=544 y=100
    width = 1920
    height = 1080
}
settings{
    x = 520 y = 800
    width = 120 height = 120
}
```

Objects support the same identifier scheme as keyed-values. 
 
## Arrays of Data
 SON supports 1d arrays of data that data can be scalar values, keyed-values, and nested-objects or arrays. 
 Multi-dimensional data can be flattened to 1d and application specific context provided in associated keyed-value elements.
 
 Arrays have the following syntax.
 
```
array [ ... ]
```
 
```
array [
 ... 
]
```
 
```
array 
[ 
... 
]
```
 
The example property store file above illustrates potential array use as follows:
 
```
 name  [ main settings ]
 x     [  544      520 ]
 y     [  100      800 ]
 width [ 1920     1080 ]
 height[  120      120 ]
 
```
 
Arrays support the same identifier scheme as keyed-values with the one exception that nested arrays cannot have identifiers.
