#include<stdio.h>
#include<unistd.h>
#include<string.h>


#define LIM 50
#define FILEPRODUTOS "produtos.dat"

FILE *arqprodutos;

// FUNÇÕES
void menuPrincipal();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void vizualizarCarrinho();
void fecharPedido();
void infoProduto(Produto prod);
int temNoCarrinho(int cod);

// STRUCTS
typedef struct { 
    int codigo;
    char nome[99];
    float preco;
} Produto;

typedef struct {
    Produto produto[LIM];
    int quantidade;
} Carrinho;

Carrinho carrinho;

