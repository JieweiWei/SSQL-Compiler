SSQL-Compiler
=============

SQL(short for Simplified SQL) is a subset of features in standard SQL language. The project is a compiler for SSQL.


SSQL
====
Four operations supported in SSQL
---------------------------------
  * Create a new table
  * Insert a row into an existed table
  * Delete rows from an existed table
  * Query on an existed table

Examples
--------
  * Standard SQL (MySQL)  
  SELECT S.sid AS id, SUM(C.score) AS score  
  FROM Student S, Courses C  
  WHERE S.sid == C.sid && S.age > 18  
  GROUP BY id  
  ORDER BY score  
  LIMIT 100;  
  * SSQL  
  SELECT sid, age  
  FROM Student  
  WHERE age > 15 && age < 18;

Context Free Grammar
--------------------
  * ssql_stmt -> create_stmt | insert_stmt | delete_stmt | query_stmt

  * create_stmt -> create table id(decl_list);
  * decl_list -> decl | decl_list, decl
  * decl -> id int default_spec | primary key (column_list)
  * default_spec -> default = simple_expr | ε
  * column_list -> id | column_list, id
  * id (identifier) is a sequence of digits, underline and letters. All identifiers should start with a letter or an underline. The maximum length of an identifier is 64.
  * simple_expr -> simple_term | simple_expr + simple_term | simple_expr - simple_term
  * simple_term -> simple_unary | simple_term * simple_unary | simple_term / simple_unary
  * simple_unary -> (simple_expr) | -simple_unary | +simple_unary | num
  * num (number) is a sequence of digits. (of 32-bits)
  * Reserved keywords are case-insensitive.
  * If the default value is not specified, 0 is used implicitly.
  * A valid create statement is:
    - can be derived from the context free grammar
    - no duplicate column names
    - no two or more primary key declarations
    - primary key contains only columns in the table
    - table name doesn't match with any existed table
    - # of columns in a table should <= 100
    - # of columns in primary key declaration <= 100
  * If a create statement is successfully executed, materialize a table with the specified schema.

  * insert_stmt -> insert into id(column_list) values (value_list);
  * value_list -> simple_expr | value_list, simple_expr
  * A valid insert statement is:
    - can be derived from the context free grammar
    - the table should exist
    - no duplicate columns
    - all columns should be in the schema of the table
    - # of columns should equal to # of values
    - no primary key constraint violation
  * For a column without specified value, default value is used. If an insert statement is executed successfully, a new row will be inserted into the table.

  * delete_stmt -> delete from id where_clause;
  * where_clause -> where conjunct_list | ε
  * conjunct_list -> bool | conjunct_list && bool
  * bool -> operand rop operand
  * operand -> num | id
  * rop -> <> | == | > | < | >= | <=
  * A valid delete statement is:
    - can be derived from the context free grammar
    - the table should exist
    - columns occurring in the where clause (if any) should be in the schema of the table
  * If there is a where clause, delete all rows whose where clause is evaluated to be TRUE. Otherwise, delete all rows in the table.

  * query_stmt -> select select_list from id where_clause;
  * select_list -> column_list | *
  * A valid query statement is:
    - can be derived from the context free grammar
    - the table should exist
    - all columns (except * ) in the select list should be in the schema of the table
    - columns occurring in the where clause (if any) should be in the schema of the table
  * If a where clause is present, those rows whose where clauses are evaluated to FALSE should be omitted. Otherwise, none should be omitted.
  * If ' * ' is present in the select list, all columns should be returned. Otherwise, return only those columns specified in the select list.


Implementation Notes
====================
  * C/C++ only, no external tools (flex, bison, and the like) except STL
  * Lexer - implement using a deterministic finite automaton
  * Parser - implement a predictive parser

Program Input
=============
Correct Input
-------------
  * You can pass a file system path to a ASCII file containing several SSQL statements to the program when you run the program.
    - eg:
    ```shell
    $ ./ssql "/home/jerry/Code/test.txt"
    ```
  * The program has to read the file and interpret the statements in the file.

Erroneous Input
---------------
  * The input may contain ill-formed statements. the program will print meaningful error prompts when it encounters one.
  * When an error is encountered, stop parsing or executing the current statement and continue to parse and execute the next statement.


Program Output
==============
  * When an error is encountered, print meaningful error prompts. (which line, which column, what's the error ...)
  * If the execution succeeds, print a message telling the success.
  * Specially, for a query, print the result in a neat way. The effect should be similar to:
  ```shell
  +--------+--------+  
  |   sid  |   age  |  
  +--------+--------+  
  |    1   |   18   |  
  +--------+--------+  
  |    2   |   19   |  
  +--------+--------+  
  ```
