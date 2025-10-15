# Basics in Xircon's Lang (XILANG)

A short and relatively detailed list of all the basics of XILANG. Also yes, the name is supposed to be all caps *always* just like older FORTRAN.

## Extremely Basic Functions

* `ret` then a value (can be a numeral or a string) will return that value
* `exit` then a value (can ONLY be a numeral) will exit with that return value
* `func` then a name (ex: `func main() {};`) allows you to define a new function
* `import` and a filename (either in `""` or `<>` depending on if it is a local file in the dir or a file from the include path, similar to C) allows you to import the functions from another file (ex: `import Example.xh`)
* `print` then a value will allow to print a character or string to the screen (you can also print any other type of variable)

## Defining Variables

you define something by doing the type of var you want to define then a name then an = and the value of it (ex: `float Example = 1.0;`)

* `int` will allow you to define an integer value, just like in C
* `float` for a floating point value
* `boolean` for a boolean value (true or false)
* `string` for a string value (the value MUST be wrapped in `""`s!)
* `char` for a single character value (must be wrapped in `''`s!)

## Ifs and Loops

* `if` is pretty simple its just `if x = y {do this};`
* `else` if's best friend! simple as `if x = y {}; else {};`
* `elif` an else if statement (just like `else if () {}` in C or C++)
* `loop` is a bit more... dangerous. you can loop... well... basically forever if you were to... forget the value... `loop 100 {print "This"}` or `loop {print "This"}` are both valid ways to use loop, one does the same thing 100 times the other does it until your CPU stops CPUing.
* `while` does something while something is true, for example `while x = 1 {print "This"}` or `while x > 1 {print "This"}`

## A Basic Program

A Basic program that just prints text and then returns.

```!This is a Comment.
string hi = "Hello";

func main() {
    print hi," World!";
    ret 0;
}
```
This small program will print `Hello World!` and return 0.