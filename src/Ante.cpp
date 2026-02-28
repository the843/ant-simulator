#include "Ante.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>
extern Texture2D redTexture;
extern Texture2D blueTexture;
float scale = 0.2f;
Ante::Ante(){
    position = Vector2{(float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight())};
    velocity = Vector2{0,0};
    forward = Vector2{0,1};
    target = Vector2{0,0};
    speed = 100.0f;
    health = 100.0f;
    alive = true;
    isRed = GetRandomValue(0,1) == 1 ? true : false;
    texture = isRed ? redTexture : blueTexture;  
    sourceRec = {0, 0, (float)texture.width, (float)texture.height};
    origin = {(float)texture.width / 2 * scale, (float)texture.height / 2 * scale};
    destRec.width = (float)texture.width * scale;
    destRec.height = (float)texture.height * scale;
    rotation = 0;
    
}



Ante::Ante(Vector2 spawnPos, bool team)
{
    position = spawnPos;
    velocity = Vector2{0,0};
    forward = Vector2{0,1};
    target = Vector2{0,0};
    speed = 100.0f;
    health = 100.0f;
    alive = true;

    isRed = team;
    texture = isRed ? redTexture : blueTexture;

    sourceRec = {0, 0, (float)texture.width, (float)texture.height};
    origin = {(float)texture.width / 2 * scale, (float)texture.height / 2 * scale};
    destRec.width = (float)texture.width * scale;
    destRec.height = (float)texture.height * scale;

    rotation = 0;
}
void Ante::Update(std::vector<food>& foods  , std::vector<Ante> & ants)
{
    timeSinceLastFood += GetFrameTime(); 

    
      health -= GetFrameTime() * 5.0f; 

    
     if (health <= 0.0f || timeSinceLastFood > 40.0f) {
         alive = false;
       }
    float closedist = 1e6;
    int closestIndex = -1;

   
    for (std::vector<food>::size_type i = 0; i < foods.size(); i++)
    {
        float d = Vector2Distance(position, foods[i].position);
        if (d < closedist)
        {
            closedist = d;
            target = foods[i].position;
            closestIndex = i;
        }
    }

   
    if(closestIndex != -1) 

    {
        Vector2 dir = Vector2Subtract(target, position);
        dir = Vector2Normalize(dir);
        velocity = Vector2Scale(dir, speed * GetFrameTime());
        position = Vector2Add(position, velocity);
        forward = dir;
        
        float targetRotation = atan2(dir.y, dir.x) * 180.0f / PI + 90.0f;
        

       
        rotation = rotation + (targetRotation - rotation) * 0.1f; 


        destRec.x = position.x - destRec.width / 2;
        destRec.y = position.y - destRec.height / 2;

        
        if (Vector2Distance(position, target) < foods[closestIndex].size)
        {
            health += foods[closestIndex].nutrition;
            foods.erase(foods.begin() + closestIndex); 
            timeSinceLastFood = 0.0f; 
            Vector2 babyPos;
            babyPos.x = position.x + GetRandomValue(-500, 1000);
            babyPos.y = position.y + GetRandomValue(-500, 1000);

            ants.push_back(Ante(babyPos, isRed));
            float radius = 10.0f;

            const float WORLD_WIDTH = 1280 * 10;
            const float WORLD_HEIGHT = 720 * 10;

            foods.push_back({
                    Vector2{
                              (float)GetRandomValue(radius, WORLD_WIDTH - radius),
                              (float)GetRandomValue(radius, WORLD_HEIGHT - radius)
                                 },
                              radius,
                             20
                        });
           
                    
        }
    }
  
}      
void Ante::Draw(){
     DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);

}