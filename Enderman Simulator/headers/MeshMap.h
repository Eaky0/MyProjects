/*
* Author : Ieracitano Alessio
*/
#pragma once
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Errors/MeshLoadingError.h>
#include <Texture.h>
#include <iostream>
#include <vector>

class MeshMap {
private:
	int width, height, bytePerPixel;
	float scale, offset;
	const float NORMALIZE;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	VertexBuffer terrainVBO;
	IndexBuffer terrainEBO;
	unsigned int terrainVAO;

	std::vector<std::vector<float>> vHEIGHTS = {};


	unsigned int NUM_STRIPS;
	unsigned int NUM_VERTS_PER_STRIP;

	/*
	* Loads the data from an given image file
	* @param file the file name
	* @param mapData place to store the heightmap data
	* @throws MeshLoadingError incase the data couldn't be loaded
	*/
	void loadData(const char* file, unsigned char* &mapData);

	/*
	* We load the veritces using the map data
	* @param mapData the heighmap data
	*/
	void loadVertices(unsigned char* &mapData);

	/*
	* Create the indices between vertices
	*/
	void loadIndices();

	/*
	* Initsialize and bind the buffers
	*/
	void initBuffers();

	/*
	* Generate perlin noise
	*/
	void perlinNoise(float x, float y);
public:
	
	/*
	* Create an meshmap instance
	*/
	MeshMap();

	/*
	* Create an meshmap
	* @param the file to read heightmap data from
	*/
	MeshMap(const char* file);

	void createMap();
	
	void draw();


	int getWidth() { return width; };
	int getHeight() { return height; };

	float getHeightOf(float x, float z);
};