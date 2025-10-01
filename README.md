# c-digo_morse

🔡 Tradutor de Código Morse

Este projeto implementa um tradutor de código Morse em linguagem C.

O programa é capaz de:

    Traduzir mensagens em Morse para texto (A–Z e espaço).

    Detectar caracteres corrompidos (representados por *) e sugerir todas as possíveis letras que poderiam substituir o caractere corrompido.

    Exibir a tradução final no terminal, indicando letras corrompidas entre colchetes [] com suas possíveis alternativas.

📌 Funcionalidades

    ✅ Entrada de mensagem em código Morse pelo usuário.

    ✅ Conversão para caracteres alfabéticos (A–Z e espaço).

    ✅ Identificação de caracteres corrompidos (*).

    ✅ Sugestão de todas as letras possíveis para as posições corrompidas.

    ✅ Saída formatada no terminal.

🛠️ Estrutura do Código

    O programa é dividido em funções para melhor organização:

    separar → separa a entrada Morse em letras/palavras.

    encontrar_corrompido → localiza caracteres corrompidos (*) e salva seus índices.

    traducao → realiza a tradução do Morse para letras, além de gerar alternativas para caracteres corrompidos.

    saida → imprime a mensagem final traduzida, exibindo alternativas para caracteres corrompidos.

    main → define o banco de tradução Morse ↔ letras, organiza as estruturas auxiliares e chama as funções.

⚙️ Como Compilar e Executar
    1. Baixe este repositório
    https://github.com/Limkol/c-digo_morse

    2.Crie um novo terminal

    3. Compile o programa

    Usando o GCC:

    gcc main.c -o main.exe

    4. Execute
    ./main.exe

📥 Exemplo de Uso

    Teste 01 - Tradução de texto em morse completo

    Entrada:
    Digite o texto: .- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --..

    Saída:
    ABCDEFGHIJKLMNOPQRSTUVWXYZ

    Teste 02 - Tradução de texto em morse corrompido

    Entrada:
    Digite o texto: -.-. .- -.. .-*  -- .- -.-. .- -.-. ---  -. ---  ... . ..-  --. .- .-.. .... ---

    Saída:
    CAD[AJLPRW] MACACO NO SEU GALHO

🧩 Banco de Tradução

  O projeto utiliza uma matriz para mapear caracteres Morse para letras:

  {"A", ".-"},   {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
  {"E", "."},    {"F", "..-."}, {"G", "--."},  {"H", "...."},
  {"I", ".."},   {"J", ".---"}, {"K", "-.-"},  {"L", ".-.."},
  {"M", "--"},   {"N", "-."},   {"O", "---"},  {"P", ".--."},
  {"Q", "--.-"}, {"R", ".-."},  {"S", "..."},  {"T", "-"},
  {"U", "..-"},  {"V", "...-"}, {"W", ".--"},  {"X", "-..-"},
  {"Y", "-.--"}, {"Z", "--.."}, {" ", "/"}

📋 Requisitos

  Compilador GCC ou compatível.

  Sistema operacional: Linux, macOS ou Windows (com MinGW/WSL).

🎥 Vídeo Explicativo

    Link: https://youtu.be/D1Z8pHH2e0s

👥 Integrantes do Grupo

    Gustavo Francisco Toito – 10438660 – 02G
    Henrique Cunha Alves – 10740428 – 02G
    Guilherme Longo Gouveia Xavier - 10736785 - 02G