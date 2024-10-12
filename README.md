<div align="center">
   
# Processamento de Texto e Extração de Palavras Relevantes usando TF-IDF

</div>

## Introdução 📝
<div align="center">
   
![TF-IDF](https://miro.medium.com/v2/resize:fit:720/format:webp/1*V9ac4hLVyms79jl65Ym_Bw.jpeg)

</div>

Este projeto tem como objetivo processar documentos de texto para normalizar os termos, remover stopwords e calcular a relevância de cada palavra em relação ao documento, utilizando o algoritmo TF-IDF (Term Frequency - Inverse Document Frequency). O TF-IDF é uma técnica amplamente utilizada em mineração de texto e recuperação de informação, capaz de destacar os termos mais significativos de um conjunto de documentos.

O algoritmo TF-IDF funciona em duas etapas principais:

1. **TF (Frequência de Termos)**: Mede a frequência de uma palavra em um documento específico. Isso reflete a importância do termo no documento em questão.
2. **IDF (Frequência Inversa de Documentos)**: Mede a raridade de uma palavra em um conjunto de documentos. Termos que aparecem em muitos documentos têm menos valor do que aqueles que aparecem em poucos.

Ao combinar essas duas métricas, o TF-IDF ajuda a identificar palavras que são frequentes em um documento, mas raras em outros, destacando-as como mais relevantes.

O projeto inclui a implementação de um sistema que faz a leitura de arquivos de texto, remove a pontuação, normaliza o texto para minúsculas e remove palavras irrelevantes usando uma lista de stopwords. Após o pré-processamento, o sistema é capaz de calcular os valores TF-IDF para cada termo, oferecendo uma visão clara dos termos mais relevantes em cada documento.

---

## Objetivos 🎯
O objetivo deste trabalho é desenvolver um sistema de ranqueamento de documentos utilizando o algoritmo TF/IDF (Term Frequency-Inverse Document Frequency). Os objetivos específicos incluem:

1. **Implementação do Algoritmo TF/IDF**: Construir um sistema que calcule a relevância de documentos em relação a uma consulta de pesquisa, aplicando o algoritmo TF/IDF para ranquear os documentos de forma eficaz.

2. **Exercício de Conceitos Fundamentais**: Reforçar o conhecimento em conceitos abordados na disciplina de Algoritmos e Estruturas de Dados I, incluindo:
   - Análise assintótica para avaliar a eficiência do algoritmo.
   - Uso de listas, pilhas, filas, e tabelas hash para armazenamento e manipulação de dados.
   - Aplicação de métodos de ordenação, como QuickSort, para organizar os documentos com base em sua relevância.

3. **Preparação para Estruturas Avançadas**: Preparar os alunos para o estudo de estruturas de dados mais complexas que serão introduzidas no decorrer do curso, como árvores e grafos. Isso inclui:
   - Analisar como a implementação de estruturas em árvore, como Árvores Binárias de Busca (BST) ou Árvores AVL, pode otimizar a busca e a inserção de termos, reduzindo a complexidade de O(n) para O(log n).
   - Compreender a aplicação de grafos na relação entre documentos e termos de pesquisa, considerando os documentos como vértices e os termos como arestas que conectam os documentos com base em sua relevância.

4. **Desenvolvimento de Habilidades Práticas**: Proporcionar uma oportunidade para os alunos aplicarem teorias de algoritmos e estruturas de dados em um projeto prático, promovendo um entendimento mais profundo sobre o funcionamento e a eficiência das diferentes estruturas de dados em aplicações reais.

Esses objetivos visam não apenas o cumprimento das exigências do trabalho, mas também um aprendizado significativo que prepara os alunos para desafios futuros na área de Ciência da Computação.

  
### Tecnologias Utilizadas

- C++
- Algoritmo TF-IDF
- Estruturas de dados para leitura e armazenamento de termos
- Manipulação de arquivos de texto
  
---

## Descrição

O **document_processor.cpp/hpp** é um programa que lê documentos de texto, processa seu conteúdo para extrair termos relevantes, e calcula a relevância de documentos em relação a uma consulta de pesquisa. O processamento inclui a remoção de stopwords, normalização de palavras, e cálculo de métricas de frequência de termos (TF), frequência inversa de documentos (IDF) e TF-IDF.

### Estruturas de Dados Utilizadas

O programa utiliza as seguintes estruturas de dados:

1. **`unordered_set<string>`**: Usado para armazenar as stopwords, permitindo a busca eficiente e a verificação se uma palavra é uma stopword.
  
2. **`queue<string>`**: Usada para armazenar os termos processados de cada documento. As filas permitem uma ordenação simples e o processamento sequencial dos termos.

3. **`unordered_map<string, int>`**: Utilizado para armazenar a frequência de cada termo (TF) em um documento.

4. **`unordered_map<string, double>`**: Usado para armazenar o IDF de cada termo e o TF-IDF resultante.

5. **`vector<unordered_map<string, double>>`**: Uma lista de mapas que armazenam o TF-IDF para todos os documentos, permitindo o acesso eficiente durante as consultas.

6. **`vector<queue<string>>`**: Utilizado para armazenar filas de termos para cada documento processado.

## Como Funciona

O funcionamento do programa pode ser resumido nas seguintes etapas:

1. **Carregamento de Stopwords**:
   - As stopwords são carregadas de um arquivo de texto usando a função `loadStopWords`. Elas são armazenadas em um `unordered_set` para acesso rápido durante o processamento.

2. **Processamento de Documentos**:
   - Cada documento é lido através da função `readFile`, que carrega o conteúdo do arquivo. Em seguida, o conteúdo é processado pela função `processDocument`, que remove pontuação, converte palavras para minúsculas, e filtra stopwords. Os termos resultantes são armazenados em uma `queue`.

3. **Cálculo de Frequências**:
   - O TF é calculado utilizando a função `calculateTF`, que conta a frequência de cada termo na fila de termos. O IDF é calculado em relação a todos os documentos usando a função `calculateIDF`.

4. **Cálculo de TF-IDF**:
   - O TF-IDF é calculado combinando os mapas de TF e IDF através da função `calculateTFIDF`.

5. **Pesquisa e Relevância**:
   - As consultas de pesquisa são processadas, e a relevância de cada documento em relação à consulta é calculada com a função `calcularRelevancia`. Os documentos são ordenados com base em sua relevância usando o algoritmo de **QuickSort**.

6. **Resultados**:
   - Os resultados da pesquisa são exibidos, mostrando a relevância de cada documento em relação à consulta.

## Dificuldades de Implementação

Ao implementar o algoritmo, algumas dificuldades podem ser encontradas:

1. **Gerenciamento de Stopwords**: A correta identificação e carregamento das stopwords pode ser desafiador, especialmente se o arquivo de stopwords não estiver no formato esperado.

2. **Processamento de Documentos**: O tratamento de diferentes formatos de documentos (como PDFs ou arquivos de texto com codificações distintas) pode exigir adaptações no código.

3. **Cálculo de TF-IDF**: A implementação eficiente do cálculo de TF-IDF em grandes conjuntos de dados pode resultar em um consumo elevado de memória e tempo de processamento.

4. **Ordenação de Resultados**: A ordenação dos documentos com base em sua relevância pode ser complexa se não houver uma estrutura de dados adequada.

## Conclusão

O **Document Processor** oferece uma solução eficaz para processar documentos de texto e calcular sua relevância em relação a consultas de pesquisa, utilizando técnicas clássicas de recuperação de informações. As estruturas de dados escolhidas garantem eficiência e rapidez no processamento.


---
 
## Compilação e Execução

 Especificações da máquina em que o código foi rodado:
  * Processador Intel Celeron N4020;
  * Sistema Operacional Ubuntu 22.04.01;
  * 4 GB de RAM.
* | Comando                |  Função                                                                                           |                     
  | -----------------------| ------------------------------------------------------------------------------------------------- |
  |  `make clean`          | Apaga a última compilação realizada contida na pasta build.                                       |
  |  `make`                | Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta build.          |
  |  `make run`            | Executa o programa da pasta build após a realização da compilação.                                |

---
Esse README oferece uma visão geral da evolução do algoritmo, as bibliotecas utilizadas e o código relevante, proporcionando uma base clara para entender e utilizar o projeto.

## Integrantes:

**João Pedro Rodrigues Silva**  
[![Static Badge](https://img.shields.io/badge/%7C%20Jottynha-black?style=flat-square&logo=github)](https://github.com/Jottynha)
[![Static Badge](https://img.shields.io/badge/%7C%20jprs1308%40gmail.com%20-black?style=flat-square&logo=gmail)](mailto:jprs1308@gmail.com)

**Pedro Augusto Moura**  
[![Static Badge](https://img.shields.io/badge/%7C%20PedroAugusto08-black?style=flat-square&logo=github)](https://github.com/PedroAugusto08)
[![Static Badge](https://img.shields.io/badge/%7C%20pedroaugustomoura70927%40gmail.com-black?style=flat-square&logo=gmail)](mailto:pedroaugustomoura70927@gmail.com)

**Henrique de Freitas Araujo**  
[![Static Badge](https://img.shields.io/badge/%7C%20Ak4ai-black?style=flat-square&logo=github)
](https://github.com/Ak4ai)
[![Static Badge](https://img.shields.io/badge/%7C%20ricosgames.henrique%40gmail.com%20-black?style=flat-square&logo=gmail)](mailto:ricosgames.henrique@gmail.com )

___


<!---
✉️ jprs1308@gmail.com (**João Pedro Rodrigues Silva**)

✉️ pedroaugustomoura70927@gmail.com (**Pedro Augusto Moura**)

✉️ ricosgames.henrique@gmail.com (**Henrique de Freitas Araujo**)

--->
