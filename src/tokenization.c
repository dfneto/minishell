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
/*
* Lesson learned: when I have an intermittent error, it means, that happen sometimes
* and others don't, it usually is a non variable declaration or bad memory allocation
* (cause also by typos)
* In this case sometimes I got tok->str saved and others don't.
* I was with an error with this 
*   tok = (token *)malloc(sizeof(token *)); 
* because I was allocating in memory a space for a address and not for a token
* I like to think in the right side as allocating space in memory of sizeof the type
*/
token   *create_token(char *input, int start, int end, int type)
{
    token   *tok;

    tok = (token *)malloc(sizeof(token));
    if (!tok)
        return (NULL);
    tok->str = NULL;
    if (type == DOUB_QUOTE_TYPE | type == SING_QUOTE_TYPE | type == STRING_TYPE)
        tok->str = ft_substr(input, start, end - start + 1);
    tok->type = type;
    tok->next = NULL;
    return (tok);
}

token   *create_space_token(char *input, int *i)
{
    int start;

    start = *i;
    (*i)++;
    while(input[*i] && input[*i] == SPACE_ASCII)
        (*i)++;
    return (create_token(input, start, *i, SPACE_TYPE));
}

token   *create_pipe_token(char *input, int *i)
{
    (*i)++;
    return (create_token(input, 0, 0, PIPE_TYPE));
}

token   *create_quote_token(char *input, int *i, int type, int quote_ascii)
{
    int     start;
    token   *tok;

    start = *i;
    (*i)++;
    while(input[*i] && input[*i] != quote_ascii)
        (*i)++;
    tok = create_token(input, start, *i, type);
    (*i)++;
    return (tok);
}

token   *create_generic_token(char *input, int *i, int type, int quote_ascii)
{
    (*i)++;
    if(input[*i] == quote_ascii)
        (*i)++;
    return (create_token(input, 0, 0, type));
}

token   *create_string_token(char *input, int *i)
{
    int start;

    start = *i;
    (*i)++;
    while(input[*i] && input[*i] != DOUB_QUOTE_ASCII && input[*i] != SING_QUOTE_ASCII && 
        input[*i] != SPACE_ASCII && input[*i] != OUTPUT_REDIRECTION_ASCII && 
        input[*i] != INPUT_REDIRECTION_ASCII && input[*i] != PIPE_ASCII)
        (*i)++;
    return (create_token(input, start, *i, STRING_TYPE));
}

/*
* type: 	0 " "	1 ' '	2 str	3 spc	4 >		5 >>	6 <		7 <<	8 | //TODO: implementar $ e $?	
* str: not null when type is 0, 1 or 2
*/
token   *tokenization(char *input)
{
    token   **first_token;
    int     i;

    i = 0;
    first_token = NULL;
    while(input[i])
    {
        if (input[i] == DOUB_QUOTE_ASCII)
            add_node_back(first_token, create_quote_token(input, &i, DOUB_QUOTE_TYPE, DOUB_QUOTE_ASCII));
        else if(input[i] == SING_QUOTE_ASCII)
            add_node_back(first_token, create_quote_token(input, &i, SING_QUOTE_TYPE, SING_QUOTE_ASCII));
        else if(input[i] == SPACE_ASCII)
            add_node_back(first_token, create_space_token(input, &i));
        else if(input[i] == PIPE_ASCII)
            add_node_back(first_token, create_pipe_token(input, &i));
        else if(input[i] == OUTPUT_REDIRECTION_ASCII && input[i+1] == OUTPUT_REDIRECTION_ASCII)
            add_node_back(first_token, create_generic_token(input, &i, APPEND_TYPE, OUTPUT_REDIRECTION_ASCII));
        else if(input[i] == OUTPUT_REDIRECTION_ASCII)
            add_node_back(first_token, create_generic_token(input, &i, OUTPUT_REDIRECTION_TYPE, OUTPUT_REDIRECTION_ASCII));
        else if(input[i] == INPUT_REDIRECTION_ASCII && input[i+1] == INPUT_REDIRECTION_ASCII)
            add_node_back(first_token, create_generic_token(input, &i, HERE_DOC_TYPE, INPUT_REDIRECTION_ASCII));
        else if(input[i] == INPUT_REDIRECTION_ASCII)
            add_node_back(first_token, create_generic_token(input, &i, INPUT_REDIRECTION_TYPE, INPUT_REDIRECTION_ASCII));
        else
            add_node_back(first_token, create_string_token(input, &i));
        printf("-----------\n");
        token *tok = get_last_node(*first_token);
        if (tok->str)
            printf("Token type %d\nToken str: %s\n", tok->type, tok->str);
        else
            printf("Token type %d\nToken str: [ ]\n", tok->type);    
    }
    return (first_token);
}