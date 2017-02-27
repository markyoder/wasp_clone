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

An example property store file that illustrates an application window attribute follows:

```
x=544 y=100
width = 1920
height = 1080
```

Lastly, if the keyed-value needs to be further disambiguated an identifier can be added.

`name ( id ) = value`

An example property store file that illustrates an application with two window (main, settings) attributes follows:

```
x(main)=544 y(main)=100
width(main) = 1920
height(main) = 1080

x(settings) = 520 y(settings) = 800
width (settings) = 120 height(settings) = 120
```
