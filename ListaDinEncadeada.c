#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncadeada.h"

struct elemento {
    struct tarefa dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

ListaTarefas* cria_lista(void){
    ListaTarefas* li = (ListaTarefas*) malloc(sizeof(ListaTarefas));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(ListaTarefas* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(ListaTarefas* li){
    if(li == NULL)
        return -1;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(ListaTarefas* li){
    if(li == NULL)
        return -1;
    return 0;
}

int lista_vazia(ListaTarefas* li){
    if(li == NULL)
        return -1;
    if(*li == NULL)
        return 1;
    return 0;
}

int insere_tarefa_inicio(ListaTarefas* li, struct tarefa t){
    if(li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = t;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_tarefa_final(ListaTarefas* li, struct tarefa t){
    if(li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = t;
    no->prox = NULL;
    if((*li) == NULL){
        *li = no;
    }else{
        Elem* aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_tarefa_ordenada(ListaTarefas* li, struct tarefa t){
    if(li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = t;
    if((*li) == NULL){
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elem *ant = NULL, *atual = *li;
        while(atual != NULL &&
              atual->dados.prioridade < t.prioridade){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){ 
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_tarefa_inicio(ListaTarefas* li){
    if(li == NULL) return 0;
    if((*li) == NULL)
        return 0;
    Elem *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_tarefa_final(ListaTarefas* li){
    if(li == NULL) return 0;
    if((*li) == NULL)
        return 0;
    Elem *ant = NULL, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }
    if(no == (*li))
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_tarefa(ListaTarefas* li, int codigo){
    if(li == NULL) return 0;
    if((*li) == NULL) /* lista vazia */
        return 0;
    Elem *ant = NULL, *no = *li;
    while(no != NULL && no->dados.codigo != codigo){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    if(no == *li)
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int busca_tarefa_pos(ListaTarefas* li, int pos, struct tarefa *t){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *t = no->dados;
        return 1;
    }
}

int busca_tarefa_cod(ListaTarefas* li, int codigo, struct tarefa *t){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.codigo != codigo){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *t = no->dados;
        return 1;
    }
}



/* Q1 */
int conta_tarefas_prioridade(ListaTarefas* li, int prioridade){
    if (li == NULL) return -1;
    
    Elem *no = *li;
    int cont = 0;
    while (no != NULL) {
        if (no->dados.prioridade == prioridade) cont++;
        no = no->prox;
    }

    return cont;
}

/* Q2 */
int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t){
    if (li == NULL || *li == NULL) return 0;

    Elem *no = *li;

    int menor = no->dados.prioridade;
    *t = (no->dados);
    no = no->prox;

    while (no != NULL) {
        if (no->dados.prioridade < menor){
            menor = no->dados.prioridade;
            *t = (no->dados);
        }

        no = no->prox;
    }

    return 1;
}

/* Q3 */
int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t){
    if (li == NULL || *li == NULL) return 0;

    Elem *no = *li;
    while (no != NULL) {
        if (strstr(no->dados.descricao, texto) != NULL) {
            *t = no->dados;
            return 1;
        }
        no = no->prox;
    }

    return 0;
}

/* Q4 */
int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t){
    if (li == NULL) return 0;

    Elem* p = (Elem*) malloc(sizeof(Elem));
    if (p == NULL) return 0;
    p->dados = t;

    if (*li == NULL) {
        p->prox = NULL;
        *li = p;
        return 1;
    }

    Elem *no = *li, *ultimo = NULL, *fim = NULL;
    while (no != NULL) {
        if (no->dados.prioridade == t.prioridade)
            ultimo = no;
        fim = no;
        no = no->prox;
    }

    if (ultimo != NULL) {
        p->prox = ultimo->prox;
        ultimo->prox = p;
    } else {
        p->prox = NULL;
        fim->prox = p;
    }
    return 1;
}

/* Q5 */
int remove_tarefas_prioridade(ListaTarefas* li, int prioridade){
    if (li == NULL) return -1;

    if (*li == NULL) return 0;

    Elem* no = *li, *ant = NULL;
    int cont = 0;

    while (no != NULL) {
        if (no->dados.prioridade == prioridade) {
            if (no == *li) {
                *li = no->prox;
                free(no);
                no = *li;
                cont++;
            } else {
                ant->prox = no->prox;
                free(no);
                no = ant->prox;
                cont++;
            }            
        } else {
            ant = no;
            no = no->prox;
        }
    }

    return cont;
}

/* Q6 */
int inverte_lista(ListaTarefas* li){
    if (li == NULL) return 0;

    if (*li == NULL || (*li)->prox == NULL) return 1;

    Elem *no = (*li)->prox, *ant = *li, *suc = NULL;
    
    while (no != NULL) {
        suc = no->prox;
        no->prox = ant;
        ant = no;
        no = suc;
    }
    (*li)->prox = NULL;
    *li = ant;

    return 1;
}

/* Q7 */
int remove_tarefa_pos(ListaTarefas* li, int pos){
    if (li == NULL || *li == NULL || pos < 1 || pos > tamanho_lista(li))
        return 0;

    Elem* no = *li, *ant = NULL;

    if (pos == 1) {
        *li = no->prox;
        free(no);
        return 1;
    }

    ant = no;
    no = no->prox;
    int cont = 1;
    while (no != NULL) {
        cont++;
        if (cont == pos) {
            ant->prox = no->prox;
            free(no);
            return 1;
        }
        ant = no;
        no = no->prox;
    }

    return 0;
}

/* Q8*/
int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src){
    if (dst == NULL || src == NULL) return -1;
    if (dst == src) return 0;

    if (*dst == NULL) {
        *dst = *src;
    } else {
        Elem* no = *dst;
        while(no->prox != NULL) {
            no = no->prox;
        }

        no->prox = *src;
    }
    
    int n = tamanho_lista(src);
    *src = NULL;

    return n;
}
