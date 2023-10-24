#include "stdio.h"
#include "stddef.h"
#include "stdlib.h"
#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *str, char *buffer, int bufferi)
{
	int		strlen;
	int		i;
	char	*newstr;
	int		j;

	i = 0;
	strlen = ft_strlen(str);
	newstr = malloc(sizeof(char) * (strlen + bufferi + 1));
	if (!newstr)
		return (NULL);
	while (str[i] != '\0')
	{
		newstr[i] = str[i];
		i++;
	}
	j = 0;
	while (bufferi > j)
	{
		newstr[i + j] = buffer[j];
		j++;
	}
	newstr[i + j] = '\0';
	free(str);
	return (newstr);
}

int	ft_findline2(char *str)
{
	int	j;

	j = 0;
	while (str[j] != '\0' && str[j] != '\n')
		j++;
	if (str[j] == '\n')
	{
		return (j + 1);
	}
	else
	{
		return (-1);
	}
}

char	*ft_processstr(char *str, int len)
{
	int		newlen;
	char	*newstr;
	int		j;

	if (len == -1)
		len = ft_strlen(str);
	j = 0;
	newlen = ft_strlen(str) - len;
	newstr = malloc(sizeof(char) * (newlen + 1));
	if (!newstr)
		return (NULL);
	while (str[len + j] != '\0')
	{
		newstr[j] = str[len + j];
		j++;
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

char	*ft_read_and_join(char *str, int fd, int *bufferi)
{
	char	*buffer;
	int		linelen;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while ((*bufferi = (read(fd, buffer, BUFFER_SIZE))) > 0)
	{
		str = ft_strjoin(str, buffer, *bufferi);
		linelen = ft_findline2(str);
		if (linelen != -1)
			break ;
	}
	free(buffer);
	return (str);
}

char	*ft_processline(char *str, char *line, int len)
{
	int		i;

	if (len == -1)
		len = ft_strlen(str);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (len > i)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

// char *processresult(char *str, char *line, int bufferi)
// {
// 	if (str[0] == '\0' || bufferi == -1)
// 	{
// 		free(str);
// 		str = NULL;
// 		return (str);
// 	}
// 	else if (str[0] != '\0')
// 	{
// 		line = ft_processline(str, line, ft_findline2(str));
// 		str = ft_processstr(str, ft_findline2(str));
// 		return (line);
// 	}
// 	else
// 		return (NULL);
// }

char	*get_next_line(int fd)
{
	static char	*str;
	int			bufferi;
	char	 	*line;
	
	line = NULL;
	if (fd < 0)
		return (NULL);
	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	str = ft_read_and_join(str, fd, &bufferi);
	if (str[0] == '\0' || bufferi == -1)
	{
		free(str);
		str = NULL;
		return (str);
	}
	else if (str[0] != '\0')
	{
		line = ft_processline(str, line, ft_findline2(str));
		str = ft_processstr(str, ft_findline2(str));
		return (line);
	}
	else
		return (NULL);
}

//https://chat.openai.com/c/0399d682-eadd-4c96-a9a8-c98257feb72b 
// #include <fcntl.h> //to remove
// int main(void)
// {
//   // Create a temporary file and write test content to it.
//   char test_content[] = 
// 						// "0123456789012345678901234567890123456789x0\n"
// 						// "0123456789012345678901234567890123456789x1\n"
// 						// "0123456789012345678901234567890123456789x2\n"
// 						// "0123456789012345678901234567890123456789x3\n"
// 						// "0123456789012345678901234567890123456789x4\n"
// 						// "0123456789012345678901234567890123456789x5\n"

// 						// "\n"
// 						// "\n"
// 						// "\n"

// 							"0123456789\n"
// 							"012345678\n"
// 							"90123456789\n" //here ownwards weird
// 							"0123456789\n"
// 							"xxxx\n"
// 						;
// 	FILE *temp = fopen("temp_test.txt", "w+");
// 	if (!temp)
// 	{
// 		perror("Error creating temporary file");
// 		return 1;
// 	}
// 	fwrite(test_content, sizeof(char), sizeof(test_content) - 1, temp);
// 	fclose(temp);
// 	// Open the temporary file to read with get_next_line.
// 	int fd = open("temp_test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening the temporary file");
// 		return 1;
// 	}
// 	int i = 0;
// 	char *line = NULL;
// 	// line = get_next_line(fd);
// 	// printf("res:%s;\n",line);
// 	while ( (line = get_next_line(fd)) != NULL)
// 	{
// 		if (line[0] == '\0')
// 		{
// 			free(line);
// 			break;
// 		}
// 		printf("res%d:%s;\n",i ,line);
// 		free(line);
// 		i ++;
// 	}
// 	close(fd);
// 	// Optionally, remove the temporary file after testing.
// 	remove("temp_test.txt");
// 	return 0;
// }
