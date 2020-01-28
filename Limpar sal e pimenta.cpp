#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include <string>
#include <math.h>

int imagem[4096][4096];

float imagem_mascara_aplicada[4096][4096];

int imagem_limpa[4096][4096];

int x, y;

char comentario[71];

void leitura()
{
	
    //Ler imagem em imagem.pbm
	char foto[100];
	scanf("%s", &foto);
	
	FILE* file;
	file = fopen(foto , "r");
	
	char header[10];
	fscanf(file, "%s", header);
	
	//Pular linha:
	char buffer[100];
	fgets(buffer, 100, file);
	char ignore[1024];
	fgets(ignore, sizeof(ignore), file);
	/////////////
	
	
	//fscanf(file, "%[^\n]\n");
	
	fscanf(file, "%d", &x);
	fscanf(file, "%d", &y);
	
	std::cout << "Resolucao: " << x << "x" << y << '\n';
	
	for(int m = 0; m < x ; m++)
	{
		for(int n = 0; n < y; n++)
		{
			char charLido;
			fscanf(file, "%ch", &charLido);
			if(charLido == '1')
			{
				imagem[m][n] = 1;
			}
			else
			{
				imagem[m][n] = 0;
			}
			//std::cout << imagem[m][n] << " ";
		}
	}
	
	fclose(file);
}

void salvarImagemLimpa()
{
	FILE* imagemSemSalPimenta;
	
	imagemSemSalPimenta = fopen("foto_sem_sal_pimenta.pgm", "w+");
	
	fprintf(imagemSemSalPimenta, "P1\n#Feita por Willian Mota Oliveira, use GIMP para ver a foto.\n%d %d\n", x, y);
	
	for(int m = 0; m < x ; m++)
	{
		for(int n = 0; n < y; n++)
		{
			fprintf(imagemSemSalPimenta, "%d ", imagem_limpa[m][n]);
		}
	}
	
	fclose(imagemSemSalPimenta);
	
	std::cout << "Imagem limpa feita!!\n";
}

void salvarImagemPadrao()
{
	FILE* imagemPadrao;
	
	imagemPadrao = fopen("foto_padrao.pgm", "w+");
	
	fprintf(imagemPadrao, "P1\n#Feita por Willian Mota Oliveira, use GIMP para ver a foto.\n%d %d\n", x, y);
	
	for(int m = 0; m < x ; m++)
	{
		for(int n = 0; n < y; n++)
		{
			fprintf(imagemPadrao, "%d", imagem[m][n]);
		}
	}
	
	fclose(imagemPadrao);
	
	std::cout << "Imagem padrao feita!!\n";
}

void salvarImagemMascarada()
{
	FILE* img_mascarada;
	
	img_mascarada = fopen( "foto_mascarada.pgm" , "w+");
	
	fprintf(img_mascarada, "P1\n#Feita por Willian Mota Oliveira, use GIMP para ver a foto.\n%d %d\n", x, y);
	
	for(int m = 0; m < x ; m++)
	{
		for(int n = 0; n < y; n++)
		{
			fprintf(img_mascarada, "%d ", imagem_mascara_aplicada[m][n]);
		}
	}
	
	fclose(img_mascarada);
}

void setLimiarizacao(int threshHold)
{	
	for(int i = 0; i <= x; i++)
	{
		for(int j = 0 ; j <= y; j++)
		{
			if(imagem_mascara_aplicada[i][j] >= threshHold)
			{ 
			imagem_limpa[i][j]  = 1;
			}
			else
			{
			imagem_limpa[i][j] = 0;
			}
		}
	}
	std::cout << "Limiarização da imagem: Sucesso!!\n";
}

//lorem_noise.pbm
void aplicarMascara()
{
	for(int i = 1 ; i <= x - 1 ; i++)
	{
		for(int j = 1 ; j <= y - 1 ; j++)
		{
			float pixel = 0.0;
			for(int m = 0 ; m < 3; m ++ )
			{
				for(int n = 0 ; n < 3; n ++ )
				{
					pixel += (1/9)*imagem[i + m - 1 ][j + n - 1];
				}
			}
			imagem_mascara_aplicada[i][j] = pixel ;
		}
	}
	
	std::cout << "Mascara aplicada!!\n";
}

int main()
{
	leitura();
	
	std::cout << "Aplicando mascara...\n";
	aplicarMascara();
	
	salvarImagemMascarada();
	
	setLimiarizacao(0.5);
	
	salvarImagemLimpa();
	
	salvarImagemPadrao();
	
	return 0;
}
































