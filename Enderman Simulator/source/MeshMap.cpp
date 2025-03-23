#include <MeshMap.h>

MeshMap::MeshMap(): width(0), height(0), bytePerPixel(0),
terrainVAO(0), NUM_STRIPS(0), NUM_VERTS_PER_STRIP(0),
NORMALIZE(255.0f), scale(200.0f), offset(150.0f) {}


MeshMap::MeshMap(const char* file) : NORMALIZE(255.0f),
scale(200.0f), offset(150.0f) {
    unsigned char* mapData;
    loadData(file, mapData);

    loadVertices(mapData);
    stbi_image_free(mapData);
    loadIndices();

    NUM_STRIPS = height - 1;
    NUM_VERTS_PER_STRIP = width * 2;

    initBuffers();
}

void MeshMap::loadData(const char* file, unsigned char* &mapData) {
	mapData = stbi_load(file, &width, &height, &bytePerPixel, 0); //bytePerVertices return the amount of bytes used in the image | example: RGB -> bytePerVertices = 3 or RGBA -> bytePerVertices = 4

	//Check if data got loaded correctly
	if (mapData == NULL) throw new MeshLoadingError();
}

void MeshMap::loadVertices(unsigned char*& mapData) {

    for (unsigned int i = 0; i < height; i++) {

        std::vector<float> vStrip;
        vHEIGHTS.push_back(vStrip);

        for (unsigned int j = 0; j < width; j++) {

            int rowOffset = (width * i);
            int pixelOffset = rowOffset + j;
            int byteOffset = pixelOffset * bytePerPixel;

            unsigned char* pixel = mapData + byteOffset;
            
            float x = i - ((float)height) / 2;
            float y = ((float)pixel[0] / NORMALIZE) * scale - offset;
            float z = j - ((float)width) / 2;

            vHEIGHTS[i].push_back(y);

            //Position coordinates
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            //Texture coordinates
            vertices.push_back(i);
            vertices.push_back(j);
        }
    }
}

void MeshMap::loadIndices() {
    for (unsigned int i = 0; i < height - 1; i++) {

        //Start of an new strip we add a degenerate
        if (i > 0)
            indices.push_back(width * i);

        //for each column add top and bottem vertices
        for (unsigned int j = 0; j < width; j++) { 

            //calculate the offset's
            unsigned int row = (width * i), nextRow = (width * (i + 1));
            unsigned int offsetRow = row + j, offsetNextRow = nextRow + j;

            //push the indices to the array
            indices.push_back(offsetRow);
            indices.push_back(offsetNextRow);
        }

        //add each end of the row we add a degenerate
        if (i < height - 2){
            unsigned int rowOffset = width * (i + 1);
            unsigned int lastItemIndex = width - 1;
            indices.push_back(rowOffset + lastItemIndex);
        }
    }
}

void MeshMap::initBuffers() {
    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    terrainVBO = VertexBuffer(vertices.size() * sizeof(float), &vertices[0]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    terrainEBO = IndexBuffer(indices.size() * sizeof(unsigned int), &indices[0]);

    //unbind
    glBindVertexArray(0);
}

void createMap() {}

void  MeshMap::draw() {
    glBindVertexArray(terrainVAO);
    glDrawElements(GL_TRIANGLE_STRIP, 
        NUM_VERTS_PER_STRIP * NUM_STRIPS,
        GL_UNSIGNED_INT,
        (void*)0);

    //unbind
    glBindVertexArray(0);
}

float MeshMap::getHeightOf(float x, float z)
{
    int i = x + ((float)height) / 2;
    int j = z + ((float)width) / 2;

    float CurrentHeight = vHEIGHTS[i][j];

    //std::cout << CurrentHeight << std::endl;

    return CurrentHeight;

}

void MeshMap::perlinNoise(float x, float y) {}