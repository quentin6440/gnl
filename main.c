#include "get_next_line.h"

int	main(void)
{
	char *file_path = "./hello.txt";
	int fd = open(file_path, O_RDONLY);

	if (fd < 0)
		return(write(1, "error opening file", 18));

	char	*output;
	while ((output = get_next_line(fd)) != 0)
	{
		write(1, output, line_len(output));
		write(1, "\n", 1);
		free (output);
	}

	close (fd);	
	return (0);
}
