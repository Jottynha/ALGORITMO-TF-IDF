#ifndef DOCUMENT_PROCESSOR_HPP
#define DOCUMENT_PROCESSOR_HPP

#include <queue>
#include <string>
#include <set>

using namespace std;

extern set<string> stopWords;

// Função para remover pontuação
string removePunctuation(const string& word);

// Função para converter string para minúsculas
string toLowerCase(const string& word);

// Função para carregar stopwords de um arquivo
set<string> loadStopWords(const string& stopWordsFile);

// Função para verificar se uma palavra é stop word
bool isStopWord(const string& word);

// Função para processar o documento e retornar uma fila de termos
queue<string> processDocument(const string& documentContent);

// Função para ler um arquivo de texto
string readFile(const string& filePath);

#endif // DOCUMENT_PROCESSOR_HPP
