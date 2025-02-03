#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

.PHONY: all bonus clean fclean re
# .SILENT:

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Detect OS
UNAME := $(shell uname -s)

# Set flags based on OS
ifeq ($(UNAME), Darwin)  # macOS
    READLINE_INC = -I/opt/homebrew/opt/readline/include
    READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lhistory
endif

# Compiler and flags
CC			=	gcc
CFLAGS		=	$(INCLUDES) $(DEBUG)
TEMP		=	-Wall -Werror -Wextra
INCLUDES	=	-I$(INC_LIBFT) -I$(INC_DIR) $(READLINE_INC)
DEBUG		=	-g3
FSAN_ADD	=	-fsanitize=address
FSAN_MEM	=	-fsanitize=memory
RM			=	rm -rf

# Output file name
NAME	=	minishell

# Directories
LIBFT_DIR		=	libft
INC_LIBFT		=	libft/includes
INC_DIR			=	includes/
SRCS_DIR		=	srcs/
OBJS_DIR		=	bin/

LIB_FLAGS		=	-L$(LIBFT_DIR) -lft $(READLINE_LIB) -lreadline

SRCS_FILES		=	srcs/main.c \
					srcs/init.c \
					srcs/utils/utils_free.c \
					srcs/utils/utils_t_envp.c \
					srcs/utils/utils_t_cmd.c \
					srcs/utils/utils_t_io_fds.c \
					srcs/utils/utils_t_token.c\
					srcs/debug/print_struct.c \
					srcs/error.c \
					srcs/parser/parse_input.c \
					srcs/parser/0.tokenization/lexer.c \
					srcs/parser/0.tokenization/utils_lexer.c \
					srcs/parser/1.parse_tokens/utils_parse_token_1.c \
					srcs/parser/1.parse_tokens/utils_parse_token_2a.c \
					srcs/parser/1.parse_tokens/utils_parse_token_2b.c \
					srcs/parser/1.parse_tokens/utils_parse_token_3.c \
					srcs/parser/2.commands/construction.c \
					srcs/parser/2.commands/0_parse_word.c \
					srcs/parser/2.commands/1_parse_redirect_in.c \
					srcs/parser/2.commands/2_parse_redirect_out.c \
					srcs/parser/2.commands/3_parse_heredoc.c \
					srcs/parser/2.commands/4_parse_append.c \
					srcs/parser/2.commands/5_parse_pipe.c \
					srcs/execution/execute.c \
					srcs/execution/prepare_commands.c \
					srcs/execution/handle_stdio.c \
					srcs/execution/utils_pipe_commands.c \
					srcs/execution/builtins/cd.c \
					srcs/execution/builtins/env.c \
					srcs/execution/builtins/export.c \
					srcs/execution/builtins/pwd.c\
					srcs/execution/builtins/echo.c \
					srcs/execution/builtins/unset.c \
					srcs/execution/builtins/exit.c \


OBJS_FILES		=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS_FILES))

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

bonus: all

# Generates output file
$(NAME): $(OBJS_FILES)
	make -C $(LIBFT_DIR)
	make clean -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_FILES) -o $(NAME) $(LIB_FLAGS)

# Rule to compile the object files
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the object directory if it doesn't exist
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

remake_libft:
	make re -C $(LIBFT_DIR)

# Removes objects
clean:
	$(RM) $(OBJS_DIR)

# Removes objects and executables
fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

# Removes objects and executables and remakes
re: fclean $(OBJS_DIR) all

test:
	make remake_libft
	$(CC) $(CFLAGS) test.c $(LIB_FLAGS)

test_clean:
	rm -rf a.out
	make fclean
