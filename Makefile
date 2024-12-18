CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell
SRCDIR = src
OBJDIR = obj
HEADER = minishell.h

BLN = $(SRCDIR)/builtin/builtin.c \
$(SRCDIR)/builtin/cd.c \
$(SRCDIR)/builtin/echo.c \
$(SRCDIR)/builtin/env.c \
$(SRCDIR)/builtin/exit.c \
$(SRCDIR)/builtin/export.c \
$(SRCDIR)/builtin/export_utils.c \
$(SRCDIR)/builtin/pwd.c \
$(SRCDIR)/builtin/unset.c \

ERR = $(SRCDIR)/error/error_case.c

EXECUT = $(SRCDIR)/executor/executor.c \
$(SRCDIR)/executor/executor_exec.c \
$(SRCDIR)/executor/executor_handle_fd.c \
$(SRCDIR)/executor/executor_utils.c \
$(SRCDIR)/executor/heredoc.c \
$(SRCDIR)/executor/heredoc_utils.c \
$(SRCDIR)/executor/redirection.c \

NUTILS = $(SRCDIR)/node_utils/init_env.c \
$(SRCDIR)/node_utils/node_create_utils.c \
$(SRCDIR)/node_utils/node_edit_utils.c \
$(SRCDIR)/node_utils/node_free_utils.c \

PARS = $(SRCDIR)/parser/handle_token.c \
$(SRCDIR)/parser/process_op.c \
$(SRCDIR)/parser/process_word.c \
$(SRCDIR)/parser/replace_env_utils.c \
$(SRCDIR)/parser/tokenize_utils.c \
$(SRCDIR)/parser/parser.c \
$(SRCDIR)/parser/parser_m_utils.c \
$(SRCDIR)/parser/parser_utils.c \
$(SRCDIR)/parser/process_quote.c \
$(SRCDIR)/parser/replace_env.c \
$(SRCDIR)/parser/tokenize.c \

SIG = $(SRCDIR)/signal/signal2.c \
$(SRCDIR)/signal/signal.c \

UTILS = $(SRCDIR)/utils/check_path.c \
$(SRCDIR)/utils/check_path_utils.c \
$(SRCDIR)/utils/free2_utils.c \
$(SRCDIR)/utils/free_utils.c \
$(SRCDIR)/utils/interface.c \
$(SRCDIR)/utils/main_util.c \
$(SRCDIR)/utils/set_shlvl.c \

SRCS = $(BLN) $(ERR) $(EXECUT) $(NUTILS) $(PARS) $(SIG) $(UTILS) src/main.c

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
