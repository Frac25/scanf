#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>

int	check_free_all(char **s, size_t size)
{
	if (s[size] == NULL)
	{
		while (size > 0)
			free(s[--size]);
		free (s);
		return (0);
	}
	return (1);
}

void	*ft_malcol(const char *s, char c)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	p = malloc(sizeof(char *) * (j + 1));
	if (p == NULL)
		return (NULL);
	return (p);
}

void	*ft_mallin(const char *s, size_t end)
{
	size_t	i;
	char	*p;

	i = 0;
	p = malloc(sizeof(char) * (end + 1));
	if (p == NULL)
		return (NULL);
	while (i < end)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;

	tab = ft_malcol(s, c);
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (i > 0)
			tab[j] = ft_mallin(s, i);
		if (i > 0)
			if (check_free_all(tab, j++) == 0)
				return (NULL);
		s = s + i;
	}
	tab[j] = NULL;
	return (tab);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	a;

	s = 1;
	a = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + str[i] - 48;
		i++;
	}
	return (s * a);
}

int	ft_strcmp_10(char *s1, char *s2)
{
	if (s1 && s2 && s1[0] == s2[0] && s1[1] == '\0')
		return (0);
	return (-1);
}

int ft_scanf(const char *format, ...)
{
	va_list args;
	char sep = '%';
	char buf[100];
	int nb_read;
	char **buf2;
	char **format2;
	int i;
	int j;

	va_start(args, format);

	nb_read = read(0, buf, 10);
//	printf("nb_read = %d\n", nb_read);
//	printf("format = %s\n", format);
	buf[nb_read] = '\0';
//	printf("buf = %s\n", buf);

	buf2 = ft_split(buf, ' ');
	format2 = ft_split(format, sep);

/*	j = 0;
	while (buf2[j])
	{
		printf("buf2[%d] = %s\n", j, buf2[j]);
		j++;
	}

	while (format2[j])
	{
		printf("format2[%d] = %s\n", j, format2[j]);
		j++;
	}*/
	
	i == 0;
	while(buf2[i])
	{
//		printf("i = %d\n", i);	
		if(format2[i][0] == 'd')
		{
//			printf("passe i\n");
			int *val;
			val = va_arg(args, int*);
			val[0] = ft_atoi(buf2[i]);
		}
		else if(format2[i][0] == 'c')
		{
//			printf("passe c\n");
			char *val;
			val = va_arg(args, char*);
			val[0] = buf2[i][0];
		}
		else if(format2[i][0] == 's')
		{
//			printf("passe s\n");
			char *val;
			val = va_arg(args, char*);
			j = 0;
			while(buf2[i][j])
			{
				val[j] = buf2[i][j];
				j++;
			}
			val[j] = '\0';
		}
		i++;
	}
//	free2(buf2);
//	free2(format2);
	va_end(args);
}

int main()
{
	int i;
	char c;
	char s[100];

	printf("i c s ?\n");
	scanf("%d %c %s", &i, &c, s);
	//ft_scanf("%d%c%s", &i, &c, s);
	printf("i = %d\n", i);
	printf("c = %c\n", c);
	printf("c = %s\n", s);

	return(0);
}

//sed -E "s/$(echo "$1" | sed 's/\([][(){}\^.*+?$\]\)/\\\1/g')/$(echo "$1" (sed - E 's/./*/g')/g"