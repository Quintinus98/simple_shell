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
	int j = 0, status = 0;
	alias_t *tmp;

	tmp = *head;
	j = 0;
	while (str[j] != '=')
		j++;
	while (tmp != NULL)
	{
		if (_strncmp(tmp->nameVal, str, j + 1) == 0)
		{
			free(tmp->nameVal);
			free(tmp->val);
			tmp->val = _strdup(str + (j + 1));
			tmp->nameVal = malloc(255);
			_strcpy(tmp->nameVal, tmp->name);
			_strcat(tmp->nameVal, "='");
			_strcat(tmp->nameVal, str + (j + 1));
			_strcat(tmp->nameVal, "'");
			status = 1;
		}
		tmp = tmp->next;
	}
	if (status)
		return;

	add_node_end(head, str);
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
			if (tmp->nameVal == NULL)
				write(1, "(nil)", 5);
			else
				write(1, tmp->nameVal, _strlen(tmp->nameVal));
			write(1, "\n", 1);
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
	int j = 0;

	/** Print specific */
	while (str[j] != '\0')
		j++;
	tmp = h;
	while (tmp != NULL)
	{
		if (_strncmp(tmp->nameVal, str, j) == 0)
		{
			write(1, tmp->nameVal, _strlen(tmp->nameVal));
			write(1, "\n", 1);
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
	newNode->val = _strdup(str + (i + 1));
	newNode->nameVal = malloc(255);
	_strcpy(newNode->nameVal, newNode->name);
	_strcat(newNode->nameVal, "='");
	_strcat(newNode->nameVal, str + (i + 1));
	_strcat(newNode->nameVal, "'");
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
