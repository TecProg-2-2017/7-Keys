#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <SDL/SDL.h>
#include <time.h>

// Function to draw rectangles

void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen){
    SDL_Rect rect = {x,y,w,h};
    SDL_FillRect(screen, &rect, color);
}

int main ( int argc, char** argv ){

    // Initialize SDL video

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // Make sure SDL cleans up before exit

    atexit(SDL_Quit);

    // Create a new window

    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // Load an image

    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // Centre the bitmap on screen

    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // Program main loop

    bool done = false;
    while (!done){

        // Message processing loop
        
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            
            // Check for messages

            switch (event.type){

                // Exit if the window is closed

                case SDL_QUIT:
                    done = true;
                    break;

                // Check for keypresses

                case SDL_KEYDOWN:{

                     // Exit if ESCAPE is pressed
                        
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        done = true;
                    }
                    break;
                }
            } 
        } 
        
        // End of message processing

        // DRAWING STARTS HERE

        // Clear screen

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        
        int random;
        int direction = 50;
        int x = 50, y = 150;

        // Initialize random seed: 

        srand (time(NULL));

        for(int num_salas = 15; num_salas != 0; num_salas--){
           random = rand() % 3;
           direction = rand() % 2;
           if (direction == 0){
               direction = 50;
           }
           else{
               direction = -50;
           }
           if (random == 0){
                FillRect(x+direction,y,50,50,0xFFFFFF,screen);
                FillRect(x+direction+1,y+1,48,48,0x0,screen);
                x = x+direction;
           }
           else if (random == 1){
                FillRect(x,y+direction,50,50,0xFFFFFF,screen);
                FillRect(x+1,y+direction+1,48,48,0x0,screen);
                y = y+direction;
           }
           else if (random == 2){
                FillRect(x,y-direction,50,50,0xFFFFFF,screen);
                FillRect(x+1,y-direction+1,48,48,0x0,screen);
                y = y-direction;
           }
           else if (random == 3){
                FillRect(x-direction,y,50,50,0xFFFFFF,screen);
                FillRect(x-direction+1,y+1,48,48,0x0,screen);
                x = x-direction;
           }
        }

        // DRAWING ENDS HERE

        // Finally, update the screen :)

        SDL_Flip(screen);
    } 

    // Free loaded bitmap
    
    SDL_FreeSurface(bmp);

    // All is well ;)
    
    printf("Exited cleanly\n");
    return 0;
}
