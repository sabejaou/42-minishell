NAME=libft.a

#------------------------------------------------------------------------------#
# 							VARIABLES										   #
#------------------------------------------------------------------------------#

SRCS_DIR= ./srcs

include source.mk

SRCS:= $(SRCS:%=$(SRCS_DIR)/%) \

OBJS_DIR= ./objs

OBJS=$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INCS= ./incs

DEPS= $(OBJS:.o=.d)


#------------------------------------------------------------------------------#
# 							COMMANDS									       #
#------------------------------------------------------------------------------#

CC= cc

CFLAGS= -Werror -Wextra -Wall -g3 -MMD -MP

RM= rm -rf

CFSIGSEV = -fsanitize=address

DIR_DUP= mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

#------------------------------------------------------------------------------#
# 							RULES											   #
#------------------------------------------------------------------------------#

all:$(NAME)

-include $(DEPS)

$(NAME): $(OBJS) $(INCS)
	$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@

fsanitize:
	$(MAKE) CFLAGS="$(CFLAGS) $(CFSIGSEV)"

clean:
	$(RM) $(OBJS_DIR)

fclean:clean
	$(RM) $(NAME)
	rm -f a.out

re:fclean all

.PHONY: all clean fclean re

# Colors
BLACK=\033[30m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
PURPLE=\033[35m
CYAN=\033[36m
WHITE=\033[37m

# Text
ERASE=\033[2K\r
RESET=\033[0m
BOLD=\033[1m
FAINT=\033[2m
ITALIC=\033[3m
UNDERLINE=\033[4m