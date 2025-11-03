#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[100];
    char cpf[15];
    char rg[20];
    char sexo;
    int dia, mes, ano;
} Aluno;

void cadastrarAluno();
void listarAlunos();
void limparBuffer();

int main() {
    int opcao;
    
    printf("=== SISTEMA DE CADASTRO DE ALUNOS ===\n");
    
    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar novo aluno\n");
        printf("2 - Listar todos os alunos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarAluno();
                break;
            case 2:
                listarAlunos();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarAluno() {
    Aluno aluno;
    FILE *arquivo;
    
    printf("\n=== NOVO CADASTRO ===\n");
    
    printf("Matricula: ");
    scanf("%d", &aluno.matricula);
    limparBuffer();
    
    printf("Nome: ");
    fgets(aluno.nome, 100, stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = 0;
    
    printf("CPF: ");
    fgets(aluno.cpf, 15, stdin);
    aluno.cpf[strcspn(aluno.cpf, "\n")] = 0;
    
    printf("RG: ");
    fgets(aluno.rg, 20, stdin);
    aluno.rg[strcspn(aluno.rg, "\n")] = 0;
    
    printf("Sexo (M/F): ");
    scanf(" %c", &aluno.sexo);
    limparBuffer();
    
    // CORRE��O PRINCIPAL: Leitura mais segura da data
    printf("Data de nascimento (DD/MM/AAAA): ");
    
    char data_input[20];
    fgets(data_input, sizeof(data_input), stdin);
    data_input[strcspn(data_input, "\n")] = 0;
    
    // Tenta ler a data no formato DD/MM/AAAA
    int valores_lidos = sscanf(data_input, "%d/%d/%d", &aluno.dia, &aluno.mes, &aluno.ano);
    
    // Se n�o conseguiu ler no formato com barras, tenta sem barras
    if (valores_lidos != 3) {
        valores_lidos = sscanf(data_input, "%2d%2d%4d", &aluno.dia, &aluno.mes, &aluno.ano);
    }
    
    // Se ainda n�o conseguiu, tenta com espa�os
    if (valores_lidos != 3) {
        valores_lidos = sscanf(data_input, "%d %d %d", &aluno.dia, &aluno.mes, &aluno.ano);
    }
    
    if (valores_lidos != 3) {
        printf("Erro: Formato de data invalido! Use DD/MM/AAAA ou DD MM AAAA\n");
        return;
    }
    
    // Valida��o da data
    if (aluno.dia < 1 || aluno.dia > 31 || aluno.mes < 1 || aluno.mes > 12 || aluno.ano < 1900 || aluno.ano > 2100) {
        printf("Erro: Data invalida!\n");
        return;
    }
    
    // Abre arquivo para append
    arquivo = fopen("alunos.txt", "a");
    
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    // Escreve no arquivo
    fprintf(arquivo, "=== ALUNO CADASTRADO ===\n");
    fprintf(arquivo, "Matricula: %d\n", aluno.matricula);
    fprintf(arquivo, "Nome: %s\n", aluno.nome);
    fprintf(arquivo, "CPF: %s\n", aluno.cpf);
    fprintf(arquivo, "RG: %s\n", aluno.rg);
    fprintf(arquivo, "Sexo: %c\n", aluno.sexo);
    fprintf(arquivo, "Data de Nascimento: %02d/%02d/%d\n", aluno.dia, aluno.mes, aluno.ano);
    fprintf(arquivo, "------------------------\n");
    
    fclose(arquivo);
    
    printf("\nAluno cadastrado com sucesso!\n");
    printf("Data salva: %02d/%02d/%d\n", aluno.dia, aluno.mes, aluno.ano);
}

void listarAlunos() {
    FILE *arquivo;
    char linha[200];
    
    printf("\n=== LISTA DE ALUNOS CADASTRADOS ===\n");
    
    arquivo = fopen("alunos.txt", "r");
    
    if(arquivo == NULL) {
        printf("Nenhum aluno cadastrado ainda!\n");
        return;
    }
    
    while(fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
    
    fclose(arquivo);
}
