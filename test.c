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
	// printf("seg fault somewhere");
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
void	*cutstring(char *str, int i)
{
	char	*temp;

	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return NULL;
	temp[i] = '\0';
	while(i >= 0)
	{
		temp[i] = str[i];
		i--;
	}
	free(str);
	return temp;
}
int ft_findline2(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] != '\0' && str[j] != '\n')
		j++;
	while (str[j + i] != '\0')
	{
		if (str[j + i] == '\n')
			return (j+i);
		i++;
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
		// printf("looping: %s\n", str);
		//free(buffer);
	}

	// printf("break out of while loop\n");
	// printf("check str content:%s\n", str);
	if (str != NULL)
	{
		// printf("return str\n");
		free(buffer); //error?
		return (str);
	}
	else if (!bufferi || bufferi < 0)
	{
		free(buffer);
		return str;
	}
	else
		return NULL;
}


// #include <fcntl.h> //to remove

// int main(void)
// {
//     int fd = open("test.txt", O_RDONLY);
// 	printf("result:%s", get_next_line(fd));
//     close(fd);
//     return (0);
// }


#include <fcntl.h> //to remove

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
	printf("result:%s:smth else", get_next_line(fd));
    close(fd);
    return (0);
}
