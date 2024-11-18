#include "bulitin.h"

void execute_tree(t_tree *node, t_env **env)
{
	//빌트인 먼저
	if (node->type == NODE_EXEC)
		builtin_cmd(node, env);

	//execute()
}

// void	execute_tree(t_tree *root, t_master *master)
// {
// 	if (root->type == NODE_PIPE)
// 		execute_pipe(root, master);
// 	else if (root->type == NODE_EXEC)
		//여기에 builtin_cmd먼저 넣기
// 		execute_command(root, master);
// }