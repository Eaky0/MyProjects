#include <Object.h>

ObjectLoader::ObjectLoader(std::string const& file) : ResourceDir{ file.substr(0, file.find_last_of('\\')) }
{
	try {
		ObjectScene = imp.ReadFile(file, aiProcess_Triangulate);

		if (InvalidScene()) {
			throw InitializingSceneError();
		}

		ObjectrootNode = ObjectScene->mRootNode;

	}
	catch (InitializingSceneError& e) {
		e.what();
		return;
	}

	loopObjectPrimitives(ObjectScene->mRootNode);
}

void ObjectLoader::ApplyTexture(Texture T)
{
}

void ObjectLoader::loopObjectPrimitives(const aiNode * n)
{
	for (int index = 0; index < n->mNumMeshes; ++index) {

		unsigned int mIndex = n->mMeshes[index];
		aiMesh* primitive = ObjectScene->mMeshes[mIndex];
		Prims.push_back(Inspect(primitive));
	}

	for (int index = 0; index < n->mNumChildren; ++index)
	{
		loopObjectPrimitives(n->mChildren[index]);
	}

}



void ObjectLoader::DrawObject(ShaderProgram* program)
{
	for (Primitive & p : Prims) {
		p.DrawPrimitive(program);
	}
}



Primitive ObjectLoader::Inspect(aiMesh* p)
{
	std::vector<PrimitiveVertex> V;
	std::vector<unsigned int> I;
	std::vector<Texture> T;


	//Get Vertices;
	for (int index = 0; index < p->mNumVertices; ++index) {

		PrimitiveVertex p_vec;
		glm::vec3 vec3;

		vec3.x = p->mVertices[index].x;
		vec3.y = p->mVertices[index].y;
		vec3.z = p->mVertices[index].z;

		p_vec.posCoordinates = vec3;

		if (p->HasNormals()) {
			vec3.x = p->mNormals[index].x;
			vec3.y = p->mNormals[index].y;
			vec3.z = p->mNormals[index].z;
			p_vec.normCoordinates = vec3;
		}

		glm::vec2 vec2;
		if (p->mTextureCoords[0])
		{
			vec2.x = p->mTextureCoords[0][index].x;
			vec2.y = p->mTextureCoords[0][index].y;
			p_vec.texCoordinates = vec2;
		}
		else {
			vec2.x = 0.0f;
			vec2.y = 0.0f;
			p_vec.texCoordinates = vec2;
		}
		V.push_back(p_vec);
	}

	//Get Indices
	for (int index = 0; index < p->mNumFaces; ++index) {
		for (int index2 = 0; index2 < p->mFaces[index].mNumIndices; ++index2) {
			I.push_back(p->mFaces[index].mIndices[index2]);
		}
	}


	//Get Materials
	ObjectMaterials = ObjectScene->mMaterials[p->mMaterialIndex];
	std::vector<Texture> diffuse = loadTextures(Texturetype::DIFFUSE);
	T.insert(T.end(), diffuse.begin(), diffuse.end());
	std::vector<Texture> specular = loadTextures(Texturetype::SPECULAR);
	T.insert(T.end(), specular.begin(), specular.end());
	std::vector<Texture> normal = loadTextures(Texturetype::NORMAL);
	T.insert(T.end(), normal.begin(), normal.end());

	return Primitive(V, I, T);
}

std::vector<Texture> ObjectLoader::loadTextures(Texturetype T) {

	std::vector<Texture> t_vec;
	aiTextureType TYPE = getType(T);

	for (int index = 0; index < ObjectMaterials->GetTextureCount(TYPE); index++) {
		aiString textureString;
		ObjectMaterials->GetTexture(TYPE, index, &textureString);
		if (!TextureLoaded(textureString.C_Str(), &t_vec)) {
			Texture t(getTextureFromResources(std::string(textureString.C_Str())).c_str());
			t.setType(T);
			t_vec.push_back(t);
			Memo_Textures.push_back(t);
		}
	}

	return t_vec;
}


std::string ObjectLoader::getTextureFromResources(std::string filename)
{
	filename = ResourceDir + "\\" + filename;
	return filename;
}


bool ObjectLoader::TextureLoaded(const char * str, std::vector<Texture> * t_vec) {
	for (Texture t : Memo_Textures) {

		std::string path = t.getPath();
		int slash = path.find_last_of("\\");
		std::string filename = path.substr(slash + 1, path.size() - 1);

		if (filename == str) {
			t_vec->push_back(t);
			return true;
		}
	}
	return false;
}





aiTextureType ObjectLoader::getType(Texturetype t)
{
	switch (t) {
	case Texturetype::DIFFUSE:
		return aiTextureType_DIFFUSE;
		break;
	case Texturetype::SPECULAR:
		return aiTextureType_SPECULAR;
		break;
	case Texturetype::NORMAL:
		return aiTextureType_HEIGHT;
		break;
	default:
		break;
	}
}






bool ObjectLoader::InvalidScene()
{
	return !ObjectScene || ObjectScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ObjectScene->mRootNode;
}
