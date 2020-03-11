#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <math.h>

class E0
{
    // LFSR y posiciones para hacer XOR.
    std::bitset<25> LFSR1;
    std::vector<int> x1;

    std::bitset<31> LFSR2;
    std::vector<int> x2;

    std::bitset<33> LFSR3;
    std::vector<int> x3;

    std::bitset<39> LFSR4;
    std::vector<int> x4;

    std::bitset<2> R1;
    // std::bitset<2> R2;

    std::string Z;

public:
    E0(){};
    ~E0(){};

    void generar();

    void insertar_semillas(std::vector<std::string> semillas);
    void pos_polinomios(std::vector<std::vector<int>> posiciones);

    void write();
    std::string get_Z() { return Z; };

private:
    void desplazar(std::bitset<1> &xt, int lfsr_x);
    void realimentacion();
};