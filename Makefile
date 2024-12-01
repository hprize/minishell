CC = cc
CFLAGS = -g
# CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell
SRCDIR = src
OBJDIR = obj
HEADER = minishell.h

# SRCS = $(SRCDIR)/main.c $(SRCDIR)/envp_set.c
# 일단 와일드 카드 써둠.

SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/builtin/*.c) \
$(wildcard $(SRCDIR)/error/*.c) \
$(wildcard $(SRCDIR)/executor/*.c) \
$(wildcard $(SRCDIR)/node_utils/*.c) \
$(wildcard $(SRCDIR)/parser/*.c) \
$(wildcard $(SRCDIR)/signal/*.c) \
$(wildcard $(SRCDIR)/utils/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))



.PHONY : all clean fclean re

all : $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR) $(OBJDIR)/builtin $(OBJDIR)/utils $(OBJDIR)/executor \
	$(OBJDIR)/node_utils $(OBJDIR)/parser $(OBJDIR)/signal $(OBJDIR)/utils \
	$(OBJDIR)/error

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADER) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@make -C libft/
	@make -C ft_fprintf/
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L libft/ -lft -L ft_fprintf/ -lft_fprintf \
	-lreadline


clean : 
	@make clean -C libft/
	@make clean -C ft_fprintf
	rm -rf $(OBJDIR)

fclean : clean
	@make fclean -C libft/
	@make fclean -C ft_fprintf
	rm -rf $(NAME)

re :
	make fclean
	make all