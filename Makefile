# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 10:00:00 by sabejaou          #+#    #+#              #
#    Updated: 2024/05/30 10:00:00 by sabejaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

# Sources par module
SRCS_CORE = $(wildcard $(SRC_DIR)/core/*.c)
SRCS_BUILTINS = $(wildcard $(SRC_DIR)/builtins/*.c)
SRCS_EXEC = $(wildcard $(SRC_DIR)/exec/*.c)
SRCS_PARSING = $(wildcard $(SRC_DIR)/parsing/*.c)
SRCS_EXPAND = $(wildcard $(SRC_DIR)/expand/*.c)
SRCS_SIGNAL = $(wildcard $(SRC_DIR)/signal/*.c)
SRCS_UTILS = $(wildcard $(SRC_DIR)/utils/*.c)

# Sources libft
LIBFT_SRCS = $(shell find $(LIBFT_DIR)/srcs -name '*.c')
LIBFT_OBJS = $(LIBFT_SRCS:$(LIBFT_DIR)/srcs/%.c=$(OBJ_DIR)/libft/%.o)

# Objets
OBJS_CORE = $(SRCS_CORE:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BUILTINS = $(SRCS_BUILTINS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_EXEC = $(SRCS_EXEC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_PARSING = $(SRCS_PARSING:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_EXPAND = $(SRCS_EXPAND:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_SIGNAL = $(SRCS_SIGNAL:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_UTILS = $(SRCS_UTILS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/incs
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS_CORE) $(OBJS_BUILTINS) $(OBJS_EXEC) $(OBJS_PARSING) $(OBJS_EXPAND) $(OBJS_SIGNAL) $(OBJS_UTILS) $(LIBFT_OBJS)
	@echo "Edition des liens pour $(NAME)..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS_CORE) $(OBJS_BUILTINS) $(OBJS_EXEC) $(OBJS_PARSING) $(OBJS_EXPAND) $(OBJS_SIGNAL) $(OBJS_UTILS) $(LIBFT_OBJS) $(LIBS)
	@echo "Binaire $(NAME) créé avec succès !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/libft/%.o: $(LIBFT_DIR)/srcs/%.c | $(OBJ_DIR)/libft
	@mkdir -p $(dir $@)
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/libft:
	@mkdir -p $(OBJ_DIR)/libft

clean:
	@echo "Nettoyage des fichiers objets..."
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage terminé !"

fclean: clean
	@echo "Nettoyage complet..."
	@rm -f $(NAME)
	@echo "Nettoyage complet terminé !"

re: fclean all

test: all
	@echo "Test de compilation terminé !"

.PHONY: all clean fclean re test 