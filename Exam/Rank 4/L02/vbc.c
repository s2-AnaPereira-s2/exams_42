/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:24:22 by kmaeda            #+#    #+#             */
/*   Updated: 2025/10/22 17:42:12 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}
//
node	*parse_group(char **s);
node	*parse_mult(char **s);
node	*parse_add(char **s);

node	*parse_group(char **s)
{
	node	*ret;
	if (accept(s, '('))
	{
		ret = parse_add(s);
		if (!ret || !expect(s, ')'))
		{
			destroy_tree(ret);
			return (NULL);
		}
		return (ret);
	}
	if (isdigit(**s))
	{
		ret = new_node((node){VAL, **s - '0', NULL, NULL});
		(*s)++;
		return (ret);
	}
	unexpected(**s);
	return (NULL);
}

node	*parse_mult(char **s)
{
	node	*left = parse_group(s);
	if (!left)
		return (NULL);
	if (accept(s, '*')) 
	{
		node	*right = parse_group(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		left = new_node((node){MULTI, 0, left, right});
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
	}
	return (left);
}

node	*parse_add(char **s)
{
	node	*left = parse_mult(s);
	if (!left)
		return (NULL);
	while (accept(s, '+'))
	{
		node	*right = parse_mult(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		left = new_node((node){ADD, 0, left, right});
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
	}
	return(left);
}
//
node    *parse_expr(char *s)
{
	node	*ret = parse_add(&s); //
	if (!ret) //
		return (NULL); //
    if (*s)
    {
        destroy_tree(ret);
		unexpected(*s); //
        return (NULL);
    }
    return (ret);
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    node *tree = parse_expr(argv[1]);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
	return (0);
}
