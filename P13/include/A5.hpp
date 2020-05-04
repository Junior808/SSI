#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <math.h>

class A5
{
    // LFSR y posiciones para hacer XOR.
    std::vector<std::bitset<1>> R1;
    std::vector<int> x1;

    std::vector<std::bitset<1>> R2;
    std::vector<int> x2;

    std::vector<std::bitset<1>> R3;
    std::vector<int> x3;

    std::string Z;
    //Posiciones función mayoría.
    int a = 0;
    int b = 0;
    int c = 0;

public:
    A5(){};
    ~A5(){};

    void cifrar();

    void insertar_semillas(std::vector<std::string> semillas);

    void pos_mayoria(std::vector<int> posiciones);
    void pos_polinomios(std::vector<std::vector<int>> posiciones);

    void write();
    std::string get_Z() { return Z; };

private:
    void desplazar(std::bitset<1> &xt, int lfsr_x);
    void mayoria(std::bitset<1> &at, std::bitset<1> &bt, std::bitset<1> &ct);
};