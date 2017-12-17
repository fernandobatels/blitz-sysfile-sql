# Blitz SysFile SQL

Sql interface to manipulate file and folder of SO.

**This project is for study purposes**, but you can use it where you want at your own risk. 

Contribuite with me on this challenge :), sending me issues or/and pull requests :)

## Concept

Folders are equivalent to tables, files are equivalent to rows and infos about files/folders like size, name, content and more are equivalent to columns.

This means that you will not be able to create tables with custom columns, for example.

[DDL](https://en.wikipedia.org/wiki/Data_definition_language) commands will be used to manipulate folders like use 'create table /tmp/test...' to create folder.

[DML](https://en.wikipedia.org/wiki/Data_manipulation_language) commands will be used to manipulate files like use 'insert into /tmp/test.txt(name,content)...' to create new file.

The biggest challange is to create an [ODBC](https://en.wikipedia.org/wiki/Open_Database_Connectivity) interface/server, so tha any language/framework can make use of.

You need more? Help me to aprimore the conecept and write unit tests :)

## Example:

With select command like 'select name, size from /tmp' you receive the list of files/folders on /tmp.

![Demo](https://github.com/FernandoBatels/blitz-sysfile-sql/blob/master/demonstracao.gif)

**Features**

- [x] List of files/folders
    - Example: 'selec name, size from Downloads'
- [x] Create files
    - Example: 'insert into Downloads(name, content) value ("test.txt", "Content!")'
- [ ] Update files
    - Example: 'update Downloads set content = "New content!" where name = "test.txt"'
- [ ] Remove files
    - Example: 'delete from Downloads where name = "test.txt"'
- [ ] Interface ODBC
- [ ] Create folders
    - Example: 'create table DownloadsTest'
- [ ] Remove fodlers
    - Example: 'drop folder DownloadsTest'
