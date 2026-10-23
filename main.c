#include <stdio.h>
#include "ListaDinEncadeada.h"

static void imprime_lista(ListaTarefas *li) {
    struct tarefa t;
    int n = tamanho_lista(li);

    printf("Lista com %d tarefa(s):\n", n);
    for (int i = 1; i <= n; i++) {
        busca_tarefa_pos(li, i, &t);
        printf("  [%d] cod=%-4d desc=%-15s prioridade=%d\n",
               i, t.codigo, t.descricao, t.prioridade);
    }
}

int main(void) {
    ListaTarefas *li = cria_lista();

    struct tarefa t1 = {1, "Estudar ED1",   2};
    struct tarefa t2 = {2, "Comprar leite", 3};
    struct tarefa t3 = {3, "Pagar conta",   1};
    struct tarefa t4 = {4, "Lavar roupa",   3};

    insere_tarefa_final(li, t1);
    insere_tarefa_final(li, t2);
    insere_tarefa_ordenada(li, t3);
    insere_tarefa_ordenada(li, t4);

    imprime_lista(li);

    printf("\ntamanho_lista: %d\n", tamanho_lista(li));
    printf("lista_vazia:   %d\n", lista_vazia(li));
    printf("lista_cheia:   %d\n", lista_cheia(li));


    /* Q1 */
    printf("\nQ1\n");
    printf("conta_tarefas_prioridade(li, 3): %d\n",
           conta_tarefas_prioridade(li, 3));

    /* Q2 */
    printf("\nQ2\n");
    struct tarefa urgente;
    if (tarefa_mais_urgente(li, &urgente) == 1)
        printf("tarefa_mais_urgente: cod=%d prioridade=%d\n",
               urgente.codigo, urgente.prioridade);

    /* Q3 */
    printf("\nQ3\n");
    struct tarefa encontrada;
    if (busca_tarefa_desc(li, "leite", &encontrada) == 1)
        printf("busca_tarefa_desc achou cod=%d\n", encontrada.codigo);

    /* Q4 */
    printf("\nQ4\n");
    struct tarefa t5 = {5, "Ler artigo", 2};
    insere_tarefa_final_prioridade(li, t5);
    imprime_lista(li);

    /* Q5 */
    printf("\nQ5\n");
    printf("remove_tarefas_prioridade(3): %d removidas\n",
           remove_tarefas_prioridade(li, 3));
    imprime_lista(li);

    /* Q6 */
    printf("\nQ6\n");
    inverte_lista(li);
    imprime_lista(li);

    /* Q7 */
    printf("\nQ7\n");
    printf("remove_tarefa_pos(1): %d\n", remove_tarefa_pos(li, 1));
    imprime_lista(li);

    /* Q8 */
    printf("\nQ8\n");
    ListaTarefas *outra = cria_lista();
    struct tarefa t6 = {6, "Regar plantas", 4};
    struct tarefa t7 = {7, "Ligar pra mae",  2};
    insere_tarefa_final(outra, t6);
    insere_tarefa_final(outra, t7);

    int transferidas = mescla_tarefas(li, outra);
    printf("mescla_tarefas transferiu %d tarefa(s)\n", transferidas);
    printf("\nsrc depois da mescla:\n");
    imprime_lista(outra);
    printf("\ndst depois da mescla:\n");
    imprime_lista(li);

    libera_lista(outra);
    libera_lista(li);
    return 0;
}