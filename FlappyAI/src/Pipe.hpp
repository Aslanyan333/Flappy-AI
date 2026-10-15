#pragma once
#include<raylib.h>

class Pipe{
private:
    Vector2 velocity;

public:
    float width=70;
    Vector2 position;

    Pipe(float posX){
        position.x=posX;
        position.y=GetRandomValue(200,500);
        // position.y=GetRandomValue(100,100);
        velocity.x=-200;
    }

    void Update(float dt){
        position.x+=velocity.x*dt;
    }

    void Draw(){
        
        DrawRectangle(position.x,position.y-1100,width,1000,GREEN);
        DrawRectangle(position.x,position.y+100,width,1000,GREEN);
        // DrawRectangle(position.x,position.y,50,50,RED );
    }
};