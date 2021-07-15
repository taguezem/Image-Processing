#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_HEIGHT 1025
#define MAX_WIDTH 1025

void imageProcessing(int theImageArray[MAX_WIDTH][MAX_HEIGHT], int theImageArrayDup[MAX_WIDTH][MAX_HEIGHT], int height, int width,int maxPixel,int wit,char* pgmOutFileName) {
    char inputFunc[3];
    char *keyAns;
    // printf("given width %d",width);

   printf("Entrer l'opperation a effectuer sur l'image. \n (S : Seuillage, L : Luminosite, R : ronner l'image, T : Transform, C : Convolution, I : Invers) Q :pour quiter\n");
    //inputFunc = tolower(getchar());
    scanf("%s", &inputFunc);
     if(strlen(inputFunc)!=1){
        printf("\n\t\t\tSVP Etrez juste un caractere\n");
        imageProcessing(theImageArray, theImageArrayDup, height, width,maxPixel,wit,pgmOutFileName);
    }else{
        inputFunc[0]=tolower(inputFunc[0]);
        switch(inputFunc[0]){
            case 'i' : invert(theImageArray);
                        keyAns="images/out/invert.pgm";
                        write_pgm_file_from_array ( keyAns, theImageArray, "# JR test file", height, width,maxPixel ) ;
                        resetImage(theImageArray, theImageArrayDup);
                        printf("\nDone\n");
                         break;
            case 'c' : convolve(theImageArray, height, width);
                        keyAns="images/out/convovole.pgm";
                        write_pgm_file_from_array ( keyAns, theImageArray, "# JR test file", height, width,maxPixel ) ;
                        resetImage(theImageArray, theImageArrayDup);
                        printf("\nDone\n");
                        break;
            case 's' : Seuillage(theImageArray);
                        keyAns="images/out/seuil.pgm";
                        write_pgm_file_from_array ( keyAns, theImageArray, "# JR test file", height, width,maxPixel ) ;
                        resetImage(theImageArray, theImageArrayDup);
                        printf("\nDone\n");
                        break;
            case 'l' : luminosity(theImageArray);
                        keyAns="images/out/lumi.pgm";
                        write_pgm_file_from_array ( keyAns, theImageArray, "# JR test file", height, width,maxPixel ) ;
                        resetImage(theImageArray, theImageArrayDup);
                        printf("\nDone\n");
                        break;
            case 'r' : frame(theImageArray, height, width);
                        keyAns="images/out/frame.pgm";
                        write_pgm_file_from_array ( keyAns, theImageArray, "# JR test file", height, width,maxPixel ) ;
                        resetImage(theImageArray, theImageArrayDup);
                        printf("\nDone\n");
                        break;
            case 't' : transformation(theImageArray, theImageArrayDup, height, width);
                        keyAns="images/out/transformation.pgm";
                        write_pgm_file_from_array ( keyAns, theImageArray, "# JR test file", height, width,maxPixel ) ;
                        resetImage(theImageArray, theImageArrayDup);
                        printf("\nDone\n");
                        break;
            case 'q' : printf("Merci et a la prochain");
                        exit(1);;
                        break;
            case 'x' : imageProcessing(theImageArray, theImageArrayDup, height, width,maxPixel,wit,pgmOutFileName);
                        break;
            default : printf("\n\n \t\tErreure, SVP entrez l'un de charactere demande\n");
                        imageProcessing(theImageArray, theImageArrayDup, height, width,maxPixel,wit,pgmOutFileName);


        }
            //Transfer the current values in theImageArray back to disk
    }
    printf("\nDone\n");
    question(theImageArray, theImageArrayDup, height, width,maxPixel,wit,pgmOutFileName);
    //system("pause");
    //printf("%c",key);


}
void question(int theImageArray[MAX_WIDTH][MAX_HEIGHT], int theImageArrayDup[MAX_WIDTH][MAX_HEIGHT], int height, int width,int maxPixel,int wit,char* pgmOutFileName){
    printf("Voulez vous continuer ? \n\n \t\t Entrer O : pour oui et N : pour non \n\n \t\t\t");
    char key[5];
     scanf("%s", key);
    //lowerletter(tfm);
    if(strlen(key)!=1 || (strcasecmp(key,"o")!=0 && strcasecmp(key,"n")!=0)){
            printf("\n\t\t\t SVP Entre uniquement O ou N en lieu de %s \n",key);
            printf("Voulez vous continuer ? \n\n \t\t Entrer O : pour oui et N : pour non \n\n \t\t\t");
            scanf("%s", key);
        }
    if(strcasecmp(key,"o")==0){
        imageProcessing(theImageArray, theImageArrayDup, height, width,maxPixel,wit,pgmOutFileName);
        }
    if(strcasecmp(key,"n")==0){
        printf("Merci et a la prochain");
        exit(1);
    }
}

void lowerletter(char myString[30]){
    int i;
    for(i = 0; i < strlen(myString); i++){
        myString[i] = tolower(myString[i]);
    }

}
void resetImage(int theImageArray[MAX_WIDTH][MAX_HEIGHT], int theImageArrayDup[MAX_WIDTH][MAX_HEIGHT]){
int i,j;
    for(i = 0; i < MAX_HEIGHT; i++){
        for(j = 0; j < MAX_WIDTH; j++){
            theImageArray[i][j] = theImageArrayDup[i][j];
        }
    }
}

