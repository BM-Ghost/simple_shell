#include "shell.h"

/**
 * addNode - Adds a new node at the beginning of the linked list
 * @head: Address of the pointer to the head node
 * @str: String field of the new node
 * @num: Node index used by history
 *
 * Returns: Pointer to the new head node
 */
StringList *addNode(StringList **head, const char *str, int num) {
    StringList *new_head;

    if (!head)
        return NULL;

    new_head = malloc(sizeof(StringList));
    if (!new_head)
        return NULL;

    memset((void *)new_head, 0, sizeof(StringList));
    new_head->num = num;

    if (str) {
        new_head->str = strdup(str);
        if (!new_head->str) {
            free(new_head);
            return NULL;
        }
    }

    new_head->next = *head;
    *head = new_head;
    return new_head;
}

/**
 * addNodeEnd - Adds a new node at the end of the linked list
 * @head: Address of the pointer to the head node
 * @str: String field of the new node
 * @num: Node index used by history
 *
 * Returns: Pointer to the new node
 */
StringList *addNodeEnd(StringList **head, const char *str, int num) {
    StringList *new_node, *node;

    if (!head)
        return NULL;

    node = *head;
    new_node = malloc(sizeof(StringList));
    if (!new_node)
        return NULL;

    memset((void *)new_node, 0, sizeof(StringList));
    new_node->num = num;

    if (str) {
        new_node->str = strdup(str);
        if (!new_node->str) {
            free(new_node);
            return NULL;
        }
    }

    if (node) {
        while (node->next)
            node = node->next;
        node->next = new_node;
    } else {
        *head = new_node;
    }
    return new_node;
}

/**
* printListStr - prints only the str element of a StringList linked list
*
* @head: pointer to first node
*
* Return: size of list
*/
size_t printListStr(const StringList *head)
{
	size_t i = 0;

	while (head)
	{
		puts(head->str ? head->str : "(nil)");
		puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
* deleteNodeAtIndex - deletes node at given index
*
* @head: address of pointer to first node
*
* @index: index of node to delete
*
* Return: 1 on success, 0 on failure
*/
int deleteNodeAtIndex(StringList **head, unsigned int index)
{
	StringList *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
	{
		return (0);
	}

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;

	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
* freeList - frees all nodes of a list
*
* @head_ptr: address of pointer to head node
*
* Return: void
*/
void freeList(StringList **head_ptr)
{
	StringList *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
