CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

HEADER = libft.h
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strchr_len.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strjoin_free.c\
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_isspace.c ft_strndup.c ft_realloc.c ft_strcmp.c
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef WITH_BONUS
	OBJS := $(OBJS) $(BONUS_OBJS)
else
	OBJS := $(OBJS)
endif

.PHONY : all clean fclean re bonus

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)

all : $(NAME)

bonus :
	make WITH_BONUS=1 all

clean : 
	@rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
	@rm -rf $(NAME)

re : 
	@make fclean
	@make all
