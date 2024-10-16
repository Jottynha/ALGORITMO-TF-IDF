#ifndef DOCUMENT_PROCESSOR_HPP
#define DOCUMENT_PROCESSOR_HPP

#include <queue>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

extern unordered_set<string> stopWords;
extern unordered_map<string, double> idfMap;
extern vector<unordered_map<string, int>> tfMaps;

// Estrutura para armazenar a relevância dos documentos
struct DocumentoRelevancia {
    int docID;     // ID do documento
    double relevancia;  // Relevância do documento

    // Operador para facilitar a comparação durante a ordenação
    bool operator<(const DocumentoRelevancia& other) const {
        return relevancia > other.relevancia;  // Maior relevância primeiro
    }
};

unordered_map<string, int> calculateTF(const queue<string>& termQueue);
unordered_map<string, double> calculateIDF(const vector<queue<string>>& termQueues, int numDocs);
unordered_map<string, double> calculateTFIDF(const unordered_map<string, int>& tfMap, const unordered_map<string, double>& idfMap);

// Função para remover pontuação
string removePunctuation(const string& word);

// Função para converter string para minúsculas
string toLowerCase(const string& word);

// Função para carregar stopwords de um arquivo
unordered_set<string> loadStopWords(const string& stopWordsFile);

// Função para verificar se uma palavra é stop word
bool isStopWord(const string& word);

// Função para processar o documento e retornar uma fila de termos
queue<string> processDocument(const string& documentContent);

// Função para ler um arquivo de texto
string readFile(const string& filePath);

vector<DocumentoRelevancia> calcularEOrdenarRelevancia(
    const vector<unordered_map<string, double>>& documentosTFIDF,
    const queue<string>& queryTerms);

// Função de particionamento para o QuickSort
int partition(vector<DocumentoRelevancia>& relevancias, int low, int high);
// Implementação do QuickSort
void quickSort(vector<DocumentoRelevancia>& relevancias, int low, int high);

void searchTermInDocuments(const vector<queue<string>>& termQueues);
void searchAndDisplayResults(const vector<unordered_map<string, double>>& tfidfMaps, const unordered_map<string, double>& idfMap, const vector<unordered_map<string, int>>& tfMaps, const string& pesquisaFile);
vector<queue<string>> processDocuments(const vector<string>& documentPaths);void writeTermsToFile(const vector<queue<string>>& termQueues, const vector<string>& documentPaths, const string& outputFile);
void writeTermsToFile(const vector<queue<string>>& termQueues, const vector<string>& documentPaths, const string& outputFile);
vector<unordered_map<string, double>> calculateTFIDF(const vector<queue<string>>& termQueues, const vector<string>& documentPaths);

#endif // DOCUMENT_PROCESSOR_HPP
