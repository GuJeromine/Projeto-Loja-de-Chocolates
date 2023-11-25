#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class chocolate {
    public:
    virtual double preco(int p, int d)
    {
        double valor;
        valor = (0.20 * p);
        return valor;
    }
};

class ovo : public chocolate {
    public:
    double preco(int p, int d)
    {
        double valor;
        valor = (0.20 * p + 0.40 * d);
        return valor;
    }
};

int main() {

    vector<chocolate *> v;
    string s;
    vector<double> p;
    vector<double> d;
    double peso, diametro;
    double pesototal=0;
    double valortotal=0;
    double preco;

    cin >> s;
    while (s != "F")
    {
        chocolate *a;
        if (s == "chocolate")
        {
            cin >> peso;
            a = new chocolate();
            p.push_back(peso);
            d.push_back(diametro);
            v.push_back(a);
        }
        else if (s == "ovo")
        {
            cin >> peso;
            cin >> diametro;
            a = new ovo();
            p.push_back(peso);
            d.push_back(diametro);
            v.push_back(a);
        }
        cin >> s;
    }

    cout << "Total: " << v.size() << " itens." << endl;
    for (int i=0;i<(int)v.size();i++)
    {
        preco = v[i]->preco(p[i],d[i]);
        cout << "Item " << i+1 << ": R$ " << fixed << setprecision(2) << preco << endl;
        pesototal = pesototal + p[i];
        valortotal = valortotal + preco;
    }
    cout << "Peso total: " << fixed << setprecision(0) << pesototal << "g" << endl;
    cout << "Valor total: R$ " << fixed << setprecision(2) << valortotal << endl;

    return 0;
}
