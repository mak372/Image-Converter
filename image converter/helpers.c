#include "helpers.h"
#include<math.h>
#include<cs50.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{ for(int i = 0;i < height; i++)
     { for(int j = 0; j < width;j++)
           {   int avg = 0;
               RGBTRIPLE dot=image[i][j];
               avg= round((dot.rgbtRed+dot.rgbtGreen+dot.rgbtBlue)/3.0);
               image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
           }

     }
    return;
}
int cap(int value)
{
    return value > 255 ? 255 : value;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{   for(int i = 0;i < height; i++)
       {  for(int j = 0;j < width;j++)
             {
                 RGBTRIPLE dot = image[i][j];
                 int originalRed = dot.rgbtRed;
                 int originalGreen = dot.rgbtGreen;
                 int originalBlue = dot.rgbtBlue;
                 image[i][j].rgbtRed = cap(round (.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
                 image[i][j].rgbtGreen = cap(round (.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
                 image[i][j].rgbtBlue = cap(round(.272 * originalRed + .131 * originalGreen + .189 * originalBlue));

             }


       }

}
void swap(RGBTRIPLE *a,RGBTRIPLE *b)
{
    RGBTRIPLE tmp= *a;
   *a=*b;
   *b=tmp;

}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{ for(int i = 0; i < height; i++)
    { for(int j = 0;j < width / 2; j++)
         {
              swap(&image[i][j],&image[i][width-1-j]);
         }



    }

    return;
}
bool is_valid_pixel(int i,int j, int height ,int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}
RGBTRIPLE get_blur_pix( int i ,int j , int height ,int width,RGBTRIPLE image[height][width] )
{   int redValue = 0; int greenValue = 0; int blueValue =  0;
    int numpix = 0;
    for(int di = -1;di <= 1;  di++)
     { for(int dj = -1;dj <= 1; dj++)
        {   int new_i = i + di;
           int new_j = j + dj;
       if(is_valid_pixel(new_i,new_j,height,width))
         {
             numpix++;
             redValue+=image[new_i][new_j].rgbtRed;
              greenValue+=image[new_i][new_j].rgbtGreen;
               blueValue+=image[new_i][new_j].rgbtBlue;
         }
        }
     }
    RGBTRIPLE blurpix;
    blurpix.rgbtRed = round((float)redValue/numpix);
    blurpix.rgbtGreen = round((float)greenValue/numpix);
    blurpix.rgbtBlue = round((float)blueValue/numpix);
    return blurpix;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{ RGBTRIPLE new_image[height][width];
    for(int i = 0;i < height;i++)
       { for(int j = 0 ;j < width;j++)
            {
            new_image[i][j] = get_blur_pix(i ,j, height, width, image);
            }


       }
     for(int i = 0;i < height;i++)
       {  for(int j = 0 ;j < width;j++)
            {
                image[i][j]=new_image[i][j];
            }

       }
}
