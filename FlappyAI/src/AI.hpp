#pragma once
#include<vector>
#include<cmath>
using namespace std;

class AI{
    private:
        vector<int> a={2,4,1};
        vector<vector<vector<float>>> w;
        vector<vector<float>> v;

    public: 
        AI(){
            w.resize(a.size()+1);
            v.resize(a.size()+1);

            for(int i=1;i<a.size();i++){
                w[i].resize(a[i]);

                for(int j=0;j<a[i];j++){
                    for(int k=0;k<a[i-1];k++){
                        w[i][j].push_back(float(GetRandomValue(-1000,1000))/1000);
                    }
                }
            }

            for(int i=0;i<a.size();i++){
                for(int j=0;j<a[i];j++){
                    v[i].push_back(0);
                }
            }
        }

        bool Evaluate(vector<float> input){
            for(int i=0;i<a[0];i++){
                v[0][i]=input[i];
            }

            for(int i=1;i<a.size();i++){
                // v[i]
                for(int j=0;j<a[i];j++){
                    v[i][j]=0;
                    for(int k=0;k<a[i-1];k++){
                        v[i][j]+=v[i-1][k]*w[i][j][k];
                    }
                    v[i][j]=2.0/(1+pow(2.71,-v[i][j]))-1.0;
                }
            }

            return v[2][0] >=0;
            // return true;
        }

        void merge(AI& x,AI& y){
            for(int i=1;i<a.size();i++){
                for(int j=0;j<a[i];j++){
                    for(int k=0;k<a[i-1];k++){
                        int Rand=GetRandomValue(0,2);

                        if(Rand == 1){
                            w[i][j][k]=x.w[i][j][k];
                        }else if(Rand == 2){
                            w[i][j][k]=y.w[i][j][k];
                        }else{
                            w[i][j][k]=float(GetRandomValue(-1000,1000))/1000;
                        }
                    }
                }
            }
        }

        
        void randomize(){
            for(int i=1;i<a.size();i++){
                for(int j=0;j<a[i];j++){
                    for(int k=0;k<a[i-1];k++){
                        w[i][j][k]=float(GetRandomValue(-1000,1000))/1000;
                    }
                }
            }
        }
};