#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

#define TF 10

// Structs

struct TpClientes
{
	char NomeCli[30];
	int QtdeCompras;
	char CPF[11];
	float ValorTotComprado;
	
};

struct TpFornecedores
{
	int CodForn;
	char NomeForn[30], CidadeForn[30];
};

struct TpData 
{
	int Dia, Mes, Ano;
};

struct TpProdutos
{
	int CodProd, Estoque;
	char Descr[30];
	float Preco;
	TpData DtValidade;
	TpFornecedores Fornecedor;
};

struct TpVendas
{
	int CodVenda;
	TpClientes CPF;
	TpData DataVenda;
	float TotVenda;
};

struct TpVendasProd
{
	TpProdutos CodProd;
	int CodVenda, Qtde;
	float ValorUnitario;
};

void LimparSaida(void){
	int x1 = 37, x2 = 88, y1 = 7, y2 = 22, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}


void LimparMsg(void){
	int x1 = 14, x2 = 88, y1 = 25, y2 = 28, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}


void LimparMenu(void){
	int x1 = 4, x2 = 35, y1 = 7, y2 = 22, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}




int validarCPF(char cpf[11])
{
    // Verificar o comprimento do CPF
    if (strlen(cpf) != 11)
        return 0;

    // Verificar se todos os caracteres são dígitos numéricos
    for (int i = 0; i < 11; i++)
    {
        if (cpf[i] < '0' || cpf[i] > '9')
            return 0;
    }

    // Cálculo dos dígitos verificadores
    int soma = 0;
    int peso = 10;

    for (int i = 0; i < 9; i++)
    {
        soma += (cpf[i] - '0') * peso;
        peso--;
    }

    int digito1 = (11 - (soma % 11)) % 10;

    soma = 0;
    peso = 11;

    for (int i = 0; i < 10; i++)
    {
        soma += (cpf[i] - '0') * peso;
        peso--;
    }

    int digito2 = (11 - (soma % 11)) % 10;

    // Verificar os dígitos verificadores
    if (digito1 == cpf[9] - '0' && digito2 == cpf[10] - '0')
        return 1;
    else
        return 0;
}


int validarData(TpData data) {
	if(data.Ano < 1900 || data.Mes <= 0 || data.Mes > 12  || data.Dia <= 0)
		return 0;
		
	if(data.Mes % 2 == 0)
		if(data.Dia > 30)
			return 0;
	else
		if(data.Dia > 31)
			return 0;
			
	if(data.Ano % 4 == 0)
		if(data.Dia > 29)
			return 0;
	else
		if(data.Dia > 28)
			return 0;
	// VALIDO
	return 1;	
}

int BuscaCPF(char cpf[15], TpClientes Cliente[TF], int TL)
{
	int pos = 0;
	
	while(pos < TL && strcmp(Cliente[pos].CPF, cpf) != 0)
		pos++;
	if(pos == TL)
		return -1;
	else
		return pos;
};

int BuscaCod(int Cod, TpFornecedores Fornecedor[], int TLF) {
    int pos = 0;
    
    while (pos < TLF && Cod != Fornecedor[pos].CodForn) {
        pos++;
    }
    
    if (pos == TLF) {
        return -1; // Código não encontrado
    } else {
        return pos; // Retorna a posição do código encontrado
    }
}

int BuscaCodProd(int Cod, TpProdutos Produto[], int TLP) {
    int pos = 0;
    
    while (pos < TLP && Cod != Produto[pos].CodProd) {
        pos++;
    }
    
    if (pos == TLP) {
        return -1; // Código não encontrado
    } else {
        return pos; // Retorna a posição do código encontrado
    }
}

void CadastroClientes(TpClientes Cliente[], int &TLC)
{
	char op, cpfaux[11];
	int pos;
	
	LimparSaida();

	do
	{
		LimparMsg();
		gotoxy(43,7);
		printf("### CADASTRO DE PESSOAS ###\n");
		gotoxy(40,9);
		printf("*CPF (APENAS NUMEROS):"); 
		fflush(stdin);
		gets(cpfaux);
		if(validarCPF(cpfaux))
		{
			pos = BuscaCPF(cpfaux, Cliente, TLC);
			if(pos == -1)
			{
				strcpy(Cliente[TLC].CPF, cpfaux);
				gotoxy(40,10);
				printf("Nome do cliente: ");
				fflush(stdin);
				gets(Cliente[TLC].NomeCli);
				gotoxy(15,26);
				printf("Cadastro realizado com sucesso!");
				Sleep(1000);
				LimparMsg();
				TLC++;
			}
			else{
				gotoxy(15,26);
				printf("Cliente ja cadastrado!");
				Sleep(1000);
				LimparMsg();
				
			}
		}
		else{
			gotoxy(15,26);
			printf("CPF invalido!");
			Sleep(1000);
			LimparMsg();
			
		}
		
		LimparSaida();
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1000);
		op = toupper(getch());	
	}while(op != 27);
	
}

void RelatorioClientes(TpClientes Cliente[TF], int TLC)
{
	int i, linha = 7;
	if (TLC == 0)
		printf("\nNao ha clientes cadastrados!\n");
	else
	{
		for(i = 0; i < TLC; i++, linha++)
		{
			gotoxy(40,linha);
			printf("CPF: %s", Cliente[i].CPF);
			gotoxy(40,linha+1);
			printf("Nome: %s", Cliente[i].NomeCli);
			linha = linha + 2;
		}
	}
	
	// TEM QUE ARRUMAR, PARA CASO ULTRAPASSE A BORDA DA SAIDA
	
}

void RelatorioFornecedores(TpFornecedores Fornecedor[TF], int TLF)
{
	int i, linha = 7;
	if (TLF == 0)
		printf("\nNao ha fornecedores cadastrados!\n");
	else
	{
		for(i = 0; i < TLF; i++, linha++)
		{
			gotoxy(40,linha);
			printf("Codigo: %d", Fornecedor[i].CodForn);
			gotoxy(40,linha+1);
			printf("Nome: %s", Fornecedor[i].NomeForn);
			gotoxy(40,linha+2);
			printf("Cidade: %s", Fornecedor[i].CidadeForn);
			linha = linha + 3;
		}
	}
	
	// TEM QUE ARRUMAR, PARA CASO ULTRAPASSE A BORDA DA SAIDA	
}


void ExcluiClientes(TpClientes Cliente[TF], int &TLC)
{
	int pos = 0;
	char auxCPF[11], op;
	

	
	do
	{
		if(TLC > 0)
		{
			LimparSaida();
			gotoxy(43,7);
			printf("### EXCLUSAO DE CLIENTES ###\n");
			gotoxy(40,9);
			printf("CPF (APENAS NUMEROS):"); 
			fflush(stdin);
			gets(auxCPF);
		
			if(strlen(auxCPF) > 0)
			{
				pos = BuscaCPF(auxCPF, Cliente, TLC);
				if(pos == -1)
				{
					LimparMsg();
					gotoxy(15,26);
					printf("Cliente nao cadastrado!");
					Sleep(1000);
					LimparMsg();
				}
			
				else
				{
					LimparSaida();
					gotoxy(40,7);
					printf("Detalhes do cliente:");
					gotoxy(40,8);
					printf("CPF: %s", Cliente[pos].CPF);
					gotoxy(40,9);
					printf("Nome: %s", Cliente[pos].NomeCli);
					
					LimparMsg();
					gotoxy(15,26);
					printf("Confirma a exclusao (S/N)?");
	
					gotoxy(42,23);
					if(toupper(getche()) == 'S'){
						for( ; pos < TLC - 1; pos++)
							Cliente[pos] = Cliente[pos + 1];
							
						TLC--;
						
						LimparMsg();
						gotoxy(15,26);
						printf("Exclusao concluida!");
						Sleep(1000);
						LimparMsg();
					}
				}
			}else{
				LimparMsg();
				gotoxy(15,26);
				printf("CPF invalido!");
				Sleep(1000);
				LimparMsg();
			}
		}else{
			LimparMsg();
			gotoxy(15,26);
			printf("Nao ha clientes cadastrados!");
			Sleep(1000);
			LimparMsg();
		}
		
		
		
		LimparSaida();
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1000);
		op = toupper(getch());	
	}while(op != 27);
	
}

void ConsultaClientes(TpClientes Cliente[TF], int TL)
{
	int pos = 0;
	char auxCPF[11], op;
	
	do
	{
		LimparSaida();
		gotoxy(43,7);
		printf("### CONSULTA DE CLIENTES ###\n");
		gotoxy(40,9);
		printf("CPF (APENAS NUMEROS):"); 
		fflush(stdin);
		gets(auxCPF);
		
		if (TL > 0 && strlen(auxCPF) > 0)
		{
			pos = BuscaCPF(auxCPF, Cliente, TL);
			if(pos == -1)
			{
				LimparMsg();
				gotoxy(15,26);
				printf("Cliente nao cadastrado!");
				Sleep(1000);
				LimparMsg();
			}else{
				LimparSaida();
				gotoxy(43,7);
				printf("Detalhes do cliente:");
				gotoxy(40,8);
				printf("CPF: %s", Cliente[pos].CPF);
				gotoxy(40,9);
				printf("Nome: %s", Cliente[pos].NomeCli);
				getch();
				// colocar o restante dos dados (qtade de compras...)
			}
		}
		
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1000);
		op = toupper(getch());
			
	}while(op != 27);
	
}

void ConsultaFornecedores(TpFornecedores Fornecedor[TF], int TLF)
{
	int pos = 0, codAux;
	char op;
	
	do
	{
		LimparSaida();
		gotoxy(43,7);
		printf("### CONSULTA DE FORNECEDORES ###\n");
		gotoxy(40,9);
		printf("Codigo:"); 
		scanf("%d", &codAux);
		
		if (codAux > 0)
		{
			pos = BuscaCod(codAux, Fornecedor, TLF);
			if(pos == -1)
			{
				LimparMsg();
				gotoxy(15,26);
				printf("Fornecedor nao cadastrado!");
				Sleep(1000);
				LimparMsg();
			}else{
				LimparSaida();
				gotoxy(43,7);
				printf("Detalhes do fornecedor:");
				gotoxy(40,8);
				printf("Codigo: %d", Fornecedor[pos].CodForn);
				gotoxy(40,9);
				printf("Nome: %s", Fornecedor[pos].NomeForn);
				gotoxy(40,10);
				printf("Cidade: %s", Fornecedor[pos].CidadeForn);
				getch();
			}
		}
		
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1000);
		
		op = toupper(getch());
			
	}while(op != 27);
	
}

void ExcluiFornecedores(TpFornecedores Fornecedor[TF], int &TLF)
{
	int pos = 0, codAux;
	char op;

	do
	{
		if(TLF > 0)
		{
			LimparSaida();
			gotoxy(43,7);
			printf("### EXCLUSAO DE FORNECEDORES ###\n");
			gotoxy(40,9);
			printf("Codigo:"); 
			scanf("%d", &codAux);
		
			if(codAux > 0)
			{
				pos = BuscaCod(codAux, Fornecedor, TLF);
				if(pos == -1)
				{
					LimparMsg();
					gotoxy(15,26);
					printf("Fornecedor nao cadastrado!");
					Sleep(1000);
					LimparMsg();
				}
			
				else
				{
					LimparSaida();
					gotoxy(43,7);
					printf("Detalhes do fornecedor:");
					gotoxy(40,8);
					printf("Codigo: %d", Fornecedor[pos].CodForn);
					gotoxy(40,9);
					printf("Nome: %s", Fornecedor[pos].NomeForn);
					gotoxy(40,10);
					printf("Cidade: %s", Fornecedor[pos].CidadeForn);
					
					gotoxy(15,26);
					printf("Confirma a exclusao (S/N)?");
	
					gotoxy(42,23);
					if(toupper(getche()) == 'S'){
						for( ; pos < TLF - 1; pos++)
							Fornecedor[pos] = Fornecedor[pos + 1];
						
						TLF--;
						
						LimparMsg();
						gotoxy(15,26);
						printf("Exclusao concluida!");
						Sleep(1000);
						LimparMsg();
					}
				}
			}else{
				LimparMsg();
				gotoxy(15,26);
				printf("Codigo invalido!");
				Sleep(1000);
				LimparMsg();
			}
		}else{
			LimparMsg();
			gotoxy(15,26);
			printf("Nao ha fornecedores cadastrados!");
			Sleep(1000);
			LimparMsg();
		}
		
		
		
		LimparSaida();
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1000);
		op = toupper(getch());	
	}while(op != 27);
	
}

void AlteraFornecedores(TpFornecedores Fornecedor[TF], int TLF){
	int pos = 0, codAux;
	char op;
	
	do
	{
		LimparSaida();
		gotoxy(43,7);
		printf("### ALTERACAO DE FORNECEDORES ###\n");
		gotoxy(40,9);
		printf("Codigo:"); 
		scanf("%d", &codAux);
		
		if (codAux > 0)
		{
			pos = BuscaCod(codAux, Fornecedor, TLF);
			if(pos == -1)
			{
				LimparMsg();
				gotoxy(15,26);
				printf("Fornecedor nao cadastrado!");
				Sleep(1000);
				LimparMsg();
			}else{
				do
				{
					gotoxy(40,11);
					printf("[A] - Codigo: ");
					printf("%d", Fornecedor[pos].CodForn);
					gotoxy(40,12);
					printf("[B] - Nome: ");
					printf("%s",Fornecedor[pos].NomeForn);
					gotoxy(40, 13);
					printf("[C] - Cidade: "); 
					printf("%s", Fornecedor[pos].CidadeForn);
					gotoxy(43, 15);
					printf("[ENTER] - SALVAR");
					gotoxy(43, 16);
					printf("[ESQ] - VOLTAR");
					gotoxy(43, 17);
					printf("OPCAO: ");
					fflush(stdin);
					op = toupper(getch());
					switch(op)
					{
					
						case 'A':
						gotoxy(54,11);
						printf("                      ");
						gotoxy(54,11);
						fflush(stdin);
						scanf("%d", &Fornecedor[pos].CodForn);
						
						if(Fornecedor[pos].CodForn > 0)
						{
							if(BuscaCod(Fornecedor[pos].CodForn,Fornecedor, TLF) == -1) 
							{
								gotoxy(15,26);
								printf("Codigo editado!");
								Sleep(1500);
								LimparMsg();
							}
							else
							{
								gotoxy(15,26);
								printf("Codigo ja esta em uso!");
								Sleep(1500);
								LimparMsg();
							}			
						}
						else
						{
							gotoxy(15,26);
							printf("Codigo Invalido!");
							Sleep(1500);
							LimparMsg();
						}	
					
						break;
						
						case 'B':
						gotoxy(52,12);
						printf("                      ");
						gotoxy(52,12);
						fflush(stdin);
						gets(Fornecedor[pos].NomeForn);
						
						gotoxy(15,26);
						printf("NOME EDITADO!");
						Sleep(1500);
						LimparMsg();
						break;
						
						case 'C':
						gotoxy(54,12);
						printf("                      ");
						gotoxy(54,12);
						fflush(stdin);
						gets(Fornecedor[pos].CidadeForn);
						
						gotoxy(15,26);
						printf("CIDADE EDITADA!");
						Sleep(1500);
						LimparMsg();
						break;
					}
				}while(op!=27);
			}
		}
		else
		{
			gotoxy(15,26);
			printf("Codigo Invalido!");
			Sleep(1500);
			LimparMsg();
		}
	}while(op!=27);
}

void CadastroProdutos(TpProdutos Produto[], int &TLP) {
    char op;
    int codAux, pos;

    LimparSaida();

    do {
        gotoxy(43, 7);
        printf("### CADASTRO DE PRODUTOS ###\n");
        gotoxy(40, 9);
        printf("Codigo do produto:");
        scanf("%d", &codAux);
        
        if(codAux > 0)
		{
	        pos = BuscaCodProd(codAux, Produto, TLP);
	        if (pos != -1) {
	        	LimparMsg();
	            gotoxy(15, 23);
	            printf("Esse produto ja foi cadastrado, deseja adicionar no estoque? (S/N): "); // tratar
	            Sleep(1500);
	            LimparMsg();
	        } else {
	            // Incrementar TLF antes de acessar o novo índice
	            Produto[TLP].CodProd = codAux;
	            gotoxy(40, 10);
	            printf("Descricao: ");
	            fflush(stdin);
	            gets(Produto[TLP].Descr);
				
				// data vazando a borda de saida
				do
				{
				    gotoxy(40, 11);
				    printf("Data de Validade(dd mm aaaa): ");
				    scanf("%d%d%d", &Produto[TLP].DtValidade.Dia, &Produto[TLP].DtValidade.Mes, &Produto[TLP].DtValidade.Ano);
				
				    if (validarData(Produto[TLP].DtValidade) != 1) {
				        // Exibe uma mensagem de erro e apaga a saída
				        gotoxy(15, 23);
				        printf("Data invalida. Digite novamente.");
				        Sleep(1500);
				        LimparMsg();
				        LimparSaida(); // Limpa a saída
				    }
				} while (validarData(Produto[TLP].DtValidade) != 1);

	            do
	            {
	            	gotoxy(40, 12);
	            	printf("Estoque: ");
	            	scanf("%d", &Produto[TLP].Estoque);
	            	if(Produto[TLP].Estoque < 0)
	            	{
	            			LimparMsg();
	            			gotoxy(15,26);
							printf("Estoque invalido");
							Sleep(1000);
							LimparMsg();
	            	}
	            }while(Produto[TLP].Estoque < 0);
	            
	            do
	            {
	            	gotoxy(40, 13);
	            	printf("Preco: ");
	            	scanf("%f", &
					Produto[TLP].Preco);
	            	if(Produto[TLP].Preco < 0)
	            	{
	            			LimparMsg();
	            			gotoxy(15,26);
							printf("Preco invalido");
							Sleep(1000);
							LimparMsg();
	            	}
	            }while(Produto[TLP].Preco < 0);
	            
	            // Incrementar TLF somente após o cadastro bem-sucedido
	            TLP++;
		
	            gotoxy(15, 23);
	            printf("Produto cadastrado.");
	            Sleep(1500);
	            LimparMsg();
	        }
        }else
        {
        	LimparMsg();
			gotoxy(15,26);
			printf("Codigo invalido");
			Sleep(1000);
			LimparMsg();
        }

        

        LimparSaida();
        gotoxy(15, 23);
        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
        Sleep(1000);
        op = toupper(getch());
    } while (op != 27);
}

void InserirDados(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int &TLC, int &TLF, int &TLP)
{
	strcpy(Cliente[0].CPF, "27085684852");
	strcpy(Cliente[0].NomeCli, "Deisi");
	Cliente[0].QtdeCompras = 2;
	Cliente[0].ValorTotComprado = 25.50;
	TLC++;
	
	strcpy(Cliente[1].CPF, "48843104896");
	strcpy(Cliente[1].NomeCli, "Livia");
	Cliente[1].QtdeCompras = 3;
	Cliente[1].ValorTotComprado = 30.75;
	TLC++;
	
	Fornecedor[0].CodForn = 11;
	strcpy(Fornecedor[0].NomeForn, "Clovis");
	strcpy(Fornecedor[0].CidadeForn, "Prudente");
	TLF++;
	
	Fornecedor[1].CodForn = 22;
	strcpy(Fornecedor[1].NomeForn, "Everaldo");
	strcpy(Fornecedor[1].CidadeForn, "Osvaldo Cruz");
	TLF++;
	
	
	gotoxy(15,26);
	printf("Dados inseridos");
	Sleep(1000);
	LimparMsg();

}

void AlteraClientes(TpClientes Cliente[TF], int TL){
	int pos = 0;
	char auxCPF[11], op;
	
	do
	{
		LimparSaida();
		gotoxy(43,7);
		printf("### ALTERACAO DE CLIENTES ###\n");
		gotoxy(40,9);
		printf("CPF (APENAS NUMEROS):"); 
		fflush(stdin);
		gets(auxCPF);
		
		if (TL > 0 && strlen(auxCPF) > 0)
		{
			pos = BuscaCPF(auxCPF, Cliente, TL);
			if(pos == -1)
			{
				gotoxy(15,26);
				printf("Cliente nao cadastrado!");
				Sleep(1000);
				LimparMsg();
			}else{
				do
				{
					gotoxy(40,11);
					printf("[A] - CPF: ");
					printf("%s", Cliente[pos].CPF);
					gotoxy(40,12);
					printf("[B] - Nome: ");
					printf("%s",Cliente[pos].NomeCli);
					gotoxy(40, 13);
					printf("[C] - Quantidade de compras: "); 
					printf("%d", Cliente[pos].QtdeCompras);
					gotoxy(40, 14);
					printf("[D] - Valor Total Comprado: "); 
					printf("%.2f", Cliente[pos].ValorTotComprado);
					gotoxy(40, 15);
					printf("[ENTER] - SALVAR");
					gotoxy(43, 16);
					printf("[ESQ] - VOLTAR");
					gotoxy(43, 18);
					printf("OPCAO: ");
					fflush(stdin);
					op = toupper(getch());
					switch(op)
					{
					
						case 'A':
						gotoxy(51,11);
						printf("                      ");
						gotoxy(51,11);
						fflush(stdin);
						gets(Cliente[pos].CPF);
						
							if(validarCPF(Cliente[pos].CPF))
							{
								if(BuscaCPF(Cliente[pos].CPF,Cliente, TL) == -1) 
								{
									gotoxy(15,26);
									printf("CPF EDITADO!");
									Sleep(1500);
									LimparMsg();
								}
								else
								{
									gotoxy(15,26);
									printf("CPF JA ESTA EM USO !");
									Sleep(1500);
									LimparMsg();
								}			
							}
							else
							{
								gotoxy(15,26);
								printf("CPF INVALIDO!");
								Sleep(1500);
								LimparMsg();
							}	
					
						break;
						
						case 'B':
						gotoxy(51,12);
						printf("                      ");
						gotoxy(51,12);
						fflush(stdin);
						gets(Cliente[pos].NomeCli);
						
						gotoxy(15,26);
						printf("NOME EDITADO!");
						Sleep(1500);
						LimparMsg();
						break;
					}
				}while(op!=27);
			}
		}
	}while(op!=27);
}

void CadastroFornecedores(TpFornecedores Fornecedores[], int &TLF) {
    char op;
    int codAux, pos;

    LimparSaida();

    do {
        gotoxy(43, 7);
        printf("### CADASTRO DE FORNECEDORES ###\n");
        gotoxy(40, 9);
        printf("Codigo do fornecedor:");
        scanf("%d", &codAux);

        pos = BuscaCod(codAux, Fornecedores, TLF);
        if (pos != -1) {
        	LimparMsg();
            gotoxy(15, 23);
            printf("Esse fornecedor ja foi cadastrado");
            Sleep(1500);
            LimparMsg();
        } else {
            // Incrementar TLF antes de acessar o novo índice
            Fornecedores[TLF].CodForn = codAux;
            gotoxy(40, 10);
            printf("Nome do fornecedor: ");
            fflush(stdin);
            gets(Fornecedores[TLF].NomeForn);

            gotoxy(40, 11);
            printf("Cidade do fornecedor: ");
            gets(Fornecedores[TLF].CidadeForn);
            
            // Incrementar TLF somente após o cadastro bem-sucedido
            TLF++;

            gotoxy(15, 23);
            printf("Fornecedor cadastrado.");
            Sleep(1500);
            LimparMsg();
        }

        LimparSaida();
        gotoxy(15, 23);
        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
        Sleep(1000);
        op = toupper(getch());
    } while (op != 27);
}

//void ConsultaFornecedores(TpClientes Cliente[TF], int TL)
//{
//	int pos = 0;
//	char auxCPF[11], op;
//	
//	do
//	{
//		LimparSaida();
//		gotoxy(43,7);
//		printf("### CONSULTA DE CLIENTES ###\n");
//		gotoxy(40,9);
//		printf("CPF (APENAS NUMEROS):"); 
//		fflush(stdin);
//		gets(auxCPF);
//		
//		if (TL > 0 && strlen(auxCPF) > 0)
//		{
//			pos = BuscaCPF(auxCPF, Cliente, TL);
//			if(pos == -1)
//			{
//				gotoxy(15,26);
//				printf("Cliente nao cadastrado!");
//				Sleep(1000);
//				LimparMsg();
//			}else{
//				LimparSaida();
//				gotoxy(43,7);
//				printf("Detalhes do cliente:");
//				gotoxy(40,8);
//				printf("CPF: %s", Cliente[pos].CPF);
//				gotoxy(40,9);
//				printf("Nome: %s", Cliente[pos].NomeCli);
//				getch();
//				// colocar o restante dos dados (qtade de compras...)
//			}
//		}
//		
//		gotoxy(15,26);
//		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
//		Sleep(1000);
//		op = toupper(getch());
//			
//	}while(op != 27);
//	
//}




char Menu(void)
{
	char op;
	LimparMsg();
	gotoxy(8,8);
	printf("###  M E N U  ###");
	gotoxy(8,10);
	printf("[A] Fazer cadastro");
	gotoxy(8,11);
	printf("[B] Fazer consulta");
    gotoxy(8,12);
	printf("[C] Fazer alteracao");
	gotoxy(8,13);
	printf("[D] Fazer exclusao");
	gotoxy(8,14);
	printf("[E] Fazer venda");
	gotoxy(8,15);
	printf("[F] Relatorios");
	gotoxy(8,16);
	printf("[ESC] Sair");
	gotoxy(8,18);
	printf("Opcao desejada: ");
	fflush(stdin);
	op = toupper(getch());
}



char MenuCadastro(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int &TLC, int &TLF, int &TLP)
{
	LimparMenu();
	char opCadastro;
	
	do
	{
		gotoxy(8,7);
		printf("### CADASTRO ###");
		gotoxy(8,9);
		printf("[A] Cadastrar cliente"); 
		gotoxy(8,10);
		printf("[B] Cadastrar fornecedor"); 
	    gotoxy(8,11);
		printf("[C] Cadastrar produto"); 
		gotoxy(8,12);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,14);
		printf("Opcao desejada: ");
		fflush(stdin);
		opCadastro = toupper(getch());
		switch(opCadastro)
			{
				case 'A': CadastroClientes(Cliente, TLC);
						  break;
				case 'B': CadastroFornecedores(Fornecedor, TLF);
					  break;
				case 'C': CadastroProdutos(Produto, TLP);
						  break;	
			}
	}while(opCadastro!=27);
}

char MenuConsulta(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int TLC, int TLF, int TLP)
{
	LimparMenu();
	char opConsulta;
	do
	{
		gotoxy(8,7);
		printf("### CONSULTA ###");
		gotoxy(8,9);
		printf("[A] Consultar cliente"); 
		gotoxy(8,10);
		printf("[B] Consultar fornecedor"); 
	    gotoxy(8,11);
		printf("[C] Consultar produto"); 
		gotoxy(8,12);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,14);
		printf("Opcao desejada: ");
		fflush(stdin);
		opConsulta = toupper(getch());
		switch(opConsulta)
			{
				case 'A': ConsultaClientes(Cliente, TLC);
						  break;
				case 'B': ConsultaFornecedores(Fornecedor,TLF);
						  break;
//				case 'C': ConsultaProdutos();
//						  break;	
			}
	}while(opConsulta != 27);
}

char MenuAlteracao(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int &TLC, int &TLF, int &TLP)
{
	LimparMenu();
	char opAlteracao;
	
	do
	{
		gotoxy(8,7);
		printf("### ALTERACAO ###");
		gotoxy(8,9);
		printf("[A] Alterar cliente"); 
		gotoxy(8,10);
		printf("[B] Alterar fornecedor"); 
	    gotoxy(8,11);
		printf("[C] Alterar produto"); 
		gotoxy(8,12);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,14);
		printf("Opcao desejada: ");
		fflush(stdin);
		opAlteracao = toupper(getch());
		switch(opAlteracao)
			{
				case 'A': AlteraClientes(Cliente, TLC);
						  break;
				case 'B': AlteraFornecedores(Fornecedor, TLF);
						  break;
//				case 'C': AlteraProdutos();
//						  break;	
			}
	}while(opAlteracao!=27);
}

char MenuExclusao(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int &TLC, int &TLF, int &TLP)
{
	LimparMenu();
	char opExclusao;
	
	do
	{
		gotoxy(8,7);
		printf("### EXCLUSAO ###");
		gotoxy(8,9);
		printf("[A] Excluir cliente"); 
		gotoxy(8,10);
		printf("[B] Excluir fornecedor"); 
	    gotoxy(8,11);
		printf("[C] Excluir produto"); 
		gotoxy(8,12);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,14);
		printf("Opcao desejada: ");
		fflush(stdin);
		opExclusao = toupper(getch());
		switch(opExclusao)
			{
				case 'A': ExcluiClientes(Cliente, TLC);
						  break;
				case 'B': ExcluiFornecedores(Fornecedor, TLF);
						  break;
//				case 'C': ExcluiProdutos();
//						  break;	
			}
	}while(opExclusao!=27);
}

char MenuRelatorios(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int TLC, int TLF, int TLP)
{
	LimparMenu();
	char opRelatorio;
	
	do
	{
		gotoxy(8,7);
		printf("### RELATORIO ###");
		gotoxy(8,9);
		printf("[A] Relatorio clientes"); 
		gotoxy(8,10);
		printf("[B] Relatorio fornecedores"); 
	    gotoxy(8,11);
		printf("[C] Relatorio produtos"); 
		gotoxy(8,12);
		printf("[C] Relatorio de vendas"); 
		gotoxy(8,13);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,14);
		printf("Opcao desejada: ");
		fflush(stdin);
		opRelatorio = toupper(getch());
		switch(opRelatorio)
			{
				case 'A': RelatorioClientes(Cliente, TLC);
						  break;
				case 'B': RelatorioFornecedores(Fornecedor, TLF);
						  break;
//				case 'C': RelatorioProdutos();
//						  break;
//				case 'D': RelatorioVendas();
//						  break;	
			}
	}while(opRelatorio!=27);
};

void Moldura(int CI, int LI, int CF, int LF, int cor)
{
	int i;
	textcolor(cor);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	
	for(i=CI+1;i<CF;i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		gotoxy(i,LF);
		printf("%c",205);
	}
	
	for(i=LI+1;i<LF;i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		gotoxy(CF,i);
		printf("%c",186);
	}
	
	textcolor(7);
};

void MoldPrincipal(void)
{
	clrscr();
	Moldura(1,1,90,30,6); // MOLDURA DE FORA
    Moldura(3,2,85,4,5); // MOLDURA TÍTULO
    
	
	gotoxy(19,3);
	printf("###  S I S T E M A   D E   V E N D A S  ###");
	Moldura(3,6,35,22,5); // MOLDURA MENU
	Moldura(36,6,88,22,5); // MOLDURA SAÍDA
	Moldura(3,24,88,28,5); // MOLDURA MENSAGEM
	
	gotoxy(5,26);
	printf("Mensagem: ");
};


//void ExecutarMenus(void)
//{
//	char opcao;
//	do
//	{
//		MoldPrincipal();
//		opcao = Menu();
//		switch(opcao)
//		{
//			case 'A': MenuCadastro( ,TLC);
//					  break;
//			case 'B': MenuConsulta();
//					  break;
//			case 'C': MenuAlteracao();
//					  break;
//			case 'D': MenuExclusao();
//					  break;
////			case 'G': FazerVenda();
////					  break;
//			case 'H': MenuRelatorios();
//					  break;		
//		}
//	}while(opcao!=27);
//}

int main(void)
{
	char opcao;
	TpClientes Clientes[TF];
	TpFornecedores Fornecedores[TF];
	TpProdutos Produtos[TF];
	int TLP = 0, TLC = 0, TLF = 0; // tamanhos lógicos
	char cpfaux[11];


	LimparSaida();

		
	textbackground(0); // (preto) 0..7 (cinza)
	
	do
	{
		MoldPrincipal();
		opcao = Menu();
		switch(opcao)
		{
			case 'A': MenuCadastro(Clientes, Fornecedores, Produtos, TLC, TLF, TLP);
					  break;
			case 'B': MenuConsulta(Clientes, Fornecedores, Produtos, TLC, TLF, TLP);
					  break;
			case 'C': MenuAlteracao(Clientes, Fornecedores, Produtos, TLC, TLF, TLP);
					  break;
			case 'D': MenuExclusao(Clientes, Fornecedores, Produtos, TLC, TLF, TLP);
					  break;
//			case 'G': FazerVenda();
//					  break;
			case 'F': MenuRelatorios(Clientes, Fornecedores, Produtos, TLC, TLF, TLP);
					  break;	
			case 'I': InserirDados(Clientes, Fornecedores, Produtos, TLC, TLF, TLP);
					  break;		
		}
	}while(opcao!=27);
	
	gotoxy(15,30);
	return 0;
}
