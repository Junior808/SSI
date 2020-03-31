# Práctica 7: Rijndael (AES).

## Seguridad en Sistemas Informáticos, ULL 19/20

## Damián Eduardo Domínguez De Barros.

---

# Introducción

El Rijndael, también conocido como AES es un algoritmo de cifrado por bloques siendo el estándar actual desde 2002.

AES tiene un tamaño de bloque fijo de 128 bits y tamaños de llave de 128, 192 o 256 bits. Trataremos el caso de 128 bits.

- Pseudocódigo.
  - Expansión de clave.
  - Primera iteración:
    - AddRoundKey
  - Resto:
    - SubBytes.
    - ShiftRows.
    - MixColums.
    - AddRoundKey.
  - Iteración final:
    - SubBytes.
    - ShiftRows.
    - AddRoundKey.

## Expansión de clave

Lo primero será expandir la clave para obtener 10 subclaves a partir de la original.

El proceso es el siguiente:

- Cada cuatro columnas se copia la columna y se le hace un _RotWord_, es decir,
  "rotamos" hacia arriba la fila.
- Se le aplica el SubBytes a dicha columna.
- Se hace una XOR con la columna que se encuentre 4 posiciones antes que la
seleccionada y con la constante de iteración ([Rcon](https://en.wikipedia.org/wiki/AES_key_schedule#Rcon)).
- Para las otras 3 columnas se aplica una XOR con la columna anterior y la columna que se encuentre 4 posiciones antes que la seleccionada.

## AddRoundKey

En la primera iteración se realiza una XOR entre el mensaje y la clave original.

Para el resto de operaciones, se realiza tambien la XOR pero ya con el resultado de la anterior iteración y con una de las subclaves generadas al principio.

## SubByte

Cambio de valores de toda la matriz utilizando la Caja S.

## ShiftRow

En este paso se realiza un desplazamiento de bytes a la izquierda diferente en cada fila:

- Para segunda fila, rotamos un byte.
- Para la tercera fila, rotamos dos bytes.
- Para la cuarta fila, rotamos tres bytes.

## MixColums

En este paso se lleva a cabo una operación de mezclado sobre las columnas del mensaje
que se va cifrando, el llamado _state_, combinando los bytes de cada columna haciendo una transformación lineal.
