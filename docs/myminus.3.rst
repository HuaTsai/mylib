myminus
==========

-------------------------------------------
A simple function to subtract two integers.
-------------------------------------------

:Author: HuaTsai
:Manual section: 3
:Manual group: mylib Library Manual
:Date: 2024-11-26
:Version: 1.2.3

SYNOPSIS
--------

.. code-block:: c++

    #include <myminus.h>

    int minus(int a, int b);

DESCRIPTION
-----------

The `minus` function takes two integers as input and returns the subtraction.

ARGUMENTS
---------

**a**
    The first integer from which b will be subtracted.

**b**
    The second integer to be subtracted from a.

RETURN VALUE
------------

Returns the subtraction of the two integers `a` and `b`.

EXAMPLES
--------

1. Subtracting two numbers:

    .. code-block:: c++

        #include <stdio.h>
        #include <myminus.h>

        int main() {
            int result = minus(3, 4);
            std::cout << "The sum is: " << result << std::endl;
        }

2. Subtracting negative numbers:

    .. code-block:: c++

        int result = minus(-2, -5);  // result = 3

SEE ALSO
--------

`myadd(3)`

