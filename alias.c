#include "main.h"


/**
 * _alias - prints alias
 * @arr: Array
 * @aliasList: Alias list
*/
int _alias(char **arr, int cnt, alias_t **aliasList)
{
	(void)cnt;
	if (arr[1] == NULL)
		print_alias(arr, *aliasList);
	else if (strchr(arr[1], '='))
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
				tmp->nameVal = _strdup(arr[i]);
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
	unsigned int len = 0;

	while (str && str[len])
		len++;
	if (!newNode)
		return (NULL);
	newNode->nameVal = strdup(str);
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
