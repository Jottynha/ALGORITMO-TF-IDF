#include "document_processor.hpp"
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

int main() {
    // Caminho do arquivo de texto e do arquivo de stopwords
    string filePath = "datasets/terremoto.txt";
    string stopWordsFile = "datasets/stopwords.txt";
    string outputFile = "output.txt";  // Arquivo de saída

    // Carrega as stopwords a partir do arquivo
    stopWords = loadStopWords(stopWordsFile);

    // Lê o conteúdo do arquivo
    string documentContent = readFile(filePath);

    if (!documentContent.empty()) {
        // Processa o documento
        queue<string> terms = processDocument(documentContent);

        // Abre o arquivo de saída
        ofstream outFile(outputFile);

        if (!outFile.is_open()) {
            cerr << "Erro ao abrir o arquivo de saída: " << outputFile << endl;
            return 1;
        }

        outFile << "Termos normalizados:" << endl;

        while (!terms.empty()) {
            string term = terms.front();
            terms.pop();
            outFile << term << endl;  // Escreve no arquivo
        }

        // Fecha o arquivo de saída
        outFile.close();
    }

    return 0;
}
