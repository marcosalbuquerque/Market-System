#include "program.c"

int main(int argc, char const *argv[])
{
    arqprodutos = fopen(FILEPRODUTOS, "ab+");
    carrinho.quantidade = 0;
    
    if (!arqprodutos) {
        printf("Erro ao inicializar o programa.");
        return 1;
    }
    menuPrincipal();
    return 0;
}
