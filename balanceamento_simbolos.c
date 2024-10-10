#include <stdio.h>
#include <stdlib.h>

typedef struct Pilha{
    char simbolo;
    struct Pilha *prox;
} pilha;

int verificar_compatibilidade(pilha *p, char simbolo);
void inserir(pilha **topo, char simbolo);
int remover_topo(pilha **topo);
int verificar_tipo(char simbolo);
void verificar_balanceamento(char *vetor_simbolos, pilha *p);

int main() {
    pilha *p = NULL;

    char vetor_simbolos[100];
    printf("Digite os simbolos: ");
    fgets(vetor_simbolos, sizeof(vetor_simbolos), stdin);

    verificar_balanceamento(vetor_simbolos, p);

    return 0;
}

void inserir(pilha **topo, char simbolo) {
    pilha* novo = (pilha*) malloc(sizeof(pilha));

    if (novo != NULL) {
        novo->simbolo = simbolo;
        novo->prox = *topo;
        *topo = novo;
    } else {
        printf("Deu ruim , memoria cheia.\n");
    }
}

int remover_topo(pilha **topo) {
    if (*topo == NULL) {
        return -1; 
    }

    pilha* aux = *topo;
    int valor = (*topo)->simbolo;
    *topo = (*topo)->prox;
    free(aux);
    return valor;
}

int verificar_tipo(char simbolo) {
    if (simbolo == '(' || simbolo == '{' || simbolo == '[') {
        return 1;
    }
    if (simbolo == ')' || simbolo == '}' || simbolo == ']') {
        return 2;
    }
    return 0;
}

int verificar_compatibilidade(pilha *p, char simbolo) {
    if (simbolo == '}') {
    	simbolo = '{';
	}
    if (simbolo == ']'){
    	simbolo = '[';
	} 
    if (simbolo == ')'){
    	simbolo = '(';
	} 

    if (p != NULL && p->simbolo == simbolo) {
        return 1;
    } else {
        return 0;
    }
}

void verificar_balanceamento(char *vetor_simbolos, pilha *p) {
    int i = 0;

    while (vetor_simbolos[i] != '\0') {
        if (verificar_tipo(vetor_simbolos[i]) == 1) {
            inserir(&p, vetor_simbolos[i]);
        }

        if (verificar_tipo(vetor_simbolos[i]) == 2) {
            if (verificar_compatibilidade(p, vetor_simbolos[i]) == 1) {
                remover_topo(&p);
            } else {
                printf("A expressao esta desbalanceada.\n");
                system('pause');
                return;
            }
        }
        i++;
    }

    if (p == NULL) {
        printf("A expressao esta balanceada.\n");
        system('pause');
    } else {
        printf("A expressao esta desbalanceada.\n");
        system('pause');
    }
}
