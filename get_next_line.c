#include "stdio.h" //to remove
#include "stdlib.h"
#include "unistd.h"
#include "get_next_line.h"
#include "stdio.h" //to remove
#include "stdlib.h"
#include "unistd.h"
#include "get_next_line.h"


#include "stdio.h" //to remove
#include "stdlib.h"
#include "unistd.h"
#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*cutstring(char *str, int i)
{
	char	*temp;
	int		j;

	j = 0;
	while (str[j] != '\0' && str[j] != '\n')
		j++;
		
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return NULL;
	temp[i] = '\0';
	while(i >= 0)
	{
		temp[i] = str[j + i];
		i--;
	}
	free(str);
	// printf("temp:%s\n", temp);
	return temp;
}

int ft_findline2(char *str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[j] != '\0' && str[j] != '\n')
		j++;

	// if it is a new line and not a null terminator
	if (str[j] != '\0')
	{
		// continue loop until the next break point
		while (str[j + i] != '\0' || str[j + i] != '\n')
		{
			if (str[j + i] == '\n' || str[j + i] == '\0')
			{
				return (i);
			}
			i++;
		}
	}
return (-1);
}

//reallocate str size
// free str before returning so it can be assigned
char	*copytostr(char *str, char *buffer, int *bufferi)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// printf("copytostr\n");
	// printf("str:%s\nbuffer:%s\nbufferi:%d\n", str, buffer, *bufferi);
	if (!str && !buffer)
		return (NULL);
	else
	{
		// str[*bufferi + 1] = '\0';
		temp = malloc(sizeof(char) * ((ft_strlen(str) + *bufferi + 1)));
		if (!temp)
			return (NULL);
		while (str != NULL && str[i] != '\0')
		{
			// printf("i:%d, c:%c\n", i, str[i]);
			temp[i] = str[i];	
			i++;
		}
		while(*bufferi > j)
		{
			temp[i + j] = buffer[j];
			j++;
		}
		temp[i + j] = '\0';
		// printf("copy to str: %s\n", temp);
		free(str); //impt
		return (temp);
	}
}

char *get_next_line(int fd)
{
	char	*buffer;
	char	*str;
	int		bufferi;

	if (!fd || fd < 0)
		return NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	str = NULL;
	if (!buffer)
		return NULL;
	// str[0] = '\0';
	while ((bufferi = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		str = copytostr(str, buffer, &bufferi);
		if (ft_findline2(str) != -1)
		{	
			free(buffer);
			return (cutstring(str, ft_findline2(str)));
		}
	}

	if (str != NULL || !bufferi || bufferi < 0)
	{
		free(buffer); //error?
		return (str);
	}
	// else if ()
	// {
	// 	free(buffer);
	// 	return str;
	// }
	else
		return str;
}


// #include <fcntl.h> //to remove

// int main(void)
// {
//     int fd = open("test.txt", O_RDONLY);
// 	printf("result:%s", get_next_line(fd));
//     close(fd);
//     return (0);
// }


