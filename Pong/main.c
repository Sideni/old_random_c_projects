#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#include "constantes.h"


int WinMain(int argc, char *argv[])
{
    //VARIABLES
    SDL_Surface *ecran = NULL, *balle = NULL, *barre = NULL, *pointage1 = NULL, *pointage2 = NULL;
    SDL_Rect positionLigne, positionLigne2, positionLigne3, positionLigne4, positionLigne5;
    SDL_Rect positionPointage1, positionPointage2;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color blanc = {255, 255, 255};
    SDL_Color noir = {0, 0, 0};

    int points1 = 0;
    int points2 = 0;
    char pointChaine1[5] = "";
    char pointChaine2[5] = "";
    char continuer = 1;
    char start = 0;
    char joueur1 = 0;
    char joueur2 = 0;
    int tempsPrecedent = 0, tempsActuel = 0;
    int temps = 4;
    char droite = 1;
    char haut = 1;
    int a = 0, b = 1;
    char initialisation = 1;

    const int max = 2, min = 1;

    SDL_Rect positionJoueur1;
    SDL_Rect positionJoueur2;
    SDL_Rect positionBalle;
    //FIN DES VARIABLES

    sprintf(pointChaine1, "%d", points1);
    sprintf(pointChaine2, "%d", points2);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("PONG", NULL);

    police = TTF_OpenFont("simhei.ttf", 65);

    pointage1 = TTF_RenderText_Shaded(police, pointChaine1, blanc, noir);
    pointage2 = TTF_RenderText_Shaded(police, pointChaine2, blanc, noir);

    positionJoueur1.x = 5;
    positionJoueur1.y = HAUTEUR_FENETRE / 2 - HAUTEUR_BARRE / 2;

    positionJoueur2.x = LARGEUR_FENETRE - 10;
    positionJoueur2.y = HAUTEUR_FENETRE / 2 - HAUTEUR_BARRE / 2;

    positionBalle.x = LARGEUR_FENETRE / 2 - GROSSEUR_BALLE / 2;
    positionBalle.y = HAUTEUR_FENETRE / 2 - GROSSEUR_BALLE / 2;

    positionLigne.x = LARGEUR_FENETRE / 2 - GROSSEUR_BARRE / 2;
    positionLigne.y = 0;

    positionLigne2.x = LARGEUR_FENETRE / 2 - GROSSEUR_BARRE / 2;
    positionLigne2.y = HAUTEUR_BARRE + HAUTEUR_BARRE / 5;

    positionLigne3.x = LARGEUR_FENETRE / 2 - GROSSEUR_BARRE / 2;
    positionLigne3.y = 2 * HAUTEUR_BARRE + 2 * HAUTEUR_BARRE / 5;

    positionLigne4.x = LARGEUR_FENETRE / 2 - GROSSEUR_BARRE / 2;
    positionLigne4.y = 3 * HAUTEUR_BARRE + 3 * HAUTEUR_BARRE / 5;

    positionLigne5.x = LARGEUR_FENETRE / 2 - GROSSEUR_BARRE / 2;
    positionLigne5.y = 4 * HAUTEUR_BARRE + 4 * HAUTEUR_BARRE / 5;

    positionPointage1.x = LARGEUR_FENETRE / 4 - pointage1->w / 2;
    positionPointage1.y = 10;

    positionPointage2.x = 3 * LARGEUR_FENETRE / 4 - pointage2->w / 2;
    positionPointage2.y = 10;

    barre = SDL_CreateRGBSurface(SDL_HWSURFACE, GROSSEUR_BARRE, HAUTEUR_BARRE, 32, 0, 0, 0, 0);
    balle = SDL_CreateRGBSurface(SDL_HWSURFACE, GROSSEUR_BALLE, GROSSEUR_BALLE, 32, 0, 0, 0, 0);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_FillRect(barre, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_FillRect(balle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));


    while (continuer)
    {
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent >= temps)
        {
            //On fait bouger la barre du joueur 1
            if(joueur1 == 1 && positionJoueur1.y > 0)
            {
                positionJoueur1.y -= (temps - 1);
            }
            else if(joueur1 == -1 && (positionJoueur1.y + HAUTEUR_BARRE) <= HAUTEUR_FENETRE)
            {
                positionJoueur1.y += (temps - 1);
            }

            //On fait bouger la barre du joueur 2
            if(joueur2 == 1 && positionJoueur2.y > 0)
            {
                positionJoueur2.y -= (temps - 1);
            }
            else if(joueur2 == -1 && (positionJoueur2.y + HAUTEUR_BARRE) <= HAUTEUR_FENETRE)
            {
                positionJoueur2.y += (temps - 1);
            }

            //On fait bouger la balle
            if(start)
            {
                if(initialisation) //On initialise les variables de la fonction linéaire
                {
                    positionBalle.x = LARGEUR_FENETRE / 2 - GROSSEUR_BALLE / 2;
                    positionBalle.y = HAUTEUR_FENETRE / 2 - GROSSEUR_BALLE / 2;

                    a = (rand() % (max - min + 1)) + min;


                    if(a == 1)
                    {
                        b = (rand() % (max - min + 1)) + min;
                    }

                    if(rand() % (1 - 0 + 1))
                            haut = 0;

                    if(rand() % (1 - 0 + 1))
                        droite = 0;

                    initialisation = 0;
                }

                if(droite)
                {
                    positionBalle.x += b;
                    if(!haut)
                    {
                        positionBalle.y += a;
                        if ((positionBalle.y + balle->h) >= ecran->h)
                        {
                            haut = 1;
                        }
                    }
                    else if(haut)
                    {
                        positionBalle.y -= a;
                        if (positionBalle.y <= 0)
                        {
                            haut = 0;
                        }
                    }

                    if ((positionBalle.x + GROSSEUR_BALLE >= positionJoueur2.x) && (positionBalle.x + GROSSEUR_BALLE <= positionJoueur2.x + GROSSEUR_BARRE) &&
                        (positionBalle.y + GROSSEUR_BALLE >= positionJoueur2.y) && (positionBalle.y <= positionJoueur2.y + HAUTEUR_BARRE)) //Si on touche la barre
                    {
                        droite = 0;
                        //temps--;

                        // Les angles avec lesquelles la balle peut repartir
                        if (positionBalle.y + GROSSEUR_BALLE >= positionJoueur2.y && positionBalle.y <= positionJoueur2.y + HAUTEUR_BARRE / 5)
                        {
                            a = 2;
                            b = 1;
                            haut = 1;
                        }
                        else if (positionBalle.y > positionJoueur2.y + HAUTEUR_BARRE / 5 && positionBalle.y <= positionJoueur2.y + 2 * HAUTEUR_BARRE / 5)
                        {
                            a = 1;
                            b = 2;
                            haut = 1;
                        }
                        else if (positionBalle.y > positionJoueur2.y + 2 * HAUTEUR_BARRE / 5 && positionBalle.y <= positionJoueur2.y + 3 * HAUTEUR_BARRE / 5)
                        {
                            a = 0;
                            b = 2;
                        }
                        else if (positionBalle.y > positionJoueur2.y + 3 * HAUTEUR_BARRE / 5 && positionBalle.y <= positionJoueur2.y + 4 * HAUTEUR_BARRE / 5)
                        {
                            a = 1;
                            b = 2;
                            haut = 0;
                        }
                        else if (positionBalle.y > positionJoueur2.y + 4 * HAUTEUR_BARRE / 5 && positionBalle.y <= positionJoueur2.y + HAUTEUR_BARRE)
                        {
                            a = 2;
                            b = 1;
                            haut = 0;
                        }
                    }
                    else if(positionBalle.x + GROSSEUR_BALLE >= LARGEUR_FENETRE) //Si joueur 2 perd
                    {
                        start = 0;
                        initialisation = 1;
                        points1++;
                    }
                }
                else if(!droite)
                {
                    positionBalle.x -= b;
                    if(!haut)
                    {
                        positionBalle.y += a;
                        if (positionBalle.y + balle->h >= ecran->h)
                        {
                            haut = 1;
                        }
                    }
                    else if(haut)
                    {
                        positionBalle.y -= a;
                        if (positionBalle.y <= 0)
                        {
                            haut = 0;
                        }
                    }

                    if ((positionBalle.x <= positionJoueur1.x + GROSSEUR_BARRE) && (positionBalle.x >= positionJoueur1.x) &&
                        ((positionBalle.y + GROSSEUR_BALLE) >= positionJoueur1.y) && (positionBalle.y <= (positionJoueur1.y + HAUTEUR_BARRE))) //Si on touche la barre
                    {
                        droite = 1;
                        //temps--;

                        // Les angles avec lesquelles la balle peut repartir
                        if (positionBalle.y + GROSSEUR_BALLE >= positionJoueur1.y && positionBalle.y <= positionJoueur1.y + HAUTEUR_BARRE / 5)
                        {
                            a = 2;
                            b = 1;
                            haut = 1;
                        }
                        else if (positionBalle.y > positionJoueur1.y + HAUTEUR_BARRE / 5 && positionBalle.y <= positionJoueur1.y + 2 * HAUTEUR_BARRE / 5)
                        {
                            a = 1;
                            b = 2;
                            haut = 1;
                        }
                        else if (positionBalle.y > positionJoueur1.y + 2 * HAUTEUR_BARRE / 5 && positionBalle.y <= positionJoueur1.y + 3 * HAUTEUR_BARRE / 5)
                        {
                            a = 0;
                            b = 2;
                        }
                        else if (positionBalle.y > positionJoueur1.y + 3 * HAUTEUR_BARRE / 5 && positionBalle.y <= positionJoueur1.y + 4 * HAUTEUR_BARRE / 5)
                        {
                            a = 1;
                            b = 2;
                            haut = 0;
                        }
                        else if (positionBalle.y > positionJoueur1.y + 4 * HAUTEUR_BARRE / 5 && positionBalle.y <= positionJoueur1.y + HAUTEUR_BARRE)
                        {
                            a = 2;
                            b = 1;
                            haut = 0;
                        }
                    }
                    else if(positionBalle.x <= 0) //Si joueur 1 perd
                    {
                        start = 0;
                        initialisation = 1;
                        points2++;
                    }
                }
            }

            tempsPrecedent = tempsActuel;
        }
        else /* Si ça fait moins de 30 ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut */
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
                    case SDLK_RETURN:
                    case SDLK_SPACE:
                    case SDLK_KP_ENTER:
                        start = 1;
                        break;
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        joueur2 = 1;
                        break;
                    case SDLK_DOWN:
                        joueur2 = -1;
                        break;
                    case SDLK_w:
                        joueur1 = 1;
                        break;
                    case SDLK_s:
                        joueur1 = -1;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if(joueur2 == 1)
                            joueur2 = 0;
                        break;
                    case SDLK_DOWN:
                        if(joueur2 == -1)
                            joueur2 = 0;
                        break;
                    case SDLK_w:
                        if(joueur1 == 1)
                            joueur1 = 0;
                        break;
                    case SDLK_s:
                        if(joueur1 == -1)
                        joueur1 = 0;
                        break;
                }
                break;


        }

        sprintf(pointChaine1, "%d", points1);
        sprintf(pointChaine2, "%d", points2);
        SDL_FreeSurface(pointage1);
        SDL_FreeSurface(pointage2);
        pointage1 = TTF_RenderText_Shaded(police, pointChaine1, blanc, noir);
        pointage2 = TTF_RenderText_Shaded(police, pointChaine2, blanc, noir);

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        SDL_BlitSurface(barre, NULL, ecran, &positionLigne);
        SDL_BlitSurface(barre, NULL, ecran, &positionLigne2);
        SDL_BlitSurface(barre, NULL, ecran, &positionLigne3);
        SDL_BlitSurface(barre, NULL, ecran, &positionLigne4);
        SDL_BlitSurface(barre, NULL, ecran, &positionLigne5);

        SDL_BlitSurface(pointage1, NULL, ecran, &positionPointage1);
        SDL_BlitSurface(pointage2, NULL, ecran, &positionPointage2);

        if(start)
            SDL_BlitSurface(balle, NULL, ecran, &positionBalle);

        SDL_BlitSurface(barre, NULL, ecran, &positionJoueur1);
        SDL_BlitSurface(barre, NULL, ecran, &positionJoueur2);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(balle);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(pointage1);
    SDL_FreeSurface(pointage2);
    TTF_CloseFont(police);
    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}
