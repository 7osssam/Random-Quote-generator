.PHONY: build clean run

COLOR_RED=\033[31m
COLOR_GREEN=\033[32m
COLOR_YELLOW=\033[33m
COLOR_RESET=\033[0m

PROJECT_NAME=RandomQuoteGenerator

build:
	@echo -e "$(COLOR_YELLOW)======== Building the project... ========$(COLOR_RESET)"
	mkdir -p build 
	cd build/ && cmake .. -G "MinGW Makefiles" && make
	@echo -e "$(COLOR_GREEN)======== Project built successfully! ========$(COLOR_RESET)"

run:
# check if the build directory exists
	@if [ ! -d build ]; then \
		echo -e "$(COLOR_RED)======== ERROR: Build the project first! ========$(COLOR_RESET)"; \
		exit 1; \
	fi
	@echo -e "$(COLOR_GREEN)======== Running the project... ========$(COLOR_RESET)"
	cd build/ && ./PROJECT_NAME

clean:
	@echo -e "$(COLOR_RED)======== Cleaning the build directory... ========$(COLOR_RESET)"
	rm -rf build

