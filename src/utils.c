#include "../minishell.h"

// ----- 토큰화 관련 util 함수 -----

// 토큰 추가해서 붙이고 현재 포인팅토큰 옮겨주는 함수
void add_token(t_token **head, t_token **current, t_token *new_token)
{
	if (*head == NULL)
	{
		*head = new_token;
		*current = new_token;
	} else
	{
		(*current)->next = new_token;
		*current = (*current)->next;
	}
}

// 새로운 토큰 생성 함수
t_token *create_token(token_type type, const char *value)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
	{
		printf("토큰 할당 실패!\n");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

// ----- 파싱 관련 util 함수 -----

// 트리 노드 생성 함수
t_tree *create_tree_node(node_type type, const char *value)
{
	t_tree *node;

	node = malloc(sizeof(t_tree));
	if (!node)
	{
		printf("메모리 할당 실패(트리 생성)\n");
		exit(EXIT_FAILURE);
	}
	node->type = type;
	if (value)
		node->value = strdup(value);
	else
		node->value = NULL;
	node->children = NULL;
	node->child_count = 0;
	return (node);
}

// 자식 노드 추가 함수
void add_child(t_tree *parent, t_tree *child)
{
	parent->children = realloc(parent->children, sizeof(t_tree*) * (parent->child_count + 1));
	if (!parent->children)
	{
		printf("메모리 할당 실패(자식 노드 추가)\n");
		exit(EXIT_FAILURE);
	}
	parent->children[parent->child_count++] = child;
}

// ----- free 함수 -----

void free_tree(t_tree *node)
{
	int i;

	if (node == NULL)
		return;
	i = 0;
	while (i < node->child_count)
	{
		free_tree(node->children[i]);
		i++;
	}
	free(node->children);
	free(node->value);
	free(node);
}

void free_tokens(t_token *tokens) {
	t_token *next;

	while (tokens != NULL)
	{
		next = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = next;
	}
}