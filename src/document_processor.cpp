#include "document_processor.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <cmath>

using namespace std;

set<string> stopWords;  // Stopwords serão carregadas do arquivo

// Função para remover pontuação
string removePunctuation(const string& word) {
    string cleanWord;
    for (char c : word) {
        if (!ispunct(c)) {
            cleanWord += c;
        }
    }
    return cleanWord;
}

// Função para converter string para minúsculas
string toLowerCase(const string& word) {
    string lowerWord = word;
    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    return lowerWord;
}

// Função para carregar stopwords de um arquivo
set<string> loadStopWords(const string& stopWordsFile) {
    set<string> stopWords;
    ifstream file(stopWordsFile);
    string word;

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo de stopwords: " << stopWordsFile << endl;
        return stopWords;
    }

    // Lê cada stopword e insere no set
    while (file >> word) {
        stopWords.insert(word);
    }

    file.close();
    return stopWords;
}

// Função para verificar se uma palavra é stop word
bool isStopWord(const string& word) {
    return stopWords.find(word) != stopWords.end();
}

// Função para processar o documento e retornar uma fila de termos
queue<string> processDocument(const string& documentContent) {
    queue<string> terms;
    stringstream ss(documentContent);
    string word;

    while (ss >> word) {
        word = removePunctuation(word);  // Remove pontuação
        word = toLowerCase(word);        // Converte para minúsculas
        if (!isStopWord(word) && !word.empty()) {
            terms.push(word);            // Adiciona o termo à fila se não for stop word
        }
    }

    return terms;
}

// Função para ler um arquivo de texto
string readFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filePath << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Função para calcular a frequência de termos (TF) em um documento
unordered_map<string, int> calculateTF(const queue<string>& termQueue) {
    unordered_map<string, int> tfMap;
    queue<string> tempQueue = termQueue;

    // Conta a frequência de cada termo no documento
    while (!tempQueue.empty()) {
        string term = tempQueue.front();
        tempQueue.pop();
        tfMap[term]++;
    }

    return tfMap;
}

// Função para calcular o IDF de cada termo considerando todos os documentos
unordered_map<string, double> calculateIDF(const vector<queue<string>>& termQueues, int numDocs) {
    unordered_map<string, int> docFrequency;  // df(t)
    set<string> uniqueTerms;
    
    // Contabiliza em quantos documentos cada termo aparece
    for (const auto& termQueue : termQueues) {
        uniqueTerms.clear();
        queue<string> tempQueue = termQueue;
        
        while (!tempQueue.empty()) {
            uniqueTerms.insert(tempQueue.front());
            tempQueue.pop();
        }

        // Aumenta o contador de documentos para cada termo único
        for (const string& term : uniqueTerms) {
            docFrequency[term]++;
        }
    }

    // Calcula o IDF de cada termo
    unordered_map<string, double> idfMap;
    for (const auto& entry : docFrequency) {
        const string& term = entry.first;
        int df = entry.second;
        idfMap[term] = log((double)numDocs / (1 + df));  // IDF(t) = log(N / (1 + df(t)))
    }

    return idfMap;
}

// Função para calcular o TF-IDF combinando os mapas de TF e IDF
unordered_map<string, double> calculateTFIDF(const unordered_map<string, int>& tfMap, const unordered_map<string, double>& idfMap) {
    unordered_map<string, double> tfidfMap;

    // Para cada termo, multiplica TF pelo IDF correspondente
    for (const auto& entry : tfMap) {
        const string& term = entry.first;
        int tf = entry.second;

        if (idfMap.find(term) != idfMap.end()) {
            double idf = idfMap.at(term);
            tfidfMap[term] = tf * idf;
        }
    }

    return tfidfMap;
}