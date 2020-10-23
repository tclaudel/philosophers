#include "../includes/philosophers.h"

void	display_status(const int i, t_status status)
{
	char				output[200];
	static char			*messages[6] = {"has taken a fork\n", "is eating\n",
							"is sleeping\n", "is thinking\n", "died\n",
							"is satiated\n"};
	static const int	msg_len[6] = {18, 11, 13, 13, 6, 13};
	char				*tmp;
	size_t				len;

	memset(output, 0, 200);
	tmp = ft_itoa_ll_base(get_ms() - g_rules.start, "0123456789");
	len = ft_strlcat(output, tmp, 18);
	len = ft_strlcat(output, " ", 200 - len);
	len = ft_strlcat(output, ft_itoa_ll_base(i + 1, "0123456789"), 200 - len);
	len = ft_strlcat(output, " ", 200 - len);
	len = ft_strlcat(output, messages[status], msg_len[status] + len);
	sem_wait(g_write);
	if (g_died == 0)
		write(1, output, len);
	sem_post(g_write);
}
