#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

int main(int argc, char const *argv[])
{
    char *s1 = "1234";
    char *s2 = "4";
    if(argc > 1)
    {
        s1 = argv[1];
        s2 = argv[2];
    }
    

    printf("%d\n", intal_compare(s1, s2));
    printf("%s\n", intal_add(s1, s2));
    printf("%s\n", intal_diff(s1, s2));
    return 0;
}
