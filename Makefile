NAME	:=	ft_ls
FLAGS	:=	-Wall -Wextra -Werror
F_N		:=	ft_ls	
SRC		:=	$(addprefix sources/, $(addsuffix .c, $(F_N)))
OBJ		:=	$(addprefix objects/, $(addsuffix .o, $(F_N)))
INCL	:=	includes

LIB			:=	libft
LIB_LINK	:=	-L $(LIB) -l ft

.PHONY:	all clean fclean re

all	: lib $(NAME)

objects/%.o : sources/%.c
	@/bin/mkdir -p objects
	@gcc $(FLAGS) -I $(INCL) -c $< -o $@ -g

lib:
	@make -C $(LIB)

$(NAME):	$(OBJ)
	@gcc $(LIB_LINK) $(OBJ) -o $(NAME)

clean:
	@/bin/rm -rf objects
	@make -C libft clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C libft fclean

re: fclean all
