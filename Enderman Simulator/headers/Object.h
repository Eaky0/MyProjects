#pragma once



#include <glad/glad.h> 


#include <Primitive.h>

#include <Errors/InitializingSceneError.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ObjectLoader {
public:

	ObjectLoader(std::string const &file);
	void ApplyTexture(Texture T);
	void loopObjectPrimitives(const aiNode * n);
	std::vector<Texture> loadTextures(Texturetype t);
	bool TextureLoaded(const char* str, std::vector<Texture> * t_vec);
	void DrawObject(ShaderProgram * program);

private:
	aiTextureType getType(Texturetype t);
	std::string getTextureFromResources(std::string filename);

	Primitive Inspect(aiMesh * p);
	bool InvalidScene();

	std::string ResourceDir;
	aiMaterial* ObjectMaterials;
	Assimp::Importer imp;
	const aiScene* ObjectScene;
	aiNode* ObjectrootNode;
	std::vector<Texture> Memo_Textures;
	std::vector<Primitive> Prims;

};
