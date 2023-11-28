/* Código para pedidos em uma loja de chocolates

Descrição: O programa pode servir como um método para que o cliente crie uma lista de compras digitando o nome dos produtos e no final retirar os produtos escolhidos,
os pedidos são armazenados em um arquivo de texto como um histórico de pedidos.

Feito por: Gustavo Allan Jeromine
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "lojadechocolates.hpp"

using namespace std;

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
        while (s != "F") // enquanto o usuario nao digita F
        {
            chocolate *a; // cria um ponteiro da classe chocolate
            if (s == "chocolate")
            {
                cin >> peso; // digita o peso do chocolate
                a = new chocolate();  // cria um objeto da classe chocolate e atribui o endereço desse objeto à variável de ponteiro a
                item.push_back("Chocolate"); // coloca o nome do item no final do vetor item para imprimir o nome da cada item no final
            }
            else if (s == "ovo")
            {
                cin >> peso; // digita o peso do ovo de pascoa
                double D = calcDiametro(peso); // chama a funcao de calcular diametro e coloca o resultado na variavel D
                cin >> diametro; // digita o diametro do ovo de pascoa
                while(diametro < D) // se o diametro for menor que o calculado
                {
                    cout << "Por favor digite um valor maior de diametro. Deve ser maior que " << D << endl; // imprime uma mensagem
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

        imprimirDetalhesPedido(v, item, p, d, quantidade, pesototal, valortotal, arquivo); // Imprime os detalhes finais do pedido

        cout << "Deseja criar outra lista de compras? (S/N): ";
        char resposta; // cria a variavel resposta em caractere
        cin >> resposta; // recebe a resposta em S/s ou N/n

         if (resposta != 'S' && resposta != 's') // se a resposta for nao
        {
            continuarComprando = false; // define a variavel continuarcomprando como false e sai do loop
        }
        else // se sim
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
    }

    for (int i = 0; i < v.size(); ++i) // desalocando a memória dos objetos
    {
        delete v[i];
    }
    arquivo.close(); // fecha o arquivo
    return 0;
}
