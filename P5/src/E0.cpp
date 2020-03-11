#include "E0.hpp"

void E0::generar()
{
    std::bitset<1> zt;
    int caja1 = 0, caja2 = 0;

    caja1 += LFSR1[24] + LFSR2[30] + LFSR3[32] + LFSR4[38];

    caja2 = R1.to_ulong() + caja1;

    std::bitset<2> sumaT2 = caja2 / 2;

    //TODO: Formula PDF
    std::bitset<2> T2 = R1 ^ sumaT2;

    std::bitset<2> T1 = ~R1 ^ T2;
    //

    zt = LFSR1[24] ^ LFSR2[30] ^ LFSR3[32] ^ LFSR4[38] ^ R1[0];
    Z += zt.to_string();

    realimentacion();
}

void E0::realimentacion()
{
}

void E0::insertar_semillas(std::vector<std::string> semillas)
{
    LFSR1 = std::bitset<25>(semillas[0]);
    LFSR2 = std::bitset<31>(semillas[1]);
    LFSR3 = std::bitset<33>(semillas[2]);
    LFSR4 = std::bitset<39>(semillas[3]);
    R1 = std::bitset<2>(semillas[4]);
}
void E0::pos_polinomios(std::vector<std::vector<int>> posiciones)
{
    x1 = posiciones[0];
    x2 = posiciones[1];
    x3 = posiciones[2];
    x4 = posiciones[3];
}