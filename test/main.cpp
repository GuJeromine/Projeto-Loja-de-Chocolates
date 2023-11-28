#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "lojadechocolates.hpp"

using namespace std;
using namespace Catch;

TEST_CASE("Preço da Barra de Chocolate", "[chocolate]") {
    chocolate barra;
    double preco = barra.preco(100, 0, 0); // peso 100
    REQUIRE(preco == Approx(20.0)); // Approx porque a variavel é double
}

TEST_CASE("Preço do Ovo de Páscoa", "[ovo]") {
    ovo ovoPascoa;
    double preco = ovoPascoa.preco(100, 10, 0); // peso 100 diametro 10
    REQUIRE(preco == Approx(24.0)); // Approx porque a variavel é double
}

TEST_CASE("Preço da Trufa", "[trufa]") {
    trufa trufa;
    double preco = trufa.preco(0, 0, 5); // quantidade 5
    REQUIRE(preco == Approx(19.5)); // Approx porque a variavel é double
}

TEST_CASE("Preço da Caixa de Bombons", "[caixaDeBombons]") {
    caixaDeBombons caixa;
    double preco = caixa.preco(0, 0, 2); // quantidade 2
    REQUIRE(preco == Approx(29.58)); // Approx porque a variavel é double
}

TEST_CASE("Preço do Biscoito", "[biscoito]") {
    biscoito biscoito;
    double preco = biscoito.preco(0, 0, 3); // quantidade 3
    REQUIRE(preco == Approx(10.71)); // Approx porque a variavel é double
}

TEST_CASE("Preço do Wafer", "[wafer]") {
    wafer wafer;
    double preco = wafer.preco(0, 0, 4); // quantidade 4
    REQUIRE(preco == Approx(17.04)); // Approx porque a variavel é double
}

TEST_CASE("Cálculo do Diâmetro", "[calcDiametro]") {
    double diametro = calcDiametro(100); // peso 100g
    REQUIRE(diametro == Approx(5.7597).margin(0.0001)); // Approx porque a variavel é double e margin para ter uma margem de erro, pois o resultado tem muitas casas decimais
}

TEST_CASE("Imprimir Detalhes do Pedido", "[imprimirDetalhesPedido]") {
    ofstream arquivo("historico_de_pedidos.txt", ios::app);  // abre o arquivo em modo append para nao limpar o arquivo
    vector<chocolate *> v;
    vector<string> item = {"chocolate", "ovo", "trufa"};
    vector<double> p = {100, 200, 0}; // pesos 100 200 e 0
    vector<double> d = {0, 10, 0}; // diametro 0 10 e 0
    vector<int> quantidade = {0, 0, 5}; // quantidade 0 0 e 5
    double pesototal = 0;
    double valortotal = 0;

    chocolate *a;
    a = new chocolate();
    v.push_back(a);
    a = new ovo();
    v.push_back(a);
    a = new trufa();
    v.push_back(a);

    imprimirDetalhesPedido(v, item, p, d, quantidade, pesototal, valortotal, arquivo); // não é possível fazer testes com valores, pois a funcao é void, somente verificacao de saida
}
