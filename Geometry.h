//made by clemdemort 07/01/2022
#ifndef geometry_H
#define geometry_H
#include "vec.h"
#define precisioncorrection 0.0001 //this is needed because floating point precision makes it so that some pixels dont meet the requierment for being inside a triangle when they should.


//vertex positions MUST be normalized as this is the format the rasterizer will read
struct triangle2d
{
	vec2 vertex1; //8
	vec2 vertex2; //8
	vec2 vertex3; //8
	//color is defined as an uint8_t going from 0 to 10
	uint8_t vCol1; //4
	uint8_t vCol2; //4
	uint8_t vCol3; //4
	float dist;//this will act as some form of priority
};

struct triangle3d
{
	vec3 vertex1; //12
	vec3 vertex2; //12
	vec3 vertex3; //12
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
	char brightness[12] = " .-:=+%*@##";
	unsigned int Buffersize = {};
	triangle3d* data = new triangle3d[0];
	triangle2d* RasterBuffer = new triangle2d[0];
	//generates a buffer to hold "size" amount of triangles
	void generate(unsigned int size)
	{
		delete[] data;
		delete[] RasterBuffer;
		Buffersize = size;
		data = new triangle3d[size];
		RasterBuffer = new triangle2d[size];
	}
	//set "ID" location in the buffer to some triangle data
	void set(unsigned int ID, triangle3d thing)
	{
		if (ID <= Buffersize) { data[ID] = thing; }
		else { printf("[BUFFER-ERROR]:specified ID was out of the allocated memory!\n"); }
	}
	//this function will project every vertexes in the buffer then sort by distance and send that data onto the raster buffer
	void project(vec3 CamPos, float FOV)
	{
		triangle2d * temp = new triangle2d[Buffersize];
		float* temp2 = new float[Buffersize];
		for (int i = 0; i < Buffersize; i++)
		{
			temp[i].vertex1 = vec2{ float(data[i].vertex1.x * FOV / data[i].vertex1.z),float(data[i].vertex1.y * FOV / data[i].vertex1.z) };
			temp[i].vertex2 = vec2{ float(data[i].vertex2.x * FOV / data[i].vertex2.z),float(data[i].vertex2.y * FOV / data[i].vertex2.z) };
			temp[i].vertex3 = vec2{ float(data[i].vertex3.x * FOV / data[i].vertex3.z),float(data[i].vertex3.y * FOV / data[i].vertex3.z) };
			temp[i].vCol1 = data[i].vCol1;
			temp[i].vCol2 = data[i].vCol2;
			temp[i].vCol3 = data[i].vCol3;
			vec3 midpoint = vec3{ (data[i].vertex1.x + data[i].vertex2.x + data[i].vertex3.x) / 3.0,(data[i].vertex1.y + data[i].vertex2.y + data[i].vertex3.y) / 3.0,(data[i].vertex1.z + data[i].vertex2.z + data[i].vertex3.z) / 3.0 };
			temp2[i] = float(sqrt(pow(midpoint.x - CamPos.x, 2) + pow(midpoint.y - CamPos.y, 2) + pow(midpoint.z - CamPos.z, 2)));
		}
		

	}
	//rasterizes a point
	char rasterize(vec2 coord)
	{
		char color  = ' ';
		float col = 0;
		int icol = 0;
		for(int i = 0; i < Buffersize; i++)
		{
			//point triangle intersection as explained here:https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
			//calculates the area of the triangle
			float Ta = area(RasterBuffer[i].vertex1, RasterBuffer[i].vertex2, RasterBuffer[i].vertex3);
			float Aa = area(coord, RasterBuffer[i].vertex2, RasterBuffer[i].vertex3);
			float Ba = area(RasterBuffer[i].vertex1, coord, RasterBuffer[i].vertex3);
			float Ca = area(RasterBuffer[i].vertex1, RasterBuffer[i].vertex2, coord);

			//we test if the point is inside the triangle with the precision correction
			if (Ta <= Aa + Ba + Ca + precisioncorrection && Ta >= Aa + Ba + Ca - precisioncorrection && Ta > 0) 
			{	
				
				if (data[i].vCol1 == data[i].vCol2 && data[i].vCol2 == data[i].vCol3)
				{
					icol = int(data[i].vCol2);
					if (col < 0) { icol = 0; } 
					if (icol > 9) { icol = 9; }
					color = brightness[icol];
					return color;
				}else{
					//now we interpolate the color based on the area(my guess on how GL does it)
					col = ((Aa / Ta) * data[i].vCol1) + ((Ba / Ta) * data[i].vCol2) + ((Ca / Ta) * data[i].vCol3);
					icol = int(floor(col));
					//makes sure we are working within our color palette
					if (col < 0) { icol = 0; } 
					if (col > 9) { icol = 9; }
					//gets the color from our color(char) palette
					color = brightness[icol];
					return color;
				}
			}

		}
		return color;
	}
	//cleans the buffer
	void destroy() { delete[] data; }
};

#endif