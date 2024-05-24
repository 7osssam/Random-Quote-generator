# Random Quote generator 
This is a simple random quote generator that generates a random quote from a list of quotes, based on the user's input.
program will predict the user's mood based on the happyor sad words in the input and generate a quote accordingly (dummy prediction).

User will be asked to create a user at the first run of the program. The user will be saved in a CSV file with hashed password (SHA224),
with chain of responsibility pattern, the program will check for prequisites in password creation (length, digits, special characters) and will hash the password before saving it to the file.

## How to run the program
1. Clone the repository
3. Use the root directory makefile to run the program
```shell
make build
make run
```
4. Follow the instructions on the terminal to generate a quote

## Used Design Patterns
- Singleton
- Factory / Abstract Factory
- Strategy
- State Machine
- Chain of Responsibility

## TODO
- Output logs to a file
	- create a logger library 