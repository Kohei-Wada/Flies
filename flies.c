#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define X 200
#define Y 50
#define N 50


typedef struct _FLY {
    int vx;
    int vy;
    int x;
    int y;
    int life;
}FLY;


typedef struct _FOOD {
    int x;
    int y;
    int life;
}FOOD;




int stage[X][Y] = {0};
FLY fly[N];
FOOD food;
int range = sqrt(X*X + Y*Y)/4;



void display(void)
{
    for(int y = 0; y < Y; ++y){
        for(int x = 0; x < X; ++x){

            if(stage[x][y] == 1)
                printf("+");
            else if(stage[x][y] == 2)
                printf("F");
            else
                printf(" ");
        }
        printf("\n");
    }
}



void init(void)
{
    srand((unsigned int)time(NULL));

    for(int n = 0; n < N; ++n){
        fly[n].x = rand()%X;
        fly[n].y = rand()%Y;
        fly[n].vx = 0;
        fly[n].vy = 0;
    }

    food.x = rand()%X;
    food.y = rand()%Y;
}




void set_stage(void)
{
    memset(stage, 0, sizeof(stage));
    for(int n = 0; n < N; ++n){
        if(0 < fly[n].x && fly[n].x < X && 0 < fly[n].y && fly[n].y < Y)
            stage[fly[n].x][fly[n].y] = 1;
    }
    if(0 < food.x  && 0 < food.y)
        stage[food.x][food.y] = 2;
}




void next_fly_v(void)
{

    if(0 < food.x && 0 < food.y){
        for(int n = 0; n < N; ++n){
            int dx = food.x - fly[n].x;
            int dy = food.y - fly[n].y;
            int d  = sqrt(dx*dx + dy*dy);

            if(d < range){
                if(dx > 0)
                    fly[n].vx = rand()%2;
                else
                    fly[n].vx = rand()%2 * (-1);

                if(dy > 0)
                    fly[n].vy = rand()%2;
                else
                    fly[n].vy = rand()%2 * (-1);

            }
            else{
                fly[n].vx = rand()%3 - 1;
                fly[n].vy = rand()%3 - 1;
            }
        }
    }
    else{
        for(int n = 0; n < N; ++n){
            fly[n].vx = rand()%3 - 1;
            fly[n].vy = rand()%3 - 1;
        }
    }
}



void next_flies(void)
{
    next_fly_v();
    for(int n = 0; n < N; ++n){
        fly[n].x += fly[n].vx;
        fly[n].y += fly[n].vy;
    }
}




void set_food(int counter)
{
    if(counter % 200 == 0){
        food.x = rand()%X;
        food.y = rand()%Y;
    }

    else if(counter % 100 == 0){
        food.x = -1;
        food.y = -1;
    }
}




int main(void)
{
int counter = 0;
int time = 1000000 * 0.1;

    init();

    while(1){
        system("clear");
        set_stage();
        display();
        next_flies();
        set_food(counter);
        usleep(time);
        ++counter;

    }
    return 0;

}
