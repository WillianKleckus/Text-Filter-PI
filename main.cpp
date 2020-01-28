#include<iostream>

int inputedImg[4096][4096];

float mask[9][9];

int imgLines, imgColumns, maskNLines, maskNColumns;

char header[5];
int mediaImg[4096][4096];

void getInputImg()
{
	//Ler imagem em imagem.ppm
	char foto[100];
	scanf("%s", &foto);
	
	FILE* file;
	file = fopen(foto , "r");
	
	fscanf(file, "%s", header);
	
	//Pular linha:
	char buffer[100];
	fgets(buffer, 100, file);
	char ignore[1024];
	fgets(ignore, sizeof(ignore), file);
	/////////////

	fscanf(file, "%d", &imgLines);
	fscanf(file, "%d", &imgColumns);
	
	std::cout << "Resolucao: " << imgLines << "x" << imgColumns << '\n';
	
	for(int line = 0; line < imgLines ; line++)
	{
		for(int column = 0; column < imgColumns; column++)
		{
			char inputChar;
			fscanf(file, "%c", &inputChar);
			if(inputChar == '1'){ inputedImg[line][column] = 1; } else if(inputChar == '0'){ inputedImg[line][column] = 0; }
			else{ column--; }
		}
	}
	
	fclose(file);
}

void saveInputImg()
{
	FILE* input;
	
	input = fopen( "input.pbm" , "w+");
	
	fprintf(input, "P1\n#Feita por Willian Mota Oliveira, use GIMP para ver a foto.\n%d %d\n", imgLines, imgColumns);
	
	int endlIndex = 0;
	for(int m = 0; m < imgLines ; m++)
	{
		for(int n = 0; n < imgColumns; n++)
		{
			if(endlIndex == 69){ fprintf(input, "%d\n", inputedImg[m][n]); endlIndex = 0;}
			else{ fprintf(input, "%d", inputedImg[m][n]); endlIndex++;}
		}
		
	}
	
	fclose(input);
	
	std::cout << "Saved original!\n";
}

void saveOutputImg()
{
	FILE* output;
	
	output = fopen( "output.pbm" , "w+");
	
	fprintf(output, "P1\n#Feita por Willian Mota Oliveira, use GIMP para ver a foto.\n%d %d\n", imgLines, imgColumns);
	
	
	int endlIndex = 0;
	for(int line = 0; line < imgLines ; line++)
	{
		for(int column = 0; column < imgColumns; column++)
		{
			if(endlIndex == 69){ fprintf(output, "%d\n", mediaImg[line][column]); endlIndex = 0;}
			else{ fprintf(output, "%d", mediaImg[line][column]); endlIndex++;}
		}
		
	}
	
	fclose(output);
	
	std::cout << "Saved Modified!\n";
}

void setupMediaMask(int l, int c)
{
	maskNLines = l;
	maskNColumns = c;
	
	for(int x = 0 ; x < l; x++)
	{
		for(int y = 0; y < c; y++)
		{
			mask[x][y] = 1.0/(l*c);
		}
	}
}

void fixSaltAndPepper()
{
	int paddingX = (maskNLines - 1)/2.0;
	int paddingY = (maskNColumns - 1)/2.0;
	float threshold = 0.5;
	
	for(int imgX = paddingX; imgX < imgLines - paddingX; imgX++)
	{
		for(int imgY = paddingY; imgY < imgColumns - paddingY; imgY++)
		{
			float resultPixel = 0.0;
			
			for(int maskX = 0; maskX < maskNLines ; maskX++)
			{
				for(int maskY = 0; maskY < maskNColumns; maskY++)
				{
					resultPixel += inputedImg[(imgX - paddingX) + maskX][(imgY - paddingY) + maskY] * mask[maskX][maskY];
				}
			}
			
			//std::cout << resultPixel << "\n";
			
			if(resultPixel > threshold){ mediaImg[imgX][imgY] = 1; } else if(resultPixel <= threshold) { mediaImg[imgX][imgY] = 0; }
			
		}
	}
}

int main()
{
	getInputImg();
	
	setupMediaMask(3,3);
	
	fixSaltAndPepper();
	
	saveInputImg();
	saveOutputImg();
	return 0;
}

