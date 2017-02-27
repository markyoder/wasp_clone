# Sequence Input Retrieval Engine (SIREN) 
SIREN is a syntax for navigating and selecting document elements. It is heavily influenced by the XML XPath [https://www.w3schools.com/xml/xpath_syntax.asp] component within the XSLT standard.



## Selecting Nodes
The selection of nodes is performed via a path expression. Path expressions can be relative to a current node or absolute to the document.

An empty result set will be produced if no elements in the document match the given path expression.

|Expression | Description |
| --------- | ----------- |
|_nodename_ | Selects all nodes with the name "_nodename_" that are children of the current node |
|/          | Selects from the root of the document|
|.          | Selects the current node|
|..         | selects the parent of the current node|


### Selection Examples

|Expression | Description |
| --------- | ----------- |
|_value_ | Selects all nodes with the name "_value_" that are children of the current node |
|/_value_   | Selects all nodes with the name "_value_" that are children of the root of the document|
|./_value_  | Selects all nodes with the name "_value_" from the current node|
|../_value_ | selects all nodes with the name "_value_" that are children of the parent of the current node|

### Predicates
Selection of document elements may require predicated search patterns that evaluate the position of value of the element.

|Expression | Description |
| --------- | ----------- |
|_value_[1] | Selects the first node with the name "_value_" that is a child of the current node |
|_child_[_value_ = 3.14] | Selects all nodes with the name "_child_" of the current node where the _child_'s _value_ is equal to 3.14  |
|_child_[_name_ = 'fred']/_ear_ | Selects all nodes with the name "_ear_" which are children of _child_ of the current node, only when _child_'s name is 'fred' |

