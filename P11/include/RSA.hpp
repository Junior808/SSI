#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <cmath> // Log
#include <climits>

class RSA
{
    int p = 0;
    int q = 0;
    int d = 0;
    int Fi = 0;
    int e = 0;
    int n = 0;

    std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<int> primos = {2, 3, 5, 7, 11, 13, 17, 19};
    std::vector<int> mensaje_codificado;
    std::vector<int> mensaje_cifrado;

public:
    RSA(int p_, int q_, int d_);
    ~RSA(){};

    bool test();
    void cifrar(std::string mensaje);
    void write();

private:
    int codificacion(int size_bloque, std::string mensaje);
    long unsigned int exp_rapida(long unsigned int base, int exponente, int primo);
    int test_euclides();
    bool lehman_peralta(int primo);
    int cod_mensaje();
};