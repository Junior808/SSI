#include "RSA.hpp"

RSA::RSA(int p_, int q_, int d_) : p(p_), q(q_), d(d_)
{
    Fi = (p - 1) * (q - 1);
    n = p * q;
}

bool RSA::test()
{
    bool pasar = true;

    pasar = lehman_peralta(p);
    if (!pasar)
    {
        std::cout << "P no es primo.\n";
        return false;
    }

    pasar = lehman_peralta(q);
    if (!pasar)
    {
        std::cout << "Q no es primo.\n";
        return false;
    }

    e = test_euclides();
    if (e == 0)
    {
        std::cout << "D no es primo con Fi(n).\n";
        return false;
    }

    return true;
}

void RSA::cifrar(std::string mensaje)
{
    int size_bloque = (int)std::log(n) / (int)std::log(alfabeto.size());
    std::cout << "Tamaño del bloque: " << size_bloque << "\n";

    int temp = 0;
    for (int i = 0; i < mensaje.size(); i++)
    {
        std::string bloque_mensaje = mensaje.substr(i, size_bloque);
        temp = codificacion(size_bloque, bloque_mensaje);
        mensaje_codificado.push_back(temp);
        mensaje_cifrado.push_back(exp_rapida(temp, e, n));
        i += size_bloque - 1;
    }
}

int RSA::codificacion(int size_bloque, std::string mensaje)
{
    int resultado = 0;
    for (int i = 0; i < size_bloque; i++)
    {
        resultado += alfabeto.find(mensaje[i]) * exp_rapida(alfabeto.size(), size_bloque - (i + 1), INT_MAX);
    }
    return resultado;
}

long unsigned int RSA::exp_rapida(long unsigned int base, int exponente, int primo)
{
    std::string cad();
    long unsigned int resultado = 1, y = base % primo;

    while ((exponente > 0) && (y > 1))
    {
        if (exponente % 2) // Impar
        {
            resultado = (resultado * y) % primo;
            exponente--;
        }
        else
        {
            y = (y * y) % primo;
            exponente /= 2;
        }
    }

    return resultado;
}

int RSA::test_euclides()
{
    int i = 1;
    std::vector<int> x, z;

    x.push_back(Fi);
    x.push_back(d);

    z.push_back(0);
    z.push_back(1);

    while (x[i - 1] % x[i] != 0)
    {
        x.push_back(x[i - 1] % x[i]);
        z.push_back((-(x[i - 1] / x[i]) * z[i] + z[i - 1]) % Fi);
        i++;
    }
    if (x[i] == 1)
    {
        if (z[i] < 0)
            z[i] += Fi;

        return z[i];
    }
    return 0;
}

bool RSA::lehman_peralta(int primo)
{
    //Comprobar que no es divisible por ningún primo pequeño
    for (int i = 0; i < primos.size(); i++)
        if ((primo % primos[i] == 0) && (primo != primos[i]))
            return false;

    //Enteros aleatorios entre 2 y p-1
    std::vector<int> aleatorios;
    std::random_device rd;
    std::uniform_int_distribution<> distr(2, primo - 1);

    for (int i = 0; i < 6; i++)
        aleatorios.push_back(distr(rd));

    // Calcular Ai^((p-1)/2) % p. Si todos dan 1 es compuesto.
    bool compuesto = true;
    for (int i = 0; i < aleatorios.size(); i++)
        if (exp_rapida(aleatorios[i], (p - 1) / 2, p) != 1)
        {
            compuesto = false;
            break;
        }

    if (compuesto)
        return false;

    // Si existe un i tal que Ai^((p-1)/2) % p != -1, es compuesto.
    int temp = 0;
    for (int i = 0; i < aleatorios.size(); i++)
    {
        temp = exp_rapida(aleatorios[i], (p - 1) / 2, p);
        if (temp != 1)
            temp -= p;

        if ((temp != -1) && (temp != 1))
            return false;
    }

    //Tal vez es primo
    return true;
}

void RSA::write()
{
    std::cout << "D:" << d << "\n";
    std::cout << "Fi:" << Fi << "\n";
    std::cout << "E:" << e << "\n";
    std::cout << "N:" << n << "\n";

    std::cout << "Mensaje codificado: ";
    for (int i = 0; i < mensaje_codificado.size(); i++)
    {
        std::cout << mensaje_codificado[i] << " ";
    }

    std::cout << "\nMensaje cifrado: ";
    for (int i = 0; i < mensaje_cifrado.size(); i++)
    {
        std::cout << mensaje_cifrado[i] << " ";
    }
    std::cout << "\n";
}
