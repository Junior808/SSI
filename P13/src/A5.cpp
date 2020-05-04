#include "A5.hpp"

void A5::cifrar()
{
    std::bitset<1> at;
    std::bitset<1> bt;
    std::bitset<1> ct;
    std::bitset<1> zt;

    std::bitset<1> aux;

    for (int i = 0; i < x1.size(); i++)
    {
        aux = R1[x1[i]];
        at ^= aux;
    }
    for (int i = 0; i < x2.size(); i++)
    {
        aux = R2[x2[i]];
        bt ^= aux;
    }
    for (int i = 0; i < x3.size(); i++)
    {
        aux = R3[x3[i]];
        ct ^= aux;
    }

    zt = R1.back() ^ R2.back() ^ R3.back();

    Z += zt.to_string();

    mayoria(at, bt, ct);
}

void A5::mayoria(std::bitset<1> &at, std::bitset<1> &bt, std::bitset<1> &ct)
{
    std::bitset<3> numero;
    std::string numero_;

    numero[2] = R1[a].to_ulong();
    numero[1] = R2[b].to_ulong();
    numero[0] = R3[c].to_ulong();

    numero_ = numero.to_string();
    std::stringstream aux_(numero_);

    int caso = 0;
    aux_ >> caso;

    std::cout << "Caso: " << caso;

    switch (caso)
    {
    case 11:  //011
    case 100: //Paralizo A.
        std::cout << "\nParalizo A\n";
        desplazar(bt, 2);
        desplazar(ct, 3);
        break;
    case 10:  //010
    case 101: // Paralizo B.
        std::cout << "\nParalizo B\n";
        desplazar(at, 1);
        desplazar(ct, 3);
        break;
    case 1:   //001
    case 110: //Paralizo C.
        std::cout << "\nParalizo C\n";
        desplazar(at, 1);
        desplazar(bt, 2);
        break;
    case 000:
    case 111:
        std::cout << "\nNo paralizo\n";
        desplazar(at, 1);
        desplazar(bt, 2);
        desplazar(ct, 3);
        break;
    default:
        std::cout << "\nCaso imposible.\n";
        return;
    }
}

void A5::desplazar(std::bitset<1> &xt, int lfsr_x)
{
    std::vector<std::bitset<1>> R_aux;

    switch (lfsr_x)
    {
    case 1:
        R_aux = R1;
        R1.clear();

        R1.push_back(xt);
        for (int i = 0; i < R_aux.size() - 1; i++)
        {
            R1.push_back(R_aux[i]);
        }
        break;
    case 2:
        R_aux = R2;
        R2.clear();

        R2.push_back(xt);
        for (int i = 0; i < R_aux.size() - 1; i++)
        {
            R2.push_back(R_aux[i]);
        }
        break;
    case 3:
        R_aux = R3;
        R3.clear();

        R3.push_back(xt);
        for (int i = 0; i < R_aux.size() - 1; i++)
        {
            R3.push_back(R_aux[i]);
        }
        break;
    default:
        std::cout << "\nCaso imposible.\n";
        return;
    }
}

void A5::insertar_semillas(std::vector<std::string> semillas)
{
    std::bitset<1> aux;

    for (int i = 0; i < semillas[0].size(); i++)
    {
        aux = semillas[0][i];
        R1.push_back(aux);
    }

    for (int i = 0; i < semillas[1].size(); i++)
    {
        aux = semillas[1][i];
        R2.push_back(aux);
    }

    for (int i = 0; i < semillas[2].size(); i++)
    {
        aux = semillas[2][i];
        R3.push_back(aux);
    }
}

void A5::pos_mayoria(std::vector<int> posiciones)
{
    a = posiciones[0];
    b = posiciones[1];
    c = posiciones[2];
}

void A5::pos_polinomios(std::vector<std::vector<int>> posiciones)
{
    x1 = posiciones[0];
    x2 = posiciones[1];
    x3 = posiciones[2];
}

void A5::write()
{
    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "Polinomio 1: ";
    for (int i = 0; i < R1.size(); i++)
    {
        std::cout << R1[i].to_ullong();
    }
    std::cout << "\nPosiciones realimentación polinomio 1: ";
    for (int i = 0; i < x1.size(); i++)
    {
        std::cout << x1[i] << " ";
    }
    std::cout << "\nPosición fun. mayoría polinomio 1: " << a;
    std::cout << "\n";

    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "Polinomio 2: ";
    for (int i = 0; i < R2.size(); i++)
    {
        std::cout << R2[i].to_ullong();
    }
    std::cout << "\nPosiciones realimentación polinomio 2: ";
    for (int i = 0; i < x2.size(); i++)
    {
        std::cout << x2[i] << " ";
    }
    std::cout << "\nPosición fun. mayoría polinomio 2: " << b;
    std::cout << "\n";
    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "Polinomio 3: ";
    for (int i = 0; i < R3.size(); i++)
    {
        std::cout << R3[i].to_ullong();
    }
    std::cout << "\nPosiciones realimentación polinomio 3: ";
    for (int i = 0; i < x3.size(); i++)
    {
        std::cout << x3[i] << " ";
    }
    std::cout << "\nPosición fun. mayoría polinomio 3: " << c;
    std::cout << "\n";
    std::cout << "----------------------------------------------------------------------\n";
}
