CC=gcc

CFLAGS=-std=c11 -Wall -Wextra -Werror ${FLAGS_DIR}
FLAGS_CAT=-Icat/cmd -Icat/internal -Icat/internal/error -Icat/internal/print

BUILD_DIR =build


SRCS_cat = $(shell find . -name '*.c')
OBJS_cat = $(patsubst %.c, $(BUILD_DIR)/$(notdir %).o, $(SRCS_cat:./%=%))

all: s21_cat 

#сборка cat
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(FLAGS_CAT) -c $< -o ${BUILD_DIR}/$(notdir $@)

s21_cat: $(OBJS_cat)
	$(CC) $(addprefix $(BUILD_DIR)/, ${notdir ${OBJS_cat}}) $(CFLAGS) -o s21_cat

clean:
	rm -rf $(BUILD_DIR)  s21_cat

rebuild: clean all

clang-format:
	find . -name "*.c" -or -name "*.h" | xargs clang-format -i -style=Google

cppcheck:
	cppcheck -I. --enable=all --suppress=missingIncludeSystem --std=c11 --check-config .

.PHONY: all clean
