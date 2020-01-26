NAME	:=	ft_ls
FLAGS	:=	-Wall -Wextra -Werror
F_N		:=	ft_ls file_ls print_ls output_ls utils_ls check_ls
SRC		:=	$(addprefix sources/, $(addsuffix .c, $(F_N)))
OBJ		:=	$(addprefix objects/, $(addsuffix .o, $(F_N)))
INCL	:=	includes

LIB		:=	libft
LIB_LINK:=	-L $(LIB) -l ft

KGRN	:=	\x1b[32;01m
KNRM	:=	\x1b[0m

all	: $(NAME)

objects/%.o : sources/%.c
	@/bin/mkdir -p objects
	@gcc $(FLAGS) -I $(INCL) -c $< -o $@ -g

$(NAME):	$(OBJ)
	@make -C $(LIB)
	@gcc $(LIB_LINK) $(OBJ) -o $(NAME)
	@echo "$(KGRN)./ft_ls is compiled $(KNRM)"

clean:
	@/bin/rm -rf objects
	@make -C libft clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C libft fclean

re: fclean all
