# Processamento de Texto e Extração de Palavras Relevantes usando TF-IDF

## Introdução

Este projeto tem como objetivo processar documentos de texto para normalizar os termos, remover stopwords e calcular a relevância de cada palavra em relação ao documento, utilizando o algoritmo TF-IDF (Term Frequency - Inverse Document Frequency). O TF-IDF é uma técnica amplamente utilizada em mineração de texto e recuperação de informação, capaz de destacar os termos mais significativos de um conjunto de documentos.

O algoritmo TF-IDF funciona em duas etapas principais:

1. **TF (Frequência de Termos)**: Mede a frequência de uma palavra em um documento específico. Isso reflete a importância do termo no documento em questão.
2. **IDF (Frequência Inversa de Documentos)**: Mede a raridade de uma palavra em um conjunto de documentos. Termos que aparecem em muitos documentos têm menos valor do que aqueles que aparecem em poucos.

Ao combinar essas duas métricas, o TF-IDF ajuda a identificar palavras que são frequentes em um documento, mas raras em outros, destacando-as como mais relevantes.

O projeto inclui a implementação de um sistema que faz a leitura de arquivos de texto, remove a pontuação, normaliza o texto para minúsculas e remove palavras irrelevantes usando uma lista de stopwords. Após o pré-processamento, o sistema é capaz de calcular os valores TF-IDF para cada termo, oferecendo uma visão clara dos termos mais relevantes em cada documento.

---

Para ilustrar o conceito de TF-IDF, a imagem abaixo demonstra visualmente como palavras importantes podem ser extraídas e priorizadas em um documento:

![TF-IDF Visualization](https://www.researchgate.net/publication/376247075/figure/fig2/AS:11431281209841725@1701888441866/TF-IDFTerm-Frequency-Inverse-Document-Frequency.ppm)

---

### Objetivos

- Processar documentos de texto para normalizar termos.
- Remover stopwords e pontuação.
- Calcular e exibir a relevância de termos em documentos usando TF-IDF.
  
### Tecnologias Utilizadas

- C++
- Algoritmo TF-IDF
- Estruturas de dados para leitura e armazenamento de termos
- Manipulação de arquivos de texto
 
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
