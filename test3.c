#include "get_next_line.h"
#include "stdio.h" //to remove

#include <fcntl.h>
#include <string.h>

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if ( s == NULL ||!s)
		return (0);
	while (s[i] != '\0')
		i++;

	return i;
}

// int copyover(char *str, char *temp)
// {
// 	int i;

// 	i = 0;
// 	while(str[i] != '\0')
// 	{
// 		temp[i] = str[i];
// 		printf("str[%d]:%c, str[%d]: %c\n", i, str[i], i , temp[i]);
// 		i++;
// 	}
// 	temp[i] = '\0';
// 	printf("check i have copied properly\n");
// 	printf("str:%s\n", str);
// 	printf("temp :%s\n",  temp);
// 	return i;
// }

// void printstrchar(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		printf("str[%d]:%c\n", i,str[i]);
// 		i++;
// 		if (i > 20)
// 			return;
// 	}
	
// }

char *cutstring(char *str, int i)
{
	char *temp;
	int j;

	j = 0;
	while (str[j] != '\0' && str[j] != '\n')
		j++;

	// printf("i:%d, j:%d\n", i, j);
	// printf("cutting from:%s\n", str + (j));
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
	// printf("temp:%s\n", temp);
	return temp;
}

int ft_findline2(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0; // start from next character

	printf("line2\n");
	// loop until the first breaking point
	while (str[j] != '\0' && str[j] != '\n')
		j++;
	printf("finished first while loop\n");
	// if it is a new line and not a null terminator, we continue
	if (str[j] != '\0')
	{
		j = j + 1;
		printf("value of j:%d\n", j);
		// continue loop until the next break point
		while (str[j + i] != '\0' && str[j + i] != '\n')
		{	
			i++;
		}
		printf("finished second while loop. Time to check\n");
		printf("important i value: %d | str:%s", i, str +j );
		if (str[j + i] == '\n')
		{
			// printf("str:%s\n", str);
			printf("value of i:%d, value of j:%d\n\n", i, j);
			return (i);
		}
		return (-1); //end as we found nul terminator instead
	}
	return (-1); //end as we found nul terminator instead
}

char	*finalcut(char *str)
{
	printf("finalcut\n");

	int i;
	int j;
	int k;
	char *final;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i ++;
	if (str[i] != '\0')
	{
		i++;
		while (str[i + j] != '\0' && str[i + j] != '\n')
			j ++;
		printf("char:%c", str[i + j-1]);
		printf("chars:%s", str);
		final = malloc(sizeof(char) * (j + 1));
		while(j>k)
		{
			final[k] = str[i + k];
			k++;
		}
		final[k] = '\0';
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
	printf("copy to str\n");
	char *temp;
	int i;
	int j;
	int breaker;

	i = 0;
	j = 0;
	breaker = 0;
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
		printf("str size:%d\n", (ft_strlen(str) + *bufferi + 1));
		printf("\nsize allocated for temp:%d\n", ft_strlen(str) + *bufferi + 1 );
		// copy from original str
		// printf("bugger\n");
		//smth wrong here as well
		if (str != NULL)
		{
			// printf("what is str:%s\n\n", str);
			// printstrchar(str);
			while (str[i] != '\0')
			{
				printf("str:%c", str[i]); //1 
				printf("str:%s", str); // 0123456789
				temp[i] = str[i];
				// printf("temp char:%c\n",  temp[i]);
				i++;
			}
			temp[i] = '\0';
			// i = copyover(str, temp);
		}	

		// if (str != NULL)
		// {
		// 	while (str[i] != '\0')
		// 	{
		// 		if ( breaker == 20)
		// 			break;
		// 		printf("strCh:%c\n", str[i]); //1 
		// 		// printf("str:%s\n", str); // 0123456789
		// 		temp[i] = str[i];
		// 		// printf("temp char:%c\n",  temp[i]);
		// 		i++;
		// 		breaker ++;

		// 	}
		// }
		// printf("bugger2\n");
		
		
		//copy from buffer
		while (*bufferi > j)
		{
			temp[i + j] = buffer[j];
			// printf("copy from buffer:%c\n",  temp[i+j]);
			j++;
		}

		printf("Check i added buffer stuff\n");
		printf("buffer:%s\n", buffer);
		printf("temp :%s\n",  temp);
		
		//null terminator
		temp[i + j] = '\0';
		// if (str != NULL) //smth wrong here
		free(str); // impt
		return (temp);
	}
}


char *get_next_line(int fd)
{
	char *buffer;
	char *str;
	int bufferi;

	int readval;
	int found;

	if (fd < 0)
		return NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return NULL;
	str = NULL;

	while (1)
	{
		readval = read(fd, buffer, BUFFER_SIZE);
		if (readval > 0)
		{
			str = copytostr(str, buffer, &readval);
			if (ft_findline2(str) != -1)
			{
				printf("found and break\n\n");
				break;
				// free(buffer);
				// return (cutstring(str, ft_findline2(str)));
			}
		}
		else
		{
			// if (buffer)
				// free(buffer);
			// if (str)
			// 	free(str);
			break;
		}
	}
	
	// while ((bufferi = read(fd, buffer, BUFFER_SIZE)) >= 0)
	// {
	// 	printf("\n\n\nbuffer content:\n%s\n;\n", buffer);
	// 	str = copytostr(str, buffer, &bufferi);

	// 	// only returns if i get '\n'
	// 	if (ft_findline2(str) != -1)
	// 	{
	// 		printf("found and break\n\n");
	// 		free(buffer);
	// 		return (cutstring(str, ft_findline2(str)));
	// 	}
	// }

	// printf("breaked out of loop; str:%s\n buffer:%s\n;", str, buffer);
	
	if (str != NULL)
	{
		// printf("buffer have been copied");
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
	// else
		return str;
}

int main(void)
{
  // Create a temporary file and write test content to it.
  char test_content[] = 
  
  						// "9876543210\n0123456789\nE";
						"0123456789012345678901234567890123456789\n";
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

	close(fd);

	// Optionally, remove the temporary file after testing.
	remove("temp_test.txt");

	return 0;
}
