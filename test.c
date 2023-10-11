#include "get_next_line.h"
#include "stdio.h" //to remove
// #include "stdlib.h"
// #include "unistd.h"

#include <fcntl.h>
// #include <stdio.h>
#include <string.h>

int ft_strlen(char *s)
{
	int i;

	i = 0;
	// printf("seg fault somewhere");
	if ( s == NULL ||!s)
		return (0);
	while (s[i] != '\0')
		i++;

	if (s[i] == '\0')
	{
		printf("ended with  null terminator\n");
		return (i - 1);
	}
	return i;
}

void *cutstring(char *str, int i)
{
	char *temp;
	int j;

	j = 0;
	while (str[j] != '\0' && str[j] != '\n')
		j++;

	printf("i:%d, j:%d\n", i, j);
	printf("cutting from:%s\n", str + (j));
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return NULL;
	temp[i] = '\0';
	while ((i) >= 0)
	{
		temp[i] = str[j + i];
		i--;
	}
	free(str);
	printf("temp:%s\n", temp);
	return temp;
}

int ft_findline2(char *str)
{
	int i;
	int j;

	i = 1;
	j = 0; // start from next character

	printf("line2\n");
	// loop until the first breaking point
	while (str[j] != '\0' && str[j] != '\n')
		j++;
	printf("finished first while loop\n");
	
	// if it is a new line and not a null terminator, we continue
	if (str[j] != '\0')
	{
		// continue loop until the next break point
		while (str[j + i] != '\0' && str[j + i] != '\n')
		{	
			i++;
		}
		printf("finished second while loop. Time to check\n");
		printf("important i value: %d", i );
		if (str[j + i] == '\n')
		{
			printf("str:%s\n", str);
			printf("value of i:%d, value of j:%d\n\n", i, j);
			return (i);
		}
		return (-1); //end as we found nul terminator instead
	}
	return (-1); //end as we found nul terminator instead
}

char	*finalcut(char *str)
{
	int i;
	int j;
	char *final;

	i = 0;
	j = 1;
	while (str[i] != '\0' && str[i] != '\n')
		i ++;
	if (str[i] != '\0')
	{
		while (str[i + j] != '\0' && str[i + j] != '\n')
			j ++;
		final = malloc(sizeof(char) * (j + 1));
		final[j ] = '\0';
		while(j)
		{
			final[j] = str[i + j];
			j--;
		}
		free(str);
		return final;
	}
	else 
	{
		return str;
	}
}

// reallocate str size
//  free str before returning so it can be assigned
char *copytostr(char *str, char *buffer, int *bufferi)
{
	char *temp;
	int i;
	int j;

	i = 0;
	j = 0;
	// printf("copytostr\n");
	// printf("str:%s\nbuffer:%s\nbufferi:%d\n", str, buffer, *bufferi);
	if (!str && !buffer)
		return (NULL);
	else
	{
		temp = malloc(sizeof(char) * ((ft_strlen(str) + *bufferi + 1)));
		if (!temp)
		{
			printf("malloc failed at temp [copytostr]\n");
			return (NULL);
		}
		// copy from original str
		printf("str that is buggy:%s\n", str);
		while (str != NULL && str[i] != '\0')
		{
			temp[i] = str[i];
			// printf("temp char:%c\n",  temp[i]);
			i++;
		}
		printf("check i have copied properly\n");
		printf("str:%s\n", str);
		printf("temp :%s\n",  temp);
		
		//copy from buffer
		while (*bufferi > j)
		{
			temp[i + j] = buffer[j];
			printf("copy from buffer:%c\n",  temp[i+j]);
			j++;
		}

		printf("check str vs buffer\n");
		printf("str:%s\n", str);
		printf("buffer:%s\n", buffer);
		printf("temp :%s\n",  temp);
		
		//null terminator
		temp[i + j] = '\0';
		free(str); // impt
		return (temp);
	}
}


char *get_next_line(int fd)
{
	char *buffer;
	char *str;
	int bufferi;

	if (fd < 0)
		return NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return NULL;
	str = NULL;
	// str[0] = '\0';
	while ((bufferi = read(fd, buffer, BUFFER_SIZE)) >= 0)
	{
		printf("\n\n\nbuffer content:\n%s\n;\n", buffer);
		str = copytostr(str, buffer, &bufferi);

		// only returns if i get '\n'
		if (ft_findline2(str) != -1)
		{
			printf("found and break\n\n");
			free(buffer);
			return (cutstring(str, ft_findline2(str)));
		}
	}

	printf("breaked out of loop; str:%s\n buffer:%s\n;", str, buffer);
	
	if (str != NULL)
	{
		printf("buffer have been copied");
		free(buffer); // error?
		printf("to cut the string seperatrely");
		return (finalcut(str));
		// return (str);
	}
	else if ( bufferi < 0)
	{
		free(buffer); // free memory?
		return (str); // returned null
	}
	// else if ()
	// {
	// 	free(buffer);
	// 	return str;
	// }
	else
		return str;
}

int main(void)
{
  // Create a temporary file and write test content to it.
  char test_content[] = "0123456789\n9876543210\nE";
						// "0123456789012345678901234567890123456789\n";
						// "01234567890123456789012345678901234567890\n";
						// "ghg"
						// "\0"
						// "wow";
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
	line = get_next_line(fd);
	printf("\nthe result:%s;", line);
	free(line);
	// while ((line = get_next_line(fd)) != NULL) {
	//     printf("Read line: %s\n", line);
	//     free(line);  // Don't forget to free the memory after using the line
	// }

	close(fd);

	// Optionally, remove the temporary file after testing.
	remove("temp_test.txt");

	return 0;
}
