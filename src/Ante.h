#pragma once
#include <raylib.h>
#include <vector>
struct food {
    Vector2 position;
    float size;
    int nutrition;
};
class Ante{
    public:
    Ante();
    Ante(Vector2 spawnPos, bool team);
    void Update(std::vector<food>& foods , std::vector<Ante> & ants);
    void Draw();
    Vector2 position;
    Vector2 velocity;
    Vector2 forward;
    Vector2 target;
    Texture2D texture;

    float speed ;
    float health;
    bool alive;
    bool isRed ;
    Rectangle sourceRec ;
    Rectangle destRec  ;
    Vector2 origin ;
    float rotation ;
    float timeSinceLastFood = 0.0f;

};