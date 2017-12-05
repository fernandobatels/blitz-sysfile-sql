Blitz SysFile SQL
==

Interface sql para manipulação de diretórios do sistema de arquivos do SO.

Atualmente a aplicação permite usar comandos sql por meio do parâmetro '-r'. Exemplos:

![Exemplo](https://github.com/FernandoBatels/blitz-sysfile-sql/blob/master/demonstracao.gif)

Com um 'select name, size from Downloads' será possível listar os arquivos da pasta Downloads, por exemplo.

A ideia é se manter dentro dos padrões do SQL, porém com a devida liberdade para criar novos conceitos e funcionalidades.

Será provido uma interface ODBC(https://pt.wikipedia.org/wiki/ODBC), para que assim qualquer linguagem possa fazer uso desse servidor.

**Aplicação para fins de estudo**

**Objetivos**

- [x] Listagem de arquivos, algo como 'selec name, size from Downloads';
- [ ] Criação de arquivos, algo como 'insert into Downloads(name, content) value ("test.txt", "Content!")'
- [ ] Edição de arquivos, algo como 'update Downloads set content = "New content!" where name = "test.txt"'
- [ ] Exclusão de arquivos, algo como 'delete from Downloads where name = "test.txt"'
- [ ] Interface ODBC
