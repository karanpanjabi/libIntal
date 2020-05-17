#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// char to int
static int ctoi(char c)
{
    return c - '0';
}

// int to char
static char itoc(int d)
{
    return '0' + d;
}

static int max2(int a, int b)
{
    return (a > b) ? a : b;
}

static void set_zero(char *intal, int numdigits)
{
    memset(intal, '0', numdigits);
}

static char *get_intal(int numdigits)
{
    int tsize = (numdigits + 1) * sizeof(char);
    char *temp = (char *)malloc(tsize);
    set_zero(temp, numdigits);
    temp[tsize-1] = 0;

    return temp;
}

// count of leading zeroes
static int count_leadz(char *st)
{
    int c = 0;
    while (st != NULL && *st == '0')
    {
        c++;
        st++;
    }
    return c;
}

// get intal without leading zeros, unless only one digit
static char *get_intal_woz(char *intal, int numdigits)
{
    char *ret = NULL;
    int num_z = count_leadz(intal);

    if (num_z == 0)
    {
        ret = intal;
    }
    else if (num_z == numdigits) // all zeroes
    {
        ret = get_intal(1);
    }
    else
    {
        int fdig = numdigits - num_z;
        ret = get_intal(fdig);
        memcpy(ret, intal + num_z, fdig); // TODO: verify indices
    }

    return ret;
}

// get ith digit from right
static int get_digit_intal(char *intal, int intallen, int digitnum)
{
    if (digitnum >= intallen)
        return 0;
    return ctoi(intal[intallen - digitnum - 1]);
}

// returns char* version of num
static char *make_intal(unsigned int num)
{
    int templen = 11;
    char *temp = get_intal(templen);

    int n = num;
    int i = 0;
    while (n != 0)
    {
        temp[templen - i - 1] = itoc(n % 10);
        n = n / 10;
        i++;
    }

    char *_temp = get_intal_woz(temp, templen);

    if (_temp != temp)
        free(temp);

    return _temp;
}

// Returns the sum of two intals.
char *intal_add(const char *intal1, const char *intal2)
{
    char *sum = NULL;

    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int sumlen = max2(len1, len2) + 1; // +1 for carry

    sum = get_intal(sumlen);

    // add digits from 0 to sumlen-1 taking care of carry
    int carry = 0;
    for (int i = 0; i < sumlen; i++)
    {
        int d1 = get_digit_intal(intal1, len1, i);
        int d2 = get_digit_intal(intal2, len2, i);

        int s = d1 + d2 + carry;
        if (s > 9)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        sum[sumlen - i - 1] = itoc(s % 10);
    }

    char *ns = get_intal_woz(sum, sumlen);

    if (ns != sum)
    {
        free(sum);
    }

    return ns;
}

// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(const char *intal1, const char *intal2)
{
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);

    // TODO: fix for 0 and 00
    if (len1 > len2)
    {
        return 1;
    }
    else if (len2 > len1)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < len1; i++)
        {
            if (intal1[i] != intal2[i])
            {
                if (ctoi(intal1[i]) > ctoi(intal2[i]))
                    return 1;
                else
                    return -1;
            }
        }
        return 0;
    }
}

// Returns the difference (obviously, nonnegative) of two intals.
char *intal_diff(const char *intal1, const char *intal2)
{
    // arrange so that intal1 is bigger than intal2
    int comp = intal_compare(intal1, intal2);
    if (comp == -1)
    {
        char *temp = intal2;
        intal2 = intal1;
        intal1 = temp;
    }

    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int difflen = len1;

    char *diff = get_intal(difflen);

    // sub digits from 0 to difflen-1, taking care of borrow
    int borrow = 0;
    for (int i = 0; i < difflen; i++)
    {
        int d1 = get_digit_intal(intal1, len1, i);
        int d2 = get_digit_intal(intal2, len2, i);

        int s = (d1 - borrow) - d2;

        if (s < 0)
        {
            s += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        diff[difflen - i - 1] = itoc(s);
    }

    char *nd = get_intal_woz(diff, difflen);

    if (nd != diff)
    {
        free(diff);
    }

    return nd;
}

// Returns the product of two intals.
char *intal_multiply(const char *intal1, const char *intal2)
{
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);
    int mullen = len1 + len2;

    char *mul = get_intal(mullen);

    char *temp = get_intal(mullen);

    for (int i = 0; i < len2; i++)
    {
        int d2 = get_digit_intal(intal2, len2, i);

        // multiply intal1 with (d2) and add to mul

        int carry = 0;
        for (int j = 0; j < len1 + 1; j++) // +1 to take care of carry
        {
            int d1 = get_digit_intal(intal1, len1, j);
            int s = d1 * d2 + carry;

            carry = s / 10;
            s = s % 10;

            temp[mullen - j - 1 - i] = itoc(s);
        }

        char *tmul = intal_add(mul, temp);
        free(mul);
        mul = tmul;

        set_zero(temp, mullen);
    }

    free(temp);

    char *_mul = get_intal_woz(mul, strlen(mul));

    if(_mul != mul)
        free(mul);

    return _mul;
}

// Returns intal1 mod intal2
// The mod value should be in the range [0, intal2 - 1].
// intal2 > 1
// Implement a O(log intal1) time taking algorithm.
// O(intal1 / intal2) time taking algorithm may exceed time limit.
// O(intal1 / intal2) algorithm may repeatedly subtract intal2 from intal1.
// That will take intal1/intal2 iterations.
// You need to design a O(log intal1) time taking algorithm.
// Generate your own testcases at https://www.omnicalculator.com/math/modulo
char *intal_mod(const char *intal1, const char *intal2)
{
}

// Returns intal1 ^ intal2.
// Let 0 ^ n = 0, where n is an intal.
// Implement a O(log n) intal multiplications algorithm.
// 2^3000 has less than 1000 decimal digits. 3000 intal multiplications may exceed time limit.
char *intal_pow(const char *intal1, unsigned int n)
{
}

// Returns Greatest Common Devisor of intal1 and intal2.
// Let GCD be "0" if both intal1 and intal2 are "0" even though it is undefined, mathematically.
// Use Euclid's theorem to not exceed the time limit.
char *intal_gcd(const char *intal1, const char *intal2)
{
}

// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".
char *intal_fibonacci(unsigned int n)
{
    char *first = make_intal(0);
    char *second = make_intal(1);

    char *fib = NULL;

    if(n == 0)
    {
        free(second);
        return first;
    }
    if(n == 1)
    {
        free(first);
        return second;
    }

    char *third;
    for (unsigned int i = 2; i <= n; i++)
    {
        // third = first + second
        // first = second
        // second = third

        third = intal_add(first, second);

        free(first);
        first = second;
        second = third;
    }
    
    free(first);

    return third;
}

// Returns the factorial of n.
char *intal_factorial(unsigned int n)
{
    char *res = get_intal(1);
    res[0] = '1';

    for (unsigned int i = 1; i <= n; i++)
    {
        char *i_intal = make_intal(i);
        char *_res = intal_multiply(res, i_intal);
        free(res);
        res = _res;
        free(i_intal);
    }

    return res;
}

// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
// C(n,k) < 10^1000 because the returning value is expected to be less than 10^1000.
// Use the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1)
// Make sure the intermediate intal values do not cross C(n,k).
// Use Dynamic Programming. Use extra space of not more than O(k) number of intals. Do not allocate the whole O(nk) DP table.
// Don't let C(1000,900) take more time than C(1000,500). Time limit may exceed otherwise.
char *intal_bincoeff(unsigned int n, unsigned int k)
{
}

// Returns the offset of the largest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_max(char **arr, int n)
{
}

// Returns the offset of the smallest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_min(char **arr, int n)
{
}

// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, const char *key)
{
}

// Returns the offset of the first occurrence of the key intal in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation should be a O(log n) algorithm.
int intal_binsearch(char **arr, int n, const char *key)
{
}

// Sorts the array of n intals.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.
void intal_sort(char **arr, int n)
{
}

// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// The implementation should be O(n) time and O(1) extra space even though the DP table may be of O(n) size.
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25
char *coin_row_problem(char **arr, int n)
{
}
