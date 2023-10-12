#include "get_next_line.h"
#include "stdio.h" //to remove
#include <fcntl.h>
#include <string.h>

int ft_strlen(char *str)
{
	int i;
	i = 0;

	if (str == NULL)
		return 0;

	while(str[i] != '\0')
	{
		i++;
	}
	return i;
}

char *ft_strjoin(char *str, char *buffer, int numofchars)
{
	int i = 0;
	int j = 0;
	
	char *temp;

	// may cause memory leak due to double null terminator
	temp = malloc(sizeof(char) * (ft_strlen(str) + numofchars + 1));
	if (!temp)
	{
		return NULL;
	}
	// first condition in which str is null
	if (str != NULL)
	{
		while (str[i] != '\0')
		{
			temp[i] = str[i];
			i++;
		}
		while(numofchars > j)
		{
			temp[i + j] = buffer[j];
			j++;
		}
	}
	//second conditino in which str is not null anymore
	else
	{
		while (numofchars > j)
		{
			temp[j] = buffer[j];
			j++;
		}
	}
	temp[i + j] = '\0';
	// if (str)
	free(str);
	// if (buffer)
		// free(buffer);
	return temp;
}

char *nextline(char *str, int leng)
{
	int i;
	int j;
	char *temp;

	i = 0;
	j = 0;

	temp = malloc((leng + 1) * sizeof(char));
	//manevour to when it hits new line
	while (str[i] != '\n')
		i ++;
	// move past it
	if (str[i] == '\n' )
		i ++;
	// continue to occupy temp
	while (str[i +j] != '\n')
	{
		temp[j] = str[i + j];
		j ++;
	}
	temp[j] = '\0';
	// free(str);
	return temp;
}

int ft_findnextline(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	if (str [i] == '\n')
	{
		i  = i + 1;
		while (str[i + j] != '\n' && str[i + j] != '\0')
		{
			j++;
		}
		if ( str[i + j] == '\n')
			return j;
	}
	return -1;
}

char *get_next_line(int fd)
{
	char *buffer;
	char *str;
	char *line;
	int readval;
	int found;

	if (fd < 0)
		return NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return buffer;
	str = NULL;
	
	while (1)
	{
		readval = read(fd, buffer, BUFFER_SIZE);
		if (readval > 0)
		{
			str = ft_strjoin(str, buffer, readval);
			free(buffer);
			found = ft_findnextline(str);
			if (found != -1)
				break;
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

	//if found, no need to free buffer.
	// just return line
	if (found != -1)
	{
		line = nextline(str, found);
		free(str);
		return line;
	}
	// if not found, need to free buffer
	else
	{
		// free(buffer);
		return str;
	}



	//foudn the next line
	// if (found != -1)
	// {
	// 	line = nextline(str, found);
	// 	free(str);
	// 	return line;
	// }
	// //did not find. just return str
	// else
	// 	return str;
}

int main(void)
{
  // Create a temporary file and write test content to it.
  char test_content[] = "9876543210\n1234567890\nE";
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

	close(fd);

	// Optionally, remove the temporary file after testing.
	remove("temp_test.txt");

	return 0;
}
