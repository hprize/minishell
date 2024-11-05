CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft_fprintf.a

SUBDIRS = ../libft

HEADER = ft_fprintf_header.h

SRCS = ft_char_int.c \
	ft_hex_pointer.c \
	ft_fprintf.c

OBJS = $(SRCS:.c=.o)

.PHONY : all clean fclean re subdirs $(SUBDIRS)

all : $(NAME)

subdirs : $(SUBDIRS)

$(SUBDIRS) :
	@$(MAKE) -C $(SUBDIRS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	@$(MAKE) -C $(SUBDIRS)
	@cp $(SUBDIRS)/libft.a $@
	@ar rcs $@ $^

clean : 
	@rm -rf $(OBJS)
	@$(MAKE) clean -C $(SUBDIRS)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(SUBDIRS)/libft.a

re :
	make fclean
	make all
