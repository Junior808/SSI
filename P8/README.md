# Práctica 8: Modos de cifrado en bloque.

## Seguridad en Sistemas Informáticos, ULL 19/20

## Damián Eduardo Domínguez De Barros.

---

En el modo CBC de los cifrados en bloque, cada bloque de texto en claro
se combina antes de cifrarse con una XOR con el bloque de texto previo
ya cifrado.

De esta forma, cada bloque de texto cifrado depende de todos los bloques
de texto en claro anteriores.

Para cifrar los bloques de texto se utiliza AES.

Se ha añadido la opción _Cipher stealing_, una técnica que se usa cuando
la longitud del mensaje no es múltiplo de la longitud del bloque.

Consiste en modificar el procesamiento de los últimos dos bloques de texto
de forma que un trozo del penúltimo bloque cifrado se usa para completar el
último bloque de texto antes de cifrarlo.

Tras esta operación, el penúltimo bloque, al que se le ha "robado" un trozo
de texto pasa a ser el último bloque y el que sería el último pasa a ser el
penúltimo.
