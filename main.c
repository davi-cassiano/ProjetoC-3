#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 // Função principal para o menu do sistema
int main() {
    int opcao, logado = 0;

    do {
        printf("\nFaça seu cadastro ou realize seu login!\n");
        printf("\n| 1 | Cadastrar Usuário\n");
        printf("| 2 | Realizar Login\n");
        printf("| 3 | Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            cadastrarUsuario();
            break;
        case 2:
            if (realizarLogin()) {
                logado = 1;
                printf("\nLogin bem-sucedido! Bem-vindo ao sistema de gerenciamento de livros.\n");
            } else {
                printf("\nLogin ou senha incorretos. Tente novamente.\n");
            }
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3 && !logado);

    if (logado) {
        do {
            printf("\nControle de Livros\n");
            printf("\n| 1 | Adicionar Livro\n");
            printf("| 2 | Listar Livros\n");
            printf("| 3 | Listar Gêneros\n");
            printf("| 4 | Buscar Livro por Título\n");
            printf("| 5 | Buscar Livro por Gênero\n");
            printf("| 6 | Editar Livro\n");
            printf("| 7 | Remover Livro\n");
            printf("| 8 | Sair\n");
            printf("\nEscolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                listarLivros();
                break;
            case 3:
                listarGeneros();
                break;
            case 4:
                buscarLivroPorTitulo();
                break;
            case 5:
                buscarLivroPorGenero();
                break;
            case 6:
                editarLivro();
                break;
            case 7:
                removerLivro();
                break;
            case 8:
                printf("Saindo do sistema de livros...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
            }
        } while (opcao != 8);
    }

#define MAX_USUARIOS 10
#define MAX_LIVROS 100
#define MAX_GENEROS 30
#define TAMANHO_LOGIN 20
#define TAMANHO_SENHA 20

typedef struct {
    char login[TAMANHO_LOGIN];
    char senha[TAMANHO_SENHA];
} Usuario;

typedef struct {
    char titulo[50];
    char autor[50];
    char genero[30];
    int ano;
} Livro;

Usuario usuarios[MAX_USUARIOS];
Livro biblioteca[MAX_LIVROS];

int totalUsuarios = 0;
int totalLivros = 0;

// Função para verificar se o login já existe
int loginExiste(char login[]) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].login, login) == 0) {
            return 1;
        }
    }
    return 0;
}

// Função para cadastrar um novo usuário
void cadastrarUsuario() {
    if (totalUsuarios >= MAX_USUARIOS) {
        printf("Limite de usuários atingido.\n");
        return;
    }

    Usuario novoUsuario;
    printf("Digite o login desejado: ");
    scanf("%s", novoUsuario.login);

    if (loginExiste(novoUsuario.login)) {
        printf("Erro: Login já existe. Tente um login diferente.\n");
        return;
    }

    printf("Digite a senha: ");
    scanf("%s", novoUsuario.senha);

    usuarios[totalUsuarios++] = novoUsuario;
    printf("Usuário cadastrado com sucesso!\n");
}

// Função para validar o login do usuário
int realizarLogin() {
    char login[TAMANHO_LOGIN];
    char senha[TAMANHO_SENHA];

    printf("Login: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%s", senha);

    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].login, login) == 0 &&
            strcmp(usuarios[i].senha, senha) == 0) {
            return 1;
        }
    }
    return 0;
}