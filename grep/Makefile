CC=gcc

CFLAGS=-std=c11 -Wall -Wextra -Werror ${FLAGS_DIR}
FLAGS_CAT=-Icat/cmd -Icat/internal -Icat/internal/error -Icat/internal/print
FLAGS_GREP=-Igrep/cmd -Igrep/internal -Igrep/internal/error -Igrep/internal/print

BUILD_DIR =build


SRCS_GREP = $(shell find . -name '*.c')
OBJS_GREP = $(patsubst %.c, $(BUILD_DIR)/$(notdir %).o, $(SRCS_GREP:./%=%))

all: s21_grep 

#сборка grep
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(FLAGS_GREP) -c $< -o ${BUILD_DIR}/$(notdir $@)

s21_grep: $(OBJS_GREP)
	$(CC) $(addprefix $(BUILD_DIR)/, ${notdir ${OBJS_GREP}}) $(CFLAGS) -o s21_grep

clean:
	rm -rf $(BUILD_DIR)  s21_grep

rebuild: clean all

cppcheck:
	cppcheck -I. --enable=all --suppress=missingIncludeSystem --std=c11 --check-config .

.PHONY: all clean
