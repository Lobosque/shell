/**
 * @mainpage Shell
 * @author Lucas Lobosque - 6792645
 * @author José Leandro Pozer - 6793222
 * @date 16/11/2011
 *
 * @section intro Introdução
 *
 * @subsection estrutura_basica_subsec Estrutura básica de Arquivos
 * Desenvolvemos o shell utilizando 4 arquivos diferentes (e seus headers):
 * 
 * <ul>
 *	<li>main.c	-	Arquivo com a função main, onde fica o loop principal e com handlers de sinais como SIGINT, SIGTSTP e SIGCHLD.</li>
 *	<li>parser.c	-	Funções relacionadas a transformar a entrada do usuário em uma estrutura compreensível para o programa.</li>
 *	<li>builtin.c	-	Aqui estáo todos os comandos builtin e também uma função que checa se um dado comando é builtin ou não.</li>
 *	<li>list.c	-	Funções que manipulam as listas usadas pelo programa.</li>
 * </ul>
 *
 * @subsection estrutura_dados_subsec Estrutura básica de Dados
 * No nosso programa, temos três listas ligadas diferentes que são constantemente utilizadas:
 * <ul>
 *	<li>history	-	Esta é a mais simples das três. Guarda strings com os comandos anteriormente utilizados pelo usuário. É usada pelo comando builtin history.</li>
 *	<li>childs	-	Nesta lista ligada armazenamos todos os processos que estão rodando ou estão interrompidos.</li>
 *	<li>cmdList	-	Lista responsável por guardar o último comando enviado pelo usuário. Nesta lista, o comando é guardado depois de "parseado", então todas suas informações são
 * guardadas aqui (roda no background? tem redirecionamento de saída? pra onde?). Cada item da lista é um comando diferente, sendo que a lista e sempre resetada no loop. Ou seja, esta lista só conterá mais de um item se houver pipe no comando.</li>
 * </ul>
 *
 * @section section_toc Características Não Implementadas (limitações).
 * Na nossa shell, os seguintes tipos de comando não são possíveis:
 * <ul>
 * <li>Comando builtin rodando em background (sempre rodará em foreground).</li>
 * <li>Redirecionamento de entrada para comandos builtin (redirecionamento de saída implementado).</li>
 * <li>Pipe com comandos builtin</li>
 * </ul>
 * Tornou-se uma tarefa complicada para nós lidar com essas peculiaridades de comandos builtin, já que implementamos sem elas em mente, e, quando percebemos que haveriam essas possibilidades, teríamos que mudar muito a estrutura do programa.
 *
 * @section testes Testes
 * Além de exaustivos testes com vários comandos complexos, rodamos nossa shell com o Valgrind e encontramos vários memory leaks (a maioria causada por erros bobos, porém alguns eram bem complexos).
 * Arrumamos a maioria deles, mas infelizmente teve um leak que não foi possível concertar, pois ele é causado pela função getlogin(), (implementada na unistd.h).
 * @section conclusao Conclusão
 * Além de bastante desafiador, o desenvolvimento da shell foi de grande valia para nós, já que nunca tivemos um contato a nível de sistema com o Linux. Depois do desenvolvimento desse programa, arriscamos dizer que entendemos ao menos um pouco de Linux :).
*/
