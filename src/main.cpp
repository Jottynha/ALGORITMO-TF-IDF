#include "document_processor.hpp"
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

int main() {
    // Caminhos dos arquivos de texto
    vector<string> filePaths = {
        "datasets/A mão e a luva.txt",
        "datasets/biblia.txt",
        "datasets/DomCasmurro.txt",
        "datasets/quincas borba.txt",
        "datasets/Semana_Machado_Assis.txt",
        "datasets/terremoto.txt"
    };

    string stopWordsFile = "datasets/stopwords.txt";
    string outputFile = "output.txt";  // Arquivo de saída
    // Carrega as stopwords a partir do arquivo
    stopWords = loadStopWords(stopWordsFile);
    // Seis filas para armazenar os termos de cada documento
    vector<queue<string>> termQueues(6);
    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída: " << outputFile << endl;
        return 1;
    }
    // Processamento de cada arquivo individualmente
    for (long unsigned int i = 0; i < filePaths.size(); ++i) {
        string documentContent = readFile(filePaths[i]);
        if (!documentContent.empty()) {
            // Processa o documento e armazena os termos na fila correspondente
            termQueues[i] = processDocument(documentContent);
            
            // Imprime os termos normalizados sem esvaziar a fila
            outFile << "Termos normalizados do documento " << i + 1 << ":" << endl;
            queue<string> tempQueue = termQueues[i];  // Cria uma cópia da fila para percorrer

            while (!tempQueue.empty()) {
                string term = tempQueue.front();  // Apenas lê o termo da fila temporária
                outFile << term << endl;
                tempQueue.pop();  // Remove da fila temporária, mas a original fica intacta
            }

            outFile << endl;  // Adiciona uma nova linha entre documentos
        }
    }
    // Processamento dos documentos
    for (long unsigned int i = 0; i < termQueues.size(); ++i) {
        // Calcula o TF para o documento atual
        unordered_map<string, int> tfMap = calculateTF(termQueues[i]);

        // Calcula o IDF baseado em todos os documentos
        unordered_map<string, double> idfMap = calculateIDF(termQueues, termQueues.size());

        // Calcula o TF-IDF para o documento atual
        unordered_map<string, double> tfidfMap = calculateTFIDF(tfMap, idfMap);

        // Escreve os valores TF-IDF no arquivo de saída
        outFile << "TF-IDF do documento " << i + 1 << ":" << endl;
        for (const auto& entry : tfidfMap) {
            outFile << entry.first << ": " << entry.second << endl;
        }
        outFile << endl;  // Adiciona uma nova linha entre documentos
    }

    // Fecha o arquivo de saída
    outFile.close();

    return 0;
}
