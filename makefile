.PHONY: build clean run doc

COLOR_RED=\033[31m
COLOR_GREEN=\033[32m
COLOR_YELLOW=\033[33m
COLOR_RESET=\033[0m

PROJECT_NAME=RandomQuoteGenerator

# build the project
# 1. create a build directory
# 2. run cmake to generate the makefile in the build directory
# 3. run make to build the project wih options -j to speed up the build process
# 4. if the build is successful, print a success message
build:
	@echo -e "$(COLOR_YELLOW)======== Building the project... ========$(COLOR_RESET)"
	mkdir -p build
#	cd build/ && cmake .. -G "MinGW Makefiles" && make 
	cmake -S . -B build  && cmake --build build --config Release 
	@echo -e "$(COLOR_GREEN)======== Project built successfully! ========$(COLOR_RESET)"

# run the project
# 1. check if the build directory exists
# 2. run the project
# 3. if the build directory does not exist, print an error message
run:
# check if the build directory exists
	@if [ ! -d build ]; then \
		echo -e "$(COLOR_RED)======== ERROR: Build the project first! ========$(COLOR_RESET)"; \
		exit 1; \
	fi
	@echo -e "$(COLOR_GREEN)======== Running the project... ========$(COLOR_RESET)"
	cd build/ && ./$(PROJECT_NAME)

# generate documentation
# 1. generate Doxygen documentation
# 1.1. use cmake to build the documentation target
# 2. generate UML diagrams
# 2.1. use clang-uml to generate UML diagrams
doc:
	@echo -e "$(COLOR_YELLOW)======== Generating Doxygen documentation... ========$(COLOR_RESET)" 
	cmake --build build -t documentation 
	@echo -e "$(COLOR_YELLOW)======== Generating UML diagrams... ========$(COLOR_RESET)"
	clang-uml
	@echo -e "$(COLOR_GREEN)======== Documentation generated successfully! ========$(COLOR_RESET)"

# clean the build directory
# 1. remove the build directory
# 2. print a message to indicate that the build directory has been removed
clean:
	@echo -e "$(COLOR_RED)======== Cleaning the build directory... ========$(COLOR_RESET)"
#rm -rf build/
	cmake --build build --target clean


