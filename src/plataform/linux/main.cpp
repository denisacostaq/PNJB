#include "../../portable/AppDelegate.h"

#include <cstdio>

/*! You can use the command line for especific resolution.
	@brief The default value is same as denisacostaq parameter
*/
int main(int argc, char **argv)
{

     // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CC_OPENGL_VIEW_;
    int width = 320;
    int height = 480;
	if(argc >1){
		if(strcmp(argv[1],"z10") == 0)
		{
			printf("Z10  :  720 x 1280");
			width = 720;
			height = 1280;
		}
		else if(strcmp(argv[1],"s2") == 0)
		{
			printf("Galaxy S2  :  480 x 800");
			width = 480;
			height = 800;
		}
		else if(strcmp(argv[1],"iphone5") == 0)
		{
			printf("iphone5 :  640 x 1136");
			width = 640;
			height = 1136;
		}
		else if(strcmp(argv[1],"iphone4") == 0)
		{
			printf("iphone4  :  640 x 960");
			width = 640;
			height = 960;
		}
		else if(strcmp(argv[1],"denisacostaq") == 0)
		{
			printf("denisacostaq  :  420 x 700");
			width = 420;
			height = 700;
		}
		
		if(strcmp(argv[1],"denisacostaq") != 0)
		{
			printf ("ERROR: only denisacostaq resolution are implemmented\n");
		}
		
	}
    eglView->setFrameSize(width, height);
    return CCApplication::sharedApplication()->run();
}
