#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "Ante.h"
#include <vector>  

#include <string>
#include <sstream>

Texture2D redTexture;
Texture2D blueTexture;
Texture2D backgroundTexture;

const float WORLD_WIDTH = 1280 *10;
const float WORLD_HEIGHT = 720 *10;


int main()
{
    
    
    InitWindow(1280, 720, "ANTE WAR");
    Camera2D camera;
    camera.target = Vector2{640, 360};  
    camera.offset = Vector2{640, 360};   
    camera.rotation = 0;               
    camera.zoom = 1.0f;                 
    SetTargetFPS(60);
    redTexture = LoadTexture("assets/ante_red.png");
    blueTexture = LoadTexture("assets/ante_blue.png");
    backgroundTexture = LoadTexture("assets/ground.png");
    std::vector<Ante> ants;  
    ants.reserve(10000); 
    std::vector<food> foods ;
  
    
    for(int i = 0 ; i < 200 ; i ++){
        float radius = 20.0f;

           

            foods.push_back({
                    Vector2{
                              (float)GetRandomValue(radius, WORLD_WIDTH - radius),
                              (float)GetRandomValue(radius, WORLD_HEIGHT - radius)
                                 },
                              radius,
                             20
                        });
    }

    for(int i = 0 ; i < 100 ; i ++){
        ants.push_back(Ante()) ;
       
    }
    
   

    while (!WindowShouldClose())
    {   
        camera.zoom += GetMouseWheelMove() * 0.1f;
        if(IsKeyDown(KEY_A)){
            camera.target.x -= 13 ;
        }
        if(IsKeyDown(KEY_D)){
            camera.target.x += 13 ;
        }
        if(IsKeyDown(KEY_W)){
            camera.target.y -= 13 ;
        }
        if(IsKeyDown(KEY_S)){
            camera.target.y += 13 ;
        }
        if(camera.zoom < 0.1f) camera.zoom = 0.1f; 
        if(camera.zoom > 3.0f) camera.zoom = 3.0f;  
        for(auto & a : ants){
            a.Update(foods , ants) ;
        }
        for (std::vector<Ante>::size_type i = 0; i < ants.size(); )
           {
              if (!ants[i].alive)
                ants.erase(ants.begin() + i); 
                   else
                   i++;
                  }


        
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        int redCount = 0;
        int blueCount = 0;
        int foodCount = 0 ;

          for (auto &a : ants) {
             if (!a.alive) continue; 
             if (a.isRed) redCount++;
             else blueCount++;
           }
           for (auto &_ : foods){
             foodCount++ ;
           }
       


        BeginMode2D(camera);
              for(int x = 0; x < WORLD_WIDTH; x += backgroundTexture.width){
                for(int y = 0; y < WORLD_HEIGHT; y += backgroundTexture.height){
                        DrawTexture(backgroundTexture, x, y, WHITE);
                                 }
                       }

        
        
        for(auto& a : ants){
            a.Draw();
        }
        for(auto &f : foods){
            DrawCircleV(f.position, f.size, BLACK);
         }
         
        EndMode2D();
        DrawRectangle(0,0 , 700 , 79 , BLACK) ;
        std::stringstream ssRed;
       ssRed << "Red ants: " << redCount;
       DrawText(ssRed.str().c_str(), 20, 50, 20, RED);

       
       std::stringstream ssBlue;
       ssBlue << "Blue ants: " << blueCount;
       DrawText(ssBlue.str().c_str(), 250, 50, 20, BLUE); 
       std::stringstream ssFood ;
       ssFood << "FOOD :  " << foodCount ;
       DrawText(ssFood.str().c_str(), 500, 50, 20, GREEN); 
       

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(redTexture);
    UnloadTexture(blueTexture);
    return 0;
}