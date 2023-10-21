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
	// int found;

	// //found
	// found = ft_findline2(str);
	// if (found != -1)
	// {
	// 	temp = cutstring(str, found);
	// 	str = strmod(str, found);
	// 	return temp;
	// }
	// //not found
	// else
	// {
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
	// }

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
		// this includes the ending \n 
		found = ft_findline2(str);
		if (found != -1)
		{
			free(buffer);
			line = cutstring(str, found);
			str = strmod(str, found);
			return line;
			// return (cutstring(str, found)); //possible issue 2
		}
	}

	if (str != NULL) 
	{
		free(buffer);
		// line = ft_strduplicate(str);
		// return line;
		return str;
	}
	else
	{
		free(buffer);
		return NULL;
	}

}
