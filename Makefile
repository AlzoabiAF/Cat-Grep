CC=gcc

CFLAGS=-std=c11 -Wall -Wextra -Werror ${FLAGS_DIR}
FLAGS_CAT=-Icat/cmd -Icat/internal -Icat/internal/error -Icat/internal/print
FLAGS_GREP=-Igrep/cmd -Igrep/internal -Igrep/internal/error -Igrep/internal/print

BUILD_DIR =build

SRCS_CAT = $(shell find ./cat -name '*.c')
OBJS_CAT = $(patsubst %.c, cat/$(BUILD_DIR)/$(notdir %).o, $(SRCS_CAT:./%=%))  

SRCS_GREP = $(shell find ./grep -name '*.c')
OBJS_GREP = $(patsubst %.c, grep/$(BUILD_DIR)/$(notdir %).o, $(SRCS_GREP:./%=%))

all: install s21_cat s21_grep 

#сборка cat
cat/$(BUILD_DIR)/%.o: %.c
	mkdir -p cat/$(BUILD_DIR)
	$(CC) $(CFLAGS) $(FLAGS_CAT) -c $< -o cat/${BUILD_DIR}/$(notdir $@)
s21_cat: $(OBJS_CAT)
	$(CC) $(addprefix cat/$(BUILD_DIR)/, ${notdir ${OBJS_CAT}}) $(CFLAGS) -o cat/s21_cat

#сборка grep
grep/$(BUILD_DIR)/%.o: %.c
	mkdir -p grep/$(BUILD_DIR)
	$(CC) $(CFLAGS) $(FLAGS_GREP) -c $< -o grep/${BUILD_DIR}/$(notdir $@)
s21_grep: $(OBJS_GREP)
	$(CC) $(addprefix grep/$(BUILD_DIR)/, ${notdir ${OBJS_GREP}}) $(CFLAGS) -o grep/s21_grep

clean:
	rm -rf */$(BUILD_DIR) cat/s21_cat grep/s21_grep

rebuild: clean all

clang-format:
	find . -name "*.c" -or -name "*.h" | xargs clang-format -i -style=Google

cppcheck:
	cppcheck -I. --enable=all --suppress=missingIncludeSystem --std=c11 --check-config .

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cat/s21_cat -e cat/test1.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./grep/s21_grep -inoe gre -e GREP grep/1test.txt grep/test2.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./grep/s21_grep -inof grep/test2.txt grep/test.txt grep/test2.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./grep/s21_grep -ino gre grep/test.txt grep/test2.txt

install:
ifeq ($(shell uname -s),Linux)
	sudo apt install -y clang-format
	sudo apt install valgrind
endif
ifeq ($(shell uname -s),Darwin)
	brew install clang-format
	brew install valgrind
endif

.PHONY: all clean
