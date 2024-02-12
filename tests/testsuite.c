#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdarg.h>
#include <stdio.h>

#include "../src/tinyprintf.h"

/* SIMPLE CASES */
Test(simple, base1)
{
    int expected = 22;
    cr_redirect_stdout();
    int actual = tinyprintf("this is the 42th test\n");
    fflush(stdout);
    cr_expect_stdout_eq_str("this is the 42th test\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(simple, base2)
{
    int expected = 1;
    cr_redirect_stdout();
    int actual = tinyprintf("\n");
    fflush(stdout);
    cr_expect_stdout_eq_str("\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(simple, base3)
{
    int expected = 0;
    cr_redirect_stdout();
    int actual = tinyprintf("");
    fflush(stdout);
    cr_expect_stdout_eq_str("");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(simple, base4)
{
    int expected = 0;
    cr_redirect_stdout();
    int actual = tinyprintf(NULL);
    fflush(stdout);
    cr_expect_stdout_eq_str("");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

/* SIGNED DECIMAL */
Test(signed_dec, base1)
{
    int expected = 22;
    cr_redirect_stdout();
    int actual = tinyprintf("this is the %dth test\n", 42);
    fflush(stdout);
    cr_expect_stdout_eq_str("this is the 42th test\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(signed_dec, base2)
{
    int expected = 4;
    cr_redirect_stdout();
    int actual = tinyprintf("%d\n", -42);
    fflush(stdout);
    cr_expect_stdout_eq_str("-42\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(signed_dec, base3)
{
    int expected = 5;
    cr_redirect_stdout();
    int actual = tinyprintf("ok %d", 69);
    fflush(stdout);
    cr_expect_stdout_eq_str("ok 69");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(signed_dec, base4)
{
    int expected = 1;
    cr_redirect_stdout();
    int actual = tinyprintf("%d", 0);
    fflush(stdout);
    cr_expect_stdout_eq_str("0");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

/* UNSIGNED DECIMAL */
Test(unsigned_dec, base1)
{
    int expected = 22;
    cr_redirect_stdout();
    int actual = tinyprintf("this is the %uth test\n", 42);
    fflush(stdout);
    cr_expect_stdout_eq_str("this is the 42th test\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(unsigned_dec, base2)
{
    int expected = 11;
    cr_redirect_stdout();
    int actual = tinyprintf("%u\n", -42);
    fflush(stdout);
    cr_expect_stdout_eq_str("4294967254\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(unsigned_dec, base3)
{
    int expected = 5;
    cr_redirect_stdout();
    int actual = tinyprintf("ok %u", 69);
    fflush(stdout);
    cr_expect_stdout_eq_str("ok 69");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(unsigned_dec, base4)
{
    int expected = 1;
    cr_redirect_stdout();
    int actual = tinyprintf("%u", 0);
    fflush(stdout);
    cr_expect_stdout_eq_str("0");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

/* STRING */
Test(string, base1)
{
    int expected = 22;
    cr_redirect_stdout();
    int actual = tinyprintf("this is the %sth test\n", "42");
    fflush(stdout);
    cr_expect_stdout_eq_str("this is the 42th test\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(string, base2)
{
    int expected = 0;
    cr_redirect_stdout();
    int actual = tinyprintf("%s", "");
    fflush(stdout);
    cr_expect_stdout_eq_str("");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

/* CHAR */
Test(c, base1)
{
    int expected = 21;
    cr_redirect_stdout();
    int actual = tinyprintf("this is the %cst test\n", '1');
    fflush(stdout);
    cr_expect_stdout_eq_str("this is the 1st test\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(c, base2)
{
    int expected = 1;
    cr_redirect_stdout();
    int actual = tinyprintf("%c", '\n');
    fflush(stdout);
    cr_expect_stdout_eq_str("\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

/* OCTAL */
Test(oct, base1)
{
    int expected = 22;
    cr_redirect_stdout();
    int actual = tinyprintf("this is the %oth test\n", 42);
    fflush(stdout);
    cr_expect_stdout_eq_str("this is the 52th test\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(oct, base2)
{
    int expected = 11;
    cr_redirect_stdout();
    int actual = tinyprintf("%o", -42);
    fflush(stdout);
    cr_expect_stdout_eq_str("37777777726");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

/* HEXA */
Test(hexa, base1)
{
    int expected = 22;
    cr_redirect_stdout();
    int actual = tinyprintf("this is the %xth test\n", 32);
    fflush(stdout);
    cr_expect_stdout_eq_str("this is the 20th test\n");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(hexa, base2)
{
    int expected = 8;
    cr_redirect_stdout();
    int actual = tinyprintf("%x", -42);
    fflush(stdout);
    cr_expect_stdout_eq_str("ffffffd6");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

/* OTHER CASES */
Test(other, base1)
{
    int expected = 17;
    cr_redirect_stdout();
    int actual = tinyprintf("%s [%d] %s", "Hello", 42, "world!");
    fflush(stdout);
    cr_expect_stdout_eq_str("Hello [42] world!");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(other, base2)
{
    int expected = 17;
    cr_redirect_stdout();
    int actual = tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    fflush(stdout);
    cr_expect_stdout_eq_str("Hello [2a] world!");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(other, base3)
{
    int expected = 2;
    cr_redirect_stdout();
    int actual = tinyprintf("%%s", "in your head");
    fflush(stdout);
    cr_expect_stdout_eq_str("%s");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(other, base4)
{
    int expected = 39;
    cr_redirect_stdout();
    int actual = tinyprintf("Good morning ACU! %t Tinyprintf is cool", 12);
    fflush(stdout);
    cr_expect_stdout_eq_str("Good morning ACU! %t Tinyprintf is cool");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(other, base5)
{
    int expected = 8;
    cr_redirect_stdout();
    int actual = tinyprintf("%% % %% %t", 12, "ok");
    fflush(stdout);
    cr_expect_stdout_eq_str("% % % %t");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}

Test(other, base6)
{
    int expected = 15;
    cr_redirect_stdout();
    int actual = tinyprintf("%%%d%u%s%c%o%x%t", -12, 42, "ok", 'a', 42, 32, 11);
    fflush(stdout);
    cr_expect_stdout_eq_str("%-1242oka5220%t");
    cr_expect_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}
