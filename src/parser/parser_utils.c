#include "../minishell.h"

// ----- 토큰화 관련 util 함수 -----

// 토큰 추가해서 붙이고 현재 포인팅토큰 옮겨주는 함수
void	add_token(t_token **head, t_token **current, t_token *new_token)
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
t_token	*create_token(token_type type, const char *value)
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

void	merge_token(t_token **current, char *new_value)
{
	char	*combined;

	combined = ft_strjoin((*current)->value, new_value);
	free((*current)->value);
	(*current)->value = combined;
}
// ----- 파싱 관련 util 함수 -----

// 트리 노드 생성 함수
t_tree	*create_tree_node(node_type type, const char *value)
{
	t_tree	*node;

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
void	add_child(t_tree *parent, t_tree *child)
{
	size_t	old_size;
	size_t	new_size;

	old_size = parent->child_count * sizeof(t_tree *);
	new_size = (parent->child_count + 1) * sizeof(t_tree *);
	parent->children = ft_realloc(parent->children, old_size, new_size);
	if (!parent->children)
	{
		printf("realloc failed\n");
		exit(EXIT_FAILURE);
	}
	parent->children[parent->child_count++] = child;
}