#include "shell.h"

/**
 * string_append - Concatenates two strings
 * @str_one: First string
 * @str_two: Second string
 * Return: Pointer to the new concatenated string
 */

char *string_append(char *str_one, char *str_two)
{
char *str;
unsigned int m;
unsigned int f;
unsigned int i;

if (str_one == NULL)
str_one = "";
if (str_two == NULL)
str_two = "";
for (i = 0; str_one[i] != '\0'; i++)
continue;
for (m = 0; str_one[m] != '\0'; m++)
continue;
m = m + 1;
str = malloc((i + m) *sizeof(char));
if (str == NULL)
return (0);

for (f = 0; f < (i + m); f++)
{
if (f < i)
str[f] = str_one[f];
if (f >= i)
str[f] = str_two[f - i];
}

return (str);

}

/**
 * fetch_env - Fetches the value of an environment variable
 * @naming: The name of the environment variable
 * Return: Value of the environment variable if found, otherwise NULL
 */

char *fetch_env(char *naming)
{
int i;
i = 0;

while (environ[i])
{
if (strcmp(environ[i], naming) == 0)
return (environ[i]);
++i;
}
return (NULL);
}
