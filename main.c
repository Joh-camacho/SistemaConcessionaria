/*------------------ BIBLIOTECAS----------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------ STRUCTS-------------------------------*/

typedef struct produto {
    int id;
    char nome[100];
    int qtde;
    int valido;
} produto;

typedef struct funcionario {
    int id;
    char nome[100];
    char CPF[12];
    int valido;
} funcionario;

typedef struct venda {
    produto *produto;
    funcionario *funcionario;
    int qtde;
} venda;

/*-----------DECLARAÇÃO DE FUNÇÕES---------------------------*/

void imprime_menu_inicial();

int le_opcao(int min, int max);
void le_valida_char(char valida[], char tipo[]);
void le_valida_qtde(int * valida, int i);

void adiciona_funcionario(funcionario funcionarios[], int * qtde);
void consulta_funcionarios(funcionario funcionarios[], int qtde);
void retira_funcionario(funcionario funcionarios[], int qtde);

void cadastrar_produto(produto produtos[], int * qtde);
void retira_produto(produto produtos[], int qtde);
void consulta_estoque(produto produtos[], int qtde);
void realiza_reestoque(produto produtos[], int qtde);

void realizar_venda(venda vendas[], int * qtde_vendas, funcionario funcionarios[], int qtde_funcionarios, produto produtos[], int qtde_produtos);
void consulta_vendas(venda vendas[], int qtde);

funcionario * busca_funcio(funcionario funcionarios[], int qtde_funcionarios, int id_funcionario);
produto * busca_produto(produto produtos[], int qtde_produtos, int id_produto);

void armazena_funcs(funcionario funcionarios[], int qtde_funcionarios);
void armazena_produtos(produto produtos[], int qtde_produtos);
void armazena_vendas(venda vendas[], int qtde_vendas);

void carrega_funcio(funcionario funcionarios[], int *qtde_funcionarios);
void carrega_produtos(produto produtos[], int * qtde_produtos);
void carrega_vendas(venda vendas[], int * qtde_vendas, funcionario funcionarios[], int qtde_funcionarios, produto produtos[], int qtde_produtos);

/*------------------MAIN----------------------------*/

int main() {
    int opcao, i;

    funcionario funcionarios[200];
    int qtde_funcionarios = 0;
    
    produto produtos[200];
    int qtde_produtos = 0;

    venda vendas[200];
    int qtde_vendas = 0;

    carrega_funcio(funcionarios, & qtde_funcionarios);
    carrega_produtos(produtos, & qtde_produtos);
    carrega_vendas(vendas, & qtde_vendas, funcionarios, qtde_funcionarios, produtos, qtde_produtos);

    do {
        imprime_menu_inicial();
        opcao = le_opcao(0, 9);

        switch (opcao) {
        case 1:
            cadastrar_produto(produtos, & qtde_produtos);
            break;
        case 2:
            consulta_estoque(produtos, qtde_produtos);
            break;
        case 3:
            retira_produto(produtos, qtde_produtos);
            break;
        case 4:
            realiza_reestoque(produtos, qtde_produtos);
            break;
        case 5:
            adiciona_funcionario(funcionarios, & qtde_funcionarios);
            break;
        case 6:
            consulta_funcionarios(funcionarios, qtde_funcionarios);
            break;
        case 7:
            retira_funcionario(funcionarios, qtde_funcionarios);
            break;
        case 8:
            realizar_venda(vendas, & qtde_vendas, funcionarios, qtde_funcionarios, produtos, qtde_produtos);
            break;
        case 9:
            consulta_vendas(vendas, qtde_vendas);
            break;
        case 0:
            printf("Encerrando programa!\n");
            break;
        default:
            break;
        }
    } while (opcao != 0);

    armazena_funcs(funcionarios, qtde_funcionarios);
    armazena_produtos(produtos, qtde_produtos);
    armazena_vendas(vendas, qtde_vendas);

    return 0;
}

/*-------------------FUNÇÕES---------------------------------*/

/* A função irá imprimir o menu inicial, onde o usuário poderá assim escolher e seguir para um outro menu.*/
void imprime_menu_inicial() {
    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t RELAMPAGO MARQUINHOS \n");
    printf("--------------------------------------\n");
    printf("1-CADASTRAR NOVO PRODUTO\n");
    printf("2-CONSULTAR ESTOQUE\n");
    printf("3-RETIRAR PRODUTO\n");
    printf("4-REALIZAR REESTOQUE\n");
    printf("5-ADICIONAR FUNCIONÁRIO\n");
    printf("6-CONSULTAR FUNCIONÁRIOS\n");
    printf("7-RETIRAR FUNCIONÁRIO\n");
    printf("8-NOVA VENDA\n");
    printf("9-CONSULTAR VENDAS\n");
    printf("0-SAIR\n");
    printf("--------------------------------------\n");
}

/*A função recebe a quantidade minima e maxima de opções a serem lidas, recebe, valida e retorna a opção desejada pelo usuário.*/
int le_opcao(int min, int max) {
    int opcao;

    do {
        printf("SELECIONE UMA OPÇÃO:\n");
        scanf("%d", & opcao);
        getchar();

        if (opcao < min || opcao > max) {
            printf("ERRO: OPÇÃO INVÁLIDA\n");
        }
    } while ((opcao < min || opcao > max));

    return opcao;
}

/* A função recebe uma string e valida se a mesma está vazia ou não.*/
void le_valida_char(char valida[], char tipo[]) {
    do {
        scanf("%[^\n]", valida);
        getchar();

        if (strcmp(valida, "") == 0) {
            printf("ERRO:%s INVÁLIDO.", tipo);
        }
    } while (strcmp(valida, "") == 0);
}

/*A função recebe um inteiro e checa se ele é valido ou não */
void le_valida_qtde(int * valida, int i) {
    if (i == 1) {
        do {
            scanf("%d", valida);
            getchar();
            if ( * valida <= 0) {
                printf("ERRO:QUANTIDADE INVÁLIDA.");
            }
        } while ( * valida <= 0);
    } else if (i == 2) {
        do {
            scanf("%d", valida);
            getchar();
            if ( * valida < 0) {
                printf("ERRO:QUANTIDADE INVÁLIDA.");
            }
        } while ( * valida < 0);
    }
}

/* A função recebe e adiciona ao sistema um novo funcionário*/
void adiciona_funcionario(funcionario funcionarios[], int * qtde) {
    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t CADASTRAR NOVO FUNCIONÁRIO \n");
    printf("--------------------------------------\n");

    printf("INFORME O NOME DO FUNCIONÁRIO:\n");
    le_valida_char(funcionarios[ * qtde].nome, "NOME");

    printf("INFORME O CPF DO FUNCIONARIO:\n");
    le_valida_char(funcionarios[ * qtde].CPF, "CPF");

    funcionarios[ * qtde].valido = 0;
    funcionarios[ * qtde].id = * qtde;

    * qtde += 1;

    printf("--------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

void consulta_funcionarios(funcionario funcionarios[], int qtde) {
    int i = 0;

    system("clear||cls");
    printf("----------------------------------------------------------\n");
    printf("\t\t\t\t\t FUNCIONARIOS \n");
    printf("----------------------------------------------------------\n");

    if (qtde == 0) {
        printf("Nenhum funcionario cadastrado no sistema.\n");
    } else {
        printf(" \tID\t\t|\t\tNOME\t\t|\t\tCPF\t \n");

        for (i = 0; i < qtde; i++) {
            if (funcionarios[i].valido == 0) {
                printf("\t%d\t\t|\t\%s\t\t|\t\t%s\t \n", funcionarios[i].id, funcionarios[i].nome , funcionarios[i].CPF);
            }
        }
    }

    printf("----------------------------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

/* A função recebe e retira do sistema um antigo funcionário*/
void retira_funcionario(funcionario funcionarios[], int qtde) {
    char cpf[12];
    int i, valida = 0;

    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t RETIRAR FUNCIONARIO \n");
    printf("--------------------------------------\n");
    printf("INFORME O CPF DO FUNCIONARIO A SER RETIRADO:\n");
    scanf("%[^\n]", cpf);
    getchar();

    for (i = 0; i < qtde; i++) {
        if (strcmp(cpf, funcionarios[i].CPF) == 0) {
            valida = 1;

            if (funcionarios[i].valido == 1) {
                printf("FUNCIONARIO JÁ ESTÁ RETIRADO.\n");
                break;
            }
                
            funcionarios[i].valido = 1;

            printf("%s RETIRADO COM SUCESSO\n", funcionarios[i].nome);
            break;
        }
    }

    if (valida == 0) {
        printf("FUNCIONARIO NÃO EXISTE.\n");
    }

    printf("--------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

/* A função cadastra um novo produto e sua respectiva quantidade ao estoque*/
void cadastrar_produto(produto produtos[], int * qtde) {
    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t CADASTRAR NOVO PRODUTO \n");
    printf("--------------------------------------\n");

    printf("INFORME O NOME DO PRODUTO:\n");
    le_valida_char(produtos[ * qtde].nome, "NOME");

    do {
        printf("INFORME A QUANTIDADE DO PRODUTO:\n");
        scanf("%d", & produtos[ * qtde].qtde);
        getchar();

        if (produtos[ * qtde].qtde < 0) {
            printf("ERRO:PRODUTO INVALIDO\n");
        }
    } while (produtos[ * qtde].qtde < 0);

    produtos[ * qtde].id = * qtde;
    produtos[ * qtde].valido = 0;

    * qtde += 1;

    printf("--------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

/*função de edição, recebe como paramêtro os dados de produto e quantiade a serem retirados do estoque, reatualizando assim o estoque. */
void retira_produto(produto produtos[], int qtde) {
    int i, id, valida = 0;
    char nome[100];

    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t RETIRAR PRODUTO \n");
    printf("--------------------------------------\n");
    printf("INFORME O ID DO PRODUTO A SER RETIRADO DO ESTOQUE:\n");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < qtde; i++) {
        if (produtos[i].id == id) {
            valida = 1;

            if (produtos[i].valido == 1) {
                printf("PRODUTO JÁ ESTÁ RETIRADO.\n");
                break;
            }
            
            produtos[i].valido = 1;
            printf("%s RETIRADO COM SUCESSO\n", produtos[i].nome);
            break;
        }
    }

    if (valida == 0) {
        printf("PRODUTO NÃO EXISTE NO ESTOQUE.\n");
    }

    printf("--------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

/* A função tem como objetivo mostrar a lista de produtos no estoque e suas respectivas quantidades, recebe como parametro as informações e imprime na tela de acordo com a formatação definida*/
void consulta_estoque(produto produtos[], int qtde) {
    int i = 0;

    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t CONSULTA DE ESTOQUE \n");
    printf("--------------------------------------\n");

    if (qtde == 0) {
        printf("Nenhum produto cadastrado no sistema.\n");
    } else {
        printf(" \tID\t\t|\t\tPRODUTO\t\t|\t\tQTDE\t \n");

        for (i = 0; i < qtde; i++) {
            if (produtos[i].valido == 0) {
                printf("\t%d\t\t|\t\t%s\t\t|\t\t%d\t \n", produtos[i].id, produtos[i].nome, produtos[i].qtde);
            }
        }
    }

    printf("--------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

/*A função percorre por todos os produtos cadastrados no estoque recebendo do usuário as respectivas novas quantidades */
void realiza_reestoque(produto produtos[], int qtde) {
    int i, qtdeprod;

    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t REALIZAR REESTOQUE \n");
    printf("--------------------------------------\n");
    printf("INFORME AS NOVAS QUANTIDADES A SEREM DEFINIDAS AO ESTOQUE:\n");

    for (i = 0; i < qtde; i++) {
        if (produtos[i].valido == 0) {
            printf("PRODUTO: %s QTDE: ", produtos[i].nome);
            le_valida_qtde( & qtdeprod, 2);

            produtos[i].qtde = qtdeprod;
            printf("\n");
        }
    }

    printf("--------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

/*A função recebe do usuário os dados de venda e relaciona com os produtos em estoque, retornando assim se existe o produto em estoque ou não e caso exista conclui a compra*/
void realizar_venda(venda vendas[], int * qtde_vendas, funcionario funcionarios[], int qtde_funcionarios, produto produtos[], int qtde_produtos) {

    funcionario * funcionario;
    produto * produto;
    
    char cpf[12];
    int i, id_produto, qtde_prod, valida = 0;

    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t NOVA VENDA \n");
    printf("--------------------------------------\n");

    do {
        printf("INFORME O CPF DO FUNCIONÁRIO:\n");
        le_valida_char(cpf, "CPF");
        
        for (i = 0; i < qtde_funcionarios; i++) {
            if (strcmp(funcionarios[i].CPF, cpf) == 0 && funcionarios[i].valido == 0) {
                valida = 1;
                funcionario = &funcionarios[i];
                break;
            }
        }

        if (valida == 0) {
            printf("ERRO: CPF INVÁLIDO.\n");
            getchar();
        }
    } while (valida == 0);

    valida = 0;

    do {
        printf("INFORME O ID DO PRODUTO:\n");
        scanf("%d", &id_produto);
        getchar();

        for (i = 0; i < qtde_produtos; i++) {
            if (produtos[i].id == id_produto && produtos[i].valido == 0) {
                valida = 1;
                produto = &produtos[i];
                break;
            }
        }

        if (valida == 0) {
            printf("ERRO: PRODUTO INEXISTENTE\n.");
            getchar();
        }
    } while (valida == 0);

    valida = 0;

    do {
        printf("INFORME A QUANTIDADE DO PRODUTO DESEJADO:\n");
        le_valida_qtde( & qtde_prod, 1);

        if (produto -> qtde >= qtde_prod) {
            valida = 1;
            produto -> qtde -= qtde_prod;
            break;
        } else {
            printf("O PRODUTO POSSUI APENAS %d\n\n", produto -> qtde);
        }
    } while (valida == 0);

    vendas[ * qtde_vendas].produto = produto;
    vendas[ * qtde_vendas].funcionario = funcionario;
    vendas[ * qtde_vendas].qtde = qtde_prod;
    
    * qtde_vendas += 1;

    printf("\nPRODUTO COMPRADO COM SUCESSO!\n");
    printf("--------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

void consulta_vendas(venda vendas[], int qtde) {
    int i = 0;

    system("clear||cls");
    printf("----------------------------------------------------------\n");
    printf("\t\t\t\t\t VENDAS REALIZADAS \n");
    printf("----------------------------------------------------------\n");

    if (qtde == 0) {
        printf("Nenhuma venda realizada no sistema.\n");
    } else {
        printf(" \tPRODUTO\t\t|\t\tFUNCIONARIO\t\t|\t\tQTDE\t \n");

        for (i = 0; i < qtde; i++) {
            printf("\t%s\t\t|\t\%s\t\t|\t\t%d\t \n", vendas[i].produto -> nome, vendas[i].funcionario -> nome , vendas[i].qtde);
        }
    }

    printf("----------------------------------------------------------\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
}

/*A função busca e confere se o funcionario existe*/
funcionario * busca_funcio(funcionario funcionarios[], int qtde_funcionarios, int id_funcionario) {
    int i;

    for (i = 0; i < qtde_funcionarios; i++) {
        if (funcionarios[i].id == id_funcionario) {
            return &funcionarios[i];
        }
    }

    return NULL;
}

/*A função busca e confere se o produto existe*/
produto * busca_produto(produto produtos[], int qtde_produtos, int id_produto) {
    int i;

    for (i = 0; i < qtde_produtos; i++) {
        if (produtos[i].id == id_produto) {
            return &produtos[i];
        }
    }

    return NULL;
}

/* Essa função armazena os dados no arquivo "funcionario.txt"*/
void armazena_funcs(funcionario funcionarios[], int qtde_funcionarios) {
    FILE * arq = fopen("funcionario.txt", "w");
    int i;

    for (i = 0; i < qtde_funcionarios; i++) {
        fprintf(arq, "%d|%s|%s|valido = %d\n", funcionarios[i].id, funcionarios[i].nome, funcionarios[i].CPF, funcionarios[i].valido);
    }

    fclose(arq);
}

/* Essa função armazena os dados no arquivo "estoque_prod.txt"*/
void armazena_produtos(produto produtos[], int qtde_produtos) {
    FILE * arq = fopen("estoque_prod.txt", "w");
    int i;

    for (i = 0; i < qtde_produtos; i++) {
        fprintf(arq, "%d|%s|%d|valido = %d\n", produtos[i].id, produtos[i].nome, produtos[i].qtde, produtos[i].valido);
    }
    
    fclose(arq);
}

/* Essa função armazena os dados no arquivo "venda.txt"*/
void armazena_vendas(venda vendas[], int qtde_vendas) {
    FILE * arq = fopen("venda.txt", "w");
    int i;

    for (i = 0; i < qtde_vendas; i++) {
        fprintf(arq, "%d|%d\n", vendas[i].produto -> id, vendas[i].funcionario -> id);
    }

    fclose(arq);
}

/*A função carrega dados do arquivo "funcionario.txt"*/
void carrega_funcio(funcionario funcionarios[], int * qtde_funcionarios) {
    FILE * arq = fopen("funcionario.txt", "r");

    if (fgetc(arq) == EOF) {
        fclose(arq);
        return;
    }

    fseek(arq, 0, SEEK_SET);

    while (!feof(arq)) {
        fscanf(arq, "%d|%[^|]|%[^|]|valido = %d\n", 
            &funcionarios[ * qtde_funcionarios].id, 
            funcionarios[ * qtde_funcionarios].nome, 
            funcionarios[ * qtde_funcionarios].CPF,
            &funcionarios[ * qtde_funcionarios].valido);

        * qtde_funcionarios += 1;
    }

    fclose(arq);
}

/*A função carrega dados do arquivo "estoque.txt"*/
void carrega_produtos(produto produtos[], int * qtde_produtos) {
    FILE * arq = fopen("estoque_prod.txt", "r");

    if (fgetc(arq) == EOF) {
        fclose(arq);
        return;
    }

    fseek(arq, 0, SEEK_SET);

    while (!feof(arq)) {
        fscanf(arq, "%d|%[^|]|%d|valido = %d\n", 
            &produtos[ * qtde_produtos].id, 
            produtos[ * qtde_produtos].nome, 
            &produtos[ * qtde_produtos].qtde, 
            &produtos[ * qtde_produtos].valido);

        * qtde_produtos += 1;
    }

    fclose(arq);
}

/*A função carrega dados do arquivo "vendas.txt*/
void carrega_vendas(venda vendas[], int * qtde_vendas, funcionario funcionarios[], int qtde_funcionarios, produto produtos[], int qtde_produtos) {
    FILE * arq = fopen("venda.txt", "r");
    int id_produto, id_funcionario, qtde;

    if (fgetc(arq) == EOF) {
        fclose(arq);
        return;
    }

    fseek(arq, 0, SEEK_SET);

    while (!feof(arq)) {
        fscanf(arq, "%d|%d|%d\n", & id_produto, & id_funcionario, & qtde);

        vendas[ * qtde_vendas].produto = busca_produto(produtos, qtde_produtos, id_produto);
        vendas[ * qtde_vendas].funcionario = busca_funcio(funcionarios, qtde_funcionarios, id_funcionario);
        vendas[ * qtde_vendas].qtde = qtde;

        * qtde_vendas += 1;
    }

    fclose(arq);
}