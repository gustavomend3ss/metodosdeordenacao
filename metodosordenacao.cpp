#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;


class Ordenacao {
    private:
        vector<double> v;  
        long long trocas;  
        double tempo;      
        string metodo;     

    public:
        Ordenacao() {
            trocas = 0;
            tempo = 0;
            metodo = "";
        }
        ~Ordenacao() {
        }

        bool ler_arquivo(string nome_arquivo) {
            ifstream arquivo(nome_arquivo);
            if (!arquivo.is_open()) {
                return false;
            }
            double num;
            while (arquivo >> num) {
                v.push_back(num);
            }
            arquivo.close();
            return true;
        }

        //bubble sort
        void borbulhamento() {
            int n = v.size();
            for (int i = 0; i < n - 1; i++) {
                bool trocou = false;
                
                for (int j = 0; j < n - 1 - i; j++) {
                    if (v[j] > v[j + 1]) {
                        double aux = v[j];   
                        v[j] = v[j + 1];
                        v[j + 1] = aux;
                        trocas++;
                        trocou = true;
                    }
                }
                
                if (!trocou) {
                    break;
                }
            }
        }

        //insert sort
        void insercao() {
            int n = v.size();

            for (int i = 1; i < n; i++) {
                int j = i;

                while (j > 0 && v[j] < v[j - 1]) {
                    double aux = v[j];
                    v[j] = v[j - 1];
                    v[j - 1] = aux;

                    trocas++;
                    j--;
                }
            }       
        }

        void selecao() {
            int n = v.size();
            for (int i = 0; i < n - 1; i++) {
                int menor = i; 
                for (int j = i + 1; j < n; j++) {
                    if (v[j] < v[menor]) {
                        menor = j;
                    }
                }
               
                if (menor != i) {
                    double aux = v[i];
                    v[i] = v[menor];
                    v[menor] = aux;
                    trocas++;
                }
            }
        }


        void ordenar(int opcao) {
            trocas = 0;

            if (opcao == 1) {
                metodo = "Borbulhamento";
            } else if (opcao == 2) {
                metodo = "Insercao";
            } else if (opcao == 3) {
                metodo = "Selecao";
            } else {
                return;
            }

            chrono::steady_clock::time_point inicio =
                chrono::steady_clock::now();

            if (opcao == 1) {
                borbulhamento();
            } else if (opcao == 2) {
                insercao();
            } else {
                selecao();
            }

            chrono::steady_clock::time_point fim =
                chrono::steady_clock::now();

            tempo = chrono::duration<double, milli>(fim - inicio).count();
        }
        
        bool ret_crescente() {
            for (int i = 0; i < (int)v.size() - 1; i++) {
                if (v[i] > v[i + 1]) {
                    return false;
                }
            }
            return true;
        }

        void print_dados() {
            cout << "\n=== RESULTADO ===";
            cout << "\nMetodo: " << metodo;
            cout << "\nNumeros ordenados: " << v.size();
            cout << "\nMenor valor: " << v[0];
            cout << "\nMaior valor: " << v[v.size() - 1];
            if (ret_crescente()) {
                cout << "\nOrdem crescente: SIM";
            } else {
                cout << "\nOrdem crescente: NAO";
            }
            cout << "\nTotal de trocas: " << trocas;
            cout << "\nTempo de ordenacao: " << tempo << " ms\n";
        }

        bool salvar_resultado(string nome_arquivo) {
            ofstream saida(nome_arquivo, ios::app);
            if (!saida.is_open()) {
                return false;
            }
            saida << "Metodo: " << metodo << "\n";
            saida << "Numeros ordenados: " << v.size() << "\n";
            if (ret_crescente()) {
                saida << "Ordem crescente: SIM\n";
            } else {
                saida << "Ordem crescente: NAO\n";
            }
            saida << "Total de trocas: " << trocas << "\n";
            saida << "Tempo de ordenacao: " << tempo << " ms\n";
            saida << "------------------------------\n";
            saida.close();
            return true;
        }

        long long ret_trocas() {
            return trocas;
        }
        double ret_tempo() {
            return tempo;
        }
        string ret_metodo() {
            return metodo;
        }
};

int main() {
    
    string metodos[3] = {
        "Borbulhamento", // 1
        "Insercao",      // 2
        "Selecao"        // 3
    };

    ofstream resultado("resultado.txt");
    resultado << "=== RESULTADOS DOS METODOS DE ORDENACAO ===\n";
    resultado << "------------------------------\n";
    resultado.close();

    int opcao;
    do {
        
        cout << "\n=== METODOS DE ORDENACAO ===\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << " - " << metodos[i] << "\n";
        }
        cout << "0 - Sair\n\n";
        cout << "Digite o numero do metodo: ";
        cin >> opcao;

        if (opcao == 0) {
            break;
        }

        if (opcao < 1 || opcao > 3) {
            cout << "Erro: Opcao invalida!\n";
            continue;
        }

        Ordenacao ord;
        if (!ord.ler_arquivo("numeros.txt")) {
            cout << "Erro: nao foi possivel abrir o arquivo numeros.txt!\n";
            return 1;
        }

        cout << "\nOrdenando com " << metodos[opcao - 1] << "...\n";
        ord.ordenar(opcao);
        ord.print_dados();

        if (ord.salvar_resultado("resultado.txt")) {
            cout << "Resultado salvo em resultado.txt\n";
        } else {
            cout << "Erro: nao foi possivel salvar o resultado!\n";
        }
    } while (opcao != 0);

    return 0;
}