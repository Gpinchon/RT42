# include <internal_framework.h>
#define __HALF_MAX_SIGNED(type) ((type)1 << (sizeof(type)*8-2))
#define __MAX_SIGNED(type) (__HALF_MAX_SIGNED(type) - 1 + __HALF_MAX_SIGNED(type))
#define __MIN_SIGNED(type) (-1 - __MAX_SIGNED(type))

#define __MIN(type) ((type)-1 < 1?__MIN_SIGNED(type):(type)0)
#define __MAX(type) ((type)~__MIN(type))

static size_t	int_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

static void		int_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void		int_putnbr_recursif(int n, int fd)
{
	if (n > 9)
		int_putnbr_recursif(n / 10, fd);
	int_putchar_fd('0' + (n % 10), fd);
}

void		int_putstr_fd(char const *str, int fd)
{
	write(fd, str, int_strlen(str));
}

void			int_putnbr_fd(int n, int fd)
{
	if (n == __MAX(int))
	{
		int_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		int_putchar_fd('-', fd);
		n = -n;
	}
	int_putnbr_recursif(n, fd);
}

void		int_putendl_fd(char const *s, int fd)
{
	int_putstr_fd((char *)s, fd);
	int_putchar_fd('\n', fd);
}