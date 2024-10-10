#include "document_processor.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>

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
