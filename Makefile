CC ?= cc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Werror -g -Iinclude

# Choose backend: dll or sll
LIST_IMPL ?= dll

LIST_SRC_dll := src/list/doublelinkedlist.c
LIST_SRC_sll := src/list/singlelinkedlist.c

LIST_SRC := $(LIST_SRC_$(LIST_IMPL))

TEST_SRC := tests/test_runner.c tests/test_list_api.c

# Output Directories
BIN_DIR := bin
TEST_BIN := $(BIN_DIR)/tests_$(LIST_IMPL)

.PHONY: test sanitize clean

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Main compile rules
$(TEST_BIN): $(LIST_SRC) $(TEST_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# test target
test: $(TEST_BIN)
	./$(TEST_BIN)

# sanitize target
sanitize: CFLAGS := $(CFLAGS) -O1 -fsanitize=address,undefined -fno-omit-frame-pointer
sanitize: clean test

# clean target
clean:
	rm -rf $(BIN_DIR)
