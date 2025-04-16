#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdarg.h>
#include <ctype.h>


// autorise : isspace isigit fgetc ungetc ferror feof stdin va_list va_arg va_start va_end va_copy

int scan_int(int fd, va_list ap)
{
	char buf[1];
	int* var;
	int i = 0;
	int sign = 1;

	var = va_arg(ap, int*);
	*var = 0;

	read(fd, buf, 1);
	while (buf && isspace(buf[0]))
		read(fd, buf, 1);
	if(buf[0] == '-')
	{
		sign = -1;
		read(fd, buf, 1);
	}
	while(isdigit(buf[0]))
	{
		*var = 10 * var[0] + buf[0]- '0';
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
	while (buf && isspace(buf[0]))
		read(fd, buf, 1);
	while(buf[0] != '\0' && buf[0] != '\n' && buf[0] != ' ')
	{
		var[i] = buf[0];
		read(fd, buf, 1);
		i++;
	}
	var[i] = '\0';
	
//	printf("var = %s\n", var);

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
			return scan_int(fd, ap);
		case 's' :
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
	va_end(ap);
	return(result);

}

int main(void)
{
	int d;
	char c;
	char c2;
	char s[100];
	int r = 0;

//	write(2, "entrez c : \n", 12);
//	r = scanf("%c", &c);
//	printf("c = %c   r = %d\n", c, r);

//	write(2, "entrez d : \n", 12);
//	r = scanf("%d", &d);
//	printf("d = %d   r = %d\n", d, r);

	write(2, "entrez s : \n", 12);
	r = scanf("%s", s);
	printf("s = %s   r = %d\n", s, r);


//	write(2, "entrez c d s c2 : \n", 19);
//	r = ft_scanf("%c %d %s %c", &c, &d, s, &c2);
//	printf("c = %c   d = %d   s = %s   c2 = %c   r = %d\n", c, d, s, c2, r);

}
