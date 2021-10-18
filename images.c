#include <stdio.h>

 #define TABLESIZE 512


  #define DEBUG    // uncomment for debug mode
 
 // global variables and functions defined in functions.c
 extern int colorPixelSafe [TABLESIZE];
 extern int colorPixel [TABLESIZE];
 extern int safePixelCount;
 extern int allPixelCount;
 extern char colorDescriptions[TABLESIZE][50];

 

 void fillDescription(int r, int g, int b, int index);
 void analysis_display();


 
int main(int argc, char *argv[])
{
	int h,  w;  // height width of image
	int safeS, safeW;  // safe start, safe width
	
	int rgb, rgb9;  // rgb for read in color value,  rgb9 for 3+3+3 bits combined value 

	int i; 
	for (i=0; i<TABLESIZE; i++ )
	{
	   colorPixelSafe[i] = colorPixel[i] = 0;
	}


 	while ( scanf("%d %d %d %d", &w, &h,&safeS, &safeW) != EOF) // try to read first 4 values of each line
	{
		allPixelCount += w*h;
	   printf("scanning pixel data for a new image..... \n");
	   for (i=0; i< w*h ; i++ )
	   {
 	    // use scanf to read in a color and process
	   scanf(" %d", &rgb);

		
		  int r = rgb & 0x00FF0000;
		  r = r >> 16;
		  int g = rgb & 0x0000FF00;
		  g = g >> 8;
		  int b = rgb & 0x000000FF;
			
		  rgb9 = ((r & 0b11100000 )<<1)+ ((g & 0b11100000)>>2) + ((b& 0b11100000)>>5);
		  
		  
		  colorPixel[rgb9]++;
		  
		  
		  fillDescription(r,g,b, rgb9);
	   
				 
	    #ifdef DEBUG //#if defined(DEBUG)
	    { 
	        printf(" processing pixel %d\t%3d %3d %3d (%s)\tConcatenated to [%d].", i, r,g,b,colorDescriptions[rgb9],rgb9);
	       
			 if((i%w)>=safeS && (i%w)<=(safeW+safeS-1)){
	           printf("\tThis is a safe pixel\n");
		 
			   colorPixelSafe[rgb9]++;
			   
			   safePixelCount++;
			   
			 }
	        else printf("\t\tThis is not a safe pixel\n");
	     }
	     #endif

	    } // end for 
       
           printf("\n");
	 } //  end while
     /****************************************************/
	
         analysis_display();
         return 0;
   }
 
     
	  
