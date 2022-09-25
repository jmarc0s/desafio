#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <math.h>
#include <time.h>


//aqui eu estabele�o todas as structs necessarias  
typedef struct {
    char tp_cartao[100]; //variavel com o tipo de cart�o (poupan�a, debito, credito etc)
    char nome_dono[100];  //aqui o cart�o recebe o nome do usuario que criou o cartao
    char identificao[100]; //identifca�o se � visa master card etc
    
    // como o numero do cartao � composto por 16 numeros separados em 4 sequencias de numeros de 4 algarismos eu criei 4 variaveis do tipo char para cada sequencia de numero 
    char psn[100]; //primeira sequencia de numero
    char ssn[100]; //segunda sequencia de numero
    char tsn[100]; //terceira sequencia de numero
    char qsn[100]; //quarta sequencia de numero

    int cvc; // a variavel para  o cvc do cartao foi tipo int mesmo
    
    //para a data de validade eu criei 2 variaveis do tipo int, uma pro mes e outra pro ano
    int dt_validade_mes; 
    int dt_validade_ano;
}cartoes;

/* logo em seguida eu criei 4 variaveis do tipo int para os numeros do meu cart�o de cr�dito. essas s�o variaveis que servem apenas para gerar o numero do cart�o, depois que os numeros 
s�o gerados, os numeros s�o armazenados dentro dos membros da struct cart�o. No mundo real os numeros dos cartoes de credito s�o gerados da seguinte maneira, o primeiro digito referece a 
identifica��o do cart�o (se � visa, master card ou outros), por exemplo se o primeiro digito for 4 significa que a identifica��o dele � visa. normalmente cada banco utiliza 
apenas um tipo de identifica�a�. Ou seja, a partir daqui eu j� escolho a identifica��o com a qual eu vou criar os meus cartoes que vai ser visa, ent�o o primeiro digito do meu numero de
cartao vai ser 4. do segundo ao sexto digito s�o usados para se referir a agencia bancaria, ou seja, esses 5 digitos s�o um numero de identifica��o da agencia bancaria, no meu caso
eu escolhi o numero 00019 para se referir a minha agencia bancaria. ent�o eu estabeleci a minha primeira sequencia de numeros como 4000 e a segunda como 1900 (os 2 ultimos algaritimos
v�o mudar de acordo com a conta do usuario) assim quando eu exebir os numeros eles ser�o exbidos 4000 1900 com o 4 se referindo a identifica��o do cartao e o 00019 se referindo a minha
agencia bancaria. do setimo ao decimo quinto digito s�o relacionados ao usuario e ao numero de conta bancaria dele, no meu caso, eu usei do setimo digito ate o decimo sexo para relacionar
com a posi��o do usuario dentro do do cadastro de clientes e com a posi��o do vetor da cria��o do cart�o.
*/
int pri_seque_num = 4000;
int se_seque_num = 1900;
int ter_seque_num = 0000;
int qua_seque_num = 0000;


int aleatorio; //essa variavel sera utilizada para calcular os anos de utilidades do cart�o, depois ela sera somada com a data atual para assim chegar ate a data de validade

/*todas essas variavis s�o usadas na area do usuario. elas s�o variaveis que ficar�o responsaveis por armazenar os dados que o usuario digita
(numero do cartao de credito ao ser cadastrado por exemplo), depois que esses dados forem armazenados, eles ir�o ser relacionados com os membros (ou variaveis de cada struct) */
char cad_sq1[100];
char cad_sq2[100];
char cad_sq3[100];
char cad_sq4[100];
int cad_mes;
int cad_ano;
int cad_cvc;
char cad_nome_dono[100];
int cad_identificao;


//cadastros de clientes//
typedef struct {
	cartoes cts[6];
    char nome[100];
    char cpf[100];
    char email[100];
    char telefone[100];
    char address[100];
    int  tp_conta;
    char senha[100];
    char confirm_senha[100];
    int qtd_cts_por_clt;
}cliente;
cliente clt[100];


int sqct;
//variaveis usadas para gerar o numero de catao
int pct; 
char vari_concatena[100];
char tsnt[100];
char qsnt[100];


int tp_cartao_provisorio; /*usada para armazenar o numero que o usuario digitar, quando o usuario digitar um numero referente a um determinado tipo de cart�o, o programa vai verificar
esse numero e vai adicionar a variavel do tipo char dentro da struct cartoes o tipo de cartao correspondente
*/





int opcao=0; //captura op�o que o usuario digitar
int qtd_clt=0; //referece ao numero de clientes cadastrados

//variaveis de controle usadas em whiles e fors
int x = 0; 
int i = 0; 

//variaveis utilizadas para relacionar os dados que o usuario digitou com os dados cadastrados
int re;
int re1;
int re2;
int re3;
char log_senha[100];
char log_cpf[100];
int usuario;

//op�oes do usuario
int op_usuario;
int op_sair;
int main()
{
    printf("BEM VINDO!! \n");
    
	while(1){
		//exibo um menu de op�oes para o usuario, ele deve digitar o numero correspondente a op��o, se ele digitar um numero invalido o while vai reiniciar e pedir para que ele digite uma op��o valida
	    printf("ESCOLHA O NUMERO DE UMA DAS OPCOES ABAIXO: \n");
	    printf("1.CADASTRAR \n2.LOGIN \n3.SAIR \nOPCAO: ");
	    scanf("%d", &opcao); //capturo o que digitou
	    
	    //se o usuario tiver escolhido a op�a� 1:
	    if(opcao==1){
	    	system("cls");
	    	printf("PREENCHA AS INFORMA��ES ABAIXO PARA REALIZAR O CADASTRO \n");
	    	printf("nome completo: ");
	    	scanf(" %[^\n]", clt[qtd_clt].nome); //captura o nome do usuario
	    	printf("Email: ");
		    scanf("%s", clt[qtd_clt].email); //captura o nome do usuario
	    	
	    	//verifica se o email j� n�o est� sendo utilizado
	    	while(x < qtd_clt){
				
		    	re = strcmp(clt[qtd_clt].email, clt[i].email); //relaciona as variaveis. se duas variaveis tivrem os mesmos caracteres a fun��o strcmp retornara o valor zero que sera armazendo na variavel re
		    	if (re == 0){
		    		
					printf("email ja cadastrado! \n");
		    		printf("digite outro email: \n");
		    		scanf("%s", clt[qtd_clt].email);
					re = strcmp(clt[qtd_clt].email, clt[i].email);		
					    		
		    		//as variaveis de controle s�o reiniciadas para poderem verificar todos os emails digitados de novo
		    		i=0; 
		    		x=0;
		    		
				}
				
				else{
					//incremento as variaveis
					x++;
					i++;
				}
				
				
			
				
			}
	    	
	    	//as variaveis de controle s�o reiniciadas para poderem verificar todos os emails digitados de novo
	    	i=0;
		    x=0;
	    	
	    	printf("CPF: ");
	    	scanf("%s", clt[qtd_clt].cpf);
	    	
	    	
	    	//verifica se o cpf j� n�o est� sendo utilizado
	    	
	    	while(x < qtd_clt){
				
		    	re = strcmp(clt[qtd_clt].cpf, clt[i].cpf);
				
		    	if (re == 0){
		    		
					printf("CPF ja cadastrado! \n");
		    		printf("digite outro CPF: \n");
		    		scanf("%s", clt[qtd_clt].cpf);
					re = strcmp(clt[qtd_clt].cpf, clt[i].cpf);		    		
		    		i=0; //as variaveis de controle s�o reiniciadas para poderem verificar todos os emails digitados de novo
		    		x=0;
		    		
				}
				
				else{
					//incremento as variaveis
					x++;
					i++;
				}
				
				
			
				
			}
			
			//as variaveis de controle s�o reiniciadas para poderem verificar todos os emails digitados de novo
			i=0;
		    x=0;
			
			
			
	    	printf("telefone: ");
	    	scanf(" %[^\n]", clt[qtd_clt].telefone);
	    	
	    	
	    	//verifica se o telefone j� n�o est� sendo utilizado
	    	while(x < qtd_clt){
				
		    	re = strcmp(clt[qtd_clt].telefone, clt[i].telefone);
			
		    	if (re == 0){
		    			
					printf("telefone ja cadastrado! \n");
		    		printf("digite outro telefone: \n");
		    		scanf("%s", clt[qtd_clt].telefone);
					re = strcmp(clt[qtd_clt].telefone, clt[i].telefone);		    		
					
					//as variaveis de controle s�o reiniciadas para poderem verificar todos os emails digitados de novo
		    		i=0;
		    		x=0;
		    		
				}
				
				else{
					//incremento as variaveis
					x++;
					i++;
				}
				
				
			
				
			}
			//as variaveis de controle s�o reiniciadas para poderem verificar todos os emails digitados de novo
			
			i=0;
		    x=0;
		    
		    
	    	printf("endereco: ");
	    	scanf(" %[^\n]", clt[qtd_clt].address);
	    	printf("digite o numero do tipo de conta que deseja \n1.Poupanca \n2.Corrente \ntipo:");
	    	
	    	//captura e verifica se o usuario digitou um numero correspondente ao tipo de contavalido
	    	while(1){
	    		scanf("%d", &clt[qtd_clt].tp_conta);
	    		if(clt[qtd_clt].tp_conta != 2 && clt[qtd_clt].tp_conta != 1){
	    			printf("digite um n�mero de conta v�lido!:");
				}
				
				else{
					break;
				}
			}
	    	
	    	printf("senha: ");
	    	scanf(" %[^\n]", clt[qtd_clt].senha); //captura a senha 
	    	printf("confime senha: ");
	    	
	    	//verifica se a senha e a confirma��o de senha s�o iguais
	    	while(1){
			scanf(" %[^\n]", clt[qtd_clt].confirm_senha);
			re = strcmp(clt[qtd_clt].confirm_senha, clt[qtd_clt].senha);
			
			if(re!=0){
				printf("a confirma��o de senha n�o � igual a senha anterior \nconfirme a senha novamente:");
				
			}
			
			else{
				break;
			}
			
			}
			
			
	    	system("cls");
	    	printf("CADASTRO CONCLUIDO! \n\n\n\n");
	    	qtd_clt++; //incrementa a quantidade de clientes cadastrados
	    	
		 
		}
		
		
		
		
		
		
		
		
		
		
		
		
	    else if (opcao==2){
	    	
	    	//area do usuario
	    	system("cls");
	    	printf("Digite o seu cpf e sua senha para logar \n");
	    	
	    	while(1){
				printf("login \n");
		    	printf("CPF:");
		    	scanf("%s", log_cpf);
		    	printf("senha:");
		    	scanf("%s", log_senha);
		    	
		    	for(usuario = 0; usuario < qtd_clt; usuario++){
		    		re = strcmp(log_cpf, clt[usuario].cpf);
		    		re2 = strcmp(log_senha, clt[usuario].senha);
		    	
		    		
		    		if(re2 == 0 && re == 0){
		    			break;
					} 
		    		    		
				}
				
				if(re2 !=0 || re!=0){
		    			printf("cpf ou senha n�o correspondente \nverifique se digitou o seu cpf e senha corretamente \n");
				}
				
				else{
					system("cls");
					printf("OLA, %s \n\n", clt[usuario].nome);
					while(1){
						
						printf("============================================O QUE DESEJA FAZER?============================================\n\n");
						printf("1.criar cart�o \n2.cadastrar cart�o \n3.listar cartoes \n4.voltar para a tela de inicio \n\n\n");
						printf("digite um numero de uma das opcoes acima:");
						scanf("%d", &op_usuario);
						
						if(op_usuario==4 ){
							op_sair=1;
							break;
							
						}
					
						
						else{
							
							
							switch(op_usuario){
							
							case 1:
								system("cls");
								
								if(clt[usuario].qtd_cts_por_clt >= 6){
									printf("voce atingiu o limite de cartoes criados!! Voce n�o pode criar mais cartoes \n\n");
								}
								
								else{
									printf("criar cart�o \n\n");
									
									while(1){
										printf("escolha um tipo de cart�o abaixo \n1.poupan�a \n2.credito \n3.debito \n4.credito e debito \n5.poupan�a e debito \n\n");
										printf("digite o numero de uma das op��es acima: ");
										scanf("%d", &tp_cartao_provisorio);
										
										if(tp_cartao_provisorio == 1 || tp_cartao_provisorio == 2 || tp_cartao_provisorio == 3 || tp_cartao_provisorio == 4 || tp_cartao_provisorio == 5){
										 	
										 	if(tp_cartao_provisorio==1){
										 		strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].tp_cartao, "POUPAN�A");
											 }
											 
											 else if(tp_cartao_provisorio==2){
											 	strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].tp_cartao, "CREDITO");
											 }
											 
											 else if(tp_cartao_provisorio==3){
											 	strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].tp_cartao, "DEBITO");
											 }
											 
											 else if(tp_cartao_provisorio==4 ){
											 	strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].tp_cartao, "CREDITO E DEBITO");
											 }
											 
											 else{
											 	strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].tp_cartao, "POUPAN�A E DEBITO");
											 }
										 	
										 	ter_seque_num = (usuario+10)*10;
										 	
										 	
										 	
										 	
										 	
										 	qua_seque_num = ter_seque_num/2 + (clt[usuario].qtd_cts_por_clt+100);
										 	
										 	
										 	
										 	pct = 0.30*ter_seque_num;
										 	
										 	while(pct >= 100){
										 		pct--;
											 }
											 
											se_seque_num+=pct;
											
											if(se_seque_num+clt[usuario].qtd_cts_por_clt>=2000){
												se_seque_num = se_seque_num-clt[usuario].qtd_cts_por_clt;
											}
											
											else{
												se_seque_num = se_seque_num+clt[usuario].qtd_cts_por_clt;
											}
											 
											 
										 	
										 	clt[usuario].cts[clt[usuario].qtd_cts_por_clt].cvc= (clt[usuario].qtd_cts_por_clt +1)*100 + usuario;
										 	strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].nome_dono, clt[usuario].nome);
										 	
											
											break;
										  }
										
										else{
											system("cls");
											printf("DIGITE UMA OP��O V�LIDA!! \n");
											
										}
									
									}
									
									sprintf(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].psn, "%d", pri_seque_num);
									sprintf(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].ssn, "%d", se_seque_num);
									sprintf(tsnt, "%d", ter_seque_num);
									sprintf(qsnt, "%d", qua_seque_num);
									
									if(ter_seque_num<1000){
										strcpy(vari_concatena,"0");
										strcat(strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].tsn, vari_concatena), tsnt);
										
									}
									
									else{
										sprintf(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].tsn, "%d", ter_seque_num);
									}
									
									if(qua_seque_num < 1000){
										strcpy(vari_concatena,"0");
										strcat(strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].qsn, vari_concatena), qsnt);
									}
									
									else{
										sprintf(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].qsn, "%d", qua_seque_num);
									}
									
									while(1){
										aleatorio = rand() % 10;
										
										if(aleatorio==2 || aleatorio==4 || aleatorio==5 || aleatorio==6){
											break;
										}
									}
									
									srand(time(NULL));
									
									while(1){
										aleatorio = rand() %10;
																		
										if(aleatorio ==2 || aleatorio==4 || aleatorio==5 || aleatorio==6){
											break;
											}
											
										}
										
										struct tm agora_data= {0};
									    time_t tempo_data;
									    time(&tempo_data);
									    agora_data = *localtime(&tempo_data);
									    
									    clt[usuario].cts[clt[usuario].qtd_cts_por_clt].dt_validade_mes = agora_data.tm_mon+1;
									    clt[usuario].cts[clt[usuario].qtd_cts_por_clt].dt_validade_ano = agora_data.tm_year+1900 + aleatorio;
									    
									    
									
									
									strcpy(clt[usuario].cts[clt[usuario].qtd_cts_por_clt].identificao, "VISA");
									clt[usuario].qtd_cts_por_clt++;
									
									system("cls");
									printf("cart�o criado!! \n\n");
									pri_seque_num = 4000;
									se_seque_num = 1900;
									ter_seque_num = 0000;
									qua_seque_num = 0000;
									}
								
								
								break;
								
							
							case 2:
								
								printf("cadastro de cart�o\n\n");
								
								while(1){
									printf("numero do cart�o:");
									scanf("%s %s %s %s", cad_sq1, cad_sq2, cad_sq3, cad_sq4);
									
									
									for(i=0; i < clt[usuario].qtd_cts_por_clt; i++){
										re=strcmp(cad_sq1, clt[usuario].cts[i].psn);
										re1=strcmp(cad_sq2, clt[usuario].cts[i].ssn);
										re2=strcmp(cad_sq3, clt[usuario].cts[i].tsn);
										re3=strcmp(cad_sq4, clt[usuario].cts[i].qsn);
									
									
										if( re==0 && re1 ==0 && re2==0 && re3==0){
											break;
											}
									}
									
									if(i >= clt[usuario].qtd_cts_por_clt){
										printf("numero de cart�o n�o registrado \n\n\n");
											
										}
										
										if( re==0 && re1 ==0 && re2==0 && re3==0 && clt[usuario].qtd_cts_por_clt!=0){
											break;
											}
										
									}
									
									printf("digite o CVC do cart�o: ");
									while(1){
										
										scanf("%d", &cad_cvc);
											
										if(cad_cvc==clt[usuario].cts[i].cvc){
											break;
										
										}
										
										else{
											printf("CVC n�o correspondente!! \n\nDigite o cvc do cartao novamente:");
										}
										
									}
									
									printf("nome completo do dono do cart�o: ");
									
									while(1){
										scanf(" %[^\n]", cad_nome_dono );
										re=strcmp(cad_nome_dono, clt[usuario].cts[i].nome_dono);
										
										if(re==0){
											break;
										}
										
										else{
											printf("nome n�o correspondente\n\ndigite o nome novamente:");
										}
									}
									
									while(1){
										printf("identifica��o do cartao \n1.HiperCard \n2.MasterCard \n3.Elo \n4.VISA \n5.American Express\n\n");
										printf("digite o numero de uma das opcoes acima: ");
										scanf("%d", &cad_identificao);
										
										if(cad_identificao==4){
											break;
										}
										
										else if(cad_identificao!=1 && cad_identificao!=2 && cad_identificao!=3 && cad_identificao!=5 ){
											printf("digite um numero de op��o valida");
										
										}
										
										else{
											printf("identifica��o de cartao n�o correspondente!!\n\n");
										}
									}
									
									while(1){
										printf("digite a data de validade (XX/XXXX-mes/ano ): ");
										scanf("%d / %d", &cad_mes, &cad_ano);
										
										if(cad_mes == clt[usuario].cts[i].dt_validade_mes && cad_ano == clt[usuario].cts[i].dt_validade_ano){
											break;
										}
										
										else{
											printf("data n�o correspondente!\n");
										}
									}
									
									
									system("cls");
									
									printf("CART�O CADASTRADO!!\n\n\n");
								
								
								
								
								break;
								
							case 3:
								system("cls");
								
								if(clt[usuario].qtd_cts_por_clt==0){
									printf("voce n�o possui nenhum cartao \n\n\n");
								}
								
								else{
									printf("==============================================seus cartoes========================================\n\n");
									
									for(i=0; i< clt[usuario].qtd_cts_por_clt; i++){
										printf("==================================cartao==================================\n\n\n\n");
										printf("numero do cartao: %s %s %s %s \n", clt[usuario].cts[i].psn, clt[usuario].cts[i].ssn, clt[usuario].cts[i].tsn, clt[usuario].cts[i].qsn);
										printf("nome do do dono: %s \n", clt[usuario].cts[i].nome_dono);
										printf("CVC: %.3d \n" , clt[usuario].cts[i].cvc);
										printf("identifica��o: %s \n", clt[usuario].cts[i].identificao);
										printf("tipo de cartao: %s \n", clt[usuario].cts[i].tp_cartao);
										printf("data de validade: %.2d/%d \n\n\n", clt[usuario].cts[i].dt_validade_mes, clt[usuario].cts[i].dt_validade_ano);
										printf("==========================================================================\n\n\n\n");
									}
									
									i=0;
								}
								
								
								break;
								
								
							default:
								system("cls");
								printf("digite uma opcao valida!\n"); //isso aqui tem que ficar aqui por enquanto por que o defalt n�o pode ficar sem nada
							
						}
						
						}
						
											
					}
					
					if(op_sair==1){
						op_sair=0;
						system("cls");
						break;
					}
					
				}
					
					
		    	}
	    	
		}
		
		
	

		
	    else if(opcao==3){
	    	system("cls");
	    	printf("Obrigado pela prefer�ncia!");
	    	break;
		}
		
		else{
			system("cls");
			printf("escolha uma opcao valida!!\n");
		}
		 
	}
   

    return 0;
}

