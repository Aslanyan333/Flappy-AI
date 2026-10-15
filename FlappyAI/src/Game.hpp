#pragma once
#include<raylib.h>
#include"Bird.hpp"
#include"Pipe.hpp"
// #include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Game{
    private:
        vector<Pipe> pipes;
        float time=0.0;
        float interval=1.6;
        float PosY=0;
        int alive =0;
        int generation=0;

        void AddPipe(){
            Pipe p(1000);
            pipes.push_back(p);
        }

        vector<Bird> birds;

        bool AreColliding(Bird& b,Pipe& p){
            if(b.position.x+b.width >= p.position.x && b.position.x <= p.position.x+p.width && (b.position.y <= p.position.y-100 || b.position.y+b.height >= p.position.y+100)){
                return true;
            }
            return false;

        }
    public:

        Game(){
            for(int i=0;i<700;i++){
                Bird b;
                birds.push_back(b);
            }
            AddPipe();
            PosY=pipes[0].position.y;
        }

        void Restart(){
            pipes.clear();
            time=0;
            AddPipe();
            PosY=pipes[0].position.y;


            sort(birds.begin(),birds.end(),[](Bird& a,Bird& b){
                return a.score > b.score;
            });

            // Bird newBird=birds[0].merge(birds[1]);
            for(int i=birds.size()-1;i>=2;i--){
                if(i <= 300){
                    birds[i].merge(birds[0],birds[1]);
                }else{
                    birds[i].randomize();
                }
                birds[i].reset();
            }
            // birds[0].randomize();
            // birds[1].randomize();
            birds[0].reset();
            birds[1].reset();
        }

        void addScore(){
            for(int i=0;i<birds.size();i++){
                if(!(birds[i].dead)){
                    birds[i].score++;
                }
            }
        }

        void Tick(float dt){
            Update(dt);
            Draw();
        }

        void Update(float dt){
            alive=0;

            for(Bird& b:birds){
                b.Update(dt,PosY);
                if(!b.dead){
                    alive++;
                }
            }
            time+=dt;

            if(time >= interval){
                time-=interval;
                AddPipe();
            }

            for(int i=0;i<pipes.size();i++){
                pipes[i].Update(dt);

                if(pipes[i].position.x < -70){
                    pipes.erase(pipes.begin()+i);
                    i--;
                }else if(pipes[i].position.x < 20){
                    addScore();
                    PosY=pipes[i+1].position.y;
                }
            }

            for(Bird& b:birds){
                for(Pipe& p:pipes){
                    if(AreColliding(b,p)){
                        b.Die();
                        break;
                    }
                }
            }
            
            if(alive == 0){
                Restart();
                generation++;
            }
        }

        void Draw(){
            ClearBackground(RAYWHITE);
            for(Bird& b:birds){
                b.Draw();
            }

            for(int i=0;i<pipes.size();i++){
                pipes[i].Draw();
            }

            DrawText(to_string(generation).c_str(),50,50,20,BLACK);
        }
};