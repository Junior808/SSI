# Práctica 6: Multiplicación en SNOW 3G y AES.

## Seguridad en Sistemas Informáticos, ULL 19/20

## Damián Eduardo Domínguez De Barros.

---

En SNOW 3G las dos multiplicaciones de 32 bits por 32 bits implicadas en el LFSR
se corresponden con productos de polinomios en módulo x^8 + x^7 + x^5 + x^3 + 1,
que pueden ser implementadas como una sucesión de desplazamientos de bytes y XORs
con el byte A9(16)=10101001(2).

En AES la multiplicación de bytes utilizada se corresponde con el producto de
polinomios en módulo x^8 + x^4 + x^3 + x + 1, que puede ser implementado como
una sucesión de desplazamientos de bytes y XORs con el byte 1B(16)=00011011(2).

En ambos casos, implica aplicar operación distributiva sobre los dos bytes
multiplicandos, usando para ello el byte de menor peso, y luego para cada bit 1 de
ese byte, desplazar a izquierda el otro byte, de forma que cada vez que su bit más
significativo antes del desplazamiento sea 1, hay que hacer, tras el desplazamiento,
una XOR bit a bit con el byte A9 o 1B.
