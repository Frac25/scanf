#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdarg.h>
#include <ctype.h>

// autorise : isspace isigit fgetc ungetc ferror feof stdin va_list va_arg va_start va_end va_copy

int scan_int(int fd, va_list ap)
{
	int *val;
	char buf[1];
	int signe = 1;

	printf("passe int\n");

	val = va_arg(ap, int*);
	val[0] = 0;

	read(fd, buf, 1);

	while(buf[0] && isspace(buf[0]))
	{
		read(fd, buf, 1);
	}
	if (buf[0] == '-')
	{
		signe = -1;
		read(fd, buf, 1);
	}
	while(buf[0] && isdigit(buf[0]))
	{
		val[0] = val[0] * 10 + buf[0] - '0';
		read(fd, buf, 1);
	}
	return(1);
}

int scan_char(int fd, va_list ap)
{
	char buf[1];
	char* var;

	var = va_arg(ap, char*);
	read(fd, buf, 1);
	var[0] = buf[0];
	while(buf[0] != '\0' && buf[0] != '\n')
		read(fd, buf, 1);
	return(1);
}

int scan_string(int fd, va_list ap)
{
	char buf[1];
	char* var;
	int i = 0;

	var = va_arg(ap, char*);
	read(fd, buf, 1);
	while (buf[0] != '\0' && isspace(buf[0]))
		read(fd, buf, 1);
	while(buf[0] != '\0' && buf[0] != '\n' && buf[0] != ' ')
	{
		var[i] = buf[0];
		read(fd, buf, 1);
		i++;
	}
	var[i] = '\0';
	return(1);
}



int receiv_input(const char format, va_list ap)
{
	int fd = 0;

	switch(format)
	{
		case 'c' :
			return scan_char(fd, ap);
		case 'd':
//			skip_input_space();
			return scan_int(fd, ap);
		case 's' :
//			skip_input_space();
			return scan_string(fd, ap);
	}


	return(0);
}

int ft_scanf(const char *format, ...)
{
	int i = 0;
	int result = 0;
	va_list ap;

	va_start(ap, format);
	while(format[i] != '\0')
	{
		if(format[i] == '%')
		{
			i++;
			if(receiv_input((format[i]), ap) != 1)
				break;
			else
				result++;
		}
		i++;
	}
	return(result);
	va_end(ap);
}

int main(void)
{
	int d;
	char c;
	char *s;

	printf(" entrez d");
	ft_scanf("%d", &d);
	printf("d = %d", d);
}
