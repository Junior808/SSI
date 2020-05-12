#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <climits>

class ElGamalEliptico
{
    int a;
    int b;
    int primo;
    int aA;
    int dB;
    std::vector<std::pair<int, int>> puntos;
    std::vector<std::pair<int, int>> mensaje_cifrado;

public:
    ElGamalEliptico(int a_, int b_, int primo_) : a(a_), b(b_), primo(primo_) { calculoDePuntos(); };
    ~ElGamalEliptico(){};

    void cifrar(int mensaje, std::pair<int, int> punto_base);
    void set_claves(int aA_, int dB_);
    void write();

private:
    void calculoDePuntos();
    std::pair<int, int> codificar(int mensaje);
    std::pair<int, int> sumar(std::pair<int, int> PuntoP, std::pair<int, int> PuntoQ);
    int test_euclides(int numero);
};