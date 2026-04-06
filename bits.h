#ifndef BITS_H
#define BITS_H

/*
 * Devuelve el valor del bit nb de buffer.
 * Si nb esta fuera del rango 0..7 devuelve -1.
 */
int Bit(unsigned char buffer, int nb);

/*
 * Setea el bit nb del buffer al valor val.
 * Si nb o val son invalidos, imprime error y devuelve buffer sin cambios.
 */
unsigned char SetBit(unsigned char buffer, int nb, int val);

/*
 * Desplaza buffer nb bits a la izquierda y coloca en la parte baja
 * los nb bits menos significativos de palabra.
 */
unsigned char Concatenar(unsigned char buffer, unsigned char palabra, int nb);

/*
 * Alias de compatibilidad que expone la misma operacion con el nombre corto.
 */
unsigned char Concatena(unsigned char buffer, unsigned char palabra, int nb);

/*
 * Crea una mascara con 1 entre min y max, inclusive.
 * Si los parametros son invalidos, devuelve 0xFF.
 */
unsigned char CrearMascara(int min, int max);

/*
 * Espeja los nb bits menos significativos y deja el resto en 0.
 * Si nb esta fuera de rango, imprime error y devuelve 0.
 */
unsigned char Espejar(unsigned char buffer, int nb);

/*
 * Imprime en pantalla los nb bits menos significativos de buffer.
 */
void VerBinario(unsigned char buffer, int nb);

/*
 * Convierte los primeros nb elementos del vector x en un byte.
 * Solo se toma el bit menos significativo de cada x[i].
 */
unsigned char Vector2Byte(unsigned char *x, int nb);

/*
 * Copia los primeros nb bits de in en x y completa el resto con 0.
 * En error pone todo el vector en 0.
 */
void Byte2Vector(unsigned char in, int nb, unsigned char *x);

/*
 * Extrae el nibble alto o bajo del byte y lo devuelve en la parte baja.
 */
unsigned char Byte2Nibble(unsigned char byte, int alto);

/*
 * Forma un byte con nibbleBajo en los bits 0..3 y nibbleAlto en 4..7.
 */
unsigned char Nibble2Byte(unsigned char nibbleBajo, unsigned char nibbleAlto);

/*
 * Alias de compatibilidad que conserva la variante plural del nombre.
 */
unsigned char Nibbles2Byte(unsigned char nibbleBajo, unsigned char nibbleAlto);

#endif
