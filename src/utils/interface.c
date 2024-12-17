#include "utils.h"

char	*get_host_name(void)
{
	int		fd;
	char	name_leng[256];
	char	*host;

	fd = open("/etc/hostname", O_RDONLY);
	// fd = open("for_test_src/test_hostname", O_RDONLY);
	ft_bzero(name_leng, 256);
	if (fd < 0)
	{
		perror("Hostname file open error\n");
		return (NULL);
	}
	if (read (fd, name_leng, sizeof(name_leng)) < 0)
	{
		perror("Hostname file read error\n");
		return (NULL);
	}
	host = ft_substr(name_leng, 0, ft_strchr_len(name_leng, '.'));
	close(fd);
	return (host);
}

char	*interface(t_env *shell_envp)
{
	char	*result;
	char	*temp;
	char	*host;

	result = ft_strjoin(find_content("USER", shell_envp), "@");
	result = ft_strjoin_free(result, get_host_name());
	result = ft_strjoin_free(result, ft_strdup(":"));
	temp = ft_strjoin(find_content("PWD", shell_envp), "$ ");
	result = ft_strjoin_free(result, temp);
	return (result);
}
