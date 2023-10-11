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

token   *define_token(char *input, int *i)
{
    int start;

    start = *i;
    (*i)++;
    while(input[*i] && input[*i] == SPACE_ASCII)
        (*i)++;
    return (create_token(input, start, *i, SPACE_TYPE));
}

/*
* type: 	0 " "	1 ' '	2 str	3 spc	4 >		5 >>	6 <		7 <<	8 | //TODO: implementar $ e $?	
* str: not null when type is 0, 1 or 2
*/
token   *tokenization(char *input)
{
    token   *tok;
    int     i;
    int     start;

    i = 0;
    start = 0;
    tok = NULL;
    while(input[i])
    {
        if (input[i] == DOUB_QUOTE_ASCII)
        {
            start = i;
            i++;
            while(input[i] && input[i] != DOUB_QUOTE_ASCII)
                i++;
            tok = create_token(input, start, i, DOUB_QUOTE_TYPE);
            i++;
        }
        else if(input[i] == SING_QUOTE_ASCII)
        {
            start = i;
            i++;
            while(input[i] && input[i] != SING_QUOTE_ASCII)
                i++;
            tok = create_token(input, start, i, SING_QUOTE_TYPE);
            i++;
        }
        else if(input[i] == SPACE_ASCII)
            // tok = define_token(input, &i);
        {
            start = i;
            i++;
            while(input[i] && input[i] == SPACE_ASCII)
                i++;
            tok = create_token(input, start, i, SPACE_TYPE);
        }
        else if(input[i] == OUTPUT_REDIRECTION_ASCII)
        {
            i++;
            if(input[i] == OUTPUT_REDIRECTION_ASCII)
            {
                tok = create_token(input, 0, 0, APPEND_TYPE);
                i++;
            }
            else
                tok = create_token(input, 0, 0, OUTPUT_REDIRECTION_TYPE);
        }
        else if(input[i] == INPUT_REDIRECTION_ASCII)
        {
            i++;
            if(input[i] == INPUT_REDIRECTION_ASCII)
            {
                tok = create_token(input, 0, 0, HERE_DOC_TYPE);
                i++;
            }
            else
                tok = create_token(input, 0, 0, INPUT_REDIRECTION_TYPE);
        }
        else if(input[i] == PIPE_ASCII)
        {
            tok = create_token(input, 0, 0, PIPE_TYPE);
            i++;
        }
        else
        {
            start = i;
            i++;
            while(input[i] && input[i] != DOUB_QUOTE_ASCII && input[i] != SING_QUOTE_ASCII && 
                input[i] != SPACE_ASCII && input[i] != OUTPUT_REDIRECTION_ASCII && 
                input[i] != INPUT_REDIRECTION_ASCII && input[i] != PIPE_ASCII)
                i++;
            tok = create_token(input, start, i, STRING_TYPE);
        }
        if (!tok)
            return (NULL);
        printf("-----------\n");
        if (tok->str)
            printf("Token type %d\nToken str: %s\n", tok->type, tok->str);
        else
            printf("Token type %d\nToken str: [ ]\n", tok->type);    
    }
    return (tok);
}