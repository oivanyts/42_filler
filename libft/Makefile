# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/17 13:27:43 by oivanyts          #+#    #+#              #
#    Updated: 2019/01/14 16:36:42 by oivanyts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

SRC_DIR		:= ./src/
OBJ_DIR 	:= ./obj/
INC_DIR 	:= ./includes/

LIBFT_DIR   := ./libft/
LIBFT       := $(LIBFT_DIR)libft.a
LIBFT_INC   := $(LIBFT_DIR)includes/
LIBFT_OBJ   := $(LIBFT_DIR)obj/*.o
LIBFT_FLAGS := -lft -L $(LIBFT_DIR)

CC		    := gcc

LINK_FLAGS  := $(LIBFT_FLAGS)

INCLUDES 	:= $(addprefix $(INC_DIR), libftprintf.h)

HEADER_FLAGS := -I $(INC_DIR) -I $(LIBFT_INC)

FLAGS		:= -Wall -Wextra -Werror

FUNCTIONS 	+= printf.c
FUNCTIONS 	+= ft_itoa_prntf.c
FUNCTIONS 	+= ft_strnum_base.c
FUNCTIONS 	+= ft_itoa_double.c
FUNCTIONS 	+= ft_exp.c
FUNCTIONS 	+= ft_round_double.c
FUNCTIONS 	+= ft_charlen.c
FUNCTIONS 	+= ft_parcer_printf.c
FUNCTIONS 	+= form_num_char.c
FUNCTIONS 	+= ft_printbits_printf.c
FUNCTIONS 	+= ft_putchar_u.c
FUNCTIONS 	+= ft_putstr_u.c
FUNCTIONS 	+= ft_strlen_u.c
FUNCTIONS 	+= ft_strdup_u.c
FUNCTIONS 	+= ft_strndup_u.c
FUNCTIONS 	+= ft_color_input.c
FUNCTIONS 	+= ft_max_number.c
FUNCTIONS 	+= ft_printf_fd.c

OBJ 		= $(addprefix $(OBJ_DIR), $(FUNCTIONS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	ar rc $(NAME) $(OBJ) $(LIBFT_OBJ);

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	@echo $@///
	$(CC) -c $< -o $@ $(FLAGS) $(HEADER_FLAGS);

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
