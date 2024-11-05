#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env
{
	char	**envp;
	char	*u_var;
}	t_env;

typedef struct s_inter
{
	char	*user;
	char	*host;
	char	*where;
}	t_inter;


#endif