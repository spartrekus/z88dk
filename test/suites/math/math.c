


#include "test.h"
#include <stdio.h>

void test_comparison()
{
     double a = 10.0;
     double b = 2.0;

     Assert( a > b, "a > b");
     Assert( a >= b, "a >= b");
     Assert( a != b, "a != b");
     Assert( b < a, "b < a");
     Assert( b <= a, "b <= a");
     Assert( a == a, "a == a");
     Assert( !(a != a), "!(a != a)");
}

void test_integer_constant_operations()
{
     double a = 2;

     a += 2;
     Assert ( a == 4, "addition: a == 4");
     a *= 2;
     Assert ( a == 8, "multiply: a == 8");
     a /= 2;
     Assert ( a == 4, "divide: a == 4");
     a -= 2;
     Assert ( a == 2, "subtract: a == 2");
}

void test_integer_operations()
{
     double a = 2;
     int    b = 2;

     a += b;
     Assert ( a == 4, "addition: a == 4");
     a *= b;
     Assert ( a == 8, "multiply: a == 8");
     a /= b;
     Assert ( a == 4, "divide: a == 4");
     a -= b;
     Assert ( a == 2, "subtract: a == 2");
}

void test_integer_constant_longform_lhs()
{
     double a = 2;

     a = 2 + a;
     Assert ( a == 4, "addition: a == 4");
     a = 2 * a;
     Assert ( a == 8, "multiply: a == 8");
     a = 32. / a;
     Assert ( a == 4, "divide: a == 4");
     a = 6 - a;
     Assert ( a == 2, "subtract: a == 2");
}

void test_integer_constant_longform()
{
     double a = 2;

     a = a + 2;
     Assert ( a == 4, "addition: a == 4");
     a = a * 2;
     Assert ( a == 8, "multiply: a == 8");
     a = a / 2;
     Assert ( a == 4, "divide: a == 4");
     a = a - 2;
     Assert ( a == 2, "subtract: a == 2");
}

void test_post_incdecrement()
{
     double a = 2;

     a++;
     Assert( a == 3, "++: a == 3");
     a--;
     Assert( a == 2, "--: a == 2");
}

void test_pre_incdecrement()
{
     double a = 2;

     ++a;
     Assert( a == 3, "++: a == 3");
     --a;
     Assert( a == 2, "--: a == 2");
}



int suite_genmath()
{
    suite_setup(MATH_LIBRARY " Tests");

    suite_add_test(test_comparison);
    suite_add_test(test_integer_operations);
    suite_add_test(test_integer_constant_operations);
    suite_add_test(test_integer_constant_longform);
    suite_add_test(test_integer_constant_longform_lhs);
    suite_add_test(test_post_incdecrement);
    suite_add_test(test_pre_incdecrement);

    return suite_run();
}


int main(int argc, char *argv[])
{
    int  res = 0;

    res += suite_genmath();

    exit(res);
}