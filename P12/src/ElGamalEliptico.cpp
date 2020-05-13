#include "ElGamalEliptico.hpp"

void ElGamalEliptico::calculoDePuntos()
{
    std::vector<int> x, y;
    int temp;

    for (int i = 0; i < primo; i++)
    {
        temp = ((int)pow(i, 3) + (a * i) + b) % primo;
        x.push_back(temp);
        y.push_back((i * i) % primo);
    }

    for (int i = 0; i < primo; i++)
        for (int j = 0; j < primo; j++)
            if (x[i] == y[j])
                puntos.push_back(std::make_pair(i, j));
}

void ElGamalEliptico::cifrar(int mensaje, std::pair<int, int> punto_base)
{
    std::pair<int, int> punto_codificado = codificar(mensaje);

    std::pair<int, int> aAP = punto_base;
    std::pair<int, int> dBP = punto_base;

    for (int i = 2; i <= aA; i += 2)
        aAP = sumar(aAP, aAP);

    for (int i = 2; i <= dB; i += 2)
        dBP = sumar(dBP, dBP);

    std::pair<int, int> aA_x_dBP = dBP;
    for (int i = 2; i <= (aA * dB); i += 2)
        aA_x_dBP = sumar(aA_x_dBP, aA_x_dBP);

    std::cout << "\naAP: (" << aAP.first << "," << aAP.second << ")";
    std::cout << "\ndBP: (" << dBP.first << "," << dBP.second << ")";
    std::cout << "\naA x dBP: (" << aA_x_dBP.first << "," << aA_x_dBP.second << ")";
    std::cout << "\nPc: (" << punto_codificado.first << "," << punto_codificado.second << ")";

    mensaje_cifrado.push_back(sumar(punto_codificado, aA_x_dBP));
    mensaje_cifrado.push_back(aAP);
}

void ElGamalEliptico::set_claves(int aA_, int dB_)
{
    aA = aA_;
    dB = dB_;
}

std::pair<int, int> ElGamalEliptico::codificar(int mensaje)
{
    int M = 2;
    while (M <= mensaje)
        M *= 2;

    std::cout << "\nM: " << M;

    int h = primo / M;

    std::cout << "\nh: " << h;

    int x = 0, y = 0;
    bool terminar = false;
    for (int j = 0; j < puntos.size(); j++)
    {
        x = (mensaje * h) + j;

        for (int i = 0; i < puntos.size(); i++)
            if (x == puntos[i].first)
            {
                y = puntos[i].second;
                terminar = true;
                break;
            }

        if (terminar)
            break;
    }

    return std::make_pair(x, y);
}

std::pair<int, int> ElGamalEliptico::sumar(std::pair<int, int> PuntoP, std::pair<int, int> PuntoQ)
{
    int lambda;
    if (PuntoP == PuntoQ)
    {
        int numerador = 3 * (PuntoP.first * PuntoP.first) + a;
        int denominador = test_euclides(2 * PuntoP.second);
        lambda = (numerador * denominador) % primo;
    }
    else
    {
        int numerador = PuntoQ.second - PuntoP.second;
        int denominador = test_euclides(PuntoQ.first - PuntoP.first);
        lambda = (numerador * denominador) % primo;
    }

    int x3 = ((lambda * lambda) - PuntoP.first - PuntoQ.first) % primo;
    if (x3 < 0)
        x3 += primo;

    int y3 = (lambda * (PuntoP.first - x3) - PuntoP.second) % primo;
    if (y3 < 0)
        y3 += primo;

    return std::make_pair(x3, y3);
}

int ElGamalEliptico::test_euclides(int numero)
{
    int i = 1;
    std::vector<int> x, z;

    x.push_back(primo);
    x.push_back(numero);

    z.push_back(0);
    z.push_back(1);

    while (x[i - 1] % x[i] != 0)
    {
        x.push_back(x[i - 1] % x[i]);
        z.push_back((-(x[i - 1] / x[i]) * z[i] + z[i - 1]) % primo);
        i++;
    }
    if (x[i] == 1)
    {
        if (z[i] < 0)
            z[i] += primo;

        return z[i];
    }
    return 0;
}

void ElGamalEliptico::write()
{
    std::cout << "\nPuntos: { ";
    for (int i = 0; i < puntos.size(); i++)
        std::cout << "(" << puntos[i].first << "," << puntos[i].second << "), ";

    std::cout << "}\n";

    std::cout << "\nMensaje cifrado: { ";

    std::cout << "(" << mensaje_cifrado[0].first << "," << mensaje_cifrado[0].second << "), ";
    std::cout << "(" << mensaje_cifrado[1].first << "," << mensaje_cifrado[1].second << ")}\n";
}
