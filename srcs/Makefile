# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 18:55:06 by qsomarri          #+#    #+#              #
#    Updated: 2024/10/02 16:50:06 by qsomarri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONUS_NAME = pipex_bonus

CC = @cc

CFLAGS = -Wall -Wextra -Werror -g

RM = @@rm -rf

MAKE = @make -C

SRCS_DIR = srcs

SRCS = $(SRCS_DIR)/pipex_utils.c \
       $(SRCS_DIR)/exec_cmd.c \
       $(SRCS_DIR)/pipex.c \
	   $(SRCS_DIR)/process.c

OBJ_DIR = obj

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

BONUS_SRCS_DIR = bonus

BONUS_SRCS =	$(BONUS_SRCS_DIR)/pipex_utils_bonus.c \
		$(BONUS_SRCS_DIR)/exec_cmd_bonus.c \
		$(BONUS_SRCS_DIR)/heredoc_bonus.c \
		$(BONUS_SRCS_DIR)/pipex_bonus.c \
		$(BONUS_SRCS_DIR)/process_bonus.c

OBJS_BONUS = $(BONUS_SRCS:$(BONUS_SRCS_DIR)/%:.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DI)/%.o: $(BONUS_SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cible principale
all: $(NAME)

# Création de l'exécutable
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft
		@echo "\033[0;92m * $(NAME) program file was created\033[0m *"

bonus :	$(LIBFT) $(OBJS_BONUS)
	@$(CC) -o $(BONUS_NAME) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_PATH) -lft
		@echo "\033[0;92m* $(BONUS_NAME) program file was created\033[0m *"


# Construction de la libft
$(LIBFT):
	@$(MAKE) $(LIBFT_PATH) all

# Création du répertoire des objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Nettoyage des fichiers objets
clean:
	@$(MAKE) $(LIBFT_PATH) clean
	@$(RM) $(OBJ_DIR)
	@echo "\033[0;91m* $(NAME) object files was deleted *\033[0m"

# Nettoyage complet
fclean: clean
	@$(MAKE) $(LIBFT_PATH) fclean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "\033[0;91m* $(NAME) was deleted *\033[0m"

# Reconstruction complète
re: fclean all

.PHONY: all clean fclean re bonus
