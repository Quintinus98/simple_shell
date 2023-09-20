#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// extern char **environ;

// typedef struct env_list
// {
// 	char *env_str;
// 	struct env_list *next;
// } env_t;
// extern env_t *environ;
// env_t *_copyenviron(void);
// void free_env(env_t *env);
// env_t *add_node_end(env_t **head, const char *str);

// int main(void)
// {
// 	env_t *env;
// 	env_t *ptr;

// 	environ = _copyenviron();
// 	ptr = environ;
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->env_str);
// 		env = env->next;
// 	}
// 	free_env(ptr);
// 	return (0);
// }

// void free_env(env_t *env)
// {
// 	env_t *temp;

// 	while (env != NULL)
// 	{
// 		temp = env;
// 		env = env->next;
// 		free(temp->env_str);
// 		free(temp);
// 	}
// }

// env_t *_copyenviron(void)
// {
// 	env_t *head = NULL;
// 	unsigned int i;

// 	for (i = 0; environ[i]; i++)
// 	{
// 		add_node_end(&head, environ[i]);
// 	}
// 	return (head);
// }


// /**
//  * add_node_end - adds a new node at the end of a env_t list.
//  * @head: Beginning of the list.
//  * @str: New string to be added.
//  * Return: the address of the new element, or NULL if it failed.
// */

// env_t *add_node_end(env_t **head, const char *str)
// {
// 	env_t *newNode = malloc(sizeof(env_t));
// 	env_t *lastNode = *head;
// 	unsigned int len = 0;

// 	while (str && str[len])
// 		len++;
// 	if (!newNode)
// 		return (NULL);
// 	newNode->env_str = strdup(str);
// 	newNode->next = NULL;

// 	if (*head == NULL)
// 	{
// 		*head = newNode;
// 		return (*head);
// 	}
// 	else
// 	{
// 		while (lastNode->next != NULL)
// 		{
// 			lastNode = lastNode->next;
// 		}
// 		lastNode->next = newNode;
// 		return (lastNode);
// 	}
// }

// char *_getenv(char *name)
// {
// 	int k = 0, len = 0, i = 0;
// 	char *str = NULL, *sp = NULL;

// 	if (!name || name[0] == '\0')
// 		return (NULL);

// 	len = _strlen(name);
// 	/** Get env matching name and = sign.*/
// 	for (i = 0; environ[i] != NULL; i++)
// 		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
// 			sp = _strdup(environ[i]);

// 	if (!sp)
// 		return (NULL);

// 	len++;
// 	str = malloc((_strlen(sp) - len) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	for (; sp[len + k] != '\0'; k++)
// 		str[k] = sp[len + k];
// 	str[k] = '\0';

// 	free(sp);
// 	/** Always remember to free str. */
// 	return (str);
// }
typedef struct alias
{
	char *name;
	char *val;
	char *nameVal;
	struct alias *next;
} alias_t;

int _alias(char **arr, int cnt, alias_t **aliasList);
void store_alias(char **arr, alias_t **head);
void print_alias(char **arr, const alias_t *h);
alias_t *add_node_end(alias_t **head, const char *str);

int main(void)
{
	char *arr[] = {"alias", "name=david", "name2=peter", "name=quentin", NULL};
	char *arr2[] = {"alias", NULL};
	int i = 0;
	alias_t *aliasList = NULL;
	int cnt = 0;

	_alias(arr, cnt, &aliasList);
	_alias(arr2, cnt, &aliasList);

	return (0);
}


/**
 * _alias - prints alias
 * @arr: Array
 * @aliasList: Alias list
*/
int _alias(char **arr, int cnt, alias_t **aliasList)
{
	(void)cnt;
	if (arr[1] == NULL)
	{
		print_alias(arr, *aliasList);
		return (0);
	}

	if (strchr(arr[1], '='))
		store_alias(arr, aliasList);
	else
		print_alias(arr, *aliasList);

	return (0);
}

/**
 * store_alias - stores alias in a linked list.
 * @arr: Array
 * @head: head pointer to struct alias_t
*/
void store_alias(char **arr, alias_t **head)
{
	int i, j = 0, status = 0;
	alias_t *tmp;

	for (i = 1; arr[i] ; i++)
	{
		tmp = *head;
		j = 0;
		while (arr[i][j] != '=')
			j++;
		while (tmp != NULL)
		{
			if (strncmp(tmp->nameVal, arr[i], j + 1) == 0)
			{
				free(tmp->nameVal);
				free(tmp->val);
				tmp->val = strdup(arr[i] + 5);
				tmp->nameVal = malloc(255);
				strcpy(tmp->nameVal, tmp->name);
				strcat(tmp->nameVal, "='");
				strcat(tmp->nameVal, arr[i] + 5);
				strcat(tmp->nameVal, "'");
				status = 1;
			}
			tmp = tmp->next;
		}
		if (status)
			continue;

		add_node_end(head, arr[i]);
	}
}
/**
 * name=david
 * name=peter
 * name
 * value - needs update
 * 
*/
/**
 * print_alias - prints alias
 * @arr: Array
 * @h: head pointer to struct alias_t
*/
void print_alias(char **arr, const alias_t *h)
{
	const alias_t *tmp;
	int i = 0, j = 0;

	/** Print all.*/
	if (arr[1] == NULL)
	{
		tmp = h;
		while (tmp != NULL)
		{
			if (tmp->nameVal == NULL)
				write(1, "(nil)", 5);
			else
				write(1, tmp->nameVal, strlen(tmp->nameVal));
			write(1, "\n", 1);
			tmp = tmp->next;
		}
		return;
	}

	/** Print specific */
	for (i = 1; arr[i] ; i++)
	{
		while (arr[i][j] != '\0')
			j++;
		tmp = h;
		while (tmp != NULL)
		{
			if (strncmp(tmp->nameVal, arr[i], j) == 0)
			{
				write(1, tmp->nameVal, strlen(tmp->nameVal));
				write(1, "\n", 1);
			}
			tmp = tmp->next;
		}
	}
}

/**
 * add_node_end - adds a new node at the end of a list_t list.
 * @head: Beginning of the list.
 * @str: New string to be added.
 * Return: the address of the new element, or NULL if it failed.
*/
alias_t *add_node_end(alias_t **head, const char *str)
{
	alias_t *newNode = malloc(sizeof(alias_t));
	alias_t *lastNode = *head;
	unsigned int len = 0, i = 0;

	while (str && str[len])
		len++;
	if (!newNode)
		return (NULL);

	newNode->name = malloc(255);
	for (; str[i] != '\0'; i++)
	{
		if (str[i] == '=')
			break;
		newNode->name[i] = str[i];
	}
	newNode->val = strdup(str + (i + 1));
	newNode->nameVal = malloc(255);
	strcpy(newNode->nameVal, newNode->name);
	strcat(newNode->nameVal, "='");
	strcat(newNode->nameVal, str + (i + 1));
	strcat(newNode->nameVal, "'");
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
