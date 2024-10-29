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
    // Salvar dados automaticamente ao sair
    salvarUsuarios(); // Salvar livros em formato txt
    salvarLivros(); // Salvar livros em formato txt
    salvarUsuariosBinario(); // Salvar usuários em formato binário
    salvarLivrosBinario();   // Salvar livros em formato binário

    return 0;
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

// Função para adicionar um livro
void adicionarLivro() {
    if (totalLivros >= MAX_LIVROS) {
        printf("Limite de livros atingido.\n");
        return;
    }

    Livro novoLivro;
    printf("Digite o título do livro: ");
    getchar();
    fgets(novoLivro.titulo, 50, stdin);
    strtok(novoLivro.titulo, "\n");

    printf("Digite o autor do livro: ");
    fgets(novoLivro.autor, 50, stdin);
    strtok(novoLivro.autor, "\n");

    printf("Digite o gênero do livro: ");
    fgets(novoLivro.genero, 30, stdin);
    strtok(novoLivro.genero, "\n");

    printf("Digite o ano de publicação: ");
    scanf("%d", &novoLivro.ano);

    biblioteca[totalLivros++] = novoLivro;
    printf("Livro adicionado com sucesso!\n");
}

// Função para listar todos os livros
void listarLivros() {
    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    printf("Lista de Livros:\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("%d. Título: %s | Autor: %s | Gênero: %s | Ano: %d\n", i + 1,
               biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].genero,
               biblioteca[i].ano);
    }
}

// Função para buscar livros por gênero
void buscarLivroPorGenero() {
    char generoBusca[30];
    int encontrado = 0;
    printf("Digite o gênero para busca: ");
    getchar();
    fgets(generoBusca, 30, stdin);
    strtok(generoBusca, "\n");

    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(biblioteca[i].genero, generoBusca) == 0) {
            printf("Título: %s | Autor: %s | Ano: %d\n", biblioteca[i].titulo,
                   biblioteca[i].autor, biblioteca[i].ano);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum livro encontrado para o gênero especificado.\n");
    }
}

// Função para listar gêneros 
void listarGeneros() {
    char generos[MAX_LIVROS][30]; // Armazenar gêneros únicos
    int totalGeneros = 0;

    for (int i = 0; i < totalLivros; i++) {
        int j;
        // Verifica se o gênero já está na lista
        for (j = 0; j < totalGeneros; j++) {
            if (strcmp(generos[j], biblioteca[i].genero) == 0) {
                break;
            }
        }
        // Se não encontrado, adiciona à lista
        if (j == totalGeneros) {
            strcpy(generos[totalGeneros++], biblioteca[i].genero);
        }
    }

    if (totalGeneros == 0) {
        printf("Nenhum gênero cadastrado.\n");
    } else {
        printf("Gêneros cadastrados:\n");
        for (int i = 0; i < totalGeneros; i++) {
            printf("%d. %s\n", i + 1, generos[i]);
        }
    }
}

// Função para buscar livros por título
void buscarLivroPorTitulo() {
    char tituloBusca[50];
    int encontrado = 0;
    printf("Digite o título do livro para busca: ");
    getchar();
    fgets(tituloBusca, 50, stdin);
    strtok(tituloBusca, "\n");

    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(biblioteca[i].titulo, tituloBusca) == 0) {
            printf(
                "Livro encontrado: Título: %s | Autor: %s | Gênero: %s | Ano: %d\n",
                biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].genero,
                biblioteca[i].ano);
            encontrado = 1;
            break; // Para retornar apenas o primeiro livro encontrado
        }
    }

    if (!encontrado) {
        printf("Nenhum livro encontrado com o título especificado.\n");
    }
}

// Função para editar os dados de um livro
void editarLivro() {
    char tituloBusca[50];
    int encontrado = 0;
    printf("Digite o título do livro que deseja editar: ");
    getchar();
    fgets(tituloBusca, 50, stdin);
    strtok(tituloBusca, "\n");

    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(biblioteca[i].titulo, tituloBusca) == 0) {
            printf("Livro encontrado. Insira os novos dados:\n");

            printf("Novo título (atual: %s): ", biblioteca[i].titulo);
            fgets(biblioteca[i].titulo, 50, stdin);
            strtok(biblioteca[i].titulo, "\n");

            printf("Novo autor (atual: %s): ", biblioteca[i].autor);
            fgets(biblioteca[i].autor, 50, stdin);
            strtok(biblioteca[i].autor, "\n");

            printf("Novo gênero (atual: %s): ", biblioteca[i].genero);
            fgets(biblioteca[i].genero, 30, stdin);
            strtok(biblioteca[i].genero, "\n");

            printf("Novo ano de publicação (atual: %d): ", biblioteca[i].ano);
            scanf("%d", &biblioteca[i].ano);

            printf("Dados do livro atualizados com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Livro não encontrado.\n");
    }
}

// Função para remover um livro pelo título
void removerLivro() {
    char tituloRemover[50];
    int encontrado = 0;
    printf("Digite o título do livro para remover: ");
    getchar();
    fgets(tituloRemover, 50, stdin);
    strtok(tituloRemover, "\n");

    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(biblioteca[i].titulo, tituloRemover) == 0) {
            for (int j = i; j < totalLivros - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            totalLivros--;
            printf("Livro removido com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Livro não encontrado.\n");
    }
}

// Função para salvar os usuários em um arquivo txt
void salvarUsuarios() {
    FILE *file = fopen("usuarios.txt", "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < totalUsuarios; i++) {
        fprintf(file, "%s\n%s\n", usuarios[i].login, usuarios[i].senha);
    }
    fclose(file);
}

// Função para salvar os livros em um arquivo txt
void salvarLivros() {
    FILE *file = fopen("livros.txt", "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < totalLivros; i++) {
        fprintf(file, "%s\n%s\n%s\n%d\n", biblioteca[i].titulo,
                biblioteca[i].autor, biblioteca[i].genero, biblioteca[i].ano);
    }
    fclose(file);
}