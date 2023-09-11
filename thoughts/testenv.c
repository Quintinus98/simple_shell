#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

typedef struct env_list
{
	char *env_str;
	struct env_list *next;
} env_t;
extern env_t *environ;
env_t *_copyenviron(void);
void free_env(env_t *env);
env_t *add_node_end(env_t **head, const char *str);

int main(void)
{
	env_t *env;
	env_t *ptr;

	environ = _copyenviron();
	ptr = environ;
	while (env != NULL)
	{
		printf("%s\n", env->env_str);
		env = env->next;
	}
	free_env(ptr);
	return (0);
}

void free_env(env_t *env)
{
	env_t *temp;

	while (env != NULL)
	{
		temp = env;
		env = env->next;
		free(temp->env_str);
		free(temp);
	}
}

env_t *_copyenviron(void)
{
	env_t *head = NULL;
	unsigned int i;

	for (i = 0; environ[i]; i++)
	{
		add_node_end(&head, environ[i]);
	}
	return (head);
}


/**
 * add_node_end - adds a new node at the end of a env_t list.
 * @head: Beginning of the list.
 * @str: New string to be added.
 * Return: the address of the new element, or NULL if it failed.
*/

env_t *add_node_end(env_t **head, const char *str)
{
	env_t *newNode = malloc(sizeof(env_t));
	env_t *lastNode = *head;
	unsigned int len = 0;

	while (str && str[len])
		len++;
	if (!newNode)
		return (NULL);
	newNode->env_str = strdup(str);
	newNode->next = NULL;

	if (*head == NULL)
	{
		*head = newNode;
		return (*head);
	}
	else
	{
		while (lastNode->next != NULL)
		{
			lastNode = lastNode->next;
		}
		lastNode->next = newNode;
		return (lastNode);
	}
}

char *_getenv(char *name)
{
	int k = 0, len = 0, i = 0;
	char *str = NULL, *sp = NULL;

	if (!name || name[0] == '\0')
		return (NULL);

	len = _strlen(name);
	/** Get env matching name and = sign.*/
	for (i = 0; environ[i] != NULL; i++)
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			sp = _strdup(environ[i]);

	if (!sp)
		return (NULL);

	len++;
	str = malloc((_strlen(sp) - len) * sizeof(char));
	if (!str)
		return (NULL);
	for (; sp[len + k] != '\0'; k++)
		str[k] = sp[len + k];
	str[k] = '\0';

	free(sp);
	/** Always remember to free str. */
	return (str);
}

