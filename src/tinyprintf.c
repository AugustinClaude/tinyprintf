#include "tinyprintf.h"

// my_itoa_base START

static char *my_itoa_base(int n, char *s, const char *base)
{
    if (n == 0)
    {
        s[0] = base[0];
        s[1] = '\0';
        return s;
    }

    size_t i = 0;

    if (n < 0)
    {
        s[0] = '-';
        i++;
        n = -n;
    }

    size_t base_len = 0;
    for (size_t k = 0; base[k] != '\0'; k++)
    {
        base_len++;
    }

    while (n > 0)
    {
        size_t r = n % base_len;
        n /= base_len;

        s[i] = base[r];
        i++;
    }

    size_t len = i;
    i = s[0] == '-';
    size_t j = len - 1;

    while (i < j)
    {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;

        i++;
        j--;
    }

    s[len] = '\0';
    return s;
}

static char *my_itoa_base_unsigned(unsigned int n, char *s, const char *base)
{
    if (n == 0)
    {
        s[0] = base[0];
        s[1] = '\0';
        return s;
    }

    size_t i = 0;

    size_t base_len = 0;
    for (size_t k = 0; base[k] != '\0'; k++)
    {
        base_len++;
    }

    while (n > 0)
    {
        size_t r = n % base_len;
        n /= base_len;

        s[i] = base[r];
        i++;
    }

    size_t len = i;
    i = 0;
    size_t j = len - 1;

    while (i < j)
    {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;

        i++;
        j--;
    }

    s[len] = '\0';
    return s;
}

// my_itoa_base END

static int get_length(const char *s)
{
    int len = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        len++;
    }

    return len;
}

static unsigned int number_digits_rec(unsigned int n, unsigned int base_len)
{
    if (n < base_len)
    {
        return 1;
    }

    return 1 + number_digits_rec(n / base_len, base_len);
}

static int print_sdec(va_list ap)
{
    int n = va_arg(ap, int);
    unsigned int n_len = number_digits_rec(abs(n), 10);

    char *s = malloc(sizeof(char) * (n_len + (n < 0) + 1));

    s = my_itoa_base(n, s, "0123456789");

    int len = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        putchar(s[i]);
        len++;
    }

    free(s);
    return len;
}

static int print_udec(va_list ap)
{
    unsigned int n = va_arg(ap, unsigned);
    unsigned int n_len = number_digits_rec(n, 10);

    char *s = malloc(sizeof(char) * (n_len + 1));

    s = my_itoa_base_unsigned(n, s, "0123456789");

    int len = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        putchar(s[i]);
        len++;
    }

    free(s);
    return len;
}

static int print_string(va_list ap)
{
    char *str = va_arg(ap, char *);
    if (!str)
    {
        str = "(null)";
    }

    int len = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        putchar(str[i]);
        len++;
    }

    return len;
}

static int print_char(va_list ap)
{
    char c = va_arg(ap, int);
    putchar(c);

    return 1;
}

static int print_octal(va_list ap)
{
    unsigned int n = va_arg(ap, unsigned);
    unsigned int n_len = number_digits_rec(n, 8);

    char *s = malloc(sizeof(char) * (n_len + 1));

    s = my_itoa_base_unsigned(n, s, "01234567");

    int len = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        putchar(s[i]);
        len++;
    }

    free(s);
    return len;
}

static int print_hexa(va_list ap)
{
    unsigned int n = va_arg(ap, unsigned);
    unsigned int n_len = number_digits_rec(n, 16);

    char *s = malloc(sizeof(char) * (n_len + 1));

    s = my_itoa_base_unsigned(n, s, "0123456789abcdef");

    int len = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        putchar(s[i]);
        len++;
    }

    free(s);
    return len;
}

int handle_dir(char c, va_list ap)
{
    int n = 0;

    switch (c)
    {
    case '%':
        putchar('%');
        n++;
        break;
    case 'd':
        n = print_sdec(ap);
        break;
    case 'u':
        n = print_udec(ap);
        break;
    case 's':
        n = print_string(ap);
        break;
    case 'c':
        n = print_char(ap);
        break;
    case 'o':
        n = print_octal(ap);
        break;
    case 'x':
        n = print_hexa(ap);
        break;
    default:
        putchar('%');
        putchar(c);
        n += 2;
        break;
    }

    return n;
}

int tinyprintf(const char *format, ...)
{
    if (!format)
    {
        return 0;
    }

    int n = 0;
    va_list ap;

    va_start(ap, format);

    int len = get_length(format);
    for (int i = 0; i < len; i++)
    {
        if (format[i] == '%')
        {
            i++;
            n += handle_dir(format[i], ap);
        }
        else
        {
            putchar(format[i]);
            n++;
        }
    }

    va_end(ap);

    return n;
}
