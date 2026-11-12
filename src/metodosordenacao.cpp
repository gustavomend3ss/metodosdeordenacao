//Método de ordenacao por Borbulhamento
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

int main()
{
    vector<double> data;
    double numero;
    double temp;
    long long trocas = 0;

    ifstream Ler("numeros.txt");

    if (!Ler.is_open())
    {
        cout << "\nErro ao abrir o arquivo!" << endl;
        return 1;
    }

    while (Ler >> numero)
    {
        data.push_back(numero);
    }

    Ler.close();

    cout << "\nQuantidade de numeros: " << data.size() << endl;

    if (data.empty())
    {
        cout << "\nNenhum numero foi encontrado!" << endl;
        return 1;
    }

    cout << "\nInicio do borbulhamento..." << endl;

    for (int i = 0; i < data.size() - 1; i++)
    {
        for (int j = data.size() - 1; j > i; j--)
        {
            if (data[j] < data[j - 1])
            {
                temp = data[j];
                data[j] = data[j - 1];
                data[j - 1] = temp;
                
                trocas++;
            }
        }
    }

    cout << "\nOrdenacao concluida!" << endl;

    ofstream Gravar("numeros_ordenados.txt");

    if (!Gravar.is_open())
    {
        cout << "\nErro ao criar arquivo de saida!" << endl;
        return 1;
    }

    for (size_t a = 0; a < data.size(); a++)
    {
        Gravar << data[a] << "\n";
    }

    Gravar.close();

    cout << "\nArquivo salvo com sucesso!" << endl;
    cout << "Total de trocas: " << trocas << endl;

    return 0;
}
