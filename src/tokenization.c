#include "minishell.h"

//type: 	0 " "	1 ' '	2 str	3 spc	4 >		5 >>	6 <		7 <<	8 | //TODO: implementar $ e $?	
int get_token_type(char c)
{
    if (c == 34) // "
        return (0);
    else if (c == 39) // ' 
        return (1);
    else if (c == 32) // spc
        return (3);
    else if (c == 62) // >
        return (4);
    else if (c == 60) // <
        return (1);
    else if (c == 124) // |
        return (1);
    return (2);
}  

token   *create_token(char *input, int start, int end, int type)
{
    token   *tok;
    char    *str = NULL;

    tok = (token *)malloc(sizeof(token *));
    if (!tok)
        return (NULL);
    if (type == 0 | type == 1 | type == 2)
        str = ft_substr(input, start, end - start + 1);
    else
        tok->str = NULL;
    tok->type = type;
    tok->next = NULL;
    // printf("Start: %d, End: %d, end - start: %d, Token str: %s\n", start, end, end - start, str);
    // ft_strlcpy(tok->str, str, ft_strlen(str));
    // printf("Token str: %s\n", tok->str);
    return (tok);
}

/*
* type: 	0 " "	1 ' '	2 str	3 spc	4 >		5 >>	6 <		7 <<	8 | //TODO: implementar $ e $?	
* str: not null when type is 0, 1 or 2
*/
token   *tokenization(char *input)
{
    // token   *first_token;
    token   *tok;
    int     i;
    int     start;
    int     type;

    i = 0;
    start = 0;
    type = 0;
    tok = NULL;
    // first_token = (token *) malloc(1 * sizeof(token *) + 1);
    // if (!first_token)
    //     return NULL;
    while(input[i])
    {
        if (input[i] == DOUB_QUOTE)
        {
            start = i;
            i++;
            type = 0;
            while(input[i] && input[i] != DOUB_QUOTE)
                i++;
        }
        tok = create_token(input, start, i, type);
        // free(tok->str);
        // tok->str = NULL;
        free(tok);
        tok = NULL;
        i++;
    }
    return (NULL);
}