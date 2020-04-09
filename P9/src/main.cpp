#include <iostream>

int pow(int base, int exponente, int primo)
{
    int resultado = 1, y = base % primo;

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

void diffie_hellman(int p, int a, int x_a, int x_b)
{
    int y_a, y_b;

    std::cout << "------------------Canal público------------------\n";
    std::cout << "Número primo: " << p;
    std::cout << "\nAlfa: " << a;
    std::cout << "\n-------------------------------------------------\n";

    std::cout << "------------------A------------------\n";
    std::cout << "Número secreto: " << x_a;
    y_a = pow(a, x_a, p);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------B------------------\n";
    std::cout << "Número secreto: " << x_b;
    y_b = pow(a, x_b, p);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------Canal público------------------\n";
    std::cout << "[A] - Me da " << y_a;
    std::cout << "\n[B] - A mi " << y_b;
    std::cout << "\n-------------------------------------------------\n";

    std::cout << "------------------A------------------\n";
    std::cout << "Entonces K vale " << pow(y_b, x_a, p);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------B------------------\n";
    std::cout << "Entonces K vale " << pow(y_a, x_b, p);
    std::cout << "\n-------------------------------------\n";
}

int main()
{
    diffie_hellman(13, 4, 5, 2);
    diffie_hellman(43, 23, 25, 33);
    diffie_hellman(113, 43, 54, 71);
    // diffie_hellman(53, 2, 29, 19);
}