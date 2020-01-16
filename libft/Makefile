# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asultanb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 20:14:05 by asultanb          #+#    #+#              #
#    Updated: 2020/01/10 13:50:18 by asultanb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:=	libft.a
FLAGS 	:=	-Wall -Wextra -Werror

F_N		:= 	ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove ft_memchr \
			ft_memcmp ft_strlen ft_strdup ft_strcpy ft_strncpy ft_strcat \
			ft_strncat ft_strlcat ft_strchr ft_strrchr ft_strstr ft_strnstr \
			ft_strcmp ft_strncmp ft_atoi ft_isalpha ft_isdigit ft_isalnum \
			ft_isascii ft_isprint ft_toupper ft_tolower ft_atoll\
			ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr ft_striter \
			ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ ft_strsub \
			ft_strjoin ft_strtrim ft_strsplit ft_itoa ft_putchar ft_putstr \
			ft_putendl ft_putnbr ft_putchar_fd ft_putstr_fd ft_putendl_fd \
			ft_putnbr_fd \
			ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap \
			ft_lstpush ft_strsplit_list ft_lstprint ft_itoa_base ft_lstfind \
			get_next_line bubble_sort\
			ft_printf parse_format verify_params set_params helper_func \
			math_func csp_specifier di_specifier ouxx_specifier \
			f_specifier

SRC		:=	$(addsuffix .c, $(F_N))
OBJ		:=	$(addsuffix .o, $(F_N))

INCL 	:=	-I libft.h

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	@gcc $(FLAGS) -c $(INCL) $< -o $@

$(NAME): $(OBJ) 
	@ar rcs $(NAME) $(OBJ)

clean:
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
