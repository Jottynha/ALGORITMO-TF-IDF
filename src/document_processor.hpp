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
    int docID;
    double relevancia;
    bool operator<(const DocumentoRelevancia& other) const {
        return relevancia > other.relevancia;
    }
};

unordered_map<string, int> calculateTF(const queue<string>& termQueue);
unordered_map<string, double> calculateIDF(const vector<queue<string>>& termQueues, int numDocs);
unordered_map<string, double> calculateTFIDF(const unordered_map<string, int>& tfMap, const unordered_map<string, double>& idfMap);
string removePunctuation(const string& word);
string toLowerCase(const string& word);
unordered_set<string> loadStopWords(const string& stopWordsFile);
bool isStopWord(const string& word);
queue<string> processDocument(const string& documentContent);
string readFile(const string& filePath);
vector<DocumentoRelevancia> calcularEOrdenarRelevancia(
    const vector<unordered_map<string, double>>& documentosTFIDF,
    const queue<string>& queryTerms);
int partition(vector<DocumentoRelevancia>& relevancias, int low, int high);
void quickSort(vector<DocumentoRelevancia>& relevancias, int low, int high);
void searchTermInDocuments(const vector<queue<string>>& termQueues);
void searchAndDisplayResults(const vector<unordered_map<string, double>>& tfidfMaps, const unordered_map<string, double>& idfMap, const vector<unordered_map<string, int>>& tfMaps, const string& pesquisaFile);
vector<queue<string>> processDocuments(const vector<string>& documentPaths);void writeTermsToFile(const vector<queue<string>>& termQueues, const vector<string>& documentPaths, const string& outputFile);
void writeTermsToFile(const vector<queue<string>>& termQueues, const vector<string>& documentPaths, const string& outputFile);
vector<unordered_map<string, double>> calculateTFIDF(const vector<queue<string>>& termQueues, const vector<string>& documentPaths);

#endif 

