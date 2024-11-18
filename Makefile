CC = cc
CFLAGS = -g
# CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell
SRCDIR = src
OBJDIR = obj
GNLDIR = gnl
HEADER = minishell.h

# SRCS = $(SRCDIR)/main.c $(SRCDIR)/envp_set.c
# 일단 와일드 카드 써둠.

SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/execute/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
GNLSRCS = $(wildcard $(GNLDIR)/*.c)
GNLOBJS = $(GNLSRCS:$(GNLDIR)/%.c=$(OBJDIR)/%.o)


.PHONY : all clean fclean re

all : $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR) $(OBJDIR)/execute

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADER) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(GNLDIR)/%.c $(HEADER) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(GNLOBJS)
	@make -C libft/

$(CC) $(CFLAGS) -o $@ $(OBJS) -L libft/ -lft -L ft_fprintf/ -lft_fprintf \
-lreadline


clean : 
	@make clean -C libft/
	rm -rf $(OBJDIR)

fclean : clean
	@make fclean -C libft/
	rm -rf $(NAME)

re :
	make fclean
	make all
