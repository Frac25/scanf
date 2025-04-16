#include<stdlib.h>

// autorise : isspace isigit fgetc ungetc ferror feof stdin va_list va_arg va_start va_end va_copy

void    skip_input_space(void)
{

}

int scan_int(fd, ap)
{

    return(1);
}

int scan_char(fd, ap)
{

    return(1);
}

int scan_string(fd, ap)
{

    return(1);
}



int receiv_input(const char format, va_list ap)
{
    switch(format)
    {
        case 'c' :
            return scan_char(fd, ap);
        case 'd':
            skip_input_space();
            return scan_int(fd, ap);
        case 's' :
            skip_input_space();
            return scan_string(fd, ap);
    }
}

int ft_scanf(const char *format, ...)
{
    int i;
    int result;

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

}

