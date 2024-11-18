#ifndef STRUCT_H
# define STRUCT_H

//VAR=value
//name=eontent
typedef struct s_var
{
	char	*name;
	char	*content;
	int		flag;
}	t_var;

typedef struct s_env
{
	t_var			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_inter
{
	char	*user;
	char	*host;
	char	*where;
}	t_inter;


#endif