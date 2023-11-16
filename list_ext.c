#include "shell.h"

/**
 * get_list_length - Determines the length of a linked list
 * @head: Pointer to the first node of the list
 *
 * Return: Size of the list
 */
size_t get_list_length(const StringList *head) {
    size_t size = 0;

    while (head) {
        head = head->next;
        size++;
    }
    return (size);
}

/**
 * stringListToStrings - Converts a StringList to an array of strings
 * @head: Pointer to the first node of the list
 *
 * Return: Array of strings from the list nodes
 */
char **stringListToStrings(StringList *head) {
    StringList *node = head;
    size_t i = get_list_length(head);
    char **strs;
    char *str;

    if (!head || !i)
        return (NULL);

    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);

    for (i = 0; node; node = node->next, i++) {
        str = malloc(strLen(node->str) + 1);
        if (!str) {
            for (size_t j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }
        str = strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return (strs);
}

/**
 * printList - Prints all elements of a StringList linked list
 * @head: Pointer to the first node of the list
 *
 * Return: Size of the list
 */
size_t printList(const StringList *head) {
    size_t size = 0;

    while (head) {
        customPuts(convertNum(head->num, 10, 0));
        putchar(':');
        putchar(' ');
        customPuts(head->str ? head->str : "(nil)");
        customPuts("\n");
        head = head->next;
        size++;
    }
    return (size);
}

/**
 * nodeStartsWith - Finds the node whose string starts with a given prefix
 * @node: Pointer to the head of the list
 * @prefix: Prefix string to match
 * @c: The next character after the prefix to match, -1 if not checked
 *
 * Returns: Pointer to the matching node or NULL if no match
 */
StringList *nodeStartsWith(StringList *node, char *prefix, char c) {
    char *match = NULL;

    while (node) {
        match = startsWith(node->str, prefix);
        if (match && ((c == -1) || (*match == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * getNodeIndex - Retrieves the index of a given node within a linked list
 * @head: Pointer to the head of the list
 * @node: Pointer to the node whose index is sought
 *
 * Returns: Index of the node within the list or -1 if not found
 */
ssize_t getNodeIndex(StringList *head, StringList *node) {
    size_t index = 0;

    while (head) {
        if (head == node)
            return (index);
        head = head->next;
        index++;
    }
    return (-1);
}
