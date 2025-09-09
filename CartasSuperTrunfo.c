#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_CARTAS 100
#define EPSILON 0.0001

typedef struct {
    char estado[3];
    char codigo[10];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
} Carta;

void calcularIndicadores(Carta *c) {
    c->densidadePopulacional = c->populacao / c->area;
    c->pibPerCapita = c->pib / c->populacao;
}

void exibirCarta(Carta c) {
    printf("Cidade: %s (%s)\n", c.nomeCidade, c.estado);
    printf("Código: %s\n", c.codigo);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", c.densidadePopulacional);
    printf("PIB per capita: %.2f\n\n", c.pibPerCapita);
}

int contarCartasPorEstado(Carta cartas[], int total, const char estado[]) {
    int contador = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(cartas[i].estado, estado) == 0) {
            contador++;
        }
    }
    return contador;
}

void cadastrarCarta(Carta *carta, Carta cartas[], int totalCartas) {
    printf("\n=== Cadastro da Carta %d ===\n", totalCartas + 1);

    printf("Estado (sigla): ");
    scanf(" %2s", carta->estado);

    printf("Nome da cidade: ");
    scanf(" %[^\n]", carta->nomeCidade);

    printf("População: ");
    scanf("%d", &carta->populacao);

    printf("Área (km²): ");
    scanf("%f", &carta->area);

    printf("PIB (em bilhões): ");
    scanf("%f", &carta->pib);

    printf("Número de pontos turísticos: ");
    scanf("%d", &carta->pontosTuristicos);

    int numero = contarCartasPorEstado(cartas, totalCartas, carta->estado) + 1;
    sprintf(carta->codigo, "%s%03d", carta->estado, numero);

    calcularIndicadores(carta);
}

float obterValorPorAtributo(Carta c, int atributo) {
    switch (atributo) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.densidadePopulacional;
        case 5: return c.pibPerCapita;
        default: return -1;
    }
}

void mostrarMenuAtributos() {
    printf("\nEscolha 2 atributos para comparação:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Densidade Populacional\n");
    printf("5 - PIB per capita\n");
}

int compararAtributo(float valor1, float valor2, int atributo) {
    // Densidade populacional: menor vence
    if (atributo == 4)
        return (valor1 < valor2) ? 1 : (valor2 < valor1 ? 2 : 0);
    else
        return (valor1 > valor2) ? 1 : (valor2 > valor1 ? 2 : 0);
}

void exibirResultado(int vencedor, Carta c1, Carta c2, int a1, int a2) {
    printf("\n=== Resultado da Comparação ===\n");

    float v1a1 = obterValorPorAtributo(c1, a1);
    float v2a1 = obterValorPorAtributo(c2, a1);
    float v1a2 = obterValorPorAtributo(c1, a2);
    float v2a2 = obterValorPorAtributo(c2, a2);

    printf("Atributo 1: %s\n", 
        (a1 == 1) ? "População" :
        (a1 == 2) ? "Área" :
        (a1 == 3) ? "PIB" :
        (a1 == 4) ? "Densidade Populacional" :
        "PIB per capita");

    printf("Carta 1 - %s: %.2f\n", c1.nomeCidade, v1a1);
    printf("Carta 2 - %s: %.2f\n", c2.nomeCidade, v2a1);

    printf("\nAtributo 2: %s\n", 
        (a2 == 1) ? "População" :
        (a2 == 2) ? "Área" :
        (a2 == 3) ? "PIB" :
        (a2 == 4) ? "Densidade Populacional" :
        "PIB per capita");

    printf("Carta 1 - %s: %.2f\n", c1.nomeCidade, v1a2);
    printf("Carta 2 - %s: %.2f\n", c2.nomeCidade, v2a2);

    if (vencedor == 1)
        printf("\n🏆 Carta 1 (%s) venceu!\n", c1.nomeCidade);
    else if (vencedor == 2)
        printf("\n🏆 Carta 2 (%s) venceu!\n", c2.nomeCidade);
    else
        printf("\n🤝 Empate entre as cartas!\n");
}

int main() {
  //  system("chcp 65001 > null"); // Configura o console para UTF-8 no Windows
    Carta cartas[MAX_CARTAS];
    int totalCartas = 0;

    cadastrarCarta(&cartas[totalCartas], cartas, totalCartas);
    totalCartas++;

    cadastrarCarta(&cartas[totalCartas], cartas, totalCartas);
    totalCartas++;

    printf("\n=== Carta 1 ===\n");
    exibirCarta(cartas[0]);

    printf("=== Carta 2 ===\n");
    exibirCarta(cartas[1]);

    mostrarMenuAtributos();

    int atributo1, atributo2;
    printf("Escolha o primeiro atributo (1-5): ");
    scanf("%d", &atributo1);
    printf("Escolha o segundo atributo (1-5): ");
    scanf("%d", &atributo2);

    int resultado1 = compararAtributo(obterValorPorAtributo(cartas[0], atributo1),
                                      obterValorPorAtributo(cartas[1], atributo1),
                                      atributo1);

    int resultado2 = compararAtributo(obterValorPorAtributo(cartas[0], atributo2),
                                      obterValorPorAtributo(cartas[1], atributo2),
                                      atributo2);

    // Lógica de decisão final
    int vencedor = (resultado1 == resultado2) ? resultado1 :
                   (resultado1 == 0 || resultado2 == 0) ? (resultado1 + resultado2) :
                   (resultado1 == 1 && resultado2 == 1) ? 1 :
                   (resultado1 == 2 && resultado2 == 2) ? 2 : 0;

    exibirResultado(vencedor, cartas[0], cartas[1], atributo1, atributo2);

    return 0;
}
