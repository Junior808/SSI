# Práctica 9: Diffie-Hellman.

## Seguridad en Sistemas Informáticos, ULL 19/20

## Damián Eduardo Domínguez De Barros.

---

Algoritmo de intercambio de claves Diffie-Hellman.

Las personas que van a intercambiar los valores escogen un número secreto y
seleccionan un número primo _P_ y un alfa _a_ común.

Se eleva _a_ al número secreto elegido y se le aplica el módulo con _P_.

Se intercambian el resultado de la operación y con el resultado de la otra
persona se eleva ese número al secreto elegido inicialmente, realizando también el módulo a la operación.

El número resultante es común para ambas personas.
