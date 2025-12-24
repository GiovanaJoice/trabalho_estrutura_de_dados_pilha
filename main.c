#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

#define RESET   "\033[0m"
#define VERDE   "\033[32m"
#define VERMELHO "\033[31m"
#define AZUL    "\033[34m"
#define ROSA    "\033[95m"
#define ROXO "\033[35m"

int erro=0;
int count=0;

/*Struct da pilha encadeada */
typedef struct Card {
    char perg[100]; //Pergunta
    char alt[4][100]; //Alternativas
    char resp; // Resposta da pergunta
    struct Card *next;   // Ponteiro para o proximo no
} Card;

/* Estrutura para representar a pilha */
typedef struct {
    Card *top;   // Ponteiro para o topo da pilha
    int size;    // Para controlar o tamanho atual da pilha
} Quiz;

/* Verifica se a pilha esta vazia */
bool isEmpty(Quiz *s) {
    return s->top == NULL;
}

/* Envia o tamanho da pilha, quant de perguntas */
int QuizSize(Quiz *s) {
    return s->size;
}

/* Cria a pilha (inicializa o topo) */
void createQuiz(Quiz *s) {
    s->top = NULL;
    s->size = 0;
    // printf("Quiz criado.\n"); // Comentei pra limpar o visual
}

/* Coloca de um elemento na pilha (Push) */
void push(Quiz *s, char* perg, char* altA, char* altB, char* altC,char* altD,char* resp) {
    Card *newCard = (Card *) malloc(sizeof(Card));
    if (newCard == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    strcpy(newCard->perg,perg);
    strcpy(newCard->alt[0],altA);
    strcpy(newCard->alt[1],altB);
    strcpy(newCard->alt[2],altC);
    strcpy(newCard->alt[3],altD);
    newCard->resp=*resp;

    newCard->next = s->top;      
    s->top = newCard;            
    s->size++;                    
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* Remover um elemento da pilha (Pop) */
char pop(Quiz *s) {
    if (isEmpty(s)) {
        printf("Erro: Pilha vazia! Nao ha elementos para remover.\n");
        return -1;
    }

    Card *temp = s->top;          
    int poppedValue = temp->resp;
    s->top = s->top->next;        
    free(temp);                  
    s->size--;                    
   
    return poppedValue;
}

/* Apaga a pilha (libera toda a memoria alocada) */
void destroyQuiz(Quiz *s) {
    Card *current = s->top;
    Card *next;

    while (current != NULL) {
        next = current->next;  
        free(current);        
        current = next;
    }

    s->size = 0;  
    s->top = NULL;
    erro=0;
    count=0;
    // printf("Quiz destruido (memoria liberada).\n"); // Comentei pra limpar o visual
}

/* MODIFICADO: Agora retorna true se acertou, ou false se atingiu o limite de erros */
bool peek(Quiz *s) {
    printf(AZUL "\n*================================*\n" RESET);
    printf(" Pergunta %d \n", count + 1);
    printf(AZUL "*================================*\n" RESET);

    printf("%s\n\n", s->top->perg);

    printf(" a) %s\n", s->top->alt[0]);
    printf(" b) %s\n", s->top->alt[1]);
    printf(" c) %s\n", s->top->alt[2]);
    printf(" d) %s\n", s->top->alt[3]);

    // limitando os erros do usuario
    if (erro >= 3) {
        printf(VERMELHO "\n💀 GAME OVER 💀\n" RESET);
        printf("\n\n VOCE ATINGIU 3 ERROS !\n");
        printf("FIM DE JOGO - De volta ao menu!\n\n");
    sleep(2);
        return false; // Retorna falso para avisar a main que o jogo acabou
    }
    while(true){
    char resposta;
    printf("\nR: ");
    scanf(" %c",&resposta);
        if(resposta!='a'&& resposta!='b'&&resposta!='c'&&resposta!='d'){
           printf("Opcao Invalida\n");
        }
        else{
        if (resposta == s->top->resp){
            printf(VERDE "\nCerta resposta! ^^ \n" RESET);
            count++;
            return true; // Acertou pode continuar
        }
        else{
            erro++;
            printf("Poxa vida... você errou T_T \n");
            printf(VERMELHO "Vidas restantes: ");
            for(int i = 0; i < 3 - erro; i++) printf("❤ ");
            printf("\n" RESET);
        }
        }
    }
}

int menu() {
    int op;
    printf(ROXO "\n****======****======****======****\n" RESET);
    printf(ROSA   "        BEM VINDO AO KIZZ 🎮\n" RESET);
    printf(ROXO "====******====******====******====\n" RESET);
    printf(" 1 - Quiz sobre Estrutura de Dados\n");
    printf(" 2 - Quiz sobre Conhecimentos Gerais\n");
    printf(" 3 - Quiz sobre Biologia:\n");
    printf(" 4 - Criar Quiz\n");
    printf(" 5 - Sair\n");
    printf(ROXO "****======****======****======****\n" RESET);
    printf("Escolha uma opcao: ");
    scanf(" %d", &op);

    return op;
}

/* Exemplo de uso */
int main() {
    setlocale(LC_ALL, "Portuguese");
   
    while(true){
        Quiz s;
        createQuiz(&s);

        switch (menu()) {
   
            case 1:
                printf("\nQuiz sobre Estrutura de Dados:\n");
   
                push(&s, "O que e uma pilha?", "Lista", "LIFO", "FIFO", "Heap", "b");
                push(&s, "O que significa FIFO?", "Ultimo a entrar, primeiro a sair", "Primeiro a entrar, primeiro a sair", "Fila invertida", "Nenhuma", "b");
                push(&s, "Qual e a estrutura de dados de uma fila?", "LIFO", "Arvore", "Heap", "FIFO", "d");
                push(&s, "Qual estrutura de dados possui Big-O igual a O(1) nas funcoes InserirNoFinal e RemoverNoFinal?", "Lista Encadeada", "Fila", "Lista Duplamente Encadeada", "Arvore binaria", "c");
                push(&s, "Qual operacao NAO pertence ao comportamento tipico de uma pilha?", "Push", "Pop", "Peek/top", "Enqueue", "d");
                push(&s, "Nome da estrutura de dados mais recomendada para representar uma playlist musical com loop:", "Lista duplamente encadeada circular", "Pilha", "Lista encadeada", "Lista circular encadeada", "a");
                push(&s, "O que acontece se voce nao inicializar um ponteiro em C?", " Ele aponta automaticamente para NULL", "Ele causa erro de compilacao", "Ele e convertido para inteiro", "Ele contem um valor lixo de memoria", "d");
                push(&s, "O que é a raiz de uma árvore?", "O último nó da arvore", "O nó principal de onde a árvore começa", "Qualquer nó sem filhos", "A parte que fica embaixo da terra absorvendo agua e minerais", "b");
                push(&s, "Qual a complexidade de tempo das operacoes Push (inserir) e Pop (remover) em uma pilha?", "O(n)", "O(log n)", "O(1) - Tempo Constante", "O(n^2)", "c");
                push(&s, "Na pilha estatica (array), como os elementos sao armazenados na memoria?", "De forma aleatoria", "Em lista encadeada", "De forma consecutiva/sequencial", "Em arvore binaria", "c");
                break;
   
            case 2:
                printf("\nQuiz sobre conhecimentos gerais:\n");
   
                push(&s, "Capital da Franca?", "Roma", "Berlim", "Paris", "Lisboa", "c");
                push(&s, "Quem pintou a Mona Lisa?", "Van Gogh", "Da Vinci", "Picasso", "Michelangelo", "b");
                push(&s, "Maior oceano do mundo?", "Atlantico", "Indico", "Pacifico", "Artico", "c");
                push(&s, "Nome do represente mais famoso da Inconfidencia Mineira, conhecido como Tiradentes?", "Deodoro da Fonseca", "Luis Inacio da Lula Silva", "Ari de Sa", "Joaquim Jose da Silva Xavier", "d");
                push(&s, "Principal genero musical da cantora Madonna?", "Pop", "Rock", "Country", "Jazz", "a");
                push(&s, "De onde e a invencao do chuveiro eletrico?", "Franca", "Inglaterra", "Australia", "Brasil", "d");
                push(&s, "O que a palavra 'legend' significa em portugues?", "Legenda", "Conto", "Lendario", "Lenda", "d");
                push(&s, "Qual o menor pais do mundo?", "Monaco", "Vaticano", "Malta", "Nauru", "b");
                push(&s, "Qual e a unica das Sete Maravilhas do Mundo Antigo que ainda existe?", "Jardins Suspensos da Babilonia", "Estatua de Zeus", "Farol de Alexandria", "Piramides de Gize", "d");
                push(&s, "Quem e creditado pela invencao da lampada eletrica comercial?", "Nikola Tesla", "Thomas Edison", "Benjamin Franklin", "Alexander Graham Bell", "b");
                break;
               
            case 3:
                printf("\nQuiz sobre Biologia:\n");
   
                push(&s, "Qual organela e responsavel pela producao de energia (ATP)?", "Ribossomo", "Lisossomo", "Mitocondria", "Complexo de Golgi", "c");
                push(&s, "Quem e considerado o pai da genetica?", "Charles Darwin", "Gregor Mendel", "Louis Pasteur", "Lamarck", "b");
                push(&s, "Qual o principal pigmento responsavel pela fotossintese?", "Hemoglobina", "Melanina", "Clorofila", "Caroteno", "c");
                push(&s, "Quantos pares de cromossomos tem um ser humano saudavel?", "23", "46", "22", "44", "a");
                push(&s, "Qual dessas doencas e causada por um virus?", "Gripe", "Tuberculose", "Colera", "Sifilis", "a");
                push(&s, "Como se chama o processo de divisao celular que gera gametas?", "Mitose", "Meiose", "Fisao binaria", "Osmose", "b");
                push(&s, "Qual o maior orgao do corpo humano?", "Figado", "Cerebro", "Intestino", "Pele", "d");
                push(&s, "Qual base nitrogenada e exclusiva do RNA (nao existe no DNA)?", "Adenina", "Uracila", "Guanina", "Timina", "b");
                push(&s, "O que caracteriza um animal homeotermico?", "Mantem temperatura constante", "Muda de cor", "Nao possui ossos", "Vive na agua e terra", "a");
                push(&s, "Qual reino engloba as bacterias?", "Fungi", "Protista", "Monera", "Plantae", "c");
                break;
   
            case 4:
                printf("\nCriador de Quiz:\n");
               
                while(true){
                    char perg[100], altA[100], altB[100], altC[100], altD[100], resp;
   
                    printf("Digite a pergunta: ");
                    scanf(" %[^\n]", perg);  
                   
                    printf("Alternativa a: ");
                    scanf(" %[^\n]", altA);
                   
                    printf("Alternativa b: ");
                    scanf(" %[^\n]", altB);
                   
                    printf("Alternativa c: ");
                    scanf(" %[^\n]", altC);
                   
                    printf("Alternativa d: ");
                    scanf(" %[^\n]", altD);
                   
                    while(true){
                    printf("Resposta correta (a/b/c/d): ");
                    scanf(" %c", &resp);
                   
                    if(resp=='a'|| resp=='b'||resp=='c'||resp=='d'){
                        break;
                    }
                       printf("Alternativa Invalida\n");
                    }
                    push(&s, perg, altA, altB, altC, altD, &resp);
                   
                    char temp;
                    printf("Deseja adicionar mais uma pergunta[S\\N?]\nR:");
                    scanf(" %c", &temp);
                    if(temp!='s' &&  temp!='S'){break;}
                }
                   
                printf("\nRodando quiz criado...\n");
                break;
   
            case 5:
                printf("Saindo...\n");
                destroyQuiz(&s);
                return 0;
   
            default:
                printf("Opcao invalida!\n");
                return 0;
        }
   
        //
        bool perdeu = false;
        while(QuizSize(&s)!=0){
           
            // peek fica FALSE se voce perder
            bool resultado = peek(&s);
           
            if (resultado == false) {
                perdeu = true;
                break; // Sai do while e vai destruir o quiz
            }

            // Se acertou, mostra a resposta e tira da pilha
            pop(&s);
            printf("\nPressione ENTER para a proxima pergunta...");
            getchar();
            getchar();
           
            limparTela();
        }
       
        if (!perdeu) {
            printf(VERDE "\n PARABENS!!! :D \n" RESET);
            printf("Voce completou o quiz!\n");
            printf("Total de erros: %d\n", erro);
   sleep(2);
        }
        destroyQuiz(&s); // Limpa tudo para recomeçar o menu

    }
    return 0;

}