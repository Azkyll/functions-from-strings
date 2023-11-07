# Functional tools for my graphical calculator project.

## Goal
Create your std::function object from a string, or a vector of strings.
Expected object shapes : "f", "ax" where a is a number, {"f", "g", "x"} or {"f", "g"}, {"f", "g", "h"} or any composition order.

## What does it currently do?

Exactly what stated above.

You can use any input of the form "a f" where a is a number, i.e. "2cos" is treated as 2 * cos ( x ). Note that {"2", "cos"} gives the same output function, as by default the output function is composed with the identity (so {"2", "cos"} is actually 2 * id composed with cos).

## Currently supported functions
 - exp
 - log
 - cos, sin, tan
 - cosh, sinh, tanh

Please note that power functions aren't yet implemented, so polynomials can't yet be expressed. While this is unfortunate for a graphical calculator, this will be fixed shortly.

# DISCLAIMER, THANKS AND CREDITS

I **did** use code straight from stackoverflow in this. The composer elements are all from the same answer : https://stackoverflow.com/questions/19071268/function-composition-in-c-c11, best answer from **Igor Tandetnik**{https://stackoverflow.com/users/1670129/igor-tandetnik}.
