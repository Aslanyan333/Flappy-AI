#pragma once
#include<raylib.h>
#include"AI.hpp"
#include<vector>
using namespace std;

class Bird{
private:
    Vector2 velocity={0,0};

    AI brain;
    Color color;
    
public:
    Vector2 position;
    float width=50;
    float height=50;


    bool dead=false;
    int score=0;

    void Die(){
        dead=true;
        velocity.y=0;
        velocity.x=-100;
    }

    Bird(){
        
        position={100,200};

        // position.y=GetRandomValue(100,400);

        color.r=(GetRandomValue(100,255));
        color.g=(GetRandomValue(100,255));
        color.b=(GetRandomValue(100,255));
        color.a=255;
    }

    void Input(float posY){
        vector<float> inp={velocity.y,position.y-posY};

        if(brain.Evaluate(inp)){
            velocity.y=-400;
        }
        
        // if(IsKeyPressed(KEY_UP)){
        //     velocity.y=-400;
        // }
    }

    void Update(float dt,float PosY){
        if(!dead){
            Input(PosY);
        }

        if(position.y <= 0 || position.y>=GetRenderHeight()-height){
            Die();
        }

        velocity.y+=900*dt;
        position.y+=velocity.y*dt;
        position.x+=velocity.x*dt;
    }

    void Draw(){
        DrawRectanglePro({position.x,position.y,width,height},{0,0},0,color);
    }

    void merge(Bird& a,Bird& b){
        // brain
        brain.merge(a.brain,b.brain);
    }

    void randomize(){
        brain.randomize();
    }

    void reset(){
        position={100,200};
        velocity={0,0};
        dead=false;
    }
};