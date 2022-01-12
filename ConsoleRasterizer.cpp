//made by clemdemort 07/01/2022
#include <iostream>
#include <windows.h>
#include <time.h>
#include "vec.h"
#include "Geometry.h"

#define Width 77
#define Height 77
#define FOV 0.5

void loop();
char draw(vec2 coord);
void gotoxy(int column, int line);
vec2 normalize(vec2 coord);
void cube(int Bpos, vec2 corner1, vec2 corner2, vec2 corner3, vec2 corner4, vec2 corner5, vec2 corner6, vec2 corner7, vec2 corner8);


//initialises our object buffer as a global entity so that we can use it's data from anywhere
ObjectBuffer Buffer;
int main()
{
    loop();
    return 1;
}
//goes to X Y location in the console
void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}
void cube(int Bpos,vec3 UR1, vec3 UL1, vec3 DR1, vec3 DL1, vec3 UR2, vec3 UL2 ,vec3 DR2,vec3 DL2)
{
    triangle3d vertexes;
    vertexes.vertex1 = UL1;
    vertexes.vertex2 = UR1;
    vertexes.vertex3 = DR1;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(0 + Bpos, vertexes);
    vertexes.vertex1 = UL1;
    vertexes.vertex2 = DL1;
    vertexes.vertex3 = DR1;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(1 + Bpos, vertexes);
    vertexes.vertex1 = UL2;
    vertexes.vertex2 = UR2;
    vertexes.vertex3 = DR2;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(2 + Bpos, vertexes);
    vertexes.vertex1 = UL2;
    vertexes.vertex2 = DL2;
    vertexes.vertex3 = DR2;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(3 + Bpos, vertexes);
    vertexes.vertex1 = DR2;
    vertexes.vertex2 = DR1;
    vertexes.vertex3 = DL1;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(4 + Bpos, vertexes);
    vertexes.vertex1 = DR2;
    vertexes.vertex2 = DL2;
    vertexes.vertex3 = DL1;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(5 + Bpos, vertexes);
    vertexes.vertex1 = UR2;
    vertexes.vertex2 = UR1;
    vertexes.vertex3 = UL1;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(6 + Bpos, vertexes);
    vertexes.vertex1 = UR2;
    vertexes.vertex2 = UL2;
    vertexes.vertex3 = UL1;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(7 + Bpos, vertexes);
    vertexes.vertex1 = UR1;
    vertexes.vertex2 = DR1;
    vertexes.vertex3 = DR2;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(8 + Bpos, vertexes);
    vertexes.vertex1 = DR2;
    vertexes.vertex2 = UR2;
    vertexes.vertex3 = UR1;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(9 + Bpos, vertexes);
    vertexes.vertex1 = UL1;
    vertexes.vertex2 = DL1;
    vertexes.vertex3 = DL2;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(10 + Bpos, vertexes);
    vertexes.vertex1 = DL2;
    vertexes.vertex2 = UL2;
    vertexes.vertex3 = UL1;
    vertexes.vCol1 = 1;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 1;
    Buffer.set(11 + Bpos, vertexes);
    
}


void loop()
{
    
    Buffer.generate(12);

    char* screenbuffer = new char[Width * Height];
    float t = 0;
    float r = 0;
    clock_t starttime = clock();
    vec2 coords;
    Mat3 rotX;
    Mat3 rotY;
    float ElapsedTime = 0;
    int count;
    while (1)
    {
        t = clock() / 1000.0;
        rotX = { cos(t),-sin(t), 0,
                sin(t),cos(t),  0,
                0,   0,         1
        };
        rotY = { cos(t) ,0,-sin(t),
                 0      ,1,      0,
                 sin(t) ,0, cos(t)
        };
        vec3 co1 = V3M3product(V3M3product(vec3{ 0.5,0.5,-0.5 }, rotY), rotX);
        vec3 co2 = V3M3product(V3M3product(vec3{ -0.5,0.5,-0.5 }, rotY), rotX);
        vec3 co3 = V3M3product(V3M3product(vec3{ 0.5,-0.5,-0.5 }, rotY), rotX);
        vec3 co4 = V3M3product(V3M3product(vec3{ -0.5,-0.5,-0.5 }, rotY), rotX);
        vec3 co5 = V3M3product(V3M3product(vec3{ 0.5,0.5,0.5 }, rotY), rotX);
        vec3 co6 = V3M3product(V3M3product(vec3{ -0.5,0.5,0.5 }, rotY), rotX);
        vec3 co7 = V3M3product(V3M3product(vec3{ 0.5,-0.5,0.5 }, rotY), rotX);
        vec3 co8 = V3M3product(V3M3product(vec3{ -0.5,-0.5,0.5 }, rotY),rotX);
        co1.z += 1;
        co2.z += 1;
        co3.z += 1;
        co4.z += 1;
        co5.z += 1;
        co6.z += 1;
        co7.z += 1;
        co8.z += 1;
        cube(0, co1,co2,co3,co4,co5,co6,co7,co8);
        


        float starttimer = clock() / 1000.0;//division by 1000 because we want to use seconds
        //resets the screen position each frame
        Buffer.project(vec3{ 0,0,0 }, FOV);
        gotoxy(0, 1);
        fflush(stdout);
        count = 0;
        for (int y = 0; y < Height; y++)
        {
            coords.y = y;
            for (int x = 0; x < Width; x++)
            {
                count += 1;
                coords.x = x;
                vec2 c = normalize(coords);
                screenbuffer[(y * Width) + x] = draw(c);
            }
            screenbuffer[(y * Width)] = '\n';
        }
        screenbuffer[(Height * Width)] = '\0';
        printf("\n%s", screenbuffer);
        //gets the amount of FPS
        float endtimer = clock() / 1000.0;//division by 1000 because we want to use seconds
        ElapsedTime = endtimer - starttimer;
        gotoxy(0, 0);
        printf("FPS: %f", (1.0 / ElapsedTime));
    }
    //cleans stuff up when we dont need it anymore
    delete[] screenbuffer;
    Buffer.destroy();
}
//works kind of like a fragment shader
char draw(vec2 coord)
{
    return Buffer.rasterize(coord);
}
//normalizes screen coordinates
vec2 normalize(vec2 coord)
{
    vec2 ncoord;
    ncoord.x = float(2.0 * coord.x / Width) - 1.0; 
    ncoord.y = -float(2.0 * coord.y / Height) + 1.0;//we want Y = 1 to be on top rather than down
    return ncoord;
}
