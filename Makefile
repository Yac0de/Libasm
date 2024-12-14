NASM = nasm
CC = gcc

CFLAGS = -Wall -Wextra -Werror
NASMFLAGS = -f elf64

NAME = libasm.a

SRC_DIR = .
OBJ_DIR = obj
TEST_DIR = tests

ASM_FILES = strlen strcpy strcmp write read strdup
TEST_FILES = libasm ft_strlen ft_strcpy ft_strcmp ft_write ft_read ft_strdup

SRCS = $(addprefix $(SRC_DIR)/ft_, $(addsuffix .s, $(ASM_FILES)))
OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(ASM_FILES)))
TESTS = $(addprefix $(TEST_DIR)/test_, $(addsuffix .c, $(TEST_FILES)))

GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)
	@echo -e "$(GREEN)[✔] Build completed.$(RESET)"

$(NAME): $(OBJS)
	@echo -e "$(BLUE)[*] Creating archive $(NAME)...$(RESET)"
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)
	@echo -e "$(GREEN)[✔] Archive $(NAME) created.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/ft_%.s
	@mkdir -p $(OBJ_DIR)
	@echo -e "$(YELLOW)[*] Assembling $<...$(RESET)"
	$(NASM) $(NASMFLAGS) $< -o $@

test_libasm: all
	@echo -e "$(BLUE)[*] Compiling and running tests...$(RESET)"
	$(CC) $(CFLAGS) $(TESTS) -L. -lasm -o test_libasm
	./test_libasm
	@echo -e "$(GREEN)[✔] Tests completed.$(RESET)"

clean:
	@echo -e "$(RED)[!] Cleaning object files and test outputs...$(RESET)"
	rm -rf $(OBJ_DIR) test*.txt

fclean: clean
	@echo -e "$(RED)[!] Removing binary files...$(RESET)"
	rm -f $(NAME) test_libasm
	@echo -e "$(GREEN)[✔] Clean complete.$(RESET)"

re: fclean all

.PHONY: all clean fclean re test_libasm