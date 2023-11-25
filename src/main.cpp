/* Código para uma loja de chocolates

Descrição: O programa pode servir como uma método para que o cliente crie uma lista de compras digitando o nome dos produtos e no final retirar os produtos escolhidos,
os pedidos são armazenados em um arquivo de texto como um histórico de pedidos.

Feito por: Gustavo Allan Jeromine
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <ctime>

using namespace std;

// descobrir qual sistema o usuário está utilizando para limpar o terminal corretamente
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

void mostrarInstrucoesTabelaPrecos() // apenas uma funcao de instrucoes e tabela de precos
{
    cout << "Faca seu pedido, caso escolha barra de chocolate informe somente o peso em gramas." << endl;
    cout << "Caso escolha ovo de pascoa informe o peso e o diametro. " << endl;
    cout << "Caso escolha outros produtos, escolha somente a quantidade (Digite 'F' para finalizar sua lista de compras): " << endl;
    cout << endl << "Tabela de Precos:" << endl;
    cout << "Chocolate: R$0.20 por grama" << endl;
    cout << "Ovo de Pascoa: R$0.20 por grama + R$0.40 por cm de diametro" << endl;
    cout << "Trufa: R$3.90 por unidade" << endl;
    cout << "Caixa de Bombons: R$14.79 por unidade" << endl;
    cout << "Biscoito: R$3.57 por unidade" << endl;
    cout << "Wafer: R$4.26 por unidade" << endl;
    cout << endl << "Escolha o produto da seguinte forma: chocolate, ovo, trufa, caixa, biscoito, wafer." << endl;
}

string hora() // função para obter a data e a hora em que o pedido foi feito
{
    time_t tempo;
    time (&tempo);
    return ctime(&tempo);
}

int main()
{
    vector<chocolate *> v; // vetor da classe chocolate
    vector<string> item; // vetor para pegar o nome de cada item
    string s; // string de leitura do item escolhido pelo usuario
    vector<double> p; // vetor p indicando peso (utilizado somente em chocolates)
    vector<double> d; // vetor d indicando diametro (utilizado somente em ovos de pascoa)
    vector<int> quantidade; // vetor quantidade (não é utilizado em ovo de pascoa e chocolate)
    int qtd; // quantidade (não é utilizado em ovo de pascoa e chocolate)
    double peso, diametro; // peso (utilizado somente em chocolates) e diametro (utilizado somente em ovos de pascoa)
    double pesototal=0; // peso total iniciado em 0 para soma
    double valortotal=0; // valor total iniciado em 0 para soma
    double preco; // preco é a variavel que recebe o valor da funcao preco de cada classe
    bool continuarComprando = true; // continuarcomprando variavel comeca em true, serve para saber se o usuario quer criar um novo pedido

    ofstream arquivo("historico_de_pedidos.txt", ios::app);  // abre o arquivo em modo append para nao limpar o arquivo

    if (!arquivo.is_open()) // verifica se o arquivo foi aberto com sucesso
    {
        cerr << "Erro ao abrir o arquivo." << endl; // gera um erro
        return 1; // para indicar que deu errado
    }

    while(continuarComprando == true) // inicia um loop em true para saber se o usuario quer criar novos pedidos
    {
        system(CLEAR_COMMAND.c_str());  // limpa o terminal usando o comando correto dependendo do sistema
        mostrarInstrucoesTabelaPrecos(); // mostra todas instrucoes e tabela de precos

        cin >> s; // usuario digita o item que deseja
        while (s != "F")
        {
            chocolate *a; // cria um ponteiro da classe chocolate
            if (s == "chocolate")
            {
                cin >> peso; // digita o peso do chocolate
                a = new chocolate();  // cria um objeto da classe chocolate e atribui o endereço desse objeto à variável de ponteiro a
                item.push_back("Chocolate");
            }
            else if (s == "ovo")
            {
                cin >> peso; // digita o peso do ovo de pascoa
                int D = cbrt((6*peso)/3.14); // fórmula para obter o diametro minimo do ovo de Páscoa
                cin >> diametro; // digita o diametro do ovo de pascoa
                while(diametro < D) // se o diametro for menor que o calculado
                {
                    cout << "Por favor digite um valor maior de diametro." << endl; // imprime uma mensagem
                    cin >> diametro; // le o diametro novamente
                }
                a = new ovo(); // cria um objeto da classe ovo e atribui o endereço desse objeto à variável de ponteiro a
                item.push_back("Ovo de pascoa"); // coloca o nome do item no final do vetor item para imprimir o nome da cada item no final
            }
            else if(s == "trufa" || s == "caixa" || s == "biscoito" || s == "wafer")
            {
                cin >> qtd; // le a quantidade do item
                peso = 0; // define peso em 0 para que nao coloque lixo de memoria nos calculos
                if (s == "trufa")
                {
                    a = new trufa(); // cria um objeto da classe trufa e atribui o endereço desse objeto à variável de ponteiro a
                    item.push_back("Trufa"); // coloca o nome do item no final do vetor item para imprimir o nome da cada item no final
                }
                else if (s == "caixa")
                {
                    a = new caixaDeBombons(); // cria um objeto da classe caixaDeBombons e atribui o endereço desse objeto à variável de ponteiro a
                    item.push_back("Caixa de bombons"); // coloca o nome do item no final do vetor item para imprimir o nome da cada item no final
                }
                else if (s == "biscoito")
                {
                    a = new biscoito(); // cria um objeto da classe biscoito e atribui o endereço desse objeto à variável de ponteiro a
                    item.push_back("Biscoito/Cookies"); // coloca o nome do item no final do vetor item para imprimir o nome da cada item no final
                }
                else if (s == "wafer")
                {
                    a = new wafer(); // cria um objeto da classe wafer e atribui o endereço desse objeto à variável de ponteiro a
                    item.push_back("Wafer"); // coloca o nome do item no final do vetor item para imprimir o nome da cada item no final
                }
            }
            else
            {
                cout << "Produto não existe, tente novamente." << endl; // informa erro se o usuario digitar o nome do item errado
                cin >> s; // digita o nome novamente
                continue; // pular loop
            }

            p.push_back(peso); // peso no final do vetor
            d.push_back(diametro); // diametro no final do vetor
            quantidade.push_back(qtd); // quantidade no final do vetor
            v.push_back(a); // adiciona um ponteiro para um objeto da classe chocolate (ou suas classes derivadas) no final do vetor v

            cin >> s; // usuario digita mais itens para o pedido
        }

        cout << hora(); // imprime a data e a hora em que o pedido foi feito
        arquivo << hora(); // escreve no arquivo a data e a hora em que o pedido foi feito
        cout << "Total: " << v.size() << " itens." << endl; // imprime a quantidade total de itens
        arquivo << "Total: " << v.size() << " itens." << endl; // escreve a quantidade total de itens no arquivo
        for (int i=0; i<(int)v.size(); i++)
        {
            preco = v[i]->preco(p[i],d[i],quantidade[i]); // calcula o preco em cada classe e insere na variavel preco
            cout << item[i] << ": R$ " << fixed << setprecision(2) << preco << endl; // imprime o item
            arquivo << item[i] << ": R$ " << fixed << setprecision(2) << preco << endl; // escreve o item no arquivo
            pesototal = pesototal + p[i]; // calcula o peso total
            valortotal = valortotal + preco; // calcula o valor total
        }
        cout << "Peso total de chocolates (barra ou ovo): " << fixed << setprecision(0) << pesototal << "g" << endl; // imprime o peso total em gramas
        arquivo << "Peso total de chocolates (barra ou ovo): " << fixed << setprecision(0) << pesototal << "g" << endl; // escreve o peso total em gramas no arquivo
        cout << "Valor total: R$ " << fixed << setprecision(2) << valortotal << endl; // imprime o valor total
        arquivo << "Valor total: R$ " << fixed << setprecision(2) << valortotal << endl; // escreve o valor total no arquivo

        cout << "Deseja criar outra lista de compras? (S/N): ";
        char resposta; // cria a variavel resposta em caractere
        cin >> resposta; // recebe a resposta em S/s ou N/n

         if (resposta != 'S' && resposta != 's') // se a resposta for diferente de sim
        {
            continuarComprando = false; // define a variavel continuarcomprando como false e sai do loop
        }
        else // se nao
        {
            // limpa os vetores
            v.clear();
            p.clear();
            d.clear();
            quantidade.clear();
            // limpa as variaveis
            pesototal = 0;
            valortotal = 0;
        }
        cout << endl; // pula linha para ficar mais organizado
        arquivo << endl; // pula linha no arquivo para ficar mais organizado
    }

    arquivo.close(); // fecha o arquivo
    return 0;
}
