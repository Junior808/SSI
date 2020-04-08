# Práctica 10: Fiat-Shamir.

## Seguridad en Sistemas Informáticos, ULL 19/20

## Damián Eduardo Domínguez De Barros.

---

Una Demostración de Conocimiento Nulo (DCN) es un protocolo criptográfico
mediante el cual un probador P puede convencer a un verificador
V de la posesión de cierta información sin mostrarle nada sobre ella.

En el protocolo Fiat-Shamir, se escogen dos números primos _p_ y _q_ y se
publica _N_, que es el producto de ambos ńumeros.

El probador selecciona un número primo secreto _S_ entre 0 y N. Se publica _V_,
que es el cuadrado de S módulo N.

Después, para cada iteración se selecciona un número primo secreto _X_ entre
0 y N. Se publica _A_ que es el cuadrado de X módulo N.

Como reto, el verificador envía un bit _e_ al probador, que puede valer 0 ó 1.

- En caso de valer 0, el probador debe publicar _Y_ que es X módulo N.
- En caso de valer 1, el probador debe publicar _Y_ que es X\*S módulo N.

- En caso de valer 0, el verificador debe comprobar que el cuadrado de _Y_ debe
  coincidir con A módulo N.
- En caso de valer 1, el verificador debe comprobar que el cuadrado de _Y_ debe
  coincidir con A\*V módulo N.
