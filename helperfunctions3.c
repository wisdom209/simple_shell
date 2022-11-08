#include "main.h"
/**
 * _printf - mini printf
 * @format: parameter
 * Return: count
 */
int _printf(const char *format, ...)
{
	int i = 0, count = 0;
	va_list ptr;

	va_start(ptr, format);

	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			count++;
		}
		if (format[i + 1] == 's')
		{
			char *s = va_arg(ptr, char *);
			int j = 0;

			if (s == NULL)
				s = "(null)";

			while (s[j] != '\0')
			{
				_putchar(s[j]);
				count = count + 1;
				j++;
			}
			i = i + 1;
		}

		i++;
	}
	return (count);
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
