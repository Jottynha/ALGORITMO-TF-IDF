#include "document_processor.hpp"

using namespace std;

int main() {
    stopWords = loadStopWords("datasets/stopwords.txt");
    vector<string> documentPaths = {
        "datasets/A mão e a luva.txt", 
        "datasets/biblia.txt", 
        "datasets/DomCasmurro.txt",
        "datasets/quincas borba.txt",
        "datasets/Semana_Machado_Assis.txt",
        "datasets/terremoto.txt"
    };
    vector<queue<string>> termQueues = processDocuments(documentPaths);
    writeTermsToFile(termQueues, documentPaths, "words.txt");
    vector<unordered_map<string, double>> tfidfMaps = calculateTFIDF(termQueues, documentPaths);
    unordered_map<string, double> idfMap = calculateIDF(termQueues,documentPaths.size());
    vector<unordered_map<string, int>> tfMaps;
    for (const auto& terms : termQueues) {
        tfMaps.push_back(calculateTF(terms));
    }
    searchAndDisplayResults(tfidfMaps, idfMap,tfMaps, "pesquisa.txt");
    searchTermInDocuments(termQueues);
    return 0;
}