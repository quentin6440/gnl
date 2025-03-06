#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		line_len(char *str);
void	buff_shift(char *buff, size_t	size);
char	*str_append(char *dst, char *src);
char	*get_next_line(int fd);

#endif
