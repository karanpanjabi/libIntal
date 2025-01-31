# libIntal
Miniproject for APSSSE Special Topic
1) Introduction
    * An intal is an arbitary length non negative integer.
    * This is different from general integer and integer data types in C because it is represented using a char * (null terminated c string). It can have arbitrary number of digits unlike the integer datatype in C.
    * Intal can be used for applications that need to avoid integer overflow bugs that could occur with normal datatypes. So, for sensitive data or scientific data, Intal can be used.

2) Approach
    The approach involves the basic functions add, diff, multiply, compare and the other functions that use these basic functions extensively. Auxiliary functions were added to malloc intal, convert a char to a digit and vice versa, to get nth digit from right, to count the number of leading zeroes and to remove them.

3) Future work
    a) The library can be made to support signed numbers as well. This can also be extended to support arbitrary length floating point values as well.
    b) If I had no restrictions, I would've implemented this library in C++ instead because it supports RAII (Resource Acquisition Is Initialization) through constructors and destructors, so I wouldn't have to worry too much about memory leaks or segfaults with malloc and free. That being said one byte of space seems wasteful to represent a digit that can take 10 values (which would just use 4 bits from those 8). An array of integers could instead be used with an appropriate base to utilize the bytes properly (though this would be more of a space time tradeoff).
