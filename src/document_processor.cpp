#include "document_processor.hpp"

using namespace std;

unordered_set<string> stopWords;
unordered_map<string, double> idfMap;  
vector<unordered_map<string, int>> tfMaps; 

string removePunctuation(const string& word) {
    string cleanWord;
    for (char c : word) {
        if (!ispunct(c)) {
            cleanWord += c;
        }
    }
    return cleanWord;
}

string toLowerCase(const string& word) {
    string lowerWord = word;
    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    return lowerWord;
}

unordered_set<string> loadStopWords(const string& stopWordsFile) {
    unordered_set<string> stopWords;
    ifstream file(stopWordsFile);
    string word;

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo de stopwords: " << stopWordsFile << endl;
        return stopWords;
    }

    // Lê cada stopword e insere no unordered_set
    while (file >> word) {
        stopWords.insert(word);
    }

    file.close();
    return stopWords;
}

bool isStopWord(const string& word) {
    return stopWords.find(word) != stopWords.end();
}

// Função para processar o documento e retornar uma fila de termos
queue<string> processDocument(const string& documentContent) {
    queue<string> terms;
    stringstream ss(documentContent);
    string word;

    while (ss >> word) {
        word = removePunctuation(word);  
        word = toLowerCase(word);        
        if (!isStopWord(word) && !word.empty()) {
            terms.push(word);            // Adiciona o termo à fila se não for stop word
        }
    }

    return terms;
}

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
    while (!tempQueue.empty()) {
        string term = tempQueue.front();
        tempQueue.pop();
        tfMap[term]++;
    }
    return tfMap;
}

unordered_map<string, double> calculateIDF(const vector<queue<string>>& termQueues, int numDocs) {
    unordered_map<string, int> docFrequency;  // df(t)
    
    for (const auto& termQueue : termQueues) {
        set<string> uniqueTerms;
        queue<string> tempQueue = termQueue;

        while (!tempQueue.empty()) {
            uniqueTerms.insert(tempQueue.front());
            tempQueue.pop();
        }

        for (const string& term : uniqueTerms) {
            docFrequency[term]++;
        }
    }

    unordered_map<string, double> idfMap;
    for (const auto& entry : docFrequency) {
        const string& term = entry.first;
        int df = entry.second;
        // Consider using max to avoid zero division
        idfMap[term] = log(static_cast<double>(numDocs) / max(1, df));
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

// Função para calcular a relevância de cada documento em relação à frase de pesquisa
double calcularRelevancia(const unordered_map<string, double>& tfidf, const queue<string>& queryTerms) {
    double relevancia = 0.0;
    queue<string> tempQueue = queryTerms;

    while (!tempQueue.empty()) {
        string term = tempQueue.front();
        tempQueue.pop();
        if (tfidf.find(term) != tfidf.end()) {
            relevancia += tfidf.at(term);
        }
    }

    return relevancia;
}

// Função para calcular a relevância de todos os documentos e ordená-los
vector<DocumentoRelevancia> calcularEOrdenarRelevancia(
    const vector<unordered_map<string, double>>& documentosTFIDF,
    const queue<string>& queryTerms) {

    vector<DocumentoRelevancia> relevancias;

    // Calcula a relevância de cada documento
    for (size_t i = 0; i < documentosTFIDF.size(); ++i) {
        double relevancia = calcularRelevancia(documentosTFIDF[i], queryTerms);
        relevancias.push_back({static_cast<int>(i + 1), relevancia});
    }

    // Ordena os documentos com base na relevância
    sort(relevancias.begin(), relevancias.end());

    return relevancias;
}

// Função de particionamento para o QuickSort
int partition(vector<DocumentoRelevancia>& relevancias, int low, int high) {
    double pivot = relevancias[high].relevancia;
    int i = (low - 1);
    
    for (int j = low; j < high; j++) {
        if (relevancias[j].relevancia > pivot) { // Ordenando de forma decrescente
            i++;
            swap(relevancias[i], relevancias[j]);
        }
    }
    swap(relevancias[i + 1], relevancias[high]);
    return (i + 1);
}

// Implementação do QuickSort
void quickSort(vector<DocumentoRelevancia>& relevancias, int low, int high) {
    if (low < high) {
        int pi = partition(relevancias, low, high);
        quickSort(relevancias, low, pi - 1);
        quickSort(relevancias, pi + 1, high);
    }
}

// Função para processar documentos e armazenar termos em filas
vector<queue<string>> processDocuments(const vector<string>& documentPaths) {
    vector<queue<string>> termQueues;
    
    for (const string& path : documentPaths) {
        string content = readFile(path);
        if (!content.empty()) {
            queue<string> terms = processDocument(content);
            termQueues.push_back(terms);
        }
    }
    
    return termQueues;
}

// Função para escrever termos normalizados em um arquivo de saída
void writeTermsToFile(const vector<queue<string>>& termQueues, const vector<string>& documentPaths, const string& outputFile) {
    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída: " << outputFile << endl;
        return;
    }

    for (size_t i = 0; i < documentPaths.size(); ++i) {
        outFile << "Termos normalizados do documento " << i + 1 << ":" << endl;
        queue<string> tempQueue = termQueues[i];

        while (!tempQueue.empty()) {
            outFile << tempQueue.front() << endl;
            tempQueue.pop();
        }
        outFile << endl;  // Adiciona uma nova linha entre documentos
    }

    outFile.close();
}

// Função para calcular TF, IDF e TF-IDF
vector<unordered_map<string, double>> calculateTFIDF(const vector<queue<string>>& termQueues, const vector<string>& documentPaths) {
    vector<unordered_map<string, int>> tfMaps;
    
    for (const auto& terms : termQueues) {
        tfMaps.push_back(calculateTF(terms));
    }

    unordered_map<string, double> idfMap = calculateIDF(termQueues, documentPaths.size());

    vector<unordered_map<string, double>> tfidfMaps;
    for (const auto& tfMap : tfMaps) {
        tfidfMaps.push_back(calculateTFIDF(tfMap, idfMap));
    }

    return tfidfMaps;
}

void searchAndDisplayResults(const vector<unordered_map<string, double>>& tfidfMaps, 
                             const unordered_map<string, double>& idfMap, 
                             const vector<unordered_map<string, int>>& tfMaps, 
                             const string& pesquisaFile) {
    ifstream pesquisaFileStream(pesquisaFile);
    string pesquisaLinha;
    
    // Abre o arquivo de saída
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "Erro ao abrir output.txt" << endl;
        return;
    }

    // Armazena todas as palavras relevantes
    unordered_map<string, double> relevanciasGlobais;

    while (getline(pesquisaFileStream, pesquisaLinha)) {
        queue<string> queryTerms = processDocument(pesquisaLinha);
        
        vector<DocumentoRelevancia> relevancias = calcularEOrdenarRelevancia(tfidfMaps, queryTerms);
        
        quickSort(relevancias, 0, relevancias.size() - 1);

        // Salva os resultados da pesquisa no arquivo
        outputFile << endl;
        outputFile << "==================================================";
        outputFile << endl;
        outputFile << "Resultados para a pesquisa: \"" << pesquisaLinha << "\"" << endl;
        for (const auto& docRelevancia : relevancias) {
            int docID = docRelevancia.docID;
            outputFile << "Documento ID: " << docID << ", Relevância: " << docRelevancia.relevancia << endl;

            // Recupera o TF e TF-IDF do documento atual
            const auto& tfMap = tfMaps[docID - 1];
            const auto& tfidfMap = tfidfMaps[docID - 1];

            // Exibe TF-IDF de cada termo da consulta no documento
            queue<string> tempQueue = queryTerms;
            while (!tempQueue.empty()) {
                string term = tempQueue.front();
                tempQueue.pop();

                // Adiciona TF-IDF globalmente
                if (tfidfMap.find(term) != tfidfMap.end()) {
                    double tfidf = tfidfMap.at(term);
                    // Adiciona a relevância ao total
                    relevanciasGlobais[term] += tfidf;
                }
            }

            // Escreve informações detalhadas no arquivo
            queue<string> tempQueueDetails = queryTerms; // Para manter a original
            while (!tempQueueDetails.empty()) {
                string term = tempQueueDetails.front();
                tempQueueDetails.pop();

                // Imprime valores de TF, IDF e TF-IDF no arquivo
                if (tfMap.find(term) != tfMap.end() && idfMap.find(term) != idfMap.end()) {
                    int tf = tfMap.at(term);
                    double idf = idfMap.at(term);
                    double tfidf = tfidfMap.at(term);
                    
                    outputFile << "  Termo: '" << term << "'" << endl;
                    outputFile << "    TF: " << tf << endl;
                    outputFile << "    IDF: " << idf << endl;
                    outputFile << "    TF-IDF: " << tfidf << endl;
                } else {
                    outputFile << "  Termo: '" << term << "' não encontrado no documento." << endl;
                }
            }

            // Imprimir as 5 palavras mais relevantes para o documento
            vector<pair<string, double>> termosRelevantes(tfidfMap.begin(), tfidfMap.end());
            sort(termosRelevantes.begin(), termosRelevantes.end(), 
                 [](const auto& a, const auto& b) { return a.second > b.second; });
            
            outputFile << "  5 termos mais relevantes no Documento ID " << docID << ":" << endl;
            for (long unsigned int i = 0; i < 5 && i < termosRelevantes.size(); ++i) {
                outputFile << "    Termo: '" << termosRelevantes[i].first << "', Relevância: " << termosRelevantes[i].second << endl;
            }
        }
        outputFile << endl;
        cout << "Resumo para a frase: \"" << pesquisaLinha << "\"" << endl;
        cout << "A relevância desta pesquisa por documentos ordenados é:" << endl;
        for (const auto& docRelevancia : relevancias) {
            cout << "Documento ID: " << docRelevancia.docID << ", Relevância: " << docRelevancia.relevancia << endl;
        }
        outputFile << "==================================================";
        outputFile << endl;
    }

    // Imprimir as 5 palavras mais relevantes de todos os documentos
    vector<pair<string, double>> termosGlobais(relevanciasGlobais.begin(), relevanciasGlobais.end());
    sort(termosGlobais.begin(), termosGlobais.end(), 
         [](const auto& a, const auto& b) { return a.second > b.second; });

    outputFile << "5 termos mais relevantes em todos os documentos:" << endl;
    for (long unsigned int i = 0; i < 5 && i < termosGlobais.size(); ++i) {
        outputFile << "  Termo: '" << termosGlobais[i].first << "', Relevância: " << termosGlobais[i].second << endl;
    }

    pesquisaFileStream.close();
    outputFile.close(); 
}


// Função para executar a pesquisa de termos
void searchTermInDocuments(const vector<queue<string>>& termQueues) {
    string searchTerm;
    cout << "Digite um termo para pesquisar (ou 'sair' para encerrar): ";
    
    while (getline(cin, searchTerm)) {
        if (searchTerm == "sair") {
            break;
        }

        cout << "Resultados da pesquisa para o termo: '" << searchTerm << "':" << endl;
        bool found = false;

        for (size_t i = 0; i < termQueues.size(); ++i) {
            queue<string> tempQueue = termQueues[i];
            while (!tempQueue.empty()) {
                if (tempQueue.front() == searchTerm) {
                    cout << "O termo foi encontrado no documento " << i + 1 << endl;
                    found = true;
                    break;  // Para buscar apenas no primeiro documento encontrado
                }
                tempQueue.pop();
            }
            if (found) break;  // Sai do loop externo se encontrado
        }

        if (!found) {
            cout << "O termo '" << searchTerm << "' não foi encontrado em nenhum documento." << endl;
        }
        cout << "Digite um termo para pesquisar (ou 'sair' para encerrar): ";
    }
}
