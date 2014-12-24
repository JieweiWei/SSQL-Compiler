SSQL-Compiler
=============

SQL(short for Simplified SQL) is a subset of features in standard SQL language. The project is a compiler for SSQL.


## Four operations supported in SSQL
  * Create a new table
  * Insert a row into an existed table
  * Delete rows from an existed table
  * Query on an existed table


## Examples
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


## Context Free Grammar
  * ssql_stmt -> create_stmt | insert_stmt | delete_stmt | query_stmt
  * create_stmt -> create table id(decl_list)
  * decl_list -> decl | decl_list, decl
  * decl -> id int default_spec | primary key (column_list)
  * default_spec -> default = num | ε
  * column_list -> id | column_list, id
  * id (identifier) is a sequence of digits, underline and letters. All identifiers should start with a letter or an underline. The maximum length of an identifier is 64.
  * num (number) is a sequence of digits. (of 32-bits)
  * Reserved keywords are case-insensitive.
  * If the default value is not specified, 0 is used implicitly.
