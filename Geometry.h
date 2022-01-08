//made by clemdemort 07/01/2022
#ifndef geometry_H
#define geometry_H
#include "vec.h"
#define precisioncorrection 0.0001 //this is needed because floating point precision makes it so that some pixels dont meet the requierment for being inside a triangle when they should.


//vertex positions MUST be normalized as this is the format the rasterizer will read
struct triangle
{
	vec2 vertex1; //8
	vec2 vertex2; //8
	vec2 vertex3; //8
	//color is defined as an uint8_t going from 0 to 10
	uint8_t vCol1; //4
	uint8_t vCol2; //4
	uint8_t vCol3; //4
};
//simple math to calculate the area of a triangle
float area(vec2 p1, vec2 p2 , vec2 p3)
{
	return abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0);
}

class ObjectBuffer
{
public:
	char brightness[11] = " .-:=+%*#@";
	unsigned int Buffersize = {};
	triangle* data = new triangle[0];
	//generates a buffer to hold "size" amount of triangles
	void generate(unsigned int size)
	{
		delete[] data;
		Buffersize = size;
		data = new triangle[size];
	}
	//set "ID" location in the buffer to some triangle data
	void set(unsigned int ID, triangle thing)
	{
		if (ID <= Buffersize) { data[ID] = thing; }
		else { printf("[BUFFER-ERROR]:specified ID was out of the allocated memory!\n"); }
	}
	//rasterizes a point
	char rasterize(vec2 coord)
	{
		char color  =' ';
		float col = 0;
		for(int i = 0; i < Buffersize; i++)
		{
			//point triangle intersection as explained here:https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
			//calculates the area of the triangle
			float Ta = area(data[i].vertex1, data[i].vertex2, data[i].vertex3);
			float Aa = area(coord, data[i].vertex2, data[i].vertex3);
			float Ba = area(data[i].vertex1, coord, data[i].vertex3);
			float Ca = area(data[i].vertex1, data[i].vertex2, coord);

			//we test if the point is inside the triangle with the precision correction
			if (Ta <= Aa + Ba + Ca + precisioncorrection && Ta >= Aa + Ba + Ca - precisioncorrection) 
			{	
				//now we interpolate the color based on the area(my guess on how GL does it)
				col = ((Aa / Ta) * data[i].vCol1) + ((Ba / Ta) * data[i].vCol2) + ((Ca / Ta) * data[i].vCol3);
				int icol = int(col);
				//makes sure we are working within our color palette
				if (icol < 0) { icol = 0; } 
				if (icol > 10) { icol = 10; }
				//gets the color from our color(char) palette
				color = brightness[icol];
			}

		}
		return color;
	}
	//cleans the buffer
	void destroy() { delete[] data; }
};

#endif
