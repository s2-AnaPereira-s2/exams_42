#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    if (c != EOF)
        ungetc(c, f);
    if (c == EOF)
        return -1;
    else
        return 0;
}

int match_char(FILE *f, char expected)
{
    int c = fgetc(f);
    if (c == expected)
        return 1;
    if (c != EOF)
        ungetc(c, f);
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
    char *ptr = va_arg(ap, char *);
    int c = fgetc(f);
    if (c == EOF)
        return 0;
    *ptr = c;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int *ptr = va_arg(ap, int *);
    int c, sign = 1, num = 0, digits = 0;

    c = fgetc(f);
    if (c == '-')
    {
        sign = -1;
        c = fgetc(f);
    }
    else if (c == '+')
        c = fgetc(f);

    while (c != EOF && isdigit(c))
    {
        num = num * 10 + (c - '0');
        digits = 1;
        c = fgetc(f);
    }

    if (c != EOF)
        ungetc(c, f);
    if (!digits)
        return 0;

    *ptr = num * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    char *ptr = va_arg(ap, char *);
    int c, count = 0;

    while ((c = fgetc(f)) != EOF && !isspace(c))
    {
        ptr[count++] = c;
    }

    if (c != EOF)
        ungetc(c, f);
    if (count == 0)
        return 0;

    ptr[count] = '\0';
    return 1;
}

int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)
    {
    case 'c':
        return scan_char(f, ap);
    case 'd':
        match_space(f);
        return scan_int(f, ap);
    case 's':
        match_space(f);
        return scan_string(f, ap);
    default:
        return -1;
    }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;

    int c = fgetc(f);
    if (c == EOF)
        return EOF;
    ungetc(c, f);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (match_conv(f, &format, ap) != 1)
                break;
            nconv++;
        }
        else if (isspace(*format))
        {
            if (match_space(f) == -1)
                break;
        }
        else if (match_char(f, *format) != 1)
        {
            break;
        }
        format++;
    }

    if (ferror(f))
        return EOF;
    return nconv;
}

int ft_scanf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}

int main()
{
    return 0;
}
