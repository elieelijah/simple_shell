#include "shell.h"

int get_token_length(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **tokenize_string(char *line, char *delim);

/**
 * get_token_length - Calculates the length of the token
 *                    within a string until the delimiter.
 * @str: The string to be analyzed.
 * @delim: The delimiter character.
 *
 * Return: The length of the token until the delimiter.
 */
int get_token_length(char *str, char *delim)
{
	int length = 0;

	while (*str && *str != *delim)
	{
		length++;
		str++;
	}

	return (length);
}

/**
 * count_tokens - Counts the number of delimited words
 *                within a string.
 * @str: The string to be analyzed.
 * @delim: The delimiter character.
 *
 * Return: The number of tokens in the string.
 */
int count_tokens(char *str, char *delim)
{
	int count = 0;

	while (*str)
	{
		if (*str != *delim)
		{
			count++;
			str += get_token_length(str, delim);
		}
		else
			str++;
	}

	return (count);
}

/**
 * tokenize_string - Tokenizes a string based on a delimiter.
 * @line: The string to be tokenized.
 * @delim: The delimiter character.
 *
 * Return: A pointer to an array of tokens.
 */
char **tokenize_string(char *line, char *delim)
{
	char **tokens;
	int index = 0, num_tokens, token_length, token_index;

	num_tokens = count_tokens(line, delim);
	if (num_tokens == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (num_tokens + 1));
	if (!tokens)
		return (NULL);

	for (token_index = 0; token_index < num_tokens; token_index++)
	{
		while (line[index] == *delim)
			index++;

		token_length = get_token_length(line + index, delim);

		tokens[token_index] = malloc(sizeof(char) * (token_length + 1));
		if (!tokens[token_index])
		{
			for (token_index--; token_index >= 0; token_index--)
				free(tokens[token_index]);
			free(tokens);
			return (NULL);
		}

		for (int i = 0; i < token_length; i++)
		{
			tokens[token_index][i] = line[index];
			index++;
		}

		tokens[token_index][token_length] = '\0';
	}

	tokens[num_tokens] = NULL;

	return (tokens);
}

