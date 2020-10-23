#include "../includes/philosophers.h"

size_t		ft_strlcat(char *dest, const char *src, size_t count)
{
	size_t i;
	size_t y;
	size_t sizea;
	size_t sizeb;

	sizea = 0;
	sizeb = 0;
	while (dest[sizea] != '\0')
		sizea++;
	while (src[sizeb] != '\0')
		sizeb++;
	if (count <= sizea)
		return (sizeb + count);
	i = 0;
	while (dest[i] != '\0' && i < count - 1)
		i++;
	y = 0;
	while (src[y] != '\0' && count - 1 > i)
	{
		dest[i] = src[y];
		i++;
		y++;
	}
	dest[i] = '\0';
	return (sizea + sizeb);
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int			ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int			ft_atoi(const char *nptr)
{
	int		i;
	int		nb;
	int		sign;

	i = 0;
	nb = 0;
	sign = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = 1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb *= 10;
		nb += nptr[i] - '0';
		i++;
	}
	return (sign ? -nb : nb);
}

char		*ft_itoa_ll_base(unsigned long n, char *base)
{
	static char	buf[18] = {0};
	int			i;
	int			lbase;

	lbase = ft_strlen(base);
	i = 16;
	while (1)
	{
		buf[i--] = base[n % lbase];
		n /= lbase;
		if (n == 0)
			break ;
	}
	return (buf + 1 + i);
}
