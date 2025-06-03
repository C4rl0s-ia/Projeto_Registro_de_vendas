#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VENDAS_DIA 100
#define DIAS_MES 30
#define MESES_ANO 12
#define PRECO_POR_KG 40

typedef enum {
	REFEICAO, QUENTINHA, BEBIDA_ISOLADA
} TipoVenda;

typedef struct {
	int quantidade_de_bebida; // Apenas quando houve bebida
	float preco_bebida;      // Apenas quando houve bebida
} Bebidas;

typedef struct {
	TipoVenda tipo_da_venda;
	float peso; // em caso de REFEICAO
	Bebidas bebida;
} Venda;

typedef struct {
	Venda vendas_dia[MAX_VENDAS_DIA];
	int quantidade_vendas_dia;
	float valor_total_vendas_dia;
} Dia;

typedef struct {
	Dia dias_mes[DIAS_MES];
	float total_valor_vendas_mes;
} Mes;

typedef struct {
	Mes total_vendas_ano[MESES_ANO];
	float total_valor_vendas_ano;
} Ano;

// Funções
void registrar_venda(Dia* dia, Venda v);
void calcular_valor_diario(Dia* dia);

// Código principal 
int main(void) {

	Dia dia = { 0 }; // inicializa tudo com 0
	Venda v[] = {
		{ REFEICAO, 0.8f, {1, 5.0f} },
		{ REFEICAO, 0.8f, {1, 5.0f} },
		{ REFEICAO, 0.8f, {1, 5.0f} },
		{ REFEICAO, 0.8f, {1, 5.0f} },
		{ REFEICAO, 0.8f, {1, 5.0f} },
		{ REFEICAO, 0.8f, {1, 5.0f} },
		{ REFEICAO, 0.8f, {1, 5.0f} },
		{ REFEICAO, 0.8f, {1, 5.0f} }
	};
	
	for (int i = 0; i < 10; i++) {
		registrar_venda(&dia, v[i]);
	}

	calcular_valor_diario(&dia);

	printf("O valor total de vendas do dia 1 foi de: R$ %0.2f", dia.valor_total_vendas_dia);

	return 0;
}

// Funções
void registrar_venda(Dia* dia, Venda v) {
	if (dia->quantidade_vendas_dia < MAX_VENDAS_DIA) {
		dia->vendas_dia[dia->quantidade_vendas_dia++] = v;
	}
}

void calcular_valor_diario(Dia* dia) {
	dia->valor_total_vendas_dia = 0.0;
	for (int i = 0; i < dia->quantidade_vendas_dia; i++) {
		Venda v = dia->vendas_dia[i];
		float valor_total_dia = 0.0;

		if (v.tipo_da_venda == REFEICAO) {
			valor_total_dia = v.peso * PRECO_POR_KG;
			if (v.bebida.quantidade_de_bebida > 0) {
				valor_total_dia += v.bebida.quantidade_de_bebida * v.bebida.preco_bebida;
			}
		}
		else if (v.tipo_da_venda == QUENTINHA) {
			valor_total_dia = 20 + 0.5; // preço fixo + valor da embalagem.
			if (v.bebida.quantidade_de_bebida > 0) {
				valor_total_dia += v.bebida.quantidade_de_bebida * v.bebida.preco_bebida;
			}
		}
		else if (v.tipo_da_venda == BEBIDA_ISOLADA) {
			valor_total_dia = v.bebida.quantidade_de_bebida * v.bebida.preco_bebida;
		}

		dia->valor_total_vendas_dia += valor_total_dia;
	}

}