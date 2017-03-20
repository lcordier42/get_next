/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcordier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 10:32:03 by lcordier          #+#    #+#             */
/*   Updated: 2016/12/21 10:33:55 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_putline(char *reste, int n)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(tmp = ft_strnew(n)))
		return (NULL);
	while (i < n)
	{
		tmp[i] = reste[i];
		i++;
	}
	reste = NULL;
	return (tmp);
}

static	int		ft_checkndl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

static	char	*ft_reallocreste(char *reste, int j)
{
	char	*tmp;
	int		i;
	int		n;

	n = 0;
	i = ft_strlen(reste);
	if (!(tmp = ft_strnew(i + j)))
		return (NULL);
	while (n < i + 1)
	{
		tmp[n] = reste[n];
		n++;
	}
	tmp[n] = '\0';
	free(reste);
	reste = NULL;
	return (tmp);
}

static	int		ft_filling(char **line, char **reste, int ret)
{
	int		i;
	char	*tmp;
	int		n;

	if (*reste)
		n = ft_strlen(*reste);
	if ((i = ft_checkndl(*reste)) != -1)
	{
		tmp = ft_strdup(*reste);
		free(*reste);
		*reste = ft_strsub(tmp, i + 1, n);
		*line = ft_putline(tmp, i);
		free(tmp);
		return (1);
	}
	else if (ret == 0 && n > 0 && *reste != NULL)
	{
		*line = ft_putline(*reste, n);
		free(*reste);
		*reste = NULL;
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static	char	*reste;
	int				ret;
	char			*buff;

	ret = 1;
	if (fd < 0)
		return (-1);
	if (!reste)
		reste = ft_strnew(BUFF_SIZE);
	else if (ft_filling(line, &reste, ret) == 1)
		return (1);
	while (ret > 0)
	{
		buff = (ft_strnew(BUFF_SIZE));
		if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		reste = ft_reallocreste(reste, ret);
		ft_strncat(reste, buff, ret);
		free(buff);
		if (ft_checkndl(reste) != -1)
			break ;
	}
	if (ft_filling(line, &reste, ret) == 1)
		return (1);
	return (0);
}
