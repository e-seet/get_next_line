// #include "stdio.h" //to remove
// #include "stdlib.h"
// #include "unistd.h"
// #include "get_next_line.h"

// int	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);

// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }
// void	*cutstring(char *str, int i)
// {
// 	char	*temp;

// 	temp = malloc(sizeof(char) * (i + 1));
// 	if (!temp)
// 		return NULL;
// 	temp[i] = '\0';
// 	while(i >= 0)
// 	{
// 		temp[i] = str[i];
// 		i--;
// 	}
// 	free(str);
// 	return temp;
// }
// int ft_findline2(char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[j] != '\0' && str[j] != '\n')
// 		j++;
// 	while (str[j + i] != '\0')
// 	{
// 		if (str[j + i] == '\n')
// 		return (j+i);
// 		i++;
// 	}
// 	return (-1);
// }

// //reallocate str size
// // free str before returning so it can be assigned
// char	*copytostr(char *str, char *buffer, int *bufferi)
// {
// 	char	*temp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	// printf("copytostr\n");
// 	// printf("str:%s\nbuffer:%s\nbufferi:%d\n", str, buffer, *bufferi);
// 	if (!str && !buffer)
// 		return (NULL);
// 	else
// 	{
// 		// str[*bufferi + 1] = '\0';
// 		temp = malloc(sizeof(char) * ((ft_strlen(str) + *bufferi + 1)));
// 		if (!temp)
// 			return (NULL);
// 		while (str != NULL && str[i] != '\0')
// 		{
// 			// printf("i:%d, c:%c\n", i, str[i]);
// 			temp[i] = str[i];	
// 			i++;
// 		}
// 		while(*bufferi > j)
// 		{
// 			temp[i + j] = buffer[j];
// 			j++;
// 		}
// 		temp[i + j] = '\0';
// 		// printf("copy to str: %s\n", temp);
// 		free(str); //impt
// 		return (temp);
// 	}
// }

// char *get_next_line(int fd)
// {
// 	char	*buffer;
// 	char	*str;
// 	int		bufferi;

// 	if (!fd || fd < 0)
// 		return NULL;
// 	buffer = malloc(sizeof(char) * BUFFER_SIZE);
// 	str = NULL;
// 	if (!buffer)
// 		return NULL;
// 	// str[0] = '\0';
// 	while ((bufferi = read(fd, buffer, BUFFER_SIZE)) > 0)
// 	{
// 		str = copytostr(str, buffer, &bufferi);
// 		if (ft_findline2(str) != -1)
// 		{	
// 			free(buffer);
// 			return (cutstring(str, ft_findline2(str)));
// 		}
// 	// printf("looping: %s\n", str);
// 	//free(buffer);
// 	}

// 	if (str != NULL || !bufferi || bufferi < 0)
// 	{
// 		free(buffer); //error?
// 		return (str);
// 	}
// 	// else if ()
// 	// {
// 	// 	free(buffer);
// 	// 	return str;
// 	// }
// 	else
// 		return str;
// }


// // #include <fcntl.h> //to remove

// // int main(void)
// // {
// //     int fd = open("test.txt", O_RDONLY);
// // 	printf("result:%s", get_next_line(fd));
// //     close(fd);
// //     return (0);
// // }

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

char	*copytostr(char *str, char *buffer, int *bufferi)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str && !buffer)
		return (NULL);
	else
	{
		temp = malloc(sizeof(char) * ((ft_strlen(str) + *bufferi + 1)));
		if (!temp)
			return (NULL);
		while (str != NULL && str[i] != '\0')
		{
			temp[i] = str[i];	
			i++;
		}
		while(*bufferi > j)
		{
			temp[i + j] = buffer[j];
			j++;
		}
		temp[i + j] = '\0';
		free(str); //impt
		return (temp);
	}
}

char *get_next_line(int fd)
{
	char	*buffer;
	static char	*str;
	int		bufferi;

	if (!fd || fd < 0)
		return NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	str = NULL;
	if (!buffer)
		return NULL;
	while ((bufferi = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		str = copytostr(str, buffer, &bufferi);
		if (ft_findline2(str) != -1)
		{	
			free(buffer);
			return (cutstring(str, ft_findline2(str)));
		}
	}

	if (str != NULL )
	{
		free(buffer); //error?
		return (str);
	}
	else if (!bufferi || bufferi < 0)
	{
		free(buffer); //error?
		return (str);
	}
	else
		return str;
}

/*
#include <fcntl.h> //to remove
int main(void)
{
  // Create a temporary file and write test content to it.
  char test_content[] = 
  
  						// "9876543210\n0123456789\nE";
						// "0123456789012345678901234567890123456789\n";
						// "\n"
						// "\n1"
						// "\n2"
						// "\n3"
						"0123456789012345678901234567890123456789x2\n"
						"0123456789012345678901234567890123456789x3\n"
						"\n"
						"0123456789012345678901234567890123456789x5\n"
						;
						
	FILE *temp = fopen("temp_test.txt", "w+");
	if (!temp)
	{
		perror("Error creating temporary file");
		return 1;
	}
	fwrite(test_content, sizeof(char), sizeof(test_content) - 1, temp);
	fclose(temp);

	// Open the temporary file to read with get_next_line.
	int fd = open("temp_test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening the temporary file");
		return 1;
	}

	char *line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("\nthe result:%s;\n", line);
		free(line);
	}
	close(fd);
	// Optionally, remove the temporary file after testing.
	remove("temp_test.txt");

	return 0;
}
*/



