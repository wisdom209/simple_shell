#include "main.h"

/**
 * _printf - printf
 * @format: String to be formatted
 *
 * Return: int
 */
int _printf(const char *format, ...)
{
	int i = 0, count = 0, ret = 0;
	va_list ptr;

	va_start(ptr, format);

	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			count++;
		}
		else
		{
			ret = print_string(&i, ptr, format, &count);
			ret = print_digits(&i, ptr, format, &count);
			if (ret == -1)
				return (-1);
		}
		i++;
	}
	return (count);
}

/**
 * print_digits - print digits
 * @i: i
 * @ptr: ptr
 * @format: format
 * @count: count
 * Return: int
 */
int print_digits(int *i, va_list ptr, const char *format, int *count)
{
	if (format[*i + 1] == 'd' || format[*i + 1] == 'i')
	{
		int num = va_arg(ptr, int);

		if (num <= INT_MAX && num >= INT_MIN)
		{
			print_num(num, count);
			*i = *i + 1;
		}
		else
			return (-1);
	}
	return (0);
}

/**
 * print_num - prints a number
 * @num: number
 * @count: length
 *
 * Return: int
 */
int print_num(long num, int *count)
{
	int *ptr;
	int i = 0, j = 0;
	long m = 0;

	if (num < 0)
	{
		_putchar('-');
		*count = *count + 1;
		num = num * -1;
	}

	m = num;

	while (m != 0)
	{
		m = m / 10;
		i++;
	}

	m = num;
	ptr = malloc(sizeof(int) * i);

	if (ptr == NULL)
		return (-1);

	for (j = 0; j < i; j++)
	{
		ptr[j] = m % 10;
		m = m / 10;
	}

	for (j = i - 1; j >= 0; j--)
	{
		_putchar(ptr[j] + '0');
		*count = *count + 1;
	}

	free(ptr);
	return (0);
}

/**
 * print_string - print string
 * @i: i
 * @ptr: ptr
 * @format: format
 * @count: count
 *
 * Return: int
 */
int print_string(int *i, va_list ptr, const char *format, int *count)
{
	if (format[*i + 1] == 's')
	{
		char *s = va_arg(ptr, char *);
		int j = 0;

		if (s == NULL)
			s = "(null)";

		while (s[j] != '\0')
		{
			_putchar(s[j]);
			*count = *count + 1;
			j++;
		}
		*i = *i + 1;
	}
	return (0);
}

/**
 * _putchar - write to STDOUT
 * @c: parameter
 * Return: int
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
