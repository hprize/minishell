CC = cc
CFLAGS = -g
# CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell
SRCDIR = src/
OBJDIR = obj/
HEADER = minishell.h

SRCS = $(SRCDIR)main.c $(SRCDIR)envp_set.c
OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

.PHONY : all clean fclean re

all : $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c $(HEADER) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@make -C libft/
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L libft/ -lft -lreadline

clean : 
	@make clean -C libft/
	rm -rf $(OBJDIR)

fclean : clean
	@make fclean -C libft/
	rm -rf $(NAME)

re :
	make fclean
	make all
