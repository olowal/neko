#include "ImageConverter.h"

int main(int argc, char* argv[])
{
	neko::ImageConverter imageConverter;
	imageConverter.Convert();
	printf("Hello\n");
	ASSERT(false);
	return 0;
}