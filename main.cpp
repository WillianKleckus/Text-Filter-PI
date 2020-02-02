#include<iostream>
#include<cstring>


class Image
{	
	private:
		int** pixels;
		int imageX, imageY;
		
		bool checkIfTouch(int x, int y) const
		{
			if(pixels[x][y] == 1 || pixels[x-1][y] == 1 || pixels[x][y-1] == 1 || pixels[x+1][y] == 1 || pixels[x][y+1] == 1){ return true; }
			else { return false; }
		}
		
		bool checkIfInside(int x, int y) const
		{
			if(pixels[x][y] == 1 && pixels[x][y-1] == 1 && pixels[x][y+1] == 1 && pixels[x-1][y] == 1 && pixels[x+1][y] == 1){ return true; }
			else { return false; }
		}
		
		int getAveragePixel(int x,int y) const
		{
			int outputPixel = 0;
			float averageCount = 0;
			
			for(int xIndex = x - 1; xIndex <= x + 1; xIndex++)
			{
				for(int yIndex = y; yIndex <= y + 1; yIndex++)
				{
					averageCount += getPixel(xIndex,yIndex);
				}
			}
			averageCount = averageCount/9.0;
			
			if(averageCount >= 0.2){ return 1; }
			else{ return 0; }
		}
		
	public:
		//constructor
		Image()
		{
			pixels = new int*[4096];
			for(int i = 0; i < 4096; i++){ pixels[i] = new int[4096]; memset(pixels[i], 0, 4096);}
		}
		
		//destructor
		~Image()
		{
			for(int i = 0; i < 4096; i++){ delete [] pixels[i]; }
			delete [] pixels;
		}
		
		Image& operator=(const Image& returned)
		{
			setImageSize(returned.imageX , returned.imageY);
			
			for(int x = 0; x < imageX; x++)
			{
				for(int y = 0; y < imageY; y++)
				{
					setPixel(x,y, returned.getPixel(x,y));
				}
			}
		}
		
		void setPixel(int x, int y , int value) { pixels[x][y] = value; }
		
		void setImageSize(int xSize, int ySize){ imageX = xSize; imageY = ySize; }
		
		int getPixel(int x, int y) const { return pixels[x][y]; }
		
		Image dilatateImage() const
		{
			Image output;
			output.setImageSize(imageX, imageY);
			
			for(int x = 2; x < imageX - 2; x++)
			{
				for(int y = 1; y < imageY - 1; y++)
				{
					if(checkIfTouch(x,y)) { output.setPixel(x,y,1); }
					else{ output.setPixel(x,y,0); }
				}
			}
			
			return output;
		}
		
		Image erodeImage() const
		{
			Image output;
			output.setImageSize(imageX, imageY);
			
			for(int x = 1; x < imageX - 1; x++)
			{
				for(int y = 1; y < imageY - 1; y++)
				{
					if(checkIfInside(x,y)) { output.setPixel(x,y,1); }
					else{ output.setPixel(x,y,0); }
				}
			}
			
			return output;
		}
		
		Image getAverageImage() const
		{
			Image output;
			output.setImageSize(imageX, imageY);
			
			for(int x = 1; x < imageX - 1; x++)
			{
				for(int y = 1; y < imageY - 1; y++)
				{
					int average = getAveragePixel(x,y);
					output.setPixel(x,y,average);
				}
			}
			
			return output;
		}
		
		void saveImage(char* name)
		{
			{
				FILE* savingImg;
				
				savingImg = fopen( name , "w+");
				
				fprintf(savingImg , "P1\n#Feita por Willian Mota Oliveira, use GIMP para ver a foto.\n%d %d\n", imageX, imageY);
				
				int endlIndex = 0;
				for(int line = 0; line < imageY ; line++)
				{
					for(int column = 0; column < imageX; column++)
					{
						if(endlIndex == 69){ fprintf(savingImg, "%d\n", getPixel(column, line)); endlIndex = 0;}
						else{ fprintf(savingImg, "%d", getPixel(column, line)); endlIndex++;}
					}
					
				}
				
				fclose(savingImg);
				
				std::cout << "Saved " << name << " \n";
			}
		}
		
		void loadImage(char* name)
		{
			//Ler imagem em imagem.ppm
			FILE* file;
			file = fopen(name , "r");
			
			char header[5];
			fscanf(file, "%s", header);
			
			//Pular linha:
			char buffer[100];
			fgets(buffer, 100, file);
			char ignore[1024];
			fgets(ignore, sizeof(ignore), file);
			/////////////
		
			fscanf(file, "%d", &imageX);
			fscanf(file, "%d", &imageY);
			
			std::cout << "Resolucao: " << imageX << "x" << imageY << '\n';
			
			for(int line = 0; line < imageY ; line++)
			{
				for(int column = 0; column < imageX; column++)
				{
					char inputChar;
					fscanf(file, "%c", &inputChar);
					if(inputChar == '1'){ setPixel(column, line, 1); } else if(inputChar == '0'){ setPixel(column, line, 0); }
					else{ column--; }
				}
			}
			
			fclose(file);
		}
};

int main()
{
	char nome[50];
	scanf("%s", nome);
	
	Image input;
	input.loadImage(nome);
	//input.saveImage("input image test.pbm");
	
	Image average = input.getAverageImage();
	average.saveImage("average image.pbm");
	
	Image eroded = average.erodeImage();
	eroded.saveImage("eroded image.pbm");
	
	Image dilated = eroded.dilatateImage();
	dilated.saveImage("dilated image.pbm");
	
	
	
	return 0;
}

