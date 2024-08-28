# SQL-like Database 

## Project Overview
This project is a custom SQL-like database that includes a variety of fundamental data structures and algorithms to handle data storage, querying, and manipulation. The project has been implemented with custom-made functions for parsing, queue management, and tree structures, all aimed at emulating the core functionalities of a SQL database.

## File Structure

- **B+ Tree**: Implementation of B+ Tree for indexing.
- **Doubly Linked Lists**: Functions for managing linked lists.
- **Parser**: SQL parser for parsing query commands.
- **Queue**: Queue implementation used in query processing.
- **Shunting Yard**: Shunting Yard algorithm for converting SQL queries into a format that can be executed by the database engine.
- **SQL**: Core logic for SQL-like query execution.
- **Table**: Table data structure to manage rows and columns of the database.
- **Tokenizer**: Tokenizer to break down SQL queries into tokens for easier processing.

### Binary Files Overview
- **student.bin, student1.bin, ...**: Binary files storing serialized student data.
- **student.txt, student1.txt, ...**: Text files storing human-readable student data.


## Installation

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/yourusername/sql-project.git

## Usage
1. Console-based interactive sql interface where user can enter simple SQL command lines in an acceptable format.
2. Use the SQL-like query interface to perform operations such as `make table`,`select`, `insert into`, `from`, `where` on the tables.
3. The database supports simple queries with logical and relational operations.
4. Data can be exported back into text or binary format.

## Features
- **SQL-like Query Execution**: Supports basic SQL commands for interacting with data.
- **Custom Data Structures**: Implemented B+ Trees, Linked Lists, Stacks, and Queues.
- **Persistence**: Data can be stored and retrieved in both binary and text formats.

## Future Enhancements
- Support for `JOIN` operations across tables.
- Remove stored data.

## License
This project is licensed under the MIT License.