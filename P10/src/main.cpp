#include <iostream>

void fiat_shamir(int p, int q, int s, int x_1, int x_2, int bit_e, int iteraciones)
{

    int n = p * q;

    std::cout << "------------------Canal público------------------\n";
    std::cout << "N: " << n;
    std::cout << "\n-------------------------------------------------\n";

    std::cout << "------------------A------------------\n";
    std::cout << "Número secreto S: " << s;
    std::cout << "\n-------------------------------------\n";

    unsigned long int v = (s * s) % n;

    std::cout << "------------------Canal público------------------\n";
    std::cout << "[A] - V vale " << v;
    std::cout << "\n-------------------------------------------------\n";

    unsigned long int y, x = x_1;
    for (int i = 0; i < iteraciones; i++)
    {
        std::cout << "------------------Iteración " << i << "------------------\n";

        std::cout << "------------------A------------------\n";
        std::cout << "Número secreto X: " << x;
        std::cout << "\n-------------------------------------\n";

        unsigned long int a = (x * x) % n;
        std::cout << "------------------Canal público------------------\n";
        std::cout << "[A] - A vale " << a;
        std::cout << "\n[B] - Pues calcula con esto: " << bit_e;
        std::cout << "\n-------------------------------------------------\n";

        if (bit_e == 0)
        {
            y = x % n;
            std::cout << "------------------Canal público------------------\n";
            std::cout << "[A] - Me da esto: " << y;
            std::cout << "\n-------------------------------------------------\n";

            std::cout << "------------------B------------------\n";
            std::cout << "Y^2 (mod N) = " << (y * y) % n << " debería coincidir con A (mod N) = " << a;
            std::cout << ".\n-------------------------------------\n";

            if (((y * y) % n) == a)
            {
                std::cout << "------------------Canal público------------------\n";
                std::cout << "[B]: ¡Correcto!";
                std::cout << "\n-------------------------------------------------\n";
            }
            else
            {
                std::cout << "------------------Canal público------------------\n";
                std::cout << "[B]: ¡ERROR!";
                std::cout << "\n-------------------------------------------------\n";
            }
        }
        else
        {
            y = (x * s) % n;
            std::cout << "------------------Canal público------------------\n";
            std::cout << "[A]: - Me da esto: " << y;
            std::cout << "\n-------------------------------------------------\n";

            std::cout << "------------------B------------------\n";
            std::cout << "Y^2 (mod N) = " << (y * y) % n << " debería coincidir con A*V (mod N) = " << (a * v) % n;
            std::cout << ".\n-------------------------------------\n";

            if (((y * y) % n) == (a * v) % n)
            {
                std::cout << "------------------Canal público------------------\n";
                std::cout << "[B]: ¡Correcto!";
                std::cout << "\n-------------------------------------------------\n";
            }
            else
            {
                std::cout << "------------------Canal público------------------\n";
                std::cout << "[B]: ¡ERROR!";
                std::cout << "\n-------------------------------------------------\n";
            }
        }
        x = x_2;
        bit_e++;
    }
}

int main()
{
    fiat_shamir(7, 5, 3, 16, 2, 0, 2);
    fiat_shamir(683, 811, 43215, 16785, 2, 1, 1);
}