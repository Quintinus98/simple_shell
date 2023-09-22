#include "main.h"


/**
 * _alias - prints alias
 * @arr: Array
 * @cnt: count
 * @aliasList: Alias list
 * Return: 0
*/
int _alias(char **arr, int cnt, alias_t **aliasList)
{
	int i = 1;

	(void)cnt;
	if (arr[1] == NULL)
		print_alias(arr, *aliasList);
	else
	{
		for (; arr[i] != NULL; i++)
		{
			if (_strchr(arr[i], '='))
				store_alias(arr[i], aliasList);
			else if (!_strchr(arr[i], '='))
				print_sp_alias(arr[i], *aliasList);
		}
	}
	return (0);
}

/**
 * store_alias - stores alias in a linked list.
 * @str: Array
 * @head: head pointer to struct alias_t
*/
void store_alias(char *str, alias_t **head)
{
	int status = 0;
	alias_t *tmp;
	char *ptr = str, *pcpy, *str_m = _strdup(str);

	tmp = *head;
	pcpy = str;
	for (; *str != '\0'; str++)
	{
		if (*str == '=')
		{
			*str = '\0';
			ptr = str + 1;
			break;
		}
	}
	while (tmp != NULL)
	{
		if (_strlen(tmp->name) == _strlen(pcpy))
		{
			if (_strcmp(tmp->name, pcpy) == 0)
			{
				free(tmp->val);
				tmp->val = _strdup(ptr);
				status = 1;
			}
		}
		tmp = tmp->next;
	}
	if (status)
	{
		free(str_m);
		return;
	}
	add_node_end(head, str_m);
	free(str_m);
}

/**
 * print_alias - prints alias
 * @arr: Array
 * @h: head pointer to struct alias_t
*/
void print_alias(char **arr, const alias_t *h)
{
	const alias_t *tmp;

	/** Print all.*/
	if (arr[1] == NULL)
	{
		tmp = h;
		while (tmp != NULL)
		{
			write(1, tmp->name, _strlen(tmp->name));
			write(1, "='", 2);
			write(1, tmp->val, _strlen(tmp->val));
			write(1, "'\n", 2);
			tmp = tmp->next;
		}
		return;
	}
}

/**
 * print_sp_alias - prints alias
 * @str: string
 * @h: head pointer to struct alias_t
*/
void print_sp_alias(char *str, const alias_t *h)
{
	const alias_t *tmp;
	int len = _strlen(str);

	/** Print specific */
	tmp = h;
	while (tmp != NULL)
	{
		if (!_strcmp(tmp->name, str) && tmp->name[len] == '\0')
		{
			write(1, tmp->name, _strlen(tmp->name));
			write(1, "='", 2);
			write(1, tmp->val, _strlen(tmp->val));
			write(1, "'\n", 2);
		}
		tmp = tmp->next;
	}
}

/**
 * add_node_end - adds a new node at the end of a list_t list.
 * @head: Beginning of the list.
 * @str: New string to be added.
 * Return: the address of the new element, or NULL if it failed.
*/
alias_t *add_node_end(alias_t **head, char *str)
{
	alias_t *newNode = malloc(sizeof(alias_t));
	alias_t *lastNode = *head;
	unsigned int len = 0;
	char *ptr = str, *ptr_cpy;

	while (str && str[len])
		len++;
	if (!newNode)
		return (NULL);

	ptr_cpy = str;
	while (*str != '\0')
	{
		if (*str == '=')
		{
			*str = '\0';
			ptr = str + 1;
			break;
		}
		str++;
	}
	newNode->name = _strdup(ptr_cpy);
	newNode->val = _strdup(ptr);
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
