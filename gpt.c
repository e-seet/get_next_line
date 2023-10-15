#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


int ft_strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return 0;

	while (str[i])
		i++;

	return i;
}

char *ft_strjoin(char *str1, char *str2)
{
	int i = 0;
	int j = 0;
	int len1 = ft_strlen(str1);
	int len2 = ft_strlen(str2);
	char *result = malloc(len1 + len2 + 1);

	if (!result)
		return NULL;

	while (str1 && str1[i])
	{
		result[i] = str1[i];
		i++;
	}

	while (str2 && str2[j])
	{
		result[i + j] = str2[j];
		j++;
	}

	result[i + j] = '\0';

	if (str1)
		free(str1);

	return result;
}

char *get_next_line(int fd)
{
	static char *remainder = NULL;
	char *buffer, *line;
	char *newline_ptr;
	int readval;

	if (fd < 0)
		return NULL;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return NULL;

	if (!remainder)
		remainder = strdup("");

	while (!(newline_ptr = strchr(remainder, '\n')))
	{
		readval = read(fd, buffer, BUFFER_SIZE);
		buffer[readval] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		if (readval <= 0)
			break;
	}

	free(buffer);

	if (newline_ptr)
	{
		*newline_ptr = '\0';
		line = strdup(remainder);
		char *temp = strdup(newline_ptr + 1);
		free(remainder);
		remainder = temp;
		return line;
	}

	if (*remainder)
	{
		line = strdup(remainder);
		free(remainder);
		remainder = NULL;
		return line;
	}

	return NULL;
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
