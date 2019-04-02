NAME = fillit

SOURCE_DIR = .
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
SOURCE_BASENAMES = $(notdir $(SOURCES))
SOURCES_MINUS_MAIN := $(filter-out main.c,$(SOURCES))
TEST_SOURCES = $(SOURCES_MINUS_MAIN) ./test/main.c

LIBFT_DIR = ./lib/libft
LIBLIST_DIR = ./lib/liblist
INCLUDES = $(LIBFT_DIR) $(LIBLIST_DIR) $(SOURCE_DIR)
CC = clang
CPP = clang -E
CFLAGS = -Wall -Werror -Wextra $(foreach d, $(INCLUDES), -I$d)
LINKER_FLAGS = -lft -L$(LIBFT_DIR) -llist -L$(LIBLIST_DIR)

.SUFFIXES: # remove the default suffix rules, because the GNU Make manual states:
# Suffix rules are the old-fashioned way of defining implicit rules for make.
# Suffix rules are obsolete because pattern rules are more general and clearer.
# They are supported in GNU make for compatibility with old makefiles.
all: $(NAME)

$(NAME): $(SOURCES)
	make -C $(LIBFT_DIR)
	make -C $(LIBLIST_DIR)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) $^ -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(LIBLIST_DIR) clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -rf $(NAME).dSYM
	make -C $(LIBFT_DIR) fclean
	make -C $(LIBLIST_DIR) fclean

re: fclean all

remove_executable:
	/bin/rm -f $(NAME)
	
debug: CFLAGS += -g -DDEBUG -DCOLORS -DDEBUG_MESSAGES
debug: remove_executable all

tests: test/main.c
	$(CC) $(CFLAGS) -g $(LINKER_FLAGS) $^ -o test/test_executable
	test/test_executable
