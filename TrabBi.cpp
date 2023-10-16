// Lívia Gomes de Souza
// Mary Adryany Duarte Gonçalves da Silva

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
	int CodProd, Estoque, CodForn;
	char Descr[30];
	float Preco;
	TpData DtValidade;
};

struct TpVendas
{
	int CodVenda;
	TpData DataVenda;
	float TotVenda;
	char ClienteCPF[11];
};

struct TpVendasProd
{
	int Qtde, CodProd, CodVenda;
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
    if (data.Ano < 2000 || data.Mes <= 0 || data.Mes > 12 || data.Dia <= 0)
        return 0;

    if (data.Mes % 2 == 0) {
        if (data.Dia > 30)
            return 0;
    } else {
        if (data.Dia > 31)
            return 0;
    }

    if (data.Ano % 4 == 0) {
        if (data.Dia > 29)
            return 0;
    } else {
        if (data.Dia > 28)
            return 0;
    }

    // A data é válida
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

int BuscaCodVenda(int Cod, TpVendas Venda[], int TLV) {
    int pos = 0;
    
    while (pos < TLV && Cod != Venda[pos].CodVenda) {
        pos++;
    }
    
    if (pos == TLV) {
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
				Sleep(1500);
				LimparMsg();
				Cliente[TLC].QtdeCompras = 0;
				Cliente[TLC].ValorTotComprado = 0;
				TLC++;
			}
			else{
				gotoxy(15,26);
				printf("Cliente ja cadastrado!");
				Sleep(1500);
				LimparMsg();
				
			}
		}
		else{
			gotoxy(15,26);
			printf("CPF invalido!");
			Sleep(1500);
			LimparMsg();
			
		}
		
		LimparSaida();
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1500);
		op = toupper(getch());	
	}while(op != 27);
	
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
					Sleep(1500);
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
	
					gotoxy(42,26);
					if(toupper(getche()) == 'S'){
						for( ; pos < TLC - 1; pos++)
							Cliente[pos] = Cliente[pos + 1];
							
						TLC--;
						
						LimparMsg();
						gotoxy(15,26);
						printf("Exclusao concluida!");
						Sleep(1500);
						LimparMsg();
					}
				}
			}else{
				LimparMsg();
				gotoxy(15,26);
				printf("CPF invalido!");
				Sleep(1500);
				LimparMsg();
			}
		}else{
			LimparMsg();
			gotoxy(15,26);
			printf("Nao ha clientes cadastrados!");
			Sleep(1500);
			LimparMsg();
		}
		
		
		
		LimparSaida();
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1500);
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
				Sleep(1500);
				LimparMsg();
			}else{
				LimparSaida();
				gotoxy(43,7);
				printf("Detalhes do cliente:");
				gotoxy(40,9);
				printf("CPF: %s", Cliente[pos].CPF);
				gotoxy(40,10);
				printf("Nome: %s", Cliente[pos].NomeCli);
				gotoxy(40,11);
				printf("Qtde de compras: %d", Cliente[pos].QtdeCompras);
				gotoxy(40,12);
				printf("Valor total comprado: %.2f", Cliente[pos].ValorTotComprado);
				getch();
			}
		}
		
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1500);
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
				Sleep(1500);
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
		Sleep(1500);
		
		op = toupper(getch());
			
	}while(op != 27);
	
}

void ConsultaProdutos(TpProdutos Produto[], int TLP)
{
	int pos = 0, codAux;
	char op;
	
	do
	{
		LimparSaida();
		gotoxy(43,7);
		printf("### CONSULTA DE PRODUTOS ###\n");
		gotoxy(40,9);
		printf("Codigo:"); 
		scanf("%d", &codAux);
		if (codAux > 0)
		{
			pos = BuscaCodProd(codAux, Produto, TLP);
			if(pos == -1)
			{
				LimparMsg();
				gotoxy(15,26);
				printf("Produto nao cadastrado!");
				Sleep(1500);
				LimparMsg();
			}else{
				LimparSaida();
				gotoxy(43,7);
				printf("Detalhes do produto:");
				gotoxy(40,8);
				printf("Codigo: %d", Produto[pos].CodProd);
				gotoxy(40,9);
				printf("Codigo do Fornecedor: %d", Produto[pos].CodForn);
				gotoxy(40,10);
				printf("Descricao: %s", Produto[pos].Descr);
				gotoxy(40,11);
				printf("Data de Validade: %d/%d/%d", Produto[pos].DtValidade.Dia, Produto[pos].DtValidade.Mes, Produto[pos].DtValidade.Ano);
				gotoxy(40,12);
				printf("Estoque: %d", Produto[pos].Estoque);
				gotoxy(40,13);
				printf("Preco: %.2f", Produto[pos].Preco);
				getch();
			}
		}
		
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1500);
		
		op = toupper(getch());
	}while(op != 27);
}


void ExcluiVendas(TpVendas Venda[], TpVendasProd VendaProd[], TpFornecedores Fornecedor[], TpProdutos Produto[], int &TLV, int &TLVP,int TLF, int TLP)
{
	int codAux, posVenda, op, linha=7, coluna=40, linhaMaxima = 19, posForn, posProd;
	double totalItem;
	do
	{
		if(TLV > 0)
		{
			LimparSaida();
			gotoxy(43,7);
			printf("### EXCLUSAO DE VENDAS ###\n");
			gotoxy(40,9);
			printf("Codigo:"); 
			scanf("%d", &codAux);
		
			if(codAux >= 0)
			{
				posVenda = BuscaCodVenda(codAux, Venda, TLV);
				if(posVenda == -1)
				{
					LimparMsg();
					gotoxy(15,26);
					printf("Venda nao cadastrado!");
					Sleep(1500);
					LimparMsg();
				}
			
				else
				{
					LimparSaida();
					gotoxy(coluna,linha);
					linha+=2;
					printf("Detalhes da Venda:");
					gotoxy(coluna,linha);
					printf("Codigo: %d", Venda[posVenda].CodVenda);
					gotoxy(60,linha);
					printf("CPF: %s",Venda[posVenda].ClienteCPF);
					linha+=1;
					gotoxy(coluna,linha);
					linha+=2;
					printf("Data: %d/%d/%d", Venda[posVenda].DataVenda.Dia, Venda[posVenda].DataVenda.Mes, Venda[posVenda].DataVenda.Ano);
					gotoxy(coluna,linha);
					printf("Produtos:");
					for (int j = 0; j < TLVP; j++)
	            {
	            	if (linha >= linhaMaxima)
		            {
		                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
		                LimparMsg();
		                gotoxy(15, 26);
		                printf("Pressione qualquer tecla para continuar...");
		                Sleep(1500);
		                getch();
		                LimparSaida();
		                LimparMsg();
		                linha = 7;
		            }
	                if (VendaProd[j].CodVenda == codAux)
	                {
	                    linha += 1;
	                    gotoxy(coluna, linha);
	                    printf("%d", VendaProd[j].CodProd);
	
	                    posProd = BuscaCodProd(VendaProd[j].CodProd, Produto, TLP);
	
	                    coluna += 10;
	                    gotoxy(coluna, linha);
	                    printf("%s", Produto[posProd].Descr);
	
	                    coluna += 9;
	                    gotoxy(coluna, linha);
	                    printf("%d", VendaProd[j].Qtde);
	
	                    totalItem = VendaProd[j].Qtde * Produto[posProd].Preco;
	                    coluna += 6;
	                    gotoxy(coluna, linha);
	                    printf("R$%.2f", totalItem);
	
	                    coluna += 10;
	                    posForn = BuscaCod(Produto[posProd].CodForn, Fornecedor, TLF);
	                    if (posForn != -1)
	                    {
	                        gotoxy(coluna, linha);
	                        printf("%s", Fornecedor[posForn].NomeForn);
	                    }
	                    else
	                    {
	                        gotoxy(coluna, linha);
	                        printf("Fornecedor nao encontrado");
	                    }
	
	                    linha += 1; // Incrementa linha para o próximo produto
	                    coluna = 40; // Reinicializa coluna para o próximo produto
	                }
	            }
            
					gotoxy(coluna,linha);
					linha+=1;
					printf("Total: R$%.2f", Venda[posVenda].TotVenda);
					linha+=1;
					gotoxy(coluna,linha);
					printf("Confirma a exclusao (S/N)? ");
	
					if(toupper(getche()) == 'S'){
						for(int i=0;i<TLVP;i++)
						{
							if(VendaProd[i].CodVenda ==  Venda[posVenda].CodVenda)
							{
								posProd=BuscaCodProd(VendaProd[i].CodProd, Produto, TLP);
								Produto[posProd].Estoque += VendaProd[i].Qtde;
							}
						}
						for(int i=0; i<TLVP;i++)
						{
							if(VendaProd[i].CodVenda ==  Venda[posVenda].CodVenda)
							{
								VendaProd[i] = VendaProd[i+1];
								TLVP--;
							}
						}
						
						for( ; posVenda < TLV - 1; posVenda++)
							Venda[posVenda] = Venda[posVenda + 1];
						
						
						TLV--;
						
						LimparMsg();
						gotoxy(15,26);
						printf("Exclusao concluida!");
						Sleep(1500);
						LimparMsg();
					}
					else
					{
						linha=7;
						coluna=40;
					}
				}
			}else{
				LimparMsg();
				gotoxy(15,26);
				printf("Codigo invalido!");
				Sleep(1500);
				LimparMsg();
			}
		}else{
			LimparMsg();
			gotoxy(15,26);
			printf("Nao ha vendas cadastradas!");
			Sleep(1500);
			LimparMsg();
		}
		
		
		
		LimparSaida();
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1500);
		op = toupper(getch());	
	}while(op != 27);
}

void ExcluiFornecedores(TpFornecedores Fornecedor[TF], int &TLF, TpProdutos Produto[], int &TLP)
{
	int pos = 0, codAux, posProd, i;
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
					Sleep(1500);
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
	
					gotoxy(42,26);
					if (toupper(getche()) == 'S') {
				    // Excluir elementos de Produto
				
				    for(i=0;i<TLP;i++)
					{
						if(Produto[i].CodForn == Fornecedor[pos].CodForn)
						{
							Produto[i]=Produto[i+1];
							TLP--;
						}
					}
					for(i=0;i<TLP;i++)
					{
						if(Produto[i].CodForn == Fornecedor[pos].CodForn)
						{
							Produto[i]=Produto[i+1];
							TLP--;
						}
					}
						
						for( ; pos < TLF - 1; pos++)
							Fornecedor[pos] = Fornecedor[pos + 1];
						TLF--;
						
						LimparMsg();
						gotoxy(15,26);
						printf("Exclusao concluida! TLP: %d",TLP);
						Sleep(1500);
						LimparMsg();
					}
				}
			}else{
				LimparMsg();
				gotoxy(15,26);
				printf("Codigo invalido!");
				Sleep(1500);
				LimparMsg();
			}
		}else{
			LimparMsg();
			gotoxy(15,26);
			printf("Nao ha fornecedores cadastrados!");
			Sleep(1500);
			LimparMsg();
		}
		
		
		
		LimparSaida();
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1500);
		op = toupper(getch());	
	}while(op != 27);
	
}

void ExcluiProdutos(TpProdutos Produto[], int &TLP)
{
	int pos = 0, codAux;
	char op;

	do
	{
		if(TLP > 0)
		{
			LimparSaida();
			gotoxy(43,7);
			printf("### EXCLUSAO DE PRODUTOS ###\n");
			gotoxy(40,9);
			printf("Codigo:"); 
			scanf("%d", &codAux);
		
			if(codAux > 0)
			{
				pos = BuscaCodProd(codAux, Produto, TLP);
				if(pos == -1)
				{
					LimparMsg();
					gotoxy(15,26);
					printf("Produto nao cadastrado!");
					Sleep(1500);
					LimparMsg();
				}
			
				else
				{
					LimparSaida();
					gotoxy(43,7);
					printf("Detalhes do produto:");
					gotoxy(40,8);
					printf("Codigo: %d", Produto[pos].CodProd);
					gotoxy(40,9);
					printf("Codigo do Fornecedor: %d", Produto[pos].CodForn);
					gotoxy(40,10);
					printf("Descricao: %s", Produto[pos].Descr);
					gotoxy(40,11);
					printf("Data de Validade: %d/%d/%d", Produto[pos].DtValidade.Dia, Produto[pos].DtValidade.Mes, Produto[pos].DtValidade.Ano);
					gotoxy(40,12);
					printf("Estoque: %d", Produto[pos].Estoque);
					gotoxy(40,13);
					printf("Preco: %.2f", Produto[pos].Preco);
					
					LimparMsg();
					gotoxy(15,26);
					printf("Confirma a exclusao (S/N)?");
	
					gotoxy(42,26);
					if(toupper(getche()) == 'S'){
						for( ; pos < TLP - 1; pos++)
							Produto[pos] = Produto[pos + 1];
						
						TLP--;
						
						LimparMsg();
						gotoxy(15,26);
						printf("Exclusao concluida!");
						Sleep(1500);
						LimparMsg();
					}
				}
			}else{
				LimparMsg();
				gotoxy(15,26);
				printf("Codigo invalido!");
				Sleep(1500);
				LimparMsg();
			}
		}else{
			LimparMsg();
			gotoxy(15,26);
			printf("Nao ha produtos cadastrados!");
			Sleep(1500);
			LimparMsg();
		}
		
		LimparSaida();
		gotoxy(15,26);
		printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
		Sleep(1500);
		op = toupper(getch());	
	}while(op != 27);
}


void CadastroFornecedores(TpFornecedores Fornecedores[], int &TLF) {
    char op;
    int codAux, pos,cont=0;

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
            gotoxy(15,26);
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

            gotoxy(15,26);
            printf("Fornecedor cadastrado.");
            Sleep(1500);
            LimparMsg();
        }

        LimparSaida();
        gotoxy(15,26);
        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
        Sleep(1500);
        op = toupper(getch());
    } while (op != 27);
}

void CadastroProdutos(TpProdutos Produto[], int &TLP, TpFornecedores Fornecedor[], int &TLF) {
    char op,resp;
    int codAux, pos, codForn,qtde, pos2;

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
	            gotoxy(15,26);
	            printf("Esse produto ja foi cadastrado, deseja adicionar no estoque? (S/N): "); 
	            op = getch();
				if(toupper(op) == 'S')
				{
					gotoxy(40, 9);
					printf("Codigo do produto: %d", codAux);
					gotoxy(40, 10);
					printf("Digite a quantidade: ");
					scanf("%d", &qtde);
					pos2 = BuscaCodProd(codAux, Produto, TLP);
					Produto[pos2].Estoque += qtde;
					LimparMsg();
					gotoxy(15,26);
	            	printf("Produto adicionado ao estoque com sucesso!"); 
	            	Sleep(1500);
	            	LimparMsg();
				}
	        } else {
	            // Incrementar TLF antes de acessar o novo índice
	            Produto[TLP].CodProd = codAux;
	            gotoxy(40, 10);
	            printf("Descricao: ");
	            fflush(stdin);
	            gets(Produto[TLP].Descr);
				
				do
				{
				    gotoxy(40, 11);
				    printf("Data de Validade(dd mm aaaa): ");
				    scanf("%d%d%d", &Produto[TLP].DtValidade.Dia, &Produto[TLP].DtValidade.Mes, &Produto[TLP].DtValidade.Ano);
				
				    if (validarData(Produto[TLP].DtValidade) != 1) {
				        LimparMsg();
				        gotoxy(70, 11);
				        printf("           ");
						gotoxy(15,26);
				        printf("Data invalida. Digite novamente.");
				        Sleep(1500);
				        LimparMsg();
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
							Sleep(1500);
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
							Sleep(1500);
							LimparMsg();
	            	}
	            }while(Produto[TLP].Preco < 0);
	            
	            do
	            {
	            	gotoxy(40, 14);
	            	printf("Codigo do Fornecedor: ");
	            	scanf("%d", &codForn);
	            	pos=BuscaCod(codForn, Fornecedor, TLF);
	            	if(pos == -1)
	            	{
	            			LimparMsg();
	            			gotoxy(15,26);
							printf("Fornecedor nao cadastrado.");
							//talvez um "deseja cadastrar um novo?"
							Sleep(1500);
							LimparMsg();
	            	}
	            	else
	            	{
	            		Produto[TLP].CodForn = Fornecedor[pos].CodForn;
					}
	            }while(pos == -1);
	            
	            // Incrementar TLF somente após o cadastro bem-sucedido
	            TLP++;
				LimparMsg();
	            gotoxy(15,26);
	            printf("Produto cadastrado.");
	            Sleep(1500);
	            LimparMsg();
	        }
        }else
        {
        	LimparMsg();
			gotoxy(15,26);
			printf("Codigo invalido");
			Sleep(1500);
			LimparMsg();
        }

        

        LimparSaida();
        gotoxy(15,26);
        printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
        Sleep(1500);
        op = toupper(getch());
    } while (op != 27);
}

void InserirDados(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], TpVendas Venda[], TpVendasProd VendaProd[], int &TLC, int &TLF, int &TLP, int &TLV, int &TLVP)
{
	strcpy(Cliente[0].CPF, "27085684852");
	strcpy(Cliente[0].NomeCli, "Deisi");
	Cliente[0].QtdeCompras = 0;
	Cliente[0].ValorTotComprado = 0;
	TLC++;
	
	strcpy(Cliente[1].CPF, "48843104896");
	strcpy(Cliente[1].NomeCli, "Livia");
	Cliente[1].QtdeCompras = 0;
	Cliente[1].ValorTotComprado = 0;
	TLC++;
	
	Fornecedor[0].CodForn = 11;
	strcpy(Fornecedor[0].NomeForn, "Clovis");
	strcpy(Fornecedor[0].CidadeForn, "Prudente");
	TLF++;
	
	Fornecedor[1].CodForn = 22;
	strcpy(Fornecedor[1].NomeForn, "Everaldo");
	strcpy(Fornecedor[1].CidadeForn, "Osvaldo Cruz");
	TLF++;
	
	Produto[0].CodProd = 111;
	Produto[0].CodForn = 22;
	strcpy(Produto[0].Descr, "Arroz");
	Produto[0].DtValidade.Mes = 10;
	Produto[0].DtValidade.Ano = 2024;
	Produto[0].DtValidade.Dia = 26;
	Produto[0].Estoque = 7;
	Produto[0].Preco = 45.60;
	TLP++;
	
	Produto[1].CodProd = 112;
	Produto[1].CodForn = 11;
	strcpy(Produto[1].Descr, "Feijao");
	Produto[1].DtValidade.Mes = 2;
	Produto[1].DtValidade.Ano = 2026;
	Produto[1].DtValidade.Dia = 5;
	Produto[1].Estoque = 24;
	Produto[1].Preco = 12.60;
	TLP++;
	
	Produto[2].CodProd = 116;
	Produto[2].CodForn = 11;
	strcpy(Produto[2].Descr, "Batata");
	Produto[2].DtValidade.Mes = 2;
	Produto[2].DtValidade.Ano = 2026;
	Produto[2].DtValidade.Dia = 5;
	Produto[2].Estoque = 24;
	Produto[2].Preco = 4.60;
	TLP++;
	
	Produto[3].CodProd = 117;
	Produto[3].CodForn = 22;
	strcpy(Produto[3].Descr, "Macarrao");
	Produto[3].DtValidade.Mes = 2;
	Produto[3].DtValidade.Ano = 2026;
	Produto[3].DtValidade.Dia = 5;
	Produto[3].Estoque = 24;
	Produto[3].Preco = 5.60;
	TLP++;
	
	Produto[4].CodProd = 118;
	Produto[4].CodForn = 11;
	strcpy(Produto[4].Descr, "Cafe");
	Produto[4].DtValidade.Mes = 2;
	Produto[4].DtValidade.Ano = 2026;
	Produto[4].DtValidade.Dia = 5;
	Produto[4].Estoque = 24;
	Produto[4].Preco = 18.60;
	TLP++;
	

	
	gotoxy(15,26);
	printf("Dados inseridos");
	Sleep(1500);
	LimparMsg();

}

void AlteraFornecedores(TpFornecedores Fornecedor[TF], int TLF){
	int pos = 0, codAux, aux, pos2;
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
				Sleep(1500);
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
						scanf("%d", &aux);
						
						if(aux > 0)
						{
							pos2 = BuscaCod(aux,Fornecedor, TLF);
							if(pos2 == -1) 
							{
								Fornecedor[pos].CodForn = aux;
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
						gotoxy(54,13);
						printf("                      ");
						gotoxy(54,13);
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

void AlteraProdutos(TpProdutos Produto[], int TLP, TpFornecedores Fornecedor[], int TLF)
{
	int pos = 0, codAux,aux;
	char op;
	
	do
	{
		LimparSaida();
		gotoxy(43,7);
		printf("### ALTERACAO DE PRODUTOS ###\n");
		gotoxy(40,9);
		printf("Codigo:"); 
		scanf("%d", &codAux);
		
		if (codAux > 0)
		{
			pos = BuscaCodProd(codAux, Produto, TLP);
			if(pos == -1)
			{
				LimparMsg();
				gotoxy(15,26);
				printf("Produto nao cadastrado!");
				Sleep(1500);
				LimparMsg();
			}else{
				do
				{
					gotoxy(40,11);
					printf("[A] - Codigo: ");
					printf("%d", Produto[pos].CodProd);
					gotoxy(40,12);
					printf("[B] - Codigo do Fornecedor: ");
					printf("%d",Produto[pos].CodForn);
					gotoxy(40, 13);
					printf("[C] - Descricao: "); 
					printf("%s", Produto[pos].Descr);
					gotoxy(40, 14);
					printf("[D] - Data de Validade: "); 
					printf("%d/%d/%d", Produto[pos].DtValidade.Dia, Produto[pos].DtValidade.Mes, Produto[pos].DtValidade.Ano);
					gotoxy(40, 15);
					printf("[E] - Estoque: "); 
					printf("%d", Produto[pos].Estoque);
					gotoxy(40, 16);
					printf("[F] - Preco: "); 
					printf("%.2f", Produto[pos].Preco);
					gotoxy(43, 18);
					printf("[ENTER] - SALVAR");
					gotoxy(43, 19);
					printf("[ESQ] - VOLTAR");
					gotoxy(43, 20);
					printf("OPCAO: ");
					fflush(stdin);
					op = toupper(getch());
					switch(op)
					{
					
						case 'A':
						gotoxy(54,11);
						printf("                      ");
						gotoxy(54,11);
						scanf("%d", &aux);
						
						if(aux > 0)
						{
							if(BuscaCodProd(aux,Produto, TLP) == -1) 
							{
								Produto[pos].CodProd = aux;
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
						gotoxy(68,12);
						printf("          ");
						gotoxy(68,12);
						scanf("%d", &aux);
						
						if(aux > 0)
						{
							if(BuscaCod(aux,Fornecedor, TLF) == -1) 
							{
								gotoxy(15,26);
								printf("Fornecedor nao cadastrado!");
								Sleep(1500);
								LimparMsg();
							}
							else
							{
								Produto[pos].CodForn = aux;
								gotoxy(15,26);
								printf("Codigo do Fornecedor editado!");
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
						
						case 'C':
						gotoxy(57,13);
						printf("                    ");
						gotoxy(57,13);
						fflush(stdin);
						gets(Produto[pos].Descr);
						
						gotoxy(15,26);
						printf("Descrico editada!");
						Sleep(1500);
						LimparMsg();
						break;
						
						case 'D':
						do
						{
							gotoxy(64,14);
							printf("                         ");
						    gotoxy(64,14);
						    fflush(stdin);
							scanf("%d%d%d", &Produto[pos].DtValidade.Dia, &Produto[pos].DtValidade.Mes, &Produto[pos].DtValidade.Ano);
						
						    if (validarData(Produto[pos].DtValidade) != 1) {
						        // Exibe uma mensagem de erro e apaga a saída
						        LimparMsg();
						        gotoxy(15,26);
						        printf("Data invalida. Digite novamente.");
						        Sleep(1500);
						        LimparMsg();
						    }
						    
						}while (validarData(Produto[pos].DtValidade) != 1);
						break;
						
						case 'E':
					    do
						{
							gotoxy(55,15);
							printf("               ");
						    gotoxy(55,15);
							scanf("%d", &Produto[pos].Estoque);
						
						    if (Produto[pos].Estoque < 0) {
						        // Exibe uma mensagem de erro e apaga a saída
						        gotoxy(15,26);
						        printf("Estoque invalido. Digite novamente.");
						        Sleep(1500);
						        LimparMsg();
						    }
						} while (Produto[pos].Estoque < 0);
						break;
					    
					    case 'F':
						do
						{
							gotoxy(53,16);
							printf("               ");
						    gotoxy(53,16);
							scanf("%f", &Produto[pos].Preco);
						
						    if (Produto[pos].Preco < 0) {
						        // Exibe uma mensagem de erro e apaga a saída
						        gotoxy(15,26);
						        printf("Preco invalido. Digite novamente.");
						        Sleep(1500);
						        LimparMsg();
						    }
						} while (Produto[pos].Preco < 0);
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

void CupomFiscal(int codVenda, TpClientes Cliente[], TpVendas Venda[], TpVendasProd VendaProd[], TpProdutos Produto[], int TLC, int TLV, int TLVP, int TLP)
{
	int linha = 7, linhaMaxima = 19, coluna = 40, posVenda, posProd, posForn, k=1, posCli;
	double totalItem=0;
	LimparSaida();
	posVenda = BuscaCodVenda(codVenda, Venda, TLV);
	gotoxy(55, linha);
	printf("SUPERMERCADO LIMA");
	linha+=2;
	gotoxy(coluna,linha);
	printf("Rua Sao Francisco de Assis, 123. Centro.");
	linha++;
	gotoxy(coluna,linha);
	printf("Sao Paulo - SP.");
	linha++;
	gotoxy(coluna,linha);
	printf("CNPJ: 12.641.071/0001-98");
	gotoxy(coluna+30,linha);
	printf("%d/%d/%d",Venda[posVenda].DataVenda.Dia,Venda[posVenda].DataVenda.Mes, Venda[posVenda].DataVenda.Ano);
	linha++;
	gotoxy(coluna,linha);
	posCli = BuscaCPF(Venda[posVenda].ClienteCPF, Cliente, TLC);
	printf("Cliente: %s",Cliente[posCli].NomeCli); 
	linha++;
	gotoxy(coluna,linha);
	printf("------------------------------------------"); 
	linha++;
	gotoxy(coluna,linha);
	printf("PRODUTOS: ");
	linha+=2;
	gotoxy(coluna,linha);
	printf("COD");
	gotoxy(coluna+5,linha);
	printf("ITEM");
	gotoxy(coluna+11,linha);
	printf("DESCRICAO");
	gotoxy(coluna+36,linha);
	printf("VALOR");
	//imprimir produtos e formatar
	for (int j = 0; j < TLVP; j++)
	            {
	            	if (linha >= linhaMaxima)
		            {
		                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
		                LimparMsg();
		                gotoxy(15, 26);
		                printf("Pressione qualquer tecla para continuar...");
		                Sleep(1500);
		                getch();
		                LimparSaida();
		                LimparMsg();
		                linha = 7;
		            }
	                if (VendaProd[j].CodVenda == codVenda)
	                {
	                    linha++;
	                    gotoxy(coluna, linha);
	                    printf("%d", k);
	                    k++;
	                    
	                    posProd = BuscaCodProd(VendaProd[j].CodProd, Produto, TLP);
						gotoxy(coluna+5,linha);
						printf("%d",VendaProd[j].CodProd);
						
	                    gotoxy(coluna+11, linha);
	                    printf("%s", Produto[posProd].Descr);
	
	                    gotoxy(coluna+22, linha);
	                    printf("%.2f",Produto[posProd].Preco);
	                    
	                    gotoxy(coluna+28, linha);
	                    printf("X");
	                    
	                    gotoxy(coluna+30, linha);
	                    printf("%d",VendaProd[j].Qtde);
	                    
	    
	
	                    totalItem = VendaProd[j].Qtde * Produto[posProd].Preco;
	                    gotoxy(coluna+36, linha);
	                    printf("R$%.2f", totalItem);
	
	                    coluna = 40; // Reinicializa coluna para o próximo produto
	                    
	                }
	            }
	linha++;
	if (linha >= linhaMaxima)
	{
		LimparMsg();
		gotoxy(15, 26);
		printf("Pressione qualquer tecla para continuar...");
		Sleep(1500);
		getch();
		LimparSaida();
		LimparMsg();
		linha = 7;
	}
	gotoxy(coluna, linha);
	printf("------------------------------------------"); 
	linha++;
	if (linha >= linhaMaxima)
	{
		LimparMsg();
		gotoxy(15, 26);
		printf("Pressione qualquer tecla para continuar...");
		Sleep(1500);
		getch();
		LimparSaida();
		LimparMsg();
		linha = 7;
	}
	gotoxy(coluna, linha);
	printf("TOTAL: R$%.2f",Venda[posVenda].TotVenda);
	linha++;
	if (linha >= linhaMaxima)
	{
		LimparMsg();
		gotoxy(15, 26);
		printf("Pressione qualquer tecla para continuar...");
		Sleep(1500);
		getch();
		LimparSaida();
		LimparMsg();
		linha = 7;
	}
	gotoxy(coluna, linha);
	printf("Agradecemos a preferencia ;)");
	Sleep(3000);
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
				Sleep(1500);
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
					gotoxy(40, 14);
					printf("[ENTER] - SALVAR");
					gotoxy(40, 15);
					printf("[ESQ] - VOLTAR");
					gotoxy(40, 16);
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



void FazerVenda(TpVendas Venda[], int &TLV, TpClientes Cliente[], int TLC, TpVendasProd VendaProduto[], int &TLVP, TpProdutos Produto[], int TLP)
{
    char auxCPF[11], op;
    int pos, aux, cont = 0, posProd, posCli;
    float totItem;
	
    do
    {
        LimparSaida();
        gotoxy(43, 7);
        printf("### VENDA ###\n");
        gotoxy(40, 9);
        printf("CPF do cliente (APENAS NUMEROS): ");
        fflush(stdin);
        gets(auxCPF);

        if (validarCPF(auxCPF) == 0)
        {
            LimparMsg();
            gotoxy(15, 26);
            printf("CPF invalido");
            Sleep(1500);
            LimparMsg();
        }
        else
        {
            posCli = BuscaCPF(auxCPF, Cliente, TLC);
            if (posCli == -1)
            {
                LimparMsg();
                gotoxy(15, 26);
                printf("Cliente nao cadastrado");
                Sleep(1500);
                LimparMsg();
            }
            else
            {
            	Venda[TLV].TotVenda = 0;
                Venda[TLV].CodVenda = TLV; // Define o código da nova venda
                VendaProduto[TLVP].CodVenda = Venda[TLV].CodVenda;
                strcpy(Venda[TLV].ClienteCPF, Cliente[posCli].CPF);
                
                do
				{
					gotoxy(58, 10);
					printf("                 ");
				    gotoxy(40, 10);
				    printf("Data(dd mm aaaa): ");
				    scanf("%d%d%d", &Venda[TLV].DataVenda.Dia, &Venda[TLV].DataVenda.Mes, &Venda[TLV].DataVenda.Ano);
				
				    if (validarData(Venda[TLV].DataVenda) != 1) {
				        // Exibe uma mensagem de erro
				        LimparMsg();
				        gotoxy(15,26);
				        printf("Data invalida. Digite novamente.");
				        Sleep(1500);
				        LimparMsg();
				    }
				} while (validarData(Venda[TLV].DataVenda) != 1);

                do
				{
					totItem = 0;
					VendaProduto[TLVP].CodVenda = Venda[TLV].CodVenda;
				    gotoxy(59, 12);
				    printf("                    ");
				    gotoxy(40, 12);
				    printf("Codigo do produto: ");
				    scanf("%d", &aux);
				
				    posProd = BuscaCodProd(aux, Produto, TLP);
				
				    if (posProd == -1)
				    {
				        LimparMsg();
				        gotoxy(15, 26);
				        printf("Produto nao cadastrado");
				        Sleep(1500);
				        LimparMsg();
				    }
				    else
				    {
				        // Copia o código do produto para a estrutura de venda do produto
						VendaProduto[TLVP].CodProd = Produto[posProd].CodProd;
						VendaProduto[TLVP].ValorUnitario = Produto[posProd].Preco;
						gotoxy(40, 13);
						printf("                              ");
						gotoxy(40, 13);
						printf("Valor unitario: %.2f", VendaProduto[TLVP].ValorUnitario);
				
				        do
				        {
				        	LimparMsg();
				            gotoxy(50, 14);
				            printf("              ");
				            gotoxy(40, 14);
				            printf("Quantidade: ");
				            scanf("%d", &VendaProduto[TLVP].Qtde);
				
				            if (VendaProduto[TLVP].Qtde < 0)
				            {
				                // Exibe uma mensagem de erro e apaga a saída
				                LimparMsg();
				                gotoxy(15, 26);
				                printf("Quantidade invalida. Digite novamente.");
				                Sleep(1500);
				            }
				
				            if (VendaProduto[TLVP].Qtde > Produto[posProd].Estoque)
				            {
				                LimparMsg();
				                gotoxy(15, 26);
				                printf("Nao ha estoque suficiente. Estoque total: %d", Produto[posProd].Estoque);
				                Sleep(1500);
				                gotoxy(15, 27);
				                printf("Digite novamente a quantidade desejada. ");
				                Sleep(1500);
				            }
				        } while (VendaProduto[TLVP].Qtde > Produto[posProd].Estoque);
				        
				            
		                // Atualiza o estoque do produto
		                Produto[posProd].Estoque -= VendaProduto[TLVP].Qtde;
		
		                // Calcula o total da venda
		                
						totItem = VendaProduto[TLVP].Qtde * VendaProduto[TLVP].ValorUnitario;
						Venda[TLV].TotVenda += totItem;
						
		                LimparMsg();
		                gotoxy(15, 26);
		                printf("Produto adicionado a venda com sucesso");
		                Sleep(1500);
				                
				        TLVP++;
				    }
				
				    LimparMsg();
				    gotoxy(15, 26);
				    printf("[ENTER] - Adicionar outro produto & [ESQ] - Concluir venda.");
				    op = toupper(getch());
				    
				} while (op != 27);
				Cliente[posCli].ValorTotComprado += Venda[TLV].TotVenda;
				Cliente[posCli].QtdeCompras += 1;
				TLV++;
				LimparMsg();
				gotoxy(15, 26);
				printf("Gerando cupom fiscal...");
				Sleep(2000);
				CupomFiscal(Venda[TLV-1].CodVenda, Cliente, Venda, VendaProduto, Produto, TLC, TLV, TLVP, TLP);
			}
		}
		LimparMsg();
		gotoxy(15, 26);
		printf("[ENTER] - Fazer outra venda & [ESQ] - Concluir venda.");
		op = toupper(getch());
	}while(op != 27);
}


void AumentarPreco(TpProdutos Produto[], int TLP, TpFornecedores Fornecedor[], int TLF)
{
	int CodFornecedor;
	float aumento,aux;
	int pos,percentualAumento;
	
	LimparSaida();
    gotoxy(43, 7);
    printf("### AUMENTO DE PRECO ###\n");
    
    do {
    	gotoxy(72, 9);
		printf("    ");
    	gotoxy(40, 9);
        printf("Percentual de aumento(inteiro): ");
        scanf("%f", &aux);
        
        percentualAumento = aux;

        if (percentualAumento != aux) {
        	LimparMsg();
			gotoxy(15,26);
            printf("Por favor, digite um valor inteiro.");
            Sleep(1500);
			LimparMsg();
        }

    } while (percentualAumento != aux);
    
    do
    {
    	gotoxy(61, 10);
    	printf("       ");
    	gotoxy(40, 10);
    	printf("Codigo do Fornecedor: ");
    	scanf("%d", &CodFornecedor);
    	pos = BuscaCod(CodFornecedor, Fornecedor, TLF);
    	if(pos == -1)
    	{
    			LimparMsg();
    			gotoxy(15,26);
				printf("Fornecedor nao cadastrado.");
				//talvez um "deseja cadastrar um novo?"
				Sleep(1500);
				LimparMsg();
    	}
    	else
    	{
    		 for (int i = 0; i < TLP; i++)
		    {
		        if (Produto[i].CodForn == CodFornecedor)
		        {
		            // Calcula o novo preço com base no percentual de aumento
		            aumento = Produto[i].Preco * (percentualAumento / 100.0);
		            Produto[i].Preco += aumento;
		        }
		    }
		    LimparMsg();
			gotoxy(15,26);
            printf("Aumento realizado com sucesso.");
            Sleep(1500);
			LimparMsg();
		}
    }while(pos == -1);
   
}

void RelatorioClientes(TpClientes Cliente[TF], int TLC) {
    int linha = 7;
    int linhaMaxima = 19; // Limite superior da área de saída
    int coluna = 40;
    
    LimparSaida();

    if (TLC <= 0) {
        gotoxy(15, 26);
        printf("Nao ha clientes cadastrados!");
        Sleep(1500);
        LimparMsg();
    } else {
        for (int i = 0; i < TLC; i++) {
            if (linha >= linhaMaxima) {
                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
                gotoxy(15, 26);
                printf("Pressione qualquer tecla para continuar...");
                Sleep(1500);
                getch();
                LimparSaida();
                LimparMsg();
                linha = 7;
            }

            gotoxy(coluna, linha);
            printf("CPF: %s", Cliente[i].CPF);
            gotoxy(coluna, linha + 1);
            printf("Nome: %s", Cliente[i].NomeCli);
            gotoxy(coluna, linha + 2);
			printf("Qtde de compras: %d", Cliente[i].QtdeCompras);
			gotoxy(coluna, linha + 3);
			printf("Valor total comprado: %.2f", Cliente[i].ValorTotComprado);

            linha += 5; 
        }
    }
}


void RelatorioFornecedores(TpFornecedores Fornecedor[TF], int TLF) {
    int linha = 7;
    int linhaMaxima = 19; // Limite superior da área de saída
    int coluna = 40;
    LimparSaida();

    if (TLF <= 0) {
        gotoxy(15, 26);
        printf("Nao ha fornecedores cadastrados!");
        Sleep(1500);
        LimparMsg();
    } else {
        for (int i = 0; i < TLF; i++) {
        	
			linha += 1;
            if (linha >= linhaMaxima) {
                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
                gotoxy(15, 26);
                printf("Pressione qualquer tecla para continuar...");
                Sleep(1500);
                getch();
                LimparSaida();
                LimparMsg();
                linha = 7;
            }

            gotoxy(coluna, linha);
            printf("Codigo: %d", Fornecedor[i].CodForn);
            gotoxy(coluna, linha + 1);
            printf("Nome: %s", Fornecedor[i].NomeForn);
            gotoxy(coluna, linha + 2);
            printf("Cidade: %s", Fornecedor[i].CidadeForn);

            linha += 3; 
        }
    }
}

void RelatorioProdutos(TpProdutos Produto[], int TLP,TpFornecedores Fornecedor[], int TLF) 
{
    int linha = 7;
    int linhaMaxima = 19; // Limite superior da área de saída
    int coluna = 40;
    int pos;
    LimparSaida();
    if (TLP < 0) {
        gotoxy(15,26);
		printf("Nao ha produtos cadastrados!");
		Sleep(1500);
		LimparMsg();
    } else {
        for (int i = 0; i < TLP; i++) {
            if (linha >= linhaMaxima) {
                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
                gotoxy(15,26);
				printf("Pressione qualquer tecla para continuar...");
				Sleep(1500);
                getch();
                LimparSaida();
                LimparMsg();
                linha = 7;
            }

            gotoxy(coluna, linha);
            printf("Codigo: %d", Produto[i].CodProd);
            gotoxy(coluna, linha + 1);
            printf("Descricao: %s", Produto[i].Descr);
            gotoxy(coluna, linha + 2);
            printf("Data de Validade: %d/%d/%d", Produto[i].DtValidade.Dia, Produto[i].DtValidade.Mes, Produto[i].DtValidade.Ano);
			gotoxy(coluna, linha + 3);
			printf("Estoque: %d", Produto[i].Estoque);
			gotoxy(coluna, linha + 4);
			printf("Preco: %.2f", Produto[i].Preco);
			gotoxy(coluna, linha + 5);
			printf("Codigo do fornecedor: %d", Produto[i].CodForn);
			gotoxy(coluna, linha + 6);
			pos = BuscaCod(Produto[i].CodForn, Fornecedor, TLF);
			printf("Nome do fornecedor: %s", Fornecedor[pos].NomeForn);
			
            linha += 8; 
        }
    }
}




void RelatorioVendas(TpVendas Venda[], int TLV, TpVendasProd VendaProduto[], int TLVP, TpProdutos Produto[], int TLP, TpFornecedores Fornecedor[], int TLF)
{
    int linha = 7, pos, posForn;
    int linhaMaxima = 19; // Limite superior da área de saída
    int coluna = 40;
    float totalItem;
    double totalVenda = 0;

    LimparSaida();
    if (TLV <= 0)
    {
        LimparSaida();
        gotoxy(15, 26);
        printf("Nao ha vendas cadastradas!");
        Sleep(1500);
        LimparMsg();
    }
    else
    {
        for (int i = 0; i < TLV; i++)
        {
            if (linha >= linhaMaxima)
            {
                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
                LimparMsg();
                gotoxy(15, 26);
                printf("Pressione qualquer tecla para continuar...");
                Sleep(1500);
                getch();
                LimparSaida();
                LimparMsg();
                linha = 7;
            }

            gotoxy(coluna, linha);
            printf("Codigo da venda: %d", Venda[i].CodVenda + 1);
            linha += 1; // Incrementa linha duas vezes
            gotoxy(coluna, linha);
            printf("Produtos:");

            for (int j = 0; j < TLVP; j++)
            {
            	if (linha >= linhaMaxima)
	            {
	                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
	                LimparMsg();
	                gotoxy(15, 26);
	                printf("Pressione qualquer tecla para continuar...");
	                Sleep(1500);
	                getch();
	                LimparSaida();
	                LimparMsg();
	                linha = 7;
	            }
                if (VendaProduto[j].CodVenda == Venda[i].CodVenda)
                {
                    linha += 1;
                    gotoxy(coluna, linha);
                    printf("%d", VendaProduto[j].CodProd);

                    pos = BuscaCodProd(VendaProduto[j].CodProd, Produto, TLP);

                    coluna += 10;
                    gotoxy(coluna, linha);
                    printf("%s", Produto[pos].Descr);

                    coluna += 9;
                    gotoxy(coluna, linha);
                    printf("%d", VendaProduto[j].Qtde);

                    totalItem = VendaProduto[j].Qtde * Produto[pos].Preco;
                    coluna += 6;
                    gotoxy(coluna, linha);
                    printf("R$%.2f", totalItem);

                    coluna += 10;
                    posForn = BuscaCod(Produto[pos].CodForn, Fornecedor, TLF);
                    if (posForn != -1)
                    {
                        gotoxy(coluna, linha);
                        printf("%s", Fornecedor[posForn].NomeForn);
                    }
                    else
                    {
                        gotoxy(coluna, linha);
                        printf("Fornecedor nao encontrado");
                    }

                    linha += 1; // Incrementa linha para o próximo produto
                    coluna = 40; // Reinicializa coluna para o próximo produto
                }
            }

            linha += 1;
            coluna = 40;
            gotoxy(coluna, linha);
            printf("Total: R$%.2f", Venda[i].TotVenda);

            linha += 1;
            gotoxy(coluna, linha);
            printf("............................................");
            linha = linha + 2; // Ajuste o espaço entre cada venda.
            if (linha >= linhaMaxima)
            {
                // Se ultrapassar a borda da área de saída, aguarde uma ação do usuário para continuar.
                LimparMsg();
                gotoxy(15, 26);
                printf("Pressione qualquer tecla para continuar...");
                Sleep(1500);
                getch();
                LimparSaida();
                LimparMsg();
                linha = 7;
            }
            
        }
    }
}


char Menu(void)
{
	char op;
	LimparMsg();
	LimparSaida();
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
	printf("[G] Aumento de precos");
	gotoxy(8,17);
	printf("[I] Inserir Dados");
	gotoxy(8,18);
	printf("[ESC] Sair");
	gotoxy(8,20);
	printf("Opcao desejada: ");
	fflush(stdin);
	op = toupper(getch());
}



char MenuCadastro(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int &TLC, int &TLF, int &TLP)
{
	LimparMenu();
	char opCadastro;
	LimparSaida();
	
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
				case 'C': CadastroProdutos(Produto, TLP, Fornecedor, TLF);
						  break;	
			}
	}while(opCadastro!=27);
}

char MenuConsulta(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int TLC, int TLF, int TLP)
{
	LimparMenu();
	LimparSaida();
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
				case 'C': ConsultaProdutos(Produto, TLP);
						  break;	
			}
	}while(opConsulta != 27);
}

char MenuAlteracao(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], int &TLC, int &TLF, int &TLP)
{
	LimparMenu();
	char opAlteracao;
	LimparSaida();
	
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
				case 'C': AlteraProdutos(Produto, TLP, Fornecedor, TLF);
						  break;	
			}
	}while(opAlteracao!=27);
}

char MenuExclusao(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[], TpVendas Venda[], TpVendasProd VendaProd[], int &TLC, int &TLF, int &TLP, int &TLV, int &TLVP)
{
	LimparMenu();
	char opExclusao;
	LimparSaida();
	
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
		printf("[D] Excluir venda"); 
		gotoxy(8,13);
		printf("[ESC] VOLTAR"); 
		gotoxy(8,15);
		printf("Opcao desejada: ");
		fflush(stdin);
		opExclusao = toupper(getch());
		switch(opExclusao)
			{
				case 'A': ExcluiClientes(Cliente, TLC);
						  break;
				case 'B': ExcluiFornecedores(Fornecedor, TLF, Produto, TLP);
						  break;
				case 'C': ExcluiProdutos(Produto, TLP);
						  break;
				case 'D': ExcluiVendas(Venda, VendaProd, Fornecedor, Produto, TLV, TLVP, TLF, TLP);
						  break;	
			}
	}while(opExclusao!=27);
}

char MenuRelatorios(TpClientes Cliente[], TpFornecedores Fornecedor[], TpProdutos Produto[],TpVendas Venda[],TpVendasProd VendaProd[], int TLC, int TLF, int TLP, int TLV, int TLVP)
{
	LimparMenu();
	char opRelatorio;
	LimparSaida();
	
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
		printf("[D] Relatorio de vendas"); 
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
				case 'C': RelatorioProdutos(Produto, TLP, Fornecedor, TLF);
						  break;
				case 'D': RelatorioVendas(Venda, TLV, VendaProd, TLVP, Produto, TLP, Fornecedor, TLF);
						  break;	
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


int main(void)
{
	char opcao;
	TpClientes Clientes[TF];
	TpFornecedores Fornecedores[TF];
	TpProdutos Produtos[TF];
	TpVendas Venda[TF];
	TpVendasProd VendaProd[TF];
	int TLP = 0, TLC = 0, TLF = 0, TLV = 0, TLVP = 0; // tamanhos lógicos

	
	
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
			case 'D': MenuExclusao(Clientes, Fornecedores, Produtos, Venda, VendaProd,  TLC, TLF, TLP, TLV, TLVP);
					  break;
			case 'E': FazerVenda(Venda, TLV, Clientes, TLC, VendaProd, TLVP, Produtos, TLP);
					  break;
			case 'F': MenuRelatorios(Clientes, Fornecedores, Produtos,Venda,VendaProd, TLC, TLF, TLP, TLV, TLVP);
					  break;
			case 'G': AumentarPreco(Produtos, TLP, Fornecedores,TLF);
					  break;	
			case 'I': InserirDados(Clientes, Fornecedores, Produtos, Venda, VendaProd, TLC, TLF, TLP, TLV, TLVP);
					  break;		
		}
	}while(opcao!=27);
	
	gotoxy(15,30);
	return 0;
}
