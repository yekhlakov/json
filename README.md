# json
a class for straightforward JSON manipulation

## Linking

- put `maxy/json.h`, `maxy/json.cpp` into your project
- this requires certain code from `maxy::strings` (http://github.com/yekhlakov/strings), put all the files into `maxy` directory.
- `#include "maxy/json.h"` and enjoy
- see `test.cpp` for examples of the class usage

## Notes

### 1. Parse

The class can parse `std::string`s and `std::istream`s, for example, `auto j = json::parse ("[null, true, 0.3]");`
The input may contain anything that can be a part of a json.
Parser is quite relaxed, it ignores many violations of specification. Most notably, it allows for unquoted object keys and trailing commas.
`{a:"1",,,b:"2",}` will therefore be parsed successfully.

### 2. Write

`output_stream << j;`

The object is written in strict format, i.e. no unnecessary whitespace, keys are quoted strings, no trailing comma.

### 3. Modify

`j = 3;` sets json to an integer value of 3 (floats, bools and strings are also accepted).

`j["key"] = value;` sets the "key" field of the object.

`j["a"]["b"]["c"] = 42;` we can construct nested objects just like that.

`j[16] = nullptr;` sets the array element.

Note that any assignment converts the json object into its appropriate type, losing any previous state.

`json x = 16.0; // x is just 16.0`

`x.push_back(666);` // x is an array [666]

`x["a"] = false; // x is an object {"a":false}`

`x[0] = "123"; // x is an array ["123"]`

### 4. Iterate

A json can be iterated over using range-for or `begin()`/`end()`. Atomary values can be iterated over too (as if they were containers with
just one element).