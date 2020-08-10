#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define X 200
#define Y 50
#define N 15




struct FLY{
    int x;
    int y;
    int v[2];
};


int stage[X][Y] = {0};


struct FLY fly[N], food;
int rangeX = X/2;
int rangeY = Y/2;



void next_v()
{
int index, dx, dy;

    if(food.x > 0 && food.y > 0){
        for(index = 0; index < N; ++index){

            dx = food.x - fly[index].x;
            dy = food.y - fly[index].y;


            if(dx > 0 && dx < rangeX)
                fly[index].v[0] = rand()%2 *1;
            else if(dx == 0){}
                //boid[index].v[0] = 0;
            else if(dx < 0 && abs(dx) < rangeX)
                fly[index].v[0] = rand()%2 *(-1);
            else
                fly[index].v[0] = rand()%2 * (rand()%2 == 0? 1 : -1);


            if(dy > 0 && dy < rangeY)
                fly[index].v[1] = rand()%2 *1;
            else if(dy ==  0){}
                //boid[index].v[1] = 0;
            else if(dy < 0 && abs(dy) < rangeY)
                fly[index].v[1] = rand()%2 *(-1);
            else
                fly[index].v[1] = rand()%2 * (rand()%2 == 0? 1 : -1);
        }
    }

    else{
        for(index = 0; index < N; ++index){
            fly[index].v[0] = rand()%2 * (rand()%2 == 0? 1 : -1);
            fly[index].v[1] = rand()%2 * (rand()%2 == 0? 1 : -1);
        }
    }

}



void next_flies()
{
int index;
    next_v();

    for(index = 0; index < N; ++index){
        fly[index].x += fly[index].v[0];
        fly[index].y += fly[index].v[1];
    }
}



void init()
{
int index;

    srand((unsigned int)time(NULL));

    for(index = 0; index < N; ++index){
        fly[index].x    = rand()%X;
        fly[index].y    = rand()%Y;
        fly[index].v[0] = rand()%4;
        fly[index].v[1] = rand()%4;
    }
}




void print_stage()
{
int x, y, index;

    for(y = 0; y < Y; ++y){
        for(x = 0; x < X; ++x){
            if(x == food.x && y == food.y){
                printf("\x1b[1m");
                printf("F");
                printf("\x1b[0m");
            }


            else{
                for(index = 0; index < N; ++index){
                    if(x == fly[index].x && y == fly[index].y){
                        //printf("\x1b[31m");
                        printf("+");
                        //printf("\x1b[39m");
                    }
                }
            }

            printf(" ");

        }

        printf("\n");

    }
}




void set_food()
{
    food.x    = rand()%X;
    food.y    = rand()%Y;
    //food.v[0] = rand()%4;
    //food.v[1] = rand()%4;
}



int main(void)
{
int time = 1000000 * 0.1;
int counter = 0;

    init();

    while(1){
        if((counter % 200) == 0)
            food.x = food.y = -1;
        else if((counter % 100) == 0)
            set_food();

        system("clear");
        //printf("\033[2J");
        print_stage();
        next_flies();
        usleep(time);
        ++counter;

    }
    return 0;
}
