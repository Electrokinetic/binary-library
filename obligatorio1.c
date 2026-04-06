#include <stdio.h>
#include "bits.h"

int main(void)
{
	unsigned char buffer;
	unsigned char codigo;
	unsigned char mask;
	unsigned char nibbleA;
	unsigned char nibbleB;
	unsigned char res;
	unsigned char vect[8];
	int i;

	buffer = 0xFF;
	mask = 0xFF;
	codigo = 0x05;

	printf("VerBinario(5,5): ");
	VerBinario(codigo, 5);
	printf("VerBinario(5,8): ");
	VerBinario(codigo, 8);
	printf("Bit(13,0)=%d Bit(13,2)=%d Bit(13,4)=%d Bit(13,8)=%d\n",
		Bit(13, 0), Bit(13, 2), Bit(13, 4), Bit(13, 8));

	printf("Concatenar(255,5,8): ");
	buffer = Concatenar(buffer, codigo, 8);
	VerBinario(buffer, 8);
	printf("Concatenar(3,1,2) = %u\n", (unsigned int)Concatenar(3, 1, 2));
	printf("Concatenar(5,2,100) = %u\n", (unsigned int)Concatenar(5, 2, 100));

	mask = CrearMascara(1, 3);
	printf("CrearMascara(1,3): ");
	VerBinario(mask, 8);
	mask = CrearMascara(0, 7);
	printf("CrearMascara(0,7): ");
	VerBinario(mask, 8);
	printf("CrearMascara(5,2): ");
	VerBinario(CrearMascara(5, 2), 8);

	mask = SetBit(0, 0, 1);
	printf("SetBit(0,0,1) = %u\n", (unsigned int)mask);
	mask = SetBit(15, 3, 0);
	printf("SetBit(15,3,0) = %u\n", (unsigned int)mask);
	mask = SetBit(10, 2, 5);
	printf("SetBit(10,2,5) = %u\n", (unsigned int)mask);

	printf("Espejar(13,4): ");
	VerBinario(Espejar(13, 4), 8);
	printf("Espejar(10,8): ");
	VerBinario(Espejar(10, 8), 8);
	printf("Espejar(10,100) = %u\n", (unsigned int)Espejar(10, 100));

	printf("Byte2Nibble(175,1): ");
	nibbleA = Byte2Nibble(175, 1);
	VerBinario(nibbleA, 4);
	printf("Byte2Nibble(175,0): ");
	nibbleB = Byte2Nibble(175, 0);
	VerBinario(nibbleB, 4);
	printf("Nibbles2Byte(15,10): ");
	res = Nibbles2Byte(15, 10);
	VerBinario(res, 8);

	Byte2Vector(26, 5, vect);
	printf("Byte2Vector(26,5): ");
	for (i = 0; i < 8; i++)
		printf("%u ", (unsigned int)vect[i]);
	printf("\n");
	printf("Vector2Byte(vect,5): ");
	VerBinario(Vector2Byte(vect, 5), 8);
	Byte2Vector(10, 9, vect);
	printf("Byte2Vector(10,9): ");
	for (i = 0; i < 8; i++)
		printf("%u ", (unsigned int)vect[i]);
	printf("\n");
	printf("Vector2Byte(vect,0): ");
	VerBinario(Vector2Byte(vect, 0), 8);

	printf("Concatena(3,1,2) = %u\n", (unsigned int)Concatena(3, 1, 2));
	printf("Nibble2Byte(12,3): ");
	VerBinario(Nibble2Byte(12, 3), 8);
	return (0);
}
