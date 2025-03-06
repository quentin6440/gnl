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

char	*str_append(char *old_line, char *buff)
{
	char	*new_line;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_line = malloc(line_len(old_line) + line_len(buff) + 2);
	if (!new_line)
		return (NULL);
	while (old_line && old_line[i])
	{
		new_line[i] = old_line[i];
		i++;
	}
	while (buff[j] && buff[j - 1] != '\n')
		new_line[i++] = buff[j++];
	new_line[i] = 0;
	buff_shift(buff, j);
	free(old_line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	buff[FOPEN_MAX][BUFFER_SIZE + 1];
	char	*line;
	int	c_read;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	if (buff[fd][0])
		c_read = 1;
	else
		c_read = read(fd, buff[fd], BUFFER_SIZE);
	while (c_read > 0)
	{
		line = str_append(line, buff[fd]);
		if (!line)
			return (NULL);
		if (line[line_len(line)] == '\n')
			return (line);
		c_read = read(fd, buff[fd], BUFFER_SIZE);
	}
	if (c_read < 0)
		return (free(line), NULL);
	return (line);
}
