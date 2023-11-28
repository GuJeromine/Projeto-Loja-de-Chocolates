#ifndef LOJADECHOCOLATES_HPP_INCLUDED
#define LOJADECHOCOLATES_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <ctime>

using namespace std;

// Descobrir qual sistema o usuário está utilizando para limpar o terminal corretamente
#ifdef _WIN32
    const string CLEAR_COMMAND = "cls";
#else
    const string CLEAR_COMMAND = "clear";
#endif

class chocolate // classe inicial da loja
{
public:
    virtual double preco(double p, double d, int quantidade) // virtual por ser uma funcao virtual que será substituida em classes dervidas, p preco, d diametro e q quantidade
    {
        double valor;
        valor = (0.20 * p);
        return valor;
    }
};

class ovo : public chocolate // classe ovo de pascoa herdando da classe chocolate
{
public:
    double preco(double p, double d, int quantidade) // p preco, d diametro e q quantidade
    {
        double valor;
        valor = (0.20 * p + 0.40 * d);
        return valor;
    }
};

class trufa : public chocolate // classe trufa herdando da classe chocolate
{
public:
    double preco(double p, double d, int quantidade) // p preco, d diametro e q quantidade
    {
        double valor;
        valor = (3.90 * quantidade);
        return valor;
    }
};

class caixaDeBombons : public chocolate // classe caixa de bombons herdando da classe chocolate
{
public:
    double preco(double p, double d, int quantidade) // p preco, d diametro e q quantidade
    {
        double valor;
        valor = (14.79 * quantidade);
        return valor;
    }
};

class biscoito : public chocolate // classe biscoito herdando da classe chocolate
{
public:
    double preco(double p, double d, int quantidade) // p preco, d diametro e q quantidade
    {
        double valor;
        valor = (3.57 * quantidade);
        return valor;
    }
};

class wafer : public chocolate // classe wafer herdando da classe chocolate
{
public:
    double preco(double p, double d, int quantidade) // p preco, d diametro e q quantidade
    {
        double valor;
        valor = (4.26 * quantidade);
        return valor;
    }
};

string hora() // função para obter a data e a hora em que o pedido foi feito
{
    time_t tempo;
    time (&tempo);
    return ctime(&tempo);
}

void imprimirDetalhesPedido(vector<chocolate *> v, vector<string> item, vector<double> p, vector<double> d, vector<int> quantidade, double pesototal, double valortotal, ofstream& arquivo)
{
        cout << hora(); // imprime a data e a hora em que o pedido foi feito
        arquivo << hora(); // escreve no arquivo a data e a hora em que o pedido foi feito
        cout << "Total: " << v.size() << " itens." << endl; // imprime a quantidade total de itens
        arquivo << "Total: " << v.size() << " itens." << endl; // escreve a quantidade total de itens no arquivo
        for (int i=0; i<(int)v.size(); i++)
        {
            double preco = v[i]->preco(p[i],d[i],quantidade[i]); // calcula o preco em cada classe e insere na variavel preco
            cout << item[i] << ": R$ " << fixed << setprecision(2) << preco << endl; // imprime o item
            arquivo << item[i] << ": R$ " << fixed << setprecision(2) << preco << endl; // escreve o item no arquivo
            pesototal = pesototal + p[i]; // calcula o peso total
            valortotal = valortotal + preco; // calcula o valor total
        }
        cout << "Peso total de chocolates (barra ou ovo): " << fixed << setprecision(0) << pesototal << "g" << endl; // imprime o peso total em gramas
        arquivo << "Peso total de chocolates (barra ou ovo): " << fixed << setprecision(0) << pesototal << "g" << endl; // escreve o peso total em gramas no arquivo
        cout << "Valor total: R$ " << fixed << setprecision(2) << valortotal << endl; // imprime o valor total
        arquivo << "Valor total: R$ " << fixed << setprecision(2) << valortotal << endl; // escreve o valor total no arquivo
        cout << endl; // pula linha para ficar mais organizado
        arquivo << endl; // pula linha no arquivo para ficar mais organizado
}

double calcDiametro(double peso) // funcao para calcular diâmetro de um ovo de pascoa
{
    double D;

    D = cbrt((6*peso)/3.14);

    return D;
}

#endif // LOJADECHOCOLATES_HPP_INCLUDED
