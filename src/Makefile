##
## Makefile for BSc Thesis
##
$(info The Almanac prototype)

$(info Requires)
$(info GMP Version 6.1.2, see https://gmplib.org/)
$(info )

# Compile test files in test directory
TEST_DIR = test

# Ignore src folder
.PHONY: src

all: project_code
default: project_code

project_code:
	$(MAKE) -C $(TEST_DIR)

check:
	$(MAKE) -C $(TEST_DIR) check

crypTest:
	$(MAKE) -C $(TEST_DIR) crypTest

static:
	$(MAKE) -C $(TEST_DIR) static

clean:
	$(MAKE) -C $(TEST_DIR) clean
