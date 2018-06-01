# json
a class for straightforward JSON manipulation

## Linking

- put `maxy/json.h`, `maxy/json.cpp` into your project
- this requires certain code from `maxy::strings` (http://github.com/yekhlakov/strings), put all the files into `maxy` directory.
- include "maxy/json.h" and enjoy
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
