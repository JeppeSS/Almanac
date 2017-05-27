##
## Makefile for BSc Thesis
##
$(info The Almanac prototype)

$(info Requires)
$(info GMP Version 6.1.2, see https://gmplib.org/)
$(info MySQL Version 10.1.23)
$(info )

# Compile test files in test directory
TEST_DIR = test

# Ignore src folder
.PHONY: src

project_code:
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) -C $(TEST_DIR) clean
