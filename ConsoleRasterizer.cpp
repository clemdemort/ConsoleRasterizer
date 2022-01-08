//made by clemdemort 07/01/2022
#include <iostream>
#include <windows.h>
#include <time.h>
#include "vec.h"
#include "Geometry.h"

#define Width 75
#define Height 75

void loop();
char draw(vec2 coord, triangle* list);
void gotoxy(int column, int line);
vec2 normalize(vec2 coord);


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

void loop()
{
    //here we generate the buffer and create a triangle to go inside it
    Buffer.generate(1);
    triangle vertexes;
    vertexes.vertex1.x = 0;
    vertexes.vertex1.y = 0.87;
    vertexes.vertex2.x = -0.75;
    vertexes.vertex2.y = -0.5;
    vertexes.vertex3.x = 0.75;
    vertexes.vertex3.y = -0.5;
    vertexes.vCol1 = 7;
    vertexes.vCol2 = 10;
    vertexes.vCol3 = 0;
    Buffer.set(0, vertexes);

    char* screenbuffer = new char[Width * Height];
    float t = 0;
    float r = 0;
    clock_t starttime = clock();
    vec2 coords;
    Mat2 rot;
    float ElapsedTime = 0;
    while (1)
    {
        t = clock() / 1000.0;
        rot = { cos(t),-sin(t),
                sin(t),cos(t) };

        float starttimer = clock() / 1000.0;//division by 1000 because we want to use seconds
        Buffer.data[0].vertex1 = V2M2product(vertexes.vertex1, rot);
        Buffer.data[0].vertex2 = V2M2product(vertexes.vertex2, rot);
        Buffer.data[0].vertex3 = V2M2product(vertexes.vertex3, rot);
        //resets the screen position each frame
        gotoxy(0, 1);
        for (int y = 0; y < Height; y++)
        {
            coords.y = y;
            for (int x = 0; x < Width; x++)
            {
                coords.x = x;
                vec2 c = normalize(coords);
                screenbuffer[(y * Width) + x] = draw(c, Buffer.data);
            }
            screenbuffer[(y * Width)] = '\n';
        }
        screenbuffer[(Height * Width) - 1] = '\0';
        printf("%s", screenbuffer);
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
char draw(vec2 coord, triangle* list)
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
