#include <stdio.h>
#include <string.h>
#include "ListaDinEncadeada.h"

static struct tarefa mk(int codigo, const char *descricao, int prioridade) {
    struct tarefa t;
    t.codigo = codigo;
    snprintf(t.descricao, sizeof(t.descricao), "%s", descricao);
    t.prioridade = prioridade;
    return t;
}

/* Imprime a lista usando apenas a interface publica, com a notacao
   [codigo:prioridade]:  inicio -> [1:p2] -> [3:p1] -> NULL */
static void imprime(const char *rotulo, ListaTarefas *li) {
    int i, n = tamanho_lista(li);
    struct tarefa t;
    printf("  %-24s tam=%d: ", rotulo, n);
    if (n <= 0) {
        printf("(vazia)\n");
        return;
    }
    printf("inicio ->");
    for (i = 1; i <= n; i++) {
        busca_tarefa_pos(li, i, &t);
        printf(" [%d:p%d] ->", t.codigo, t.prioridade);
    }
    printf(" NULL\n");
}

/* Monta uma lista com as tarefas dadas, inserindo no final. */
static ListaTarefas* monta(const struct tarefa *v, int n) {
    ListaTarefas *li = cria_lista();
    for (int i = 0; i < n; i++)
        insere_tarefa_final(li, v[i]);
    return li;
}

static void titulo(const char *t) {
    printf("\n%s\n", t);
}

int main(void) {
    /* lista usada na maioria dos testes: prioridades 2, 3, 1, 3 */
    struct tarefa base[] = {
        {1, "Estudar ED1",   2},
        {2, "Comprar leite", 3},
        {3, "Pagar conta",   1},
        {4, "Lavar roupa",   3}
    };
    ListaTarefas *li, *outra;

    /* ---------- Questao 1 ---------- */
    titulo("Q1 - conta_tarefas_prioridade");
    {
        li = monta(base, 4);
        imprime("lista", li);
        printf("  prioridade 3: %d (esperado 2)\n", conta_tarefas_prioridade(li, 3));
        printf("  prioridade 1: %d (esperado 1)\n", conta_tarefas_prioridade(li, 1));
        printf("  prioridade 9: %d (esperado 0)\n", conta_tarefas_prioridade(li, 9));
        libera_lista(li);

        li = cria_lista();
        printf("  lista vazia:  %d (esperado 0)\n", conta_tarefas_prioridade(li, 3));
        libera_lista(li);
        printf("  NULL:         %d (esperado -1)\n", conta_tarefas_prioridade(NULL, 3));
    }

    /* ---------- Questao 2 ---------- */
    titulo("Q2 - tarefa_mais_urgente (menor valor de prioridade)");
    {
        struct tarefa u;
        int r;
        li = monta(base, 4);
        imprime("lista", li);
        r = tarefa_mais_urgente(li, &u);
        printf("  devolve %d, cod=%d prioridade=%d (esperado 1, 3 e 1)\n",
               r, u.codigo, u.prioridade);
        libera_lista(li);

        li = cria_lista();
        printf("  lista vazia: %d (esperado 0)\n", tarefa_mais_urgente(li, &u));
        libera_lista(li);
        printf("  NULL:        %d (esperado 0)\n", tarefa_mais_urgente(NULL, &u));
    }

    /* ---------- Questao 3 ---------- */
    titulo("Q3 - busca_tarefa_desc (trecho da descricao)");
    {
        struct tarefa achada;
        li = monta(base, 4);
        if (busca_tarefa_desc(li, "leite", &achada))
            printf("  \"leite\"  -> cod=%d (esperado 2)\n", achada.codigo);
        if (busca_tarefa_desc(li, "roupa", &achada))
            printf("  \"roupa\"  -> cod=%d (esperado 4)\n", achada.codigo);
        if (busca_tarefa_desc(li, "Estudar ED1", &achada))
            printf("  inteira  -> cod=%d (esperado 1)\n", achada.codigo);
        printf("  \"xyz\"    -> %d (esperado 0)\n", busca_tarefa_desc(li, "xyz", &achada));
        libera_lista(li);

        li = cria_lista();
        printf("  lista vazia -> %d (esperado 0)\n", busca_tarefa_desc(li, "leite", &achada));
        libera_lista(li);
    }

    /* ---------- Questao 4 ---------- */
    titulo("Q4 - insere_tarefa_final_prioridade");
    {
        li = monta(base, 4);
        imprime("antes", li);
        insere_tarefa_final_prioridade(li, mk(5, "Ler artigo", 2));
        imprime("p2: apos a ultima p2", li);
        insere_tarefa_final_prioridade(li, mk(6, "Fazer cafe", 3));
        imprime("p3: apos a ultima p3", li);
        insere_tarefa_final_prioridade(li, mk(7, "Arrumar mesa", 9));
        imprime("p9: sem igual, final", li);
        libera_lista(li);

        li = cria_lista();
        insere_tarefa_final_prioridade(li, mk(8, "Primeira", 5));
        imprime("lista vazia", li);
        libera_lista(li);
    }

    /* ---------- Questao 5 ---------- */
    titulo("Q5 - remove_tarefas_prioridade");
    {
        struct tarefa v[] = {
            {1, "A", 3}, {2, "B", 3}, {3, "C", 1}, {4, "D", 3}, {5, "E", 2}, {6, "F", 3}
        };
        struct tarefa iguais[] = { {1, "A", 3}, {2, "B", 3} };
        int r;

        li = monta(base, 4);
        imprime("antes", li);
        r = remove_tarefas_prioridade(li, 3);
        printf("  prioridade 3: removeu %d (esperado 2)\n", r);
        imprime("depois", li);
        libera_lista(li);

        li = monta(v, 6);
        imprime("inicio e final iguais", li);
        r = remove_tarefas_prioridade(li, 3);
        printf("  prioridade 3: removeu %d (esperado 4)\n", r);
        imprime("depois", li);
        libera_lista(li);

        li = monta(iguais, 2);
        r = remove_tarefas_prioridade(li, 3);
        printf("  todas iguais: removeu %d (esperado 2)\n", r);
        imprime("depois", li);
        libera_lista(li);

        li = monta(base, 4);
        printf("  nenhuma p9: removeu %d (esperado 0)\n", remove_tarefas_prioridade(li, 9));
        libera_lista(li);
        printf("  NULL: %d (esperado -1)\n", remove_tarefas_prioridade(NULL, 3));
    }

    /* ---------- Questao 6 ---------- */
    titulo("Q6 - inverte_lista");
    {
        struct tarefa uma[] = { {9, "Unica", 1} };
        li = monta(base, 4);
        imprime("antes", li);
        printf("  devolve %d (esperado 1)\n", inverte_lista(li));
        imprime("depois", li);
        libera_lista(li);

        li = monta(uma, 1);
        inverte_lista(li);
        imprime("um elemento", li);
        libera_lista(li);

        li = cria_lista();
        printf("  lista vazia: %d (esperado 1)\n", inverte_lista(li));
        libera_lista(li);
        printf("  NULL:        %d (esperado 0)\n", inverte_lista(NULL));
    }

    /* ---------- Questao 7 ---------- */
    titulo("Q7 - remove_tarefa_pos");
    {
        li = monta(base, 4);
        imprime("antes", li);
        remove_tarefa_pos(li, 2);
        imprime("pos 2 (meio)", li);
        remove_tarefa_pos(li, 3);
        imprime("pos 3 (ultima)", li);
        remove_tarefa_pos(li, 1);
        imprime("pos 1 (primeira)", li);
        printf("  pos 9 devolve %d (esperado 0)\n", remove_tarefa_pos(li, 9));
        printf("  pos 0 devolve %d (esperado 0)\n", remove_tarefa_pos(li, 0));
        remove_tarefa_pos(li, 1);
        imprime("pos 1 (unica)", li);
        printf("  lista vazia devolve %d (esperado 0)\n", remove_tarefa_pos(li, 1));
        libera_lista(li);
        printf("  NULL devolve %d (esperado 0)\n", remove_tarefa_pos(NULL, 1));
    }

    /* ---------- Questao 8 ---------- */
    titulo("Q8 - mescla_tarefas");
    {
        struct tarefa src[] = { {6, "Regar plantas", 4}, {7, "Ligar pra mae", 2} };
        int r;

        li = monta(base, 4);
        outra = monta(src, 2);
        imprime("dst antes", li);
        imprime("src antes", outra);
        r = mescla_tarefas(li, outra);
        printf("  transferiu %d (esperado 2)\n", r);
        imprime("dst depois", li);
        imprime("src depois", outra);
        insere_tarefa_final(outra, mk(10, "Nova", 1));
        imprime("src segue valida", outra);
        libera_lista(outra);
        libera_lista(li);

        li = cria_lista();
        outra = monta(src, 2);
        r = mescla_tarefas(li, outra);
        printf("  dst vazia: transferiu %d (esperado 2)\n", r);
        imprime("dst depois", li);
        libera_lista(outra);
        libera_lista(li);

        li = monta(base, 4);
        outra = cria_lista();
        r = mescla_tarefas(li, outra);
        printf("  src vazia: transferiu %d (esperado 0)\n", r);
        imprime("dst intacta", li);
        libera_lista(outra);

        printf("  mesma lista: %d (esperado 0)\n", mescla_tarefas(li, li));
        imprime("dst intacta", li);
        printf("  NULL: %d (esperado -1)\n", mescla_tarefas(li, NULL));
        libera_lista(li);
    }

    printf("\n");
    return 0;
}