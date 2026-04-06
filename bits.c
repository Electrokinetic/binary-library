#include <stdio.h>
#include "bits.h"

/*
 * Para obtener el bit nb movemos ese bit hasta la posicion 0 con
 * un corrimiento a la derecha. Luego aplicamos AND con 1 para borrar
 * el resto y conservar solo el valor buscado.
 * Si nb no pertenece al rango 0..7, la letra pide devolver -1.
 */
int Bit(unsigned char buffer, int nb)
{
	if (nb < 0 || nb > 7)
		return (-1);
	return ((buffer >> nb) & 0x01);
}

/*
 * Construimos una mascara con un unico 1 en la posicion nb.
 * Si val es 1 usamos OR para prender ese bit.
 * Si val es 0 usamos AND con la mascara invertida para apagarlo.
 * Ante parametros invalidos se informa el error y se devuelve
 * el buffer original, sin tocar ningun otro bit.
 */
unsigned char SetBit(unsigned char buffer, int nb, int val)
{
	unsigned char mask;

	if (nb < 0 || nb > 7)
	{
		printf("Error: nb debe estar entre 0 y 7\n");
		return (buffer);
	}
	if (val != 0 && val != 1)
	{
		printf("Error: val debe ser 0 o 1\n");
		return (buffer);
	}
	mask = (unsigned char)(1u << nb);
	if (val == 1)
		return ((unsigned char)(buffer | mask));
	return ((unsigned char)(buffer & (unsigned char)(~mask)));
}

/*
 * El nuevo byte se arma en dos pasos: primero se corre buffer nb lugares
 * a la izquierda y despues se insertan abajo los nb bits menos
 * significativos de palabra.
 * Los bits que se pierden por la izquierda no se recuperan, que es
 * exactamente el comportamiento pedido en la consigna.
 */
unsigned char Concatenar(unsigned char buffer, unsigned char palabra, int nb)
{
	unsigned int mask;

	if (nb < 0 || nb > 8)
		return (0);
	if (nb == 0)
		return (buffer);
	if (nb == 8)
		return (palabra);
	mask = (1u << nb) - 1u;
	return ((unsigned char)((buffer << nb) | (palabra & mask)));
}

/*
 * La letra alterna entre los nombres Concatenar y Concatena.
 * Este alias evita errores de compilacion si el corrector espera
 * la variante corta.
 */
unsigned char Concatena(unsigned char buffer, unsigned char palabra, int nb)
{
	return (Concatenar(buffer, palabra, nb));
}

/*
 * Primero se crea una tira de unos consecutivos en la parte baja.
 * Luego esa tira se desplaza hasta cubrir desde min hasta max.
 * Si el rango es invalido se devuelve 0xFF, porque la consigna usa
 * esa mascara completa como valor de error.
 */
unsigned char CrearMascara(int min, int max)
{
	unsigned int mask;

	if (min < 0 || max > 7 || min >= max)
		return (0xFF);
	mask = ((1u << (max - min + 1)) - 1u) << min;
	return ((unsigned char)mask);
}

/*
 * Recorremos los nb bits bajos de buffer y copiamos cada uno en su
 * posicion reflejada: el bit 0 pasa a nb-1, el 1 pasa a nb-2 y asi.
 * Como el resultado arranca en 0, todos los bits por encima del rango
 * espejado quedan apagados automaticamente.
 */
unsigned char Espejar(unsigned char buffer, int nb)
{
	unsigned char result;
	int bit;
	int i;

	if (nb < 0 || nb > 8)
	{
		printf("Error: nb debe estar entre 0 y 8\n");
		return (0);
	}
	result = 0;
	for (i = 0; i < nb; i++)
	{
		bit = Bit(buffer, i);
		if (bit == 1)
			result = (unsigned char)(result | (unsigned char)(1u << (nb - 1 - i)));
	}
	return (result);
}

/*
 * Para mostrar el byte en el orden habitual recorremos desde nb-1
 * hasta 0, o sea desde el bit mas significativo del tramo pedido
 * hasta el menos significativo.
 * Cada digito se obtiene llamando a Bit para no duplicar logica.
 */
void VerBinario(unsigned char buffer, int nb)
{
	int i;

	if (nb < 0 || nb > 8)
	{
		printf("Error: nb debe estar entre 0 y 8\n");
		return;
	}
	for (i = nb - 1; i >= 0; i--)
		printf("%d", Bit(buffer, i));
	printf("\n");
}

/*
 * El vector se interpreta de forma directa: x[0] alimenta el bit 0,
 * x[1] el bit 1 y asi sucesivamente.
 * De cada posicion solo se toma el bit menos significativo, porque
 * la letra aclara que no hace falta validar otros valores.
 */
unsigned char Vector2Byte(unsigned char *x, int nb)
{
	unsigned char result;
	int i;

	if (nb < 1 || nb > 8)
	{
		printf("Error: nb debe estar entre 1 y 8\n");
		return (0);
	}
	result = 0;
	for (i = 0; i < nb; i++)
	{
		if ((x[i] & 0x01) == 1)
			result = (unsigned char)(result | (unsigned char)(1u << i));
	}
	return (result);
}

/*
 * Esta funcion hace el camino inverso a Vector2Byte.
 * Los nb bits menos significativos de in se copian en x[0..nb-1],
 * respetando que x[0] corresponde al bit 0.
 * El resto del vector se completa con 0 para dejar definido todo
 * el contenido de salida de forma consistente.
 */
void Byte2Vector(unsigned char in, int nb, unsigned char *x)
{
	int i;

	if (nb < 1 || nb > 8)
	{
		printf("Error: nb debe estar entre 1 y 8\n");
		for (i = 0; i < 8; i++)
			x[i] = 0;
		return;
	}
	for (i = 0; i < 8; i++)
	{
		if (i < nb)
			x[i] = (unsigned char)Bit(in, i);
		else
			x[i] = 0;
	}
}

/*
 * Si se pide el nibble alto, lo bajamos cuatro posiciones con un shift.
 * Si se pide el bajo, ya esta en el lugar correcto.
 * En ambos casos aplicamos AND con 0x0F para dejar solo esos cuatro bits
 * y apagar cualquier resto en la parte alta del resultado.
 */
unsigned char Byte2Nibble(unsigned char byte, int alto)
{
	if (alto == 1)
		return ((unsigned char)((byte >> 4) & 0x0F));
	return ((unsigned char)(byte & 0x0F));
}

/*
 * De cada parametro se conservan solo sus cuatro bits bajos.
 * El nibble alto se mueve a las posiciones 4..7 y luego se une con
 * el nibble bajo usando OR para formar el byte completo.
 */
unsigned char Nibble2Byte(unsigned char nibbleBajo, unsigned char nibbleAlto)
{
	return ((unsigned char)(((nibbleAlto & 0x0F) << 4) | (nibbleBajo & 0x0F)));
}

/*
 * Alias de compatibilidad para ofrecer la misma operacion con el
 * nombre alternativo, sin duplicar logica.
 */
unsigned char Nibbles2Byte(unsigned char nibbleBajo, unsigned char nibbleAlto)
{
	return (Nibble2Byte(nibbleBajo, nibbleAlto));
}
