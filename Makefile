NAME = fillit

SOURCE_DIR = .
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
SOURCE_BASENAMES = $(notdir $(SOURCES))


LIBFT_DIR = ./lib/libft
INCLUDES = $(LIBFT_DIR) $(SOURCE_DIR)
CC = clang
CPP = clang -E
CFLAGS = -Wall -Werror -Wextra -I$(foreach d, $(INCLUDES), -I$d)

# ------------------------------------------------------------------------------#
# This method of directory creation is adapted from:
# https://gist.github.com/maxtruxa/4b3929e118914ccef057f8a05c614b0f

# intermediate directory for generated object files
OBJECT_DIR := .o

# object files, auto generated from source files
OBJECTS := $(patsubst %,$(OBJECT_DIR)/%.o,$(basename $(SOURCE_BASENAMES)))
# ------------------------------------------------------------------------------#


.SUFFIXES: # remove the default suffix rules, because the GNU Make manual states:
# Suffix rules are the old-fashioned way of defining implicit rules for make.
# Suffix rules are obsolete because pattern rules are more general and clearer.
# They are supported in GNU make for compatibility with old makefiles.
all: $(NAME)

$(NAME): $(SOURCES)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -lft -L$(LIBFT_DIR) $^ -o $@

clean:
	/bin/rm -rf $(OBJECT_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: clean all
	
debug: CFLAGS += -g -DDEBUG
debug: fclean all
