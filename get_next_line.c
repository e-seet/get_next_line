
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

char *returnline(char *str)
{
	int i;
	int len;
	char *line;

	i = 0;
	len = ft_strlen(str);
	line = malloc(sizeof(char) * (len + 1));
	while(str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	free(str); // why i cannot free here
	str = NULL;
	return line;
}

char *cutstringhelper(char *str, int j)
{
	int newlen;
	newlen = ft_strlen(str) - (j+1); //may have fault
	
	char *newstr;
	newstr = malloc(sizeof(char) * newlen);
	int k;
	k = 0;
	while(str[j] != '\0')
	{
		newstr[k] = str[j];
		k++;
		j++;
	}
	free(str);

	printf("check my leftover:%s\n", newstr);
	return newstr;
}

//need to change this
void	*cutstring(char *str, int i)
{
	char	*temp;
	int j;
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return NULL;

	printf("cutstring\n");
	printf("check the i value:%d\n", i);	
	j = 0;
	while (str[j] != '\n')
	{
		temp[j] = str[j];
		j++;
	}
	temp[j] = '\0';
	// while(i > j )
	// {
	// 	j++;
	// }
	

	// free(newstr);
	return temp;
}

int ft_findline2(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("findline2\n");
	
	// printf("check the str:%s\n", str);
	while (str[j] != '\0' && str[j] != '\n')
		j++;
	if (str[j] == '\n' && j != 0)
	{
		// printf("found\n");
		return (j + 1);
	}
	printf("is it a char:%c\n",str[j]);
	printf("value of j:%d\n", j);
	printf("end of findline2\n");
	// while (str[j + i] != '\0')
	// {
	// 	if (str[j + i] == '\n')
	// 		return (j+i);
	// 	i++;
	// }
	return (-1);
}

char	*copytostr(char *str, char *buffer, int *bufferi)
{
	char	*temp;
	int		i;
	int		j;

	printf("copytostr\n");
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

		printf("str:%s;\n", str);
		printf("buffer:%s;\n", buffer);
		printf("temp[new str]:%s;\n", temp);

		free(str); //impt
		return (temp);
	}
}

char *get_next_line(int fd)
{
	char	*buffer;
	static char	*str;
	int		bufferi;
	char *line;

	printf("\n\nget next line\n\n");
	if (!fd || fd < 0)
		return NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return NULL;
	while ((bufferi = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		str = copytostr(str, buffer, &bufferi);

		if (ft_findline2(str) != -1)
		{	
			free(buffer);
			line = cutstring(str, ft_findline2(str)); // returns the line
			str = cutstringhelper(str, ft_findline2(str));
			printf("before returning check str2: %s\n", str);
			printf("before returning check line: %s\n", line);
			return line;
		}
	}

	if (str != NULL )
	{
		free(buffer); //error?
		printf("if");
		return str;
		// line = returnline(str);
		// return (line);
	}
	else if (!bufferi || bufferi < 0)
	{
		free(buffer); //error?
		printf("else if");
		// line = returnline(str);
		// return (line);
		return str;
	}
	else
	{
		printf("else");
		return str;
	}
}


#include <fcntl.h> //to remove
int main(void)
{
  // Create a temporary file and write test content to it.
  char test_content[] = 
  
						"0123456789012345678901234567890123456789x0\n"
						"0123456789012345678901234567890123456789x1\n"
						"0123456789012345678901234567890123456789x2\n"
						// "0123456789012345678901234567890123456789x3\n"
						// "0123456789012345678901234567890123456789x4\n"
						// "0123456789012345678901234567890123456789x5\n"
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

	int i = 0;
	char *line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("\n\n\nthe result %d:%s;\n", i,line);
		free(line);
		i ++;
	}
	close(fd);
	// Optionally, remove the temporary file after testing.
	remove("temp_test.txt");

	return 0;
}


