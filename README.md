# Projeto LI2 - Puzzle Solver em C

Projeto da unidade curricular **Laboratórios de Informática II** (Licenciatura em Engenharia Informática, Universidade do Minho).

Aplicação interativa em C para jogar e resolver um puzzle lógico de grelha (do estilo *Hitori*). O tabuleiro é uma matriz de letras e o jogador decide, casa a casa, se a letra fica **pintada de branco** (maiúscula) ou **riscada** (`#`), respeitando as regras do jogo.

## Regras do puzzle

- Em cada linha e coluna, cada letra só pode aparecer uma vez pintada de branco.
- Uma casa riscada não pode ter outra casa riscada ao lado (na horizontal ou vertical).
- As casas vizinhas de uma casa riscada têm de estar pintadas de branco.
- As casas brancas têm de formar uma região conectada (nenhuma pode ficar isolada).

## Funcionalidades

- **Jogar manualmente**: pintar (`b`) ou riscar (`r`) qualquer casa indicando a coordenada (ex.: `b a1`, `r c3`).
- **Desfazer** (`d`): histórico completo de jogadas implementado com uma pilha, permitindo voltar atrás quantas vezes for preciso.
- **Verificar** (`v`): valida o tabuleiro atual e indica cada restrição violada, com linha e coluna.
- **Ajuda** (`a`): infere e aplica automaticamente todas as jogadas que decorrem do estado atual do tabuleiro.
- **Ajuda repetida** (`A`): aplica `a` em ciclo até o tabuleiro deixar de mudar.
- **Resolver** (`R`): resolve o puzzle automaticamente.
- **Guardar e carregar** (`g <ficheiro>`, `l <ficheiro>`): persistência do estado do jogo em ficheiro de texto.
- Gestão de memória dinâmica cuidada, com validação de input e libertação de recursos em todos os caminhos de erro.

## Compilar e executar

Requisitos: `gcc`, `make` e a biblioteca **CUnit** (para os testes).

```bash
# Compilar o jogo (com AddressSanitizer para detetar erros de memória)
make jogo

# Executar
./jogo

# Limpar, recompilar e executar de uma vez
make tudo
```

Ao iniciar, o programa pede as dimensões do tabuleiro (`L C`) seguidas das linhas, ou `l <ficheiro>` para carregar um jogo guardado.

### Formato do ficheiro de jogo

```
5 5
ecadc
dcdec
bddce
cdeeb
accbb
```

A primeira linha indica o número de linhas e colunas; as seguintes representam o tabuleiro.

## Comandos

| Comando | Descrição |
|---|---|
| `b <coord>` | Pintar de branco a casa (letra em maiúscula) |
| `r <coord>` | Riscar a casa (`#`) |
| `v` | Verificar as restrições do tabuleiro |
| `a` | Aplicar as jogadas que se podem inferir |
| `A` | Repetir `a` até não haver alterações |
| `R` | Resolver o jogo automaticamente |
| `d` | Desfazer o último comando |
| `g <ficheiro>` | Guardar o jogo |
| `l <ficheiro>` | Carregar um jogo |
| `s` | Sair |

As coordenadas usam uma letra para a linha e um número para a coluna (ex.: `a1` é o canto superior esquerdo).

## Testes

O projeto inclui uma suite de **14 testes unitários em CUnit**, que cobrem a leitura de coordenadas, guardar e carregar jogos, pintar e riscar casas, o histórico e o desfazer, a verificação de restrições, a inferência automática e a resolução completa.

```bash
# Correr os testes
make testar

# Correr os testes e gerar relatório de cobertura com gcov
make cobertura-testes
```

## Estrutura

```
.
├── main.c        # Ciclo principal e interpretação de comandos
├── funcoes.c     # Lógica do jogo: regras, histórico, ajuda e resolução
├── testes.c      # Testes unitários (CUnit)
├── Makefile      # Compilação, testes e cobertura
└── *.txt         # Tabuleiros de exemplo para testes
```

## Tecnologias

C · Makefile · CUnit · gcov · AddressSanitizer · Git

## Autores

- João Pedro Cunha Cerqueira
- Rafael Figueiras Esteves
- Nuno Henrique Dias Pereira
