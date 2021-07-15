 #define MAX_HEIGHT 1025
    #define MAX_WIDTH 1025
    #include <stdio.h>
    #include <math.h>
    #include <string.h>


void convolve(int theImageArray[MAX_WIDTH][MAX_HEIGHT], int theImageArrayDup[MAX_WIDTH][MAX_HEIGHT], int height, int width){
    //printf("%d = %d k",height,width);
    int hid=height;
    int wid=width;
    int boxBlur[3][3] = {
        { 1, 1, 1 },
        { 1,  1, 1 },
        { 1, 1, 1 }
    };

    int gaussian[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
     int edgeDetect[3][3] = {
        {-1, -1, -1},
        {-1,  5, -1},
        {-1, -1, -1}
    };

    int sharpen[3][3] = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };
/*
    int medi[3][3] = {
        {0, -1,  0},
        {-1, 5, -1},
        {0, -1,  0}
    };*/

    int horizonL[3][3] = {
        {-1, -1, -1},
        {2, 2, 2},
        {-1, -1, -1}
    };

    int verticatL[3][3] = {
        {-1, 2, -1},
        {-1, 2, -1},
        {-1, 2, -1}
    };


    char convolution[3];
    printf("Would you like to run box blur, Gaussian blur, edge detection, or sharpen?\n(M: Moyeurneur, G : Gaussian, E: Edge, S: mediane, V : ligneVertical, H: ligneHorizontal,P :piquer ,Q: quiter) \n");
    //scanf("%s", convolution);
    //lowerletter(convolution);
    int i,j;
    //convolution=tolower(getchar());
    scanf("%s", &convolution);
     if(strlen(convolution)!=1){
        printf("\n\t\t\tSVP Etrez juste un caractere\n");
        convolve(theImageArray, theImageArrayDup, height, width);
    }else{
        convolution[0]=tolower(convolution[0]);
        switch(convolution[0]){
            case 'm' : for (i = 1; i < MAX_HEIGHT; i++) {
                            for (j = 1; j < MAX_WIDTH; j++) {
                                conMatrixMult(theImageArray, theImageArrayDup, boxBlur, i, j, 9, 0);
                            }
                        }
                        break;
            case 'g' : for (i = 1; i < MAX_HEIGHT; i++) {
                            for (j = 1; j < MAX_WIDTH; j++) {
                                conMatrixMult(theImageArray, theImageArrayDup, gaussian, i, j, 16, 0);

                            }
                        }
                        break;
            case 'e' : for (i = 1; i < MAX_HEIGHT; i++) {
                            for (j = 1; j < MAX_WIDTH; j++) {
                                conMatrixMult(theImageArray, theImageArrayDup, edgeDetect, i, j, 128, 0);

                            }
                        }
                        break;
            case 's' : for (i = 1; i < MAX_HEIGHT; i++) {
                            for (j = 1; j < MAX_WIDTH; j++) {
                                MoyMatrixMult(theImageArray,i,j);
                            }

                        }
                    //printf("Image is washed out, sorry. Couldn't figure out a way around that. It is sharpened though.");
                            break;
            case 'h' : for (i = 1; i < MAX_HEIGHT; i++) {
                            for (j = 1; j < MAX_WIDTH; j++) {
                                conMatrixMult(theImageArray, theImageArrayDup, verticatL, i, j, 1, 0);
                            }
                        }
                        break;
            case 'v' : for (i = 1; i < MAX_HEIGHT; i++) {
                            for (j = 1; j < MAX_WIDTH; j++) {
                                conMatrixMult(theImageArray, theImageArrayDup, horizonL, i, j, 1, 0);
                            }
                        }
                        break;
            case 'p' : for (i = 1; i < MAX_HEIGHT; i++) {
                            for (j = 1; j < MAX_WIDTH; j++) {
                                conMatrixMult(theImageArray, theImageArrayDup, sharpen, i, j, 1, 0);
                            }
                        }
                        break;
            case 'q' : exit(1);
                        break;
            case 'x' : convolve(theImageArray, theImageArrayDup, height, width);
                        break;
            default : printf("\n\n \t\tErreure, SVP entrez l'un de charactere demande\n");
                        convolve(theImageArray, theImageArrayDup, height, width);
                        break;
        }

    }
}

void conMatrixMult(int theImageArray[MAX_WIDTH][MAX_HEIGHT], int theImageArrayDup[MAX_WIDTH][MAX_HEIGHT], int myMatrix[3][3], int i, int j, int divisor, int subtractor){
     theImageArray[i][j] = (theImageArray[i+1][j+1]*myMatrix[0][0] + theImageArray[i][j+1]*myMatrix[0][1]+ theImageArray[i-1][j+1]*myMatrix[0][2]+theImageArray[i+1][j]*myMatrix[1][0]+theImageArray[i][j]*myMatrix[1][1]+theImageArray[i-1][j]*myMatrix[1][2]+theImageArray[i+1][j-1]*myMatrix[2][0]+theImageArray[i][j+1]*myMatrix[2][1]+theImageArray[i-1][j-1]*myMatrix[2][2])/divisor - subtractor;
}

void MoyMatrixMult(int theImageArray[MAX_WIDTH][MAX_HEIGHT], int i, int j){
     /*theImageArray[i][j] = (theImageArray[i-1][j-1]+ theImageArray[i-1][j]+theImageArray[i-1][j+1]+
                            + theImageArray[i][j-1]+theImageArray[i][j]+theImageArray[i][j+1]
                            + theImageArray[i+1][j-1]+theImageArray[i+1][j]+theImageArray[i+1][j+1])*/

    int cp=0,k,p;
    int tab[9];
    int tmp[9];
    for(k=i-1;k<=(i+1);k++){
        for(p=j-1;p<=(j+1);p++){
            tab[cp]=theImageArray[k][p];
            cp++;
        }
    }
    triFusion(0, 8, tab, tmp);
        theImageArray[i][j]=tab[4];

}

void invert(int theImageArray[MAX_WIDTH][MAX_HEIGHT]){
    int i,j;
    for (i = 1; i < MAX_HEIGHT; i++) {
        for (j = 1; j < MAX_WIDTH; j++) {
              theImageArray[i][j] = 255 - theImageArray[i][j];
        }
    }

}

void Seuillage(int theImageArray[MAX_WIDTH][MAX_HEIGHT]) {


    int n;
    printf("Enter the number of levels you wish to threshold by. \n(Integer between 2-6 inclusive). \n");
    scanf("%d", &n);
    int i,j;
    for (i = 0; i < MAX_HEIGHT; i++) {
        for (j = 0; j < MAX_WIDTH; j++) {
            switch (n){

            case 1:
                printf("Invalid response. Please start over. /n");
                break;

            case 2:
                if (theImageArray[i][j] > ((n-1)*255)/n) {
                    theImageArray[i][j] = 255;
                }
                else {
                    theImageArray[i][j] = 0;
                }
                break;
            case 3:
                if (theImageArray[i][j] > (n-1)*255/n) {
                    theImageArray[i][j] = 255;
                }
                else if (theImageArray[i][j] > (n-2)*(255/n)){
                    theImageArray[i][j] = (n-2)*(255/n);
                }
                else {
                    theImageArray[i][j] = 0;
                }
                break;
            case 4:
                if (theImageArray[i][j] > (n-1)*255/n) {
                    theImageArray[i][j] = 255;
                }
                else if (theImageArray[i][j] > (n-2)*(255/n)){
                    theImageArray[i][j] = (n-2)*(255/n);
                }
                else if (theImageArray[i][j] > (n-3)*(255/n)){
                    theImageArray[i][j] = (n-3)*(255/n);
                }
                else {
                    theImageArray[i][j] = 0;
                }
                break;
            case 5:
                if (theImageArray[i][j] > (n-1)*255/n) {
                    theImageArray[i][j] = 255;
                }
                else if (theImageArray[i][j] > (n-2)*(255/n)){
                    theImageArray[i][j] = (n-2)*(255/n);
                }
                else if (theImageArray[i][j] > (n-3)*(255/n)){
                    theImageArray[i][j] = (n-3)*(255/n);
                }
                else if (theImageArray[i][j] > (n-4)*(255/n)){
                    theImageArray[i][j] = (n-4)*(255/n);
                }
                else {
                    theImageArray[i][j] = 0;
                }
                break;
            case 6:
                if (theImageArray[i][j] > (n-1)*255/n) {
                    theImageArray[i][j] = 255;
                }
                else if (theImageArray[i][j] > (n-2)*(255/n)){
                    theImageArray[i][j] = (n-2)*(255/n);
                }
                else if (theImageArray[i][j] > (n-3)*(255/n)){
                    theImageArray[i][j] = (n-3)*(255/n);
                }
                else if (theImageArray[i][j] > (n-4)*(255/n)){
                    theImageArray[i][j] = (n-4)*(255/n);
                }
                else if (theImageArray[i][j] > (n-5)*(255/n)){
                    theImageArray[i][j] = (n-5)*(255/n);
                }
                else {
                    theImageArray[i][j] = 0;
                }
                break;
            default:
                printf("\n\n \t\t Mauvaise entre. \n");
                break;
            }
        }
    }
}

void luminosity(int theImageArray[MAX_WIDTH][MAX_HEIGHT]) {
    char lum[3];
    double perc;
    printf("Do you want to lighten or darken the image? (L: Lighten, D: Darken, Q: Cancel ) \n");
    scanf("%s", &lum);
    //lowerletter(lum);
    //lum = tolower(getchar());
     //printf("\n lum");
    //printf("\n lum = %d \n",strlen(lum));
    if(strcasecmp(lum,"Q")==0){
        printf("Merci et a la prochain");
        exit(1);
    }
    if(strlen(lum)!=1 || (strcasecmp(lum,"d")!=0 && strcasecmp(lum,"l")!=0)){
        printf("\n\t\t\t SVP Entre uniquement D ou L en lieu de %s= ",lum);
        luminosity(theImageArray);
    }
    lum[0]=tolower(lum);

    printf("Enter a percentage between 0 and 100 (without the %%) of how much you want\nthe luminosity to change by. \n");
    scanf("%lf", &perc);
    perc = 0.01* perc;

    int i,j;
    if(strcmp(lum, "l") == 0){
        perc = 1.0 + perc;

        for (i = 0; i < MAX_HEIGHT; i++) {
            for (j = 0; j < MAX_WIDTH; j++) {
                if(perc*theImageArray[i][j]<= 255){
                    theImageArray[i][j] = perc*theImageArray[i][j];
                }
                else{
                    theImageArray[i][j] = 255;
                }
            }
        }
    }

    if(strcmp(lum, "d") == 0){
        perc = 1.0 - perc;

        for (i = 0; i < MAX_HEIGHT; i++) {
            for (j = 0; j < MAX_WIDTH; j++) {
                theImageArray[i][j] = perc*theImageArray[i][j];

            }
        }
    }
}

void frame(int theImageArray[MAX_WIDTH][MAX_HEIGHT], int width, int height){
    int startPosX;
    int endPosX;
    int startPosY;
    int endPosY;
    int lum,i,j;

    printf("Enter leftmost X position (0-%d): ", width);
    scanf("%d", &startPosX);
    printf("\nEnter rightmost X position (0-%d): ", width);
    scanf("%d", &endPosX);
    printf("\nEnter topmost Y position (0-%d): ", height);
    scanf("%d", &startPosY);
    printf("\nEnter bottommost Y position (0-%d): ", height);
    scanf("%d", &endPosY);
    printf("\n");
    printf("Enter frame luminosity (0-255): ");
    scanf("%d", &lum);
    printf("\n");

    for(i = 0; i < MAX_WIDTH; i++){
        for(j = 0; j < startPosY; j++){
            theImageArray[i][j] = lum;
        }
    }
    for(i = 0; i < startPosX; i++){
        for(j = startPosY; j < MAX_HEIGHT; j++){
            theImageArray[i][j] = lum;
        }
    }
    for(i = startPosX; i < endPosX; i++){
        for(j = endPosY; j < MAX_HEIGHT; j++){
            theImageArray[i][j] = lum;
        }
    }
    for(i = endPosX; i < MAX_WIDTH; i++){
        for(j = startPosY; j < MAX_HEIGHT; j++){
            theImageArray[i][j] = lum;
        }
    }

}

void transformation(int theImageArray[MAX_WIDTH][MAX_HEIGHT], int theImageArrayDup[MAX_WIDTH][MAX_HEIGHT], int width, int height){
    char tfm[10];
    int rotation,i,j;
    printf("Vous voulez faire un rotation de l'image ou une reflection de l'image? (Rt: Rotate, Rf: Reflect, Q: Quiter) \n");
    scanf("%s", tfm);
    //lowerletter(tfm);
    if(strcasecmp(tfm,"rt")!=0 && strcasecmp(tfm,"rf")!=0 && strcasecmp(tfm,"Q")!=0){
            printf("\n\t\t\t SVP Entre uniquement Rt ou Rf en lieu de %s \n",tfm);
            transformation(theImageArray, theImageArrayDup, width, height);
        }
        //lum[0]=tolower(lum);
    if (strcasecmp(tfm, "Q") == 0) {
        printf("Merci et a la prochain");
        exit(1);
    }
    if (strcasecmp(tfm, "rf") == 0) {
        printf("\n Voulez vous fair une reflection Vertical ou Horizontal ?\n( V: Vertical, H: Horizontal, Q: Quiter)\n");
        char direction[15];
        scanf("%s", direction);
        //lowerletter(direction);
        if (strcasecmp(direction, "Q") == 0) {
            printf("Merci et a la prochain");
            exit(1);
        }
        if(strlen(direction)!=2 || (strcasecmp(direction,"h")!=0 && strcasecmp(direction,"v")!=0)){
            printf("\n\t\t\t SVP Entre uniquement V ou H en lieu de %s \n",direction);
            printf("\n Voulez vous fair une reflection Vertical ou Horizontal ?\n( V: Vertical, H: Horizontal )\n");
            scanf("%s", direction);
        }
        if(strcasecmp(direction,"v") == 0){
            for(i = 0; i < width; i++){
                for(j = 0; j < height; j++){
                    theImageArrayDup[i][j] = theImageArray[width-i][j];
                }
            }

            for(i = 0; i < width; i++){
                for(j = 0; j < height; j++){
                    theImageArray[i][j] = theImageArrayDup[i][j];
                }
            }
        }

        if(strcasecmp(direction,"h") == 0){
            for(i = 0; i < width; i++){
                for(j = 0; j < height; j++){
                    theImageArrayDup[i][j] = theImageArray[i][height-j];
                }
            }

            for(i = 0; i < width; i++){
                for(j = 0; j < height; j++){
                    theImageArray[i][j] = theImageArrayDup[i][j];
                }
            }
        }
    }

    if(strcasecmp(tfm, "rt") == 0) {
        printf("Do you want the image rotated 90, 180, or 270 degrees clockwise? ");
        scanf("%d", &rotation);

        if (rotation == 90){
            for(i = 0; i < MAX_WIDTH; i++){
                for(j = 0; j < MAX_HEIGHT; j++){
                    theImageArrayDup[i][j] = theImageArray[j][i];
                }
            }

            for(i = 0; i < MAX_WIDTH; i++){
                for(j = 0; j < MAX_HEIGHT; j++){
                    theImageArray[i][j] = theImageArrayDup[i][j];
                }
            }
        }

         if(rotation ==  180) {
             for(i = 0; i < width; i++){
                for(j = 0; j < height; j++){
                    theImageArrayDup[i][j] = theImageArray[width-i][height-j];
                }
            }

            for(i = 0; i < width; i++){
                for(j = 0; j < height; j++){
                    theImageArray[i][j] = theImageArrayDup[i][j];
                }
            }
        }

        if (rotation == 270){
            for(i = 0; i < width; i++){
                for(j = 0; j < height; j++){
                    theImageArrayDup[i][j] = theImageArray[height-j][i];
                }
            }

            for(i = 0; i < width; i++){
                for(j = 0; j < height; j++){
                    theImageArray[i][j] = theImageArrayDup[i][j];
                }
            }
        }
    }

}

void histogramEga(int width,int hieght){

}


int triFusion(int i, int j, int tab[], int tmp[]) {
    if(j <= i){ return 0;}

    int m = (i + j) / 2;

    triFusion(i, m, tab, tmp);     //trier la moitié gauche récursivement
    triFusion(m + 1, j, tab, tmp); //trier la moitié droite récursivement

    int pg = i;     //pg pointe au début du sous-tableau de gauche
    int pd = m + 1; //pd pointe au début du sous-tableau de droite
    int c;          //compteur

// on boucle de i à j pour remplir chaque élément du tableau final fusionné
    for(c = i; c <= j; c++) {
        if(pg == m + 1) { //le pointeur du sous-tableau de gauche a atteint la limite
            tmp[c] = tab[pd];
            pd++;
        }else if (pd == j + 1) { //le pointeur du sous-tableau de droite a atteint la limite
            tmp[c] = tab[pg];
            pg++;
        }else if (tab[pg] < tab[pd]) { //le pointeur du sous-tableau de gauche pointe vers un élément plus petit
            tmp[c] = tab[pg];
            pg++;
        }else {  //le pointeur du sous-tableau de droite pointe vers un élément plus petit
            tmp[c] = tab[pd];
            pd++;
        }
    }

    for(c = i; c <= j; c++) {  //copier les éléments de tmp[] à tab[]
        tab[c] = tmp[c];
    }
    return 1;
}




