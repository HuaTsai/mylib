myadd
=========

--------------------------------------
A simple function to add two integers.
--------------------------------------

:Author: HuaTsai
:Manual section: 3
:Manual group: mylib Library Manual
:Date: 2024-11-26
:Version: 1.2.3

SYNOPSIS
--------

.. code-block:: c++

    #include <myadd.h>

    int add(int a, int b);

DESCRIPTION
-----------

The `add` function takes two integers as input and returns their sum.

ARGUMENTS
---------

**a**
    The first integer to be added.

**b**
    The second integer to be added.

RETURN VALUE
------------

Returns the sum of the two integers `a` and `b`.

EXAMPLES
--------

1. Adding two numbers:

    .. code-block:: c++

        #include <stdio.h>
        #include <myadd.h>

        int main() {
            int result = add(3, 4);
            std::cout << "The sum is: " << result << std::endl;
        }

2. Adding negative numbers:

    .. code-block:: c++

        int result = add(-2, -5);  // result = -7

SEE ALSO
--------

`myminus(3)`

