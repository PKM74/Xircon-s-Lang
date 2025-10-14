# Basics in Xircon's Lang (XILANG)

A short and relatively detailed list of all the basics of XILANG. Also yes, the name is supposed to be all caps *always* just like older FORTRAN.

## Extremly Basic Functions

* `ret` then a value (can be a numeral or a string) will return that value
* `func` then a name (ex: `func main() {}`) allows you to define a new function
* `import` and a filename (either in `""` or `<>` depending on if it is a local file in the dir or a file from the include path, similar to C) allows you to import the functions from another file
* `print` then a value will allow to print a character or string to the screen (you can also print any other type of varible)

## Defining Varibles

you define something by doing the type of var you want to define then a name then an = and the value of it (ex: `float Example = 1.0;`)

* `int` will allow you to define an integer value, just like in C
* `float` for a floating point value
* `boolean` for a boolean value (true or false)
* `string` for a string value (the value MUST be wrapped in `""`s!)
* `char` for a single character value (must be wrapped in `''`s!)

## A Basic Program

A Basic program that just prints text and then returns.

```!This is a Comment.
string hi = "Hello";

func main() {
    print hi," World!";
    ret 0;
}
```
This small prgram will print `Hello World!` and return 0.