#include "get_next_line.h"

int	line_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	buff_shift(char *buff, size_t size)
{
	int	i;

	i = 0;
	while (buff[size])
		buff[i++] = buff[size++];
	while (i < BUFFER_SIZE)
		buff[i++] = 0;
}

char	*str_append(char *stash, char *buff)
{
	char	*line;
	int	i;
	int	j;

	i = 0;
	j = 0;
	line = malloc(line_len(stash) + line_len(buff) + 2);
	if (!line)
		return (NULL);
	while (stash && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	while (buff[j] && buff[j - 1] != '\n')
		line[i++] = buff[j++];
	line[i] = 0;
	buff_shift(buff, j);
	free(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[FOPEN_MAX][BUFFER_SIZE + 1];
	char	*line;
	int	len_read;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	if (buff[fd][0])
		len_read = 1;
	else
		len_read = read(fd, buff[fd], BUFFER_SIZE);
	while (len_read > 0)
	{
		line = str_append(line, buff[fd]);
		if (!line)
			return (NULL);
		if (line[line_len(line)] == '\n')
			return (line);
		len_read = read(fd, buff[fd], BUFFER_SIZE);
	}
	if (len_read < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
