
#include "get_next_line.h"
#include "stdio.h" //to remove
#include "stdlib.h"
#include "unistd.h"


int ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char *strmod(char *str, int i)
{
	int j;
	char *temp;

	j = 0;
	temp = malloc(sizeof(char) * ((ft_strlen(str) - i )+ 1));
	if(!temp)
		return NULL;
	i --;
	while(str[i + j] != '\0')
	{
		temp[j] = str[i + j];
		j++;
	}
	temp[j] = '\0';
	free(str);
	return temp;
}

char *cutstring(char *str, int i)
{
	char *temp;
	int j;

	j = 0;
	temp = malloc(sizeof(char) * (i + 1)); 
	if (!temp)
	{
		return NULL;
	}
	while (j < i)
	{
		temp[j] = str[j];
		j++;
	}
	temp[j] = '\0';
	return temp;
}

int ft_findline2(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[j] != '\0' && str[j] != '\n')
		j++;

	while (str[j + i] != '\0')
	{
		if (str[j + i] == '\n' && i != 0)
			return (j + i + 1);
		else if (str[j + i] == '\n' && i == 0)
			return (j + i + 1);
		i++;
	}
	return (-1);
}

char *ft_strduplicate(char  *str)
{
	int i;
	char *temp;
	int found;

	//found
	found = ft_findline2(str);
	if (found != -1)
	{
		temp = cutstring(str, found);
		str = strmod(str, found);
		return temp;
	}
	//not found
	else
	{
		temp = malloc (sizeof(char) * (ft_strlen(str) + 1));
		i = 0;

		while(str[i] != '\0')
		{
			temp[i] = str[i];
			i++;
		}

		if (temp[0] == '\0')
		{
			// free(str);
			str = NULL;
		}
		return temp;
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
	if (!str && !buffer)
		return NULL; //issue not here
	else
	{

		printf("\nstri size:%d;\n", (ft_strlen(str)));
		printf("buff size:%d;\n", (*bufferi));
		printf("temp size:%d;\n", (ft_strlen(str) + *bufferi + 1));
		
		temp = malloc(sizeof(char) * ((ft_strlen(str) + *bufferi + 1)));
		if (!temp)
			return (NULL);

		while (str != NULL && str[i] != '\0')
		{
			temp[i] = str[i];
			i++;
		}
		while (*bufferi > j)
		{
			temp[i + j] = buffer[j];
			j++;
		}
		temp[i + j] = '\0';

		printf("str copied:%s;\n", str);
		printf("temp copied:%s;\n", temp);

		free(str); // impt
		// str = temp;
		return (temp);
	}
}

//issue is not static
// i lose previous data therefore getting weird result
char *get_next_line(int fd)
{
	char *buffer;
	static char *str;
	char *line;
	int bufferi;
	int found;

	if (fd == -1) //changed this.
		return NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	// str = NULL;
	line = NULL;
	if (!buffer )
		return NULL;

	//issue is here. i need to find out whether i need to break or not
	while ((bufferi = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		str = copytostr(str, buffer, &bufferi);
		printf("after copytostr:%s\n", str);
		// this includes the ending \n 
		found = ft_findline2(str);
		if (found != -1)
		{
			free(buffer);
			line = cutstring(str, found);
			str = strmod(str, found);
			printf("check str before ending:%s", str);
			return line;
			// return (cutstring(str, found)); //possible issue 2
		}
	}

	if (str != NULL && str[0] != '\0') 
	{
		free(buffer);
		printf("eh?");
		line = ft_strduplicate(str);
		return line;
	}
	else
	{
		free(buffer);
		return NULL;
	}

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