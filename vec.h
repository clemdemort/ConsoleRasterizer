//made by clemdemort 07/01/2022
//working build 12/01/2022
#ifndef vec_H
#define vec_H
//a vector struct holding two values
struct vec2
{
	float x;
	float y;
};
struct vec3
{
	float x;
	float y;
	float z;
};
//a Matrix struct holding four values
struct Mat2
{
	float Mat[4];
};
struct Mat3
{
	float Mat[9];
};
//product of two vectors
vec2 V2product(vec2 V1, vec2 V2)
{
	vec2 result;
	result.x = V1.x * V2.x;
	result.y = V1.y * V2.y;
	return result;
}
//product of a vector and a matrix
vec2 V2M2product(vec2 V, Mat2 M)
{
	vec2 result;
	result.x = V.x * M.Mat[0] + V.y * M.Mat[2];
	result.y = V.x * M.Mat[1] + V.y * M.Mat[3];
	return result;
}
vec3 V3M3product(vec3 V, Mat3 M)
{
	vec3 result;
	result.x = V.x * M.Mat[0] + V.y * M.Mat[3] + V.z * M.Mat[6];
	result.y = V.x * M.Mat[1] + V.y * M.Mat[4] + V.z * M.Mat[7];
	result.z = V.x * M.Mat[2] + V.y * M.Mat[5] + V.z * M.Mat[8];
	return result;
}
//i should probably learn how to use operator overloading...
#endif