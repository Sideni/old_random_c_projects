#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void viderBuffer();
int lire(char *chaine, int longueur);
unsigned int_to_int(unsigned k);
int nombreDigit (int n);
int tableauANombre(char tableau[], int tailleTableau);
int binToDec(int nombre);
void afficherTableau(char tableau[], int tailleTableau);

int main()
{
    const char clef[256] = {1,0,0,1,1,0,1,1,0,1,1,1,0,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,1,0,1,1,0,0,1,1,1,0,0,0
    ,1,0,0,1,1,0,1,1,0,0,1,0,0,0,0,1,1,0,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,0,0,1,0,0,
    0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,1,1,1,0,1,0,1,
    1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,1,0,1,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,1,1,0,1};
    unsigned char message[500] = {0};
    int i = 0, j, k;
    int longueur = 0;

    printf("Entrez votre message(max. 500 caract%cres, sans espaces) :\n", 138);
    lire(message, 500);
    longueur = strlen(message);
    printf("Voici votre message crypt%c :\n\n", 130);

    for(k = 0; k < longueur; k++)
    {
        char intermediaire[8] = {0};
        sprintf(intermediaire+(8-nombreDigit(int_to_int(message[k]))), "%d", int_to_int(message[k]));
        for(j = 0; j < 8; j++)
        {
            if(intermediaire[j] == 48 || intermediaire[j] == 49)
            {
                intermediaire[j] = intermediaire[j] - 48;
            }
            if(i == 256)
            {
                i = 0;
            }
            if(intermediaire[j] != (clef[i]))
            {
                intermediaire[j] = 1;
            }
            else
            {
                intermediaire[j] = 0;
            }
            i++;
        }
        printf("%c", binToDec(tableauANombre(intermediaire, 8)));
    }
    printf("\n");
    system("pause");
    return 0;
}

unsigned int_to_int(unsigned k)
{
    if (k == 0) return 0;
    if (k == 1) return 1;                       /* optional */
    return (k % 2) + 10 * int_to_int(k / 2);

}

int nombreDigit (int n)
{
    if (n == 0) return 1;
    return floor (log10 (abs (n))) + 1;
}

int tableauANombre(char tableau[], int tailleTableau)
{
    int i;
    int nombre = 0;
    for(i = 0; i < tailleTableau; i++)
    {
        nombre = (nombre + tableau[i])*10;
    }
    nombre = nombre / 10;
    return nombre;
}

int binToDec(int nombre)
{
    int i;
    int sortie = 0;
    for(i = 0; i < 8; i++)
    {
        if(nombre % 2 == 1)
        {
            sortie = sortie + pow(2, i);
        }
        nombre = nombre / 10;
    }
    return sortie;
}

void afficherTableau(char tableau[], int tailleTableau)
{
    int i;

    for(i = 0 ; i <tailleTableau ; i++)
    {
        printf("%d\n", tableau[i]);
    }
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}
