#include<iostream>
#include<cstring>
#include "mask.h"
#include "image.h"

int main()
{
	char nome[50];
	scanf("%s", nome);
	
	Mask mask;
	mask.setMaskSize(3);
	mask.setCrossMask();
	
	Image input;
	input.loadImage(nome);
	//input.saveImage("input image test.pbm");
	
	Image average = input.getAverageImage();
	average.saveImage("average image.pbm");
	
	Image eroded = average.erodeImage(mask);
	eroded.saveImage("eroded image.pbm");
	
	Image dilated = eroded.dilatateImage(mask);
	dilated.saveImage("dilated image.pbm");
	
	
	
	return 0;
}

