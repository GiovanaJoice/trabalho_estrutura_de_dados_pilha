# 🎮 KIZZ - Quiz Interativo em C

## 📝 Descrição

**KIZZ** é um **jogo de quiz em C** para testar conhecimentos em diferentes áreas:  

- 🖥️ **Estrutura de Dados**  
- 🌍 **Conhecimentos Gerais**  
- 🧬 **Biologia**  

Você também pode **criar seu próprio quiz**!  
O jogo utiliza uma **pilha encadeada (LIFO)** e dá **3 vidas** para acertar as perguntas. Se errar todas, é **Game Over**.  

---

## 🌟 Funcionalidades

- 📋 **Menu interativo** com quizzes prontos  
- ✏️ **Criador de quizzes customizados**  
- ❤️ **3 vidas**, com contagem visual de erros  
- 🎨 **Sistema de cores** para perguntas, acertos e erros  
- 🔢 **Contador de perguntas respondidas**  
- 🧹 **Limpeza de tela** entre perguntas para melhor visualização  

---

## 🧩 Estrutura do Código

### 📦 Card
Representa cada pergunta do quiz:

- **Pergunta** (`perg`): Armazena o texto da pergunta  
- **Alternativas** (`alt[4]`): Armazena as 4 opções de resposta  
- **Resposta correta** (`resp`): Guarda a letra da alternativa correta ('a', 'b', 'c' ou 'd')  
- **Próximo elemento da pilha** (`next`): Ponteiro para a próxima pergunta (LIFO)

---

### 📦 Quiz
Representa a pilha de perguntas:

- **Topo da pilha** (`top`): Ponteiro para a pergunta no topo da pilha  
- **Tamanho da pilha** (`size`): Número de perguntas atualmente na pilha  

---

### 🔹 Funções Principais

| Função | Descrição |
|--------|-----------|
| `createQuiz()` | Inicializa a pilha e configura tamanho inicial |
| `push()` | Adiciona uma nova pergunta ao topo da pilha |
| `pop()` | Remove a pergunta do topo da pilha e retorna a resposta correta |
| `peek()` | Exibe a pergunta atual, verifica a resposta do usuário e atualiza erros/acertos |
| `destroyQuiz()` | Libera toda a memória alocada para a pilha |
| `menu()` | Mostra o menu principal do jogo e lê a opção do usuário |

