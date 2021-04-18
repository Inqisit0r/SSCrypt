// CryptoTesting.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "SSMagma.h"
#include "SSMode.h"
#include <stdio.h>

void ssEncryptBlockMagmaTest()
{
	uint8_t Key[] =
	{ 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
	  0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
	  0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	  0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

	uint64_t a = 0xfedcba9876543210;
	uint64_t b = 0;

	ssEncryptBlockMagma((uint8_t*)&a, Key, (uint8_t*)&b);
	printf("%llx", b);
}

//Сделать проверку для Decrypt

//Переделать
void ssPaddingTest()
{
	uint8_t a1[] = { 0x92, 0xde, 0xf0, 0x6b };
	uint8_t a0[] = { 0x92, 0xde, 0xf0, 0x6b, 0x3c, 0x13 };
	uint8_t b[8] = { 0 };
	ssPadding01(a0, 6, b, 8);
	printf("\nssPadding01 result = ");
	for (int i = 0; i < 8; ++i) {
		if (b[i] >= 0x10)
		{
			printf("%x", b[i]);
		}
		else
		{
			printf("0%x", b[i]);
		}
	}
	ssPadding02(a0, 6, b, 8);
	printf("\nssPadding02 result = ");
	for (int i = 0; i < 8; ++i) {
		if (b[i] >= 0x10)
		{
			printf("%x", b[i]);
		}
		else
		{
			printf("0%x", b[i]);
		}
	}
	ssPadding03(a0, 6, b, 8);
	printf("\nssPadding03 result = ");
	for (int i = 0; i < 8; ++i) {
		if (b[i] >= 0x10)
		{
			printf("%x", b[i]);
		}
		else
		{
			printf("0%x", b[i]);
		}
	}
}

void ssModeECBTest()
{
	int chek = 0x00;
	uint8_t key[] = 
	{ 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 
	  0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 
	  0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 
   	  0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

	uint8_t a0[] =
	{ 0x92, 0xde, 0xf0, 0x6b, 0x3c, 0x13, 0x0a, 0x59,
	  0xdb, 0x54, 0xc7, 0x04, 0xf8, 0x18, 0x9d, 0x20,
	  0x4a, 0x98, 0xfb, 0x2e, 0x67, 0xa8, 0x02, 0x4c,
	  0x89, 0x12, 0x40, 0x9b, 0x17, 0xb5, 0x7e, 0x41 };

	uint8_t a1[] =
	{ 0x2b, 0x07, 0x3f, 0x04, 0x94, 0xf3, 0x72, 0xa0,
	  0xde, 0x70, 0xe7, 0x15, 0xd3, 0x55, 0x6e, 0x48,
	  0x11, 0xd8, 0xd9, 0xe9, 0xea, 0xcf, 0xbc, 0x1e,
	  0x7c, 0x68, 0x26, 0x09, 0x96, 0xc6, 0x7e, 0xfb };

	uint8_t b[32] = { 0 };

	ssModeECB(a0, 32, key, 32, b, 32, 64, ssIdPadding00, ssIdCipherAlgorithmMagma ,0x00);
	for (int i = 0; i < 32; ++i)
	{
		if (b[i] != a1[i])
			chek = 0x01;
	}

	if (chek == 0x00)
		printf("ssEncryptModeECB - OK\n");
	else
		printf("ssEncryptModeECB - ERROR\n");

	ssModeECB(a1, 32, key, 32, b, 32, 64, ssIdPadding00, ssIdCipherAlgorithmMagma, 0x01);
	for (int i = 0; i < 32; ++i)
	{
		if (b[i] != a0[i])
			chek = 0x01;
	}

	if (chek == 0x00)
		printf("ssDecryptModeECB - OK");
	else
		printf("ssDecryptModeECB - ERROR");
}

int main()
{
	ssEncryptBlockMagmaTest();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
