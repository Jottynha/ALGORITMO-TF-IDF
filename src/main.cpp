#include "document_processor.hpp"

using namespace std;

int main() {
    // Carregar stopwords
    stopWords = loadStopWords("datasets/stopwords.txt");

    // Caminhos dos documentos
    vector<string> documentPaths = {
        "datasets/A mão e a luva.txt", 
        "datasets/biblia.txt", 
        "datasets/DomCasmurro.txt",
        "datasets/quincas borba.txt",
        "datasets/Semana_Machado_Assis.txt",
        "datasets/terremoto.txt"
    };

    // Processar documentos
    vector<queue<string>> termQueues = processDocuments(documentPaths);

    // Escrever termos em arquivo
    writeTermsToFile(termQueues, documentPaths, "output.txt");

    // Calcular TF-IDF
    vector<unordered_map<string, double>> tfidfMaps = calculateTFIDF(termQueues, documentPaths);

    // Pesquisar e exibir resultados
    searchAndDisplayResults(tfidfMaps, "pesquisa.txt");

    // Loop para pesquisa de termos
    searchTermInDocuments(termQueues);

    return 0;
}