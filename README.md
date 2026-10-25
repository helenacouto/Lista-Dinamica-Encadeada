# Lista de exercícios: Lista dinâmica encadeada

Resolução da lista de exercícios da **Aula 06** da disciplina **Estrutura de Dados**
(Departamento de Informática, UFPB), sobre a lista dinâmica encadeada, em C.

## Sobre a atividade

Uma atividade da disciplina é uma **lista de exercícios** construída sobre uma biblioteca
que o professor apresenta em aula. Em vez de escrever um programa do zero, o trabalho é
**estender a biblioteca**: cada questão pede uma nova função, e todas seguem as mesmas regras.

1. A função é escrita dentro do arquivo `.c` da biblioteca.
2. O protótipo é acrescentado ao arquivo `.h`.
3. A função é testada a partir do `main.c`.

Na lista dinâmica encadeada, cada elemento é um nó alocado com `malloc`, que guarda os
dados e o endereço do próximo nó, e o último aponta para `NULL`. As funções precisam ficar
dentro do `.c` porque o tipo da lista é **opaco**: a `struct elemento` só existe no `.c`, e
por isso nenhuma função que percorre os nós (usando `dados` e `prox`) compila fora dele.

### Questões

| Questão | Função | O que faz |
|---|---|---|
| 1 | `conta_tarefas_prioridade` | Conta quantas tarefas têm uma determinada prioridade |
| 2 | `tarefa_mais_urgente` | Copia para `*t` a tarefa de menor valor de prioridade, ou seja, a mais urgente |
| 3 | `busca_tarefa_desc` | Busca a primeira tarefa cuja descrição contém um trecho de texto e a copia para `*t` |
| 4 | `insere_tarefa_final_prioridade` | Insere a nova tarefa logo depois da última com a mesma prioridade, ou no final se não houver nenhuma |
| 5 | `remove_tarefas_prioridade` | Remove todas as tarefas de uma prioridade e devolve quantas foram removidas |
| 6 | `inverte_lista` | Inverte a ordem da lista religando os ponteiros, sem alocar nem liberar nós |
| 7 | `remove_tarefa_pos` | Remove a tarefa de uma posição, contada a partir de 1 |
| 8 | `mescla_tarefas` | Anexa a lista de origem ao final da de destino religando ponteiros, deixa a origem vazia e devolve quantas tarefas foram transferidas |

## Biblioteca base

A biblioteca de partida é do **Prof. Daniel Faustino Lacerda de Souza** e vem da pasta
`02-lista-encadeadas-dinamicas` do repositório da disciplina:
[github.com/Ensino-UFPB/exemplosed1](https://github.com/Ensino-UFPB/exemplosed1).

Ela traz criação e destruição da lista, inserção (início, final e ordenada), remoção
(início, final e por código) e busca (por posição e por código).

**Adaptação:** os exercícios trabalham com tarefas, então a biblioteca foi ajustada ao
vocabulário da atividade. A estrutura do código e os comentários do professor foram
mantidos, com apenas estas mudanças:

| Original | Neste repositório |
|---|---|
| `struct aluno` (`matricula`, `nome`, `n1`, `n2`, `n3`) | `struct tarefa` (`codigo`, `descricao`, `prioridade`) |
| tipo `Lista` | tipo `ListaTarefas` |
| `insere_lista_inicio`, `insere_lista_final`, `insere_lista_ordenada` | `insere_tarefa_inicio`, `insere_tarefa_final`, `insere_tarefa_ordenada` |
| `remove_lista_inicio`, `remove_lista_final`, `remove_lista` | `remove_tarefa_inicio`, `remove_tarefa_final`, `remove_tarefa` |
| `busca_lista_pos`, `busca_lista_mat` | `busca_tarefa_pos`, `busca_tarefa_cod` |
| inserção ordenada por `matricula` | inserção ordenada por `prioridade`, em ordem crescente |
| arquivos `ListaDinEncad.h` e `ListaDinEncad.c` | `ListaDinEncadeada.h` e `ListaDinEncadeada.c` |

As funções `cria_lista`, `libera_lista`, `tamanho_lista`, `lista_cheia` e `lista_vazia`
mantêm os nomes originais.

O que foi acrescentado por mim está marcado nos arquivos:

- no `.h`, pela seção `ATIVIDADE`;
- no `.c`, pelos comentários `QUESTÃO N`, no final do arquivo.

## Organização do repositório

```
.
├── ListaDinEncadeada.h     interface: tipo opaco e protótipos (base do professor + atividade)
├── ListaDinEncadeada.c     implementação: base do professor + funções das questões
├── main.c                  programa de testes das questões
├── Makefile                compilação separada dos módulos
└── README.md
```

## Como compilar e executar

```bash
make        # gera o executável ./teste
./teste     # executa os testes
make clean  # remove os .o e o executável
```

Sem o `make`, a compilação manual é:

```bash
gcc -Wall -Wextra -std=c11 -o teste ListaDinEncadeada.c main.c
```

O único requisito é um compilador C com suporte a C11 (`gcc` ou `clang`). Para procurar
vazamentos de memória nas funções que alocam ou liberam nós:

```bash
valgrind --leak-check=full ./teste
```

## Como os testes funcionam

O `main.c` tem um bloco por questão. Cada bloco monta uma lista, imprime o estado dela
antes e depois da operação, no formato `inicio -> [1:p2] -> [3:p1] -> NULL` (em cada nó,
`código:prioridade`), e confere casos de borda (lista vazia, `NULL`, elemento único,
primeiro e último). Ao lado de cada resultado aparece o valor esperado, para a conferência
ser imediata.

O `main.c` usa apenas o que está declarado no `.h`: em nenhum ponto ele acessa os campos
`dados` ou `prox`.

## Convenções

- **Tipo opaco:** a `struct elemento` é definida apenas no `.c`.
- **Compilação limpa:** o código compila com `gcc -Wall -Wextra -std=c11` sem avisos.
- **Retorno:** inserção e remoção devolvem `1` em caso de sucesso e `0` caso contrário.
  `tamanho_lista`, `lista_cheia` e `lista_vazia` devolvem `-1` quando o ponteiro da lista
  é `NULL`.
- **Comentários sem acentuação** nos arquivos `.c` e `.h` da biblioteca base, para evitar
  problemas de codificação em editores com outra página de código. Os arquivos
  `README.md` usam acentuação normal.
- **Nomes em português**, iguais aos dos slides e das listas de exercícios.

## Referências

- BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*. Rio de Janeiro: LTC, 2023.
- TENENBAUM, A. M.; LANGSAM, Y.; AUGENSTEIN, M. J. *Estruturas de dados usando C*. São Paulo: Makron Books, 1995.
- CORMEN, T. H. et al. *Algoritmos: teoria e prática*. 3. ed. Rio de Janeiro: Elsevier, 2012.

## Autoria

Atividade resolvida por Helena Couto, estudante de Ciência de Dados e Inteligência
Artificial na UFPB. A biblioteca base e o enunciado da lista são do Prof. Daniel Faustino
Lacerda de Souza.