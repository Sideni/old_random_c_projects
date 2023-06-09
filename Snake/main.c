#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define HAUTEUR_NB_BLOCS        25
    #define LARGEUR_NB_BLOCS        25
    #define LARGEUR_BLOC            10
    #define LARGEUR_FENETRE         LARGEUR_BLOC * LARGEUR_NB_BLOCS
    #define HAUTEUR_FENETRE         LARGEUR_BLOC * HAUTEUR_NB_BLOCS

    enum {HAUT, BAS, GAUCHE, DROITE};

#endif

char bougerSerpent(char direction, char map[HAUTEUR_NB_BLOCS][LARGEUR_NB_BLOCS], SDL_Rect serpent[], int *longueurSerpent, int *MAJSouris);
void miseAJourMap(char map[HAUTEUR_NB_BLOCS][LARGEUR_NB_BLOCS], SDL_Rect serpent[], int longueurSerpent, SDL_Rect *souris, int n, int *MAJSouris);
void reinitialiser(int *longueurSerpent, SDL_Rect serpent[], int startX, int startY, char *direction, int *MAJSouris, char *echec);
void pause(char *stop);
void menuFonction(char *stop);

int main(int argc, char *argv[])
{
    srand (time(NULL));
    SDL_Surface *ecran = NULL, *carre = NULL, *texte1 = NULL, *texte2 = NULL;
    SDL_Event event;
    TTF_Font *police1 = NULL;
    TTF_Font *police2 = NULL;
    SDL_Color rouge = {255, 0, 0};
    SDL_Color gris = {150, 150, 150};
    int un = 255, deux = 0, trois = 0;

    char texteChaine1[6] = "SNAKE";
    char texteChaine2[5] = "";

    char continuer = 1;
    int MAJSouris = 1;
    char direction = GAUCHE;
    int longueurSerpent = 4;
    char echec = 0;
    char poil = 0;

    int max = HAUTEUR_NB_BLOCS * LARGEUR_NB_BLOCS - longueurSerpent;

    int tempsPrecedent = 0, tempsActuel = 0;
    int temps = 80; //millisecondes

    int startY = HAUTEUR_NB_BLOCS / 2, startX = LARGEUR_NB_BLOCS / 2,
    endY = startY, endX = startX + 3,
    i = 0, j = 0;

    char map[HAUTEUR_NB_BLOCS][LARGEUR_NB_BLOCS] = {{0}};

    SDL_Rect serpent[HAUTEUR_NB_BLOCS * LARGEUR_NB_BLOCS];
    SDL_Rect souris;
    SDL_Rect coorTexte1;
    SDL_Rect coorTexte2;

    for(i = 0; i < HAUTEUR_NB_BLOCS * LARGEUR_NB_BLOCS; i++)
    {
        serpent[i].x = 0;
        serpent[j].y = 0;
    }

    serpent[0].x = startX * LARGEUR_BLOC;
    serpent[0].y = startY * LARGEUR_BLOC;
    serpent[1].x = (startX + 1) * LARGEUR_BLOC;
    serpent[1].y = startY * LARGEUR_BLOC;
    serpent[2].x = (startX + 2) * LARGEUR_BLOC;
    serpent[2].y = startY * LARGEUR_BLOC;
    serpent[3].x = endX * LARGEUR_BLOC;
    serpent[3].y = endY * LARGEUR_BLOC;



    miseAJourMap(map, serpent, longueurSerpent, &souris, rand() % (max + 1), &MAJSouris);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_WM_SetCaption("Snake", NULL);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    police1 = TTF_OpenFont("nnumber.ttf", (int)(LARGEUR_FENETRE * 0.26));
    police2 = TTF_OpenFont("nnumber.ttf", (int)(LARGEUR_FENETRE * 0.16));

    texte1 = TTF_RenderText_Blended(police1, texteChaine1, rouge);

    coorTexte1.x = LARGEUR_FENETRE / 2 - texte1->w / 2;
    coorTexte1.y = HAUTEUR_FENETRE / 2 - texte1->h;

    carre = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_BLOC, LARGEUR_BLOC, 32, 0, 0, 0, 0);
    SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    while(continuer)
    {
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > temps)
        {
            if(!bougerSerpent(direction, map, serpent, &longueurSerpent, &MAJSouris))
                echec = 1;
            if(echec)
            {
                if(longueurSerpent == LARGEUR_NB_BLOCS * HAUTEUR_NB_BLOCS)
                    sprintf(texteChaine2, "Victoire !");
                else
                    sprintf(texteChaine2, "%d", longueurSerpent);

                texte2 = TTF_RenderText_Blended(police2, texteChaine2, gris);

                coorTexte2.x = LARGEUR_FENETRE / 2 - texte2->w / 2;
                coorTexte2.y = HAUTEUR_FENETRE / 2 + texte2->h;

                SDL_BlitSurface(texte1, NULL, ecran, &coorTexte1);
                SDL_BlitSurface(texte2, NULL, ecran, &coorTexte2);
                SDL_Flip(ecran);
                pause(&continuer);

                SDL_FreeSurface(texte2);
                reinitialiser(&longueurSerpent, serpent, startX, startY, &direction, &MAJSouris, &echec);
            }
                miseAJourMap(map, serpent, longueurSerpent, &souris, rand() % (max + 1), &MAJSouris);

                if(un == 255 && deux < 255 && trois == 0)
                    deux = deux + 15;
                else if(deux == 255 && un > 0 && trois == 0)
                    un = un - 15;
                else if(deux == 255 && trois < 255 && un == 0)
                    trois = trois + 15;
                else if(trois == 255 && deux > 0 && un == 0)
                    deux = deux - 15;
                else if(trois == 255 && un < 255 && deux == 0)
                    un = un + 15;
                else if(un == 255 && trois > 0 && deux == 0)
                    trois = trois - 15;

            tempsPrecedent = tempsActuel;
            if(poil == 255)
                poil = 1;
            poil++;
        }
        else // Si ça fait moins de 'temps' ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut
        {
            SDL_Delay(temps - (tempsActuel - tempsPrecedent));
        }

        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        if(direction != HAUT && direction != BAS)
                        {
                            direction = HAUT;
                            tempsPrecedent = tempsPrecedent - temps;
                        }
                        break;
                    case SDLK_DOWN:
                        if(direction != HAUT && direction != BAS)
                        {
                            direction = BAS;
                            tempsPrecedent = tempsPrecedent - temps;
                        }
                        break;
                    case SDLK_RIGHT:
                        if(direction != GAUCHE && direction != DROITE)
                        {
                            direction = DROITE;
                            tempsPrecedent = tempsPrecedent - temps;
                        }
                        break;
                    case SDLK_LEFT:
                        if(direction != GAUCHE && direction != DROITE)
                        {
                            direction = GAUCHE;
                            tempsPrecedent = tempsPrecedent - temps;
                        }
                        break;
                    case SDLK_m:
                        menuFonction(&continuer);
                        break;
                    default:
                        break;
                }
                break;
        }

        // Effacement de l'écran

        SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, un, deux, trois));
        if(poil % 2)
        {
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
            SDL_BlitSurface(carre, NULL, ecran, &souris);
            SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        }
        else
        {
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
            SDL_BlitSurface(carre, NULL, ecran, &souris);
            SDL_FillRect(carre, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        }

        for(i = 0; i < longueurSerpent; i++)
        {
            SDL_BlitSurface(carre, NULL, ecran, &serpent[i]);
        }
        if(continuer)
            SDL_Flip(ecran);
    }
    TTF_CloseFont(police1);
    TTF_CloseFont(police2);
    TTF_Quit();

    SDL_FreeSurface(carre);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(texte2);
    SDL_Quit();

    return EXIT_SUCCESS;
}

char bougerSerpent(char direction, char map[HAUTEUR_NB_BLOCS][LARGEUR_NB_BLOCS], SDL_Rect serpent[], int *longueurSerpent, int *MAJSouris) // if return 0 -> dead, if return 1 -> IT'S ALIVE !!!
{
    int x = 0;
    int y = 0;
    int i = 0;

    x = serpent[0].x / LARGEUR_BLOC;
    y = serpent[0].y / LARGEUR_BLOC;

    if(direction == HAUT)
    {
        if(y - 1 < 0) //S'il fonce dans un mur
            return 0;
        else if(map[y - 1][x] == 1) //S'il fonce dans lui-même
            return 0;
        else if(map[y - 1][x] == 2) //S'il mange la souris
        {
            for(i = *longueurSerpent - 1; i >= 0; i--)
            {
                serpent[i + 1].x = serpent[i].x;
                serpent[i + 1].y = serpent[i].y;
            }
            serpent[0].y = (y - 1) * LARGEUR_BLOC;
            *longueurSerpent = *longueurSerpent + 1;
            *MAJSouris = 1;
            return 1;
        }
        else if(map[y - 1][x] == 0) //S'il avance normalement comme la société lui ordonne !!!
        {
            for(i = *longueurSerpent - 1; i > 0; i--)
            {
                serpent[i].x = serpent[i - 1].x;
                serpent[i].y = serpent[i - 1].y;
            }
            serpent[0].y = (y - 1) * LARGEUR_BLOC;
            return 1;
        }
    }
    else if(direction == BAS)
    {
        if(y + 1 >= HAUTEUR_NB_BLOCS) //S'il fonce dans un mur
            return 0;
        else if(map[y + 1][x] == 1) //S'il fonce dans lui-même
            return 0;
        else if(map[y + 1][x] == 2) //S'il mange la souris
        {
            for(i = *longueurSerpent - 1; i >= 0; i--)
            {
                serpent[i + 1].x = serpent[i].x;
                serpent[i + 1].y = serpent[i].y;
            }
            serpent[0].y = (y + 1) * LARGEUR_BLOC;
            *longueurSerpent = *longueurSerpent + 1;
            *MAJSouris = 1;
            return 1;
        }
        else if(map[y + 1][x] == 0) //S'il avance normalement en se serrant la ceinture !!!
        {
            for(i = *longueurSerpent - 1; i > 0; i--)
            {
                serpent[i].x = serpent[i - 1].x;
                serpent[i].y = serpent[i - 1].y;
            }
            serpent[0].y = (y + 1) * LARGEUR_BLOC;
            return 1;
        }
    }
    else if(direction == DROITE)
    {
        if(x + 1 >= LARGEUR_NB_BLOCS) //S'il fonce dans un mur
            return 0;
        else if(map[y][x + 1] == 1) //S'il fonce dans lui-même
            return 0;
        else if(map[y][x + 1] == 2) //S'il mange la souris
        {
            for(i = *longueurSerpent - 1; i >= 0; i--)
            {
                serpent[i + 1].x = serpent[i].x;
                serpent[i + 1].y = serpent[i].y;
            }
            serpent[0].x = (x + 1) * LARGEUR_BLOC;
            *longueurSerpent = *longueurSerpent + 1;
            *MAJSouris = 1;
            return 1;
        }
        else if(map[y][x + 1] == 0) //S'il se conforme au code pré-établi !!!
        {
            for(i = *longueurSerpent - 1; i > 0; i--)
            {
                serpent[i].x = serpent[i - 1].x;
                serpent[i].y = serpent[i - 1].y;
            }
            serpent[0].x = (x + 1) * LARGEUR_BLOC;
            return 1;
        }
    }
    else if(direction == GAUCHE)
    {
        if(x - 1 < 0) //S'il fonce dans un mur
            return 0;
        else if(map[y][x - 1] == 1) //S'il fonce dans lui-même
            return 0;
        else if(map[y][x - 1] == 2) //S'il mange la souris !
        {
            for(i = *longueurSerpent - 1; i >= 0; i--)
            {
                serpent[i + 1].x = serpent[i].x;
                serpent[i + 1].y = serpent[i].y;
            }
            serpent[0].x = (x - 1) * LARGEUR_BLOC;
            *longueurSerpent = *longueurSerpent + 1;
            *MAJSouris = 1;
            return 1;
        }
        else if(map[y][x - 1] == 0) //S'il abandonne ses libertés !!!
        {
            for(i = *longueurSerpent - 1; i > 0; i--)
            {
                serpent[i].x = serpent[i - 1].x;
                serpent[i].y = serpent[i - 1].y;
            }
            serpent[0].x = (x - 1) * LARGEUR_BLOC;
            return 1;
        }
    }
    return 0;
}

void miseAJourMap(char map[HAUTEUR_NB_BLOCS][LARGEUR_NB_BLOCS], SDL_Rect serpent[], int longueurSerpent, SDL_Rect *souris, int n, int *MAJSouris)
{
    int i = 0, j = 0, k = 0, test = 0;

    for(i = 0; i < HAUTEUR_NB_BLOCS; i++) // On remet la map à zéro
    {
        for(j = 0; j < LARGEUR_NB_BLOCS; j++)
        {
            map[i][j] = 0;
        }
    }
    for(i = 0; i < longueurSerpent; i++) // On y met le serpent
    {
        map[serpent[i].y / LARGEUR_BLOC][serpent[i].x / LARGEUR_BLOC] = 1;
    }

    if(*MAJSouris)
    {
        for(i = 0; i < HAUTEUR_NB_BLOCS; i++) // On trouve la position de la n ième case vide
        {
            for(j = 0; j < LARGEUR_NB_BLOCS; j++)
            {
                if(map[i][j] == 0)
                {
                    if(k == n && test == 0)
                    {
                        map[i][j] = 2;
                        souris->x = j * LARGEUR_BLOC;
                        souris->y = i * LARGEUR_BLOC;
                        test = 1;
                        *MAJSouris = 0;
                    }
                    else
                        k++;
                }
            }
        }
    }
    else
    {
        map[souris->y / LARGEUR_BLOC][souris->x / LARGEUR_BLOC] = 2;
    }

}

void reinitialiser(int *longueurSerpent, SDL_Rect serpent[], int startX, int startY, char *direction, int *MAJSouris, char *echec)
{
    serpent[0].x = startX * LARGEUR_BLOC;
    serpent[0].y = startY * LARGEUR_BLOC;
    serpent[1].x = (startX + 1) * LARGEUR_BLOC;
    serpent[1].y = startY * LARGEUR_BLOC;
    serpent[2].x = (startX + 2) * LARGEUR_BLOC;
    serpent[2].y = startY * LARGEUR_BLOC;
    serpent[3].x = (startX + 3) * LARGEUR_BLOC;
    serpent[3].y = startY * LARGEUR_BLOC;

    *longueurSerpent = 4;
    *direction = GAUCHE;
    *MAJSouris = 1;
    *echec = 0;
}

void pause(char *stop)
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *stop = 0;
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    case SDLK_RETURN:
                    case SDLK_SPACE:
                        continuer = 0;
                        break;
                    case SDLK_ESCAPE:
                        *stop = 0;
                        continuer = 0;
                        break;
                    default:
                        break;
                }
        }
    }
}

void menuFonction(char *stop)
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *stop = 0;
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    case SDLK_RETURN:
                    case SDLK_SPACE:
                        continuer = 0;
                        break;
                    case SDLK_ESCAPE:
                        *stop = 0;
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        break;
                    case SDLK_DOWN:
                        break;
                    default:
                        break;
                }
        }
    }
}
