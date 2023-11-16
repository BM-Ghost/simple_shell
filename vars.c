#include "shell.h"
/**
* isChainDel - test if current char in buffer is a chain delimeter
*
* @info: the parameter struct
*
* @buf: the char buffer
*
* @cur_pos: address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
*/
int isChainDel(FuncInfo *info, char *buf, size_t *cur_pos)
{
	size_t j = *cur_pos;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->chainBufType = SH_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->chainBufType = SH_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->chainBufType = SH_CHAIN;
	}
	else
	return (0);
	*cur_pos = j;
	return (1);
}
/**
* chain_status - checks we should continue chaining based on last status
*
* @info: the parameter struct
*
* @buf: the char buffer
*
* @cur_pos: address of current position in buf
*
* @ist_pos: starting position in buf
*
* @buf_len: length of buf
*
* Return: Void
*/
void chainStat(FuncInfo *info, char *buf, size_t *cur_pos, size_t ist_pos,
size_t buf_len)
{
	size_t j = *cur_pos;

	if (info->chainBufType == SH_AND)
	{
		if (info->status)
		{
			buf[ist_pos] = 0;
			j = buf_len;
		}
	}
	if (info->chainBufType == SH_OR)
	{
		if (!info->status)
		{
			buf[ist_pos] = 0;
			j = buf_len;
		}
	}
	*cur_pos = j;
}
/**
* replaceAlias - replaces an aliases in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replaceAlias(FuncInfo *info)
{
	int i;
	StringList *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
	node = nodeStartsWith(info->alias, info->argv[0], '=');
	if (!node)
		return (0);
	free(info->argv[0]);
	p = _strchr(node->str, '=');
	if (!p)
		return (0);
	p = strDup(p + 1);
	if (!p)
		return (0);
	info->argv[0] = p;
	}
	return (1);
}
/**
* replaceVariables - replaces vars in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replaceVariables(FuncInfo *)
{
	int b;
	StringList *node;

	for (b = 0; info->argv[b]; b++)
	{
		if (info->argv[b][0] != '$' || !info->argv[b][1])
			continue;
		if (!_strcmp(info->argv[b], "$?"))
		{
			replaceStr(&(info->argv[b]),
			strDup(convertNum(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[b], "$$"))
		{
			replaceStr(&(info->argv[b]),
			strDup(convertNum(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[b][1], '=');
		if (node)
		{
			replaceStr(&(info->argv[b]),
			strDup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceStr(&info->argv[b], strDup(""));
	}
	return (0);
}
/**
* replaceStr - replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replaceStr(char **old, char *new)
{
	free(*old);

	*old = new;
	return (1);
}
