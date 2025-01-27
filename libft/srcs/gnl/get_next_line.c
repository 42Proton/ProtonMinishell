/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 08:41:16 by amsaleh           #+#    #+#             */
/*   Updated: 2024/12/20 16:05:47 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	gnl_newline(char *read_buf, char **res, char **buffer)
{
	char	*temp;
	ssize_t	i_newline;

	i_newline = find_newline(read_buf);
	if (i_newline == -1)
		return (0);
	temp = malloc(i_newline + 2);
	if (!temp)
		return (-1);
	ft_strncpy(temp, read_buf, i_newline + 1);
	if (ft_strlen(read_buf + i_newline + 1) > 0)
	{
		*buffer = malloc(ft_strlen(read_buf + i_newline + 1) + 1);
		if (!*buffer)
			free(temp);
		if (!*buffer)
			return (-1);
		ft_strncpy(*buffer, read_buf + i_newline + 1,
			ft_strlen(read_buf + i_newline + 1));
	}
	*res = gnl_strjoin(*res, temp, 2);
	if (!*res)
		return (-1);
	return (1);
}

ssize_t	gnl_read(int fd, char **res, char **buffer)
{
	ssize_t	read_bytes;
	char	*read_buf;
	int		ret;

	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (0);
	read_bytes = read(fd, read_buf, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		read_buf[read_bytes] = 0;
		ret = gnl_newline(read_buf, res, buffer);
		if (ret == -1 || ret == 1)
			free(read_buf);
		if (ret == -1 || ret == 1)
			return (ret);
		*res = gnl_strjoin(*res, read_buf, 1);
		if (!*res)
			free(read_buf);
		if (!*res)
			return (0);
		read_bytes = read(fd, read_buf, BUFFER_SIZE);
	}
	free(read_buf);
	return (read_bytes + 1);
}

void	gnl_recover_buffer(char **res, char **buffer)
{
	ssize_t	newline_i;
	size_t	res_size;
	int		is_newline;

	is_newline = 0;
	newline_i = find_newline(*buffer);
	if (newline_i != -1)
		is_newline = 1;
	if (is_newline)
		res_size = newline_i + 1;
	else
		res_size = ft_strlen(*buffer);
	*res = malloc(res_size + 1);
	if (!*res)
		return ;
	ft_strncpy(*res, *buffer, res_size);
	if (is_newline)
		ft_strncpy(*buffer, *buffer + newline_i + 1,
			ft_strlen(*buffer + newline_i + 1));
	else
	{
		free(*buffer);
		*buffer = 0;
	}
}

int	pre_gnl(char **res, char **buffer)
{
	if (*buffer)
	{
		gnl_recover_buffer(res, buffer);
		if (!*res)
			return (0);
		if (*buffer && !**buffer)
		{
			free(*buffer);
			*buffer = 0;
		}
		return (1);
	}
	*res = malloc(1);
	if (!*res)
		return (0);
	**res = 0;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;
	int			ret_code;

	if (fd < 0 || BUFFER_SIZE <= 0 || !pre_gnl(&res, &buffer))
	{
		free(buffer);
		buffer = 0;
		return (0);
	}
	if (*res && res[ft_strlen(res) - 1] == '\n')
		return (res);
	ret_code = gnl_read(fd, &res, &buffer);
	if (!ret_code || ret_code == -1 || !*res)
	{
		free(buffer);
		buffer = 0;
		free(res);
		return (0);
	}
	return (res);
}
