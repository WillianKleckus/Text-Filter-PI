#include<cstring>

class Mask{
	private:
		int maskSize = 0;
		int** pixel;
		
	public:
		
		Mask()
		{
			pixel = new int*[13];
			for(int i = 0; i < 13; i++){ pixel[i] = new int[13]; memset(pixel[i], 0, 13); }
		}
		~Mask()
		{
			for(int i = 0; i < 13; i++){ delete [] pixel[i]; }
			delete [] pixel;
		}
		
		void setMaskSize(int size) { maskSize = size; }
		
		int getMaskPixel(int x, int y) { return pixel[x][y]; }
		
		int getMaskSize(){ return maskSize; }
		
		void setCrossMask()
		{
			int padding = (maskSize - 1)/2;
			
			for(int y = 0; y < maskSize; y++)
			{
				for(int x = 0; x < maskSize; x++)
				{
					if(x == padding || y == padding)
					{ pixel[x][y] = 1; }
				}
			}
		}
		
};














