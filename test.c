#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

int main(int argc, char const *argv[])
{
    char *s1 = "4";
    char *s2 = "1234";
    if(argc > 1)
    {
        s1 = argv[1];
        
        if(argc > 2)
            s2 = argv[2];
    }
    

    // printf("%d\n", intal_compare(s1, s2));
    // printf("%s\n", intal_add(s1, s2));
    // printf("%s\n", intal_diff(s1, s2));
    // printf("%s\n", intal_multiply(s1, s2));
    // printf("%s\n", intal_factorial(atoi(s1)));
    // printf("%s\n", intal_fibonacci(atoi(s1)));
    // printf("%s\n", intal_mod(s1, s2));
    // printf("%s\n", intal_pow(s1, atoi(s2)));
    // printf("%s\n", intal_bincoeff(atoi(s1), atoi(s2)));


    // char *arr[] = {
    //     "7",
    //     "3",
    //     "4",
    //     "88",
    //     "1"
    // };

    // int arrlen = 5;
    // intal_sort(arr, arrlen);

    char *arr[] = {
        "1",
        "2",
        "3",
        "3",
        "3",
        "4",
        "7",
        "88"
    };

    printf("%d\n", intal_binsearch(arr, 8, "3"));

    return 0;
}
