#include <Primitive.h>

Primitive::Primitive(const std::vector<PrimitiveVertex> V, const std::vector<unsigned int> I, const std::vector<Texture> T) : m_V{ V }, m_I{I},m_T{T}
{
	initBuffers();
}

void Primitive::initBuffers()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_V.size() * sizeof(PrimitiveVertex), &m_V[0], GL_STATIC_DRAW);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_I.size() * sizeof(unsigned int), m_I.data(), GL_STATIC_DRAW);

    // set VAO attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PrimitiveVertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PrimitiveVertex), (void*)offsetof(PrimitiveVertex, texCoordinates));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(PrimitiveVertex), (void*)offsetof(PrimitiveVertex, normCoordinates));

    glBindVertexArray(0);


}

void Primitive::DrawPrimitive(ShaderProgram* program) {
    unsigned int numDiffuseTex = 1, numSpecTex = 1, numNormals = 1;


    for (int index = 0; index < m_T.size(); index++) {
        glActiveTexture(GL_TEXTURE0 + index);
        Texturetype TexType = m_T[index].getType();
        std::string shaderTexture = "material";
        switch (TexType) {
        case Texturetype::DIFFUSE:
            shaderTexture += std::to_string(numDiffuseTex) + std::string(".diffuse");
            ++numDiffuseTex;
            break;
        case Texturetype::SPECULAR:
            shaderTexture += std::to_string(numSpecTex) + std::string(".specular") ;
            ++numSpecTex;
            break;
        case Texturetype::NORMAL:
            shaderTexture += std::to_string(numNormals) + std::string(".normal");
            ++numNormals;
            break;
        default:
            break;
        }
        program->setInt(shaderTexture.c_str(), index);
        m_T[index].bind();
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_I.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(0);

    for (int index = 0; index < m_T.size(); index++) {
        m_T[index].unbind();
    }

}


std::vector<PrimitiveVertex>* Primitive::getVertices()
{
	return &m_V;
}

std::vector<unsigned int>* Primitive::getIndices()
{
	return &m_I;
}

std::vector<Texture>* Primitive::getTextures()
{
	return &m_T;
}

unsigned int * Primitive::getVAO()
{
	return &VAO;
}

unsigned int * Primitive::getVBO()
{
	return &VBO;
}

unsigned int * Primitive::getEBO()
{
	return &EBO;
}
