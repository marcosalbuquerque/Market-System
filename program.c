#include "library.h"

void clear() {
    system("cls");
}

void menuPrincipal() {
    int op;
    do
    {
        clear();
        printf("---- SISTEMA MERCADO ---- \n");
        printf("1. Cadrastar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Fechar Pedido\n");
        printf("6. Sair do Sistema\n");
        printf("-> ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            cadastrarProduto();
            break;
        case 2:
            listarProdutos();
            break;
        case 3:
            comprarProduto();
            break;
        case 4:
            vizualizarCarrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 6:
            /* code */
            break;
        
        default:
            break;
        }
    } while (op != 6);
    
}

void cadastrarProduto() {
    fclose(arqprodutos);
    Produto produto;
    int tempcodigo, flag;

    arqprodutos = fopen(FILEPRODUTOS, "rb");
    rewind(arqprodutos);
    do
    {
        flag = 0;
        clear();
        printf("-= CADASTRAR PRODUTO =- \n");
        printf("Informe o codigo do produto: ");
        scanf("%d", &tempcodigo);
        while(fread(&produto, sizeof(Produto), 1, arqprodutos) == 1) {
            if(tempcodigo == produto.codigo) {
                printf("Codigo ja existente, tente novamente.\n");
                sleep(1);
                flag = 1;
                break;
            }
        }
    } while (flag == 1);
    produto.codigo = tempcodigo;

    printf("Informe o nome do produto: ");
    fflush(stdin);
    fgets(produto.nome, sizeof(produto.nome), stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    printf("Informe o preco do produto: R$ ");
    scanf("%f", &produto.preco);

    fclose(arqprodutos);
    arqprodutos = fopen(FILEPRODUTOS, "ab+");
    fseek(arqprodutos, 0, SEEK_END);
    fwrite(&produto, sizeof(Produto), 1, arqprodutos);
    fclose(arqprodutos);

    printf("Produto cadastrado com sucesso!\n");
    sleep(1);
}

void listarProdutos() {
    fclose(arqprodutos);
    arqprodutos = fopen(FILEPRODUTOS, "rb");
    rewind(arqprodutos);

    Produto produto;
    clear();
    while(fread(&produto, sizeof(Produto), 1, arqprodutos) == 1) {
        printf("------------------------\n");
        printf("Nome: %s\n", produto.nome);
        printf("Codigo: %d\n", produto.codigo);
        printf("Preco: R$ %.2f\n", produto.preco);
        printf("------------------------\n\n");
    }
    system("pause");
}

void comprarProduto() {
    clear();

    Produto produto;
    int encontrado = 0;

    fclose(arqprodutos);
    arqprodutos = fopen(FILEPRODUTOS, "rb");
    rewind(arqprodutos);

    if (carrinho.quantidade < LIM) {
        int cod;
        printf("Infome o codigo do produto: ");
        scanf("%d", &cod);
        while(fread(&produto, sizeof(Produto), 1, arqprodutos) == 1) {
            if(cod == produto.codigo) {
                encontrado = 1;
                carrinho.produto[carrinho.quantidade] = produto;
                carrinho.quantidade++;
                printf("Item adicionado no carrinho com sucesso!\n");
                sleep(1);
            }
        }
        if (!encontrado) {
            printf("Codigo invalido. Tente novamente.\n");
            sleep(1);
        }
        fclose(arqprodutos);

    } else {
        printf("Limite de itens no carrinho excedido, remova um dos itens para continuar.\n");
        sleep(1);
    }
}

void vizualizarCarrinho() {
    clear();
    for(int i = 0; i < carrinho.quantidade; i++) {
        printf("------------------------\n");
        printf("Nome: %s\n", carrinho.produto[i].nome);
        printf("Codigo: %d\n", carrinho.produto[i].codigo);
        printf("Preco: R$ %.2f\n", carrinho.produto[i].preco);
        printf("------------------------\n\n");
    }
    printf("Quantidade de itens: %d\n", carrinho.quantidade);
    system("pause");

}

void fecharPedido() {
    Carrinho new;
    clear();
    float result = 0;
    for(int i = 0; i < carrinho.quantidade; i++) {
        result += carrinho.produto[i].preco;
    }
    printf("Valor total: R$ %.2f\n", result);
    carrinho = new;
    carrinho.quantidade = 0;
    printf("Compra realizada com sucesso!\n");
    system("pause");
}

void infoProduto(Produto prod) {
    printf("------------------------\n");
    printf("Nome: %s\n", prod.nome);
    printf("Codigo: %d\n", prod.codigo);
    printf("Preco: R$ %.2f\n", prod.preco);
    printf("------------------------\n\n");
}

int temNoCarrinho(int cod) {
    for (int i = 0; i < carrinho.quantidade; i++) {
        if (carrinho.produto[i].codigo == cod) {
            return 1;
            break;
        }
    }
    return 0;
}

Produto pegarProdutoPorCodigo(int cod) {
    Produto produto;
    arqprodutos = fopen(FILEPRODUTOS, "rb");
    rewind(arqprodutos);
    while(fread(&produto, sizeof(Produto), 1, arqprodutos) == 1) {
        if(cod == produto.codigo) {
            fclose(arqprodutos);
            return produto;
        }
    }
}