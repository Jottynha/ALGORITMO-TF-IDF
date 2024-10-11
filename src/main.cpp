#include "document_processor.hpp"
#include <iostream>
#include <queue>
#include <fstream>
#include <unordered_map>

using namespace std;

int main() {
    // Carregar stopwords
    stopWords = loadStopWords("datasets/stopwords.txt");

    // Ler documentos e processá-los
    vector<string> documentPaths = {"datasets/A mão e a luva.txt", "datasets/biblia.txt", "datasets/DomCasmurro.txt","datasets/quincas borba.txt","datasets/Semana_Machado_Assis.txt","datasets/terremoto.txt"}; // Substitua pelos seus arquivos
    vector<queue<string>> termQueues;
    string outputFile = "output.txt";  // Arquivo de saída

    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída: " << outputFile << endl;
        return 1;
    }

    for (const string& path : documentPaths) {
        string content = readFile(path);
        if (!content.empty()) {
            queue<string> terms = processDocument(content);
            termQueues.push_back(terms);
        }
    }

    // Processamento de cada arquivo individualmente
    for (size_t i = 0; i < documentPaths.size(); ++i) {
        string documentContent = readFile(documentPaths[i]);
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


    // Calcular TF para cada documento
    vector<unordered_map<string, int>> tfMaps;
    for (const auto& terms : termQueues) {
        tfMaps.push_back(calculateTF(terms));
    }

    // Calcular IDF
    unordered_map<string, double> idfMap = calculateIDF(termQueues, documentPaths.size());

    // Calcular TF-IDF
    vector<unordered_map<string, double>> tfidfMaps;
    for (const auto& tfMap : tfMaps) {
        tfidfMaps.push_back(calculateTFIDF(tfMap, idfMap));
    }

    // Ler frases de pesquisa
    ifstream pesquisaFile("pesquisa.txt");
    string pesquisaLinha;
    
    while (getline(pesquisaFile, pesquisaLinha)) {
        queue<string> queryTerms = processDocument(pesquisaLinha);
        
        // Calcular e ordenar relevância
        vector<DocumentoRelevancia> relevancias = calcularEOrdenarRelevancia(tfidfMaps, queryTerms);
        
        // Ordenar com QuickSort
        quickSort(relevancias, 0, relevancias.size() - 1);

        // Exibir resultados
        cout << "Resultados para a pesquisa: \"" << pesquisaLinha << "\"" << endl;
        for (const auto& docRelevancia : relevancias) {
            cout << "Documento ID: " << docRelevancia.docID << ", Relevância: " << docRelevancia.relevancia << endl;
        }
        cout << endl;
    }

    // Loop para pesquisa de termos
    string searchTerm;
    cout << "Digite um termo para pesquisar (ou 'sair' para encerrar): ";
    while (getline(cin, searchTerm)) {
        if (searchTerm == "sair") {
            break;
        }

        // Executa a pesquisa nos documentos
        cout << "Resultados da pesquisa para o termo: '" << searchTerm << "':" << endl;
        bool found = false;
        for (size_t i = 0; i < termQueues.size(); ++i) {
            // Cria uma cópia da fila para verificar a presença do termo
            queue<string> tempQueue = termQueues[i];
            while (!tempQueue.empty()) {
                string term = tempQueue.front();
                tempQueue.pop();
                if (term == searchTerm) {
                    cout << "O termo foi encontrado no documento " << i + 1 << endl;
                    found = true;
                    break;  // Para buscar apenas no primeiro documento encontrado
                }
            }
        }
        if (!found) {
            cout << "O termo '" << searchTerm << "' não foi encontrado em nenhum documento." << endl;
        }
        cout << "Digite um termo para pesquisar (ou 'sair' para encerrar): ";
    }

    pesquisaFile.close();
    return 0;
}
