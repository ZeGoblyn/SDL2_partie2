#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


int main(int argc, char *argv[])
{
    SDL_Window *pWindow=NULL;           //Pointeur sur la fenêtre, ref d'un window win32
    SDL_Renderer *pRenderer=NULL;       //Pointeur sur le Rendus, ref rendu encapsulé dans window
    //SDL_Texture *pTexture=NULL;         //Pointeur sur la texture, qui possède l'image à afficher, ref image/texture/materiel


    //Requis pour utiliser la SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)    //INIT_EVERYTHING = initialise l'audio, la vidéo, les contrôles,... cf; SDL wiki/API by name/SDL_Init
    {
        //succès, créer window
        pWindow=SDL_CreateWindow("SDL_Application",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 780, SDL_WINDOW_SHOWN);//x,y,width,eight

        //si succès, créer window et renderer
        if(pWindow!=NULL)
        {
            pRenderer=SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_PRESENTVSYNC);
           /* }
            else
            {*/

            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

            //Implantation d'une image en format png
            SDL_SetRenderTarget(pRenderer, NULL);
            SDL_Surface* image = IMG_Load("sandwich-kebab.png");                   //Creation d'une surface à partir d'une image
            SDL_Texture* Image = SDL_CreateTextureFromSurface(pRenderer,image);     //Creation d'une texture à partir de la surface
            if(!image)
            {
                printf("Erreur de chargement de l'image : %s",SDL_GetError());
                return -1;
            }

            SDL_Rect myRect;                                                        //Définition d'une zone d'affichage
            myRect.x = 0;
            myRect.y = 0;
            SDL_QueryTexture(Image, NULL, NULL, &myRect.w, &myRect.h);              //Appel de la texture dans le rectangle

            SDL_RenderCopy(pRenderer, Image, NULL, &myRect);
            SDL_RenderPresent(pRenderer);


            //Implantation tileset
            SDL_Surface * surfaceSprite = IMG_Load("george.png");
            SDL_Texture * spriteGuy = SDL_CreateTextureFromSurface(pRenderer,
                surfaceSprite);

            int quit = 0;
            SDL_Event event;

            SDL_Rect myRectSource;                                                        //Définition d'une zone d'affichage
            myRect.x = 0;
            myRect.y = 0;

           while (!quit)
            {
                Uint32 ticks = SDL_GetTicks();
                Uint32 sprite = (ticks / 100) % 4;
                SDL_QueryTexture(spriteGuy, NULL, NULL, &myRectSource.w, &myRectSource.h);  //Appel de la texture créer à partir de l'image
                myRectSource.w = myRectSource.w/4;          //Division des dimensions pour adapter à la taille de chaque images
                myRectSource.h = myRectSource.h/4;

                SDL_Rect srcrect = { sprite * myRectSource.w, 0, myRectSource.w,  myRectSource.h };     //Mise en place des rects de source et de réception
                SDL_Rect dstrect = { 500, 500, myRectSource.w,  myRectSource.h };

                SDL_PollEvent(&event);

                switch (event.type)
                {
                    case SDL_MOUSEBUTTONDOWN :
                        quit = 1;
                        break;
                }

                SDL_RenderClear(pRenderer);
                SDL_RenderCopy(pRenderer, Image, NULL, &myRect);
                SDL_RenderCopy(pRenderer, spriteGuy, &srcrect, &dstrect);
                SDL_RenderPresent(pRenderer);
            }

           /* SDL_Rect srcrect = { 0, 0, 41.33, 36 };
            SDL_Rect dstrect = { 500, 500, 41.33, 36 };

            SDL_RenderCopy(pRenderer, Image, NULL, &myRect, &srcrect, &dstrect);*/


            SDL_Delay(10000);

            SDL_DestroyTexture(Image);
            SDL_DestroyTexture(spriteGuy);
            SDL_FreeSurface(image);
            SDL_FreeSurface(surfaceSprite);
            SDL_DestroyRenderer(pRenderer); //On supprime tout ce qui à été créer
            SDL_DestroyWindow(pWindow);
            SDL_Quit();
        }
     }

    return 0;
}
