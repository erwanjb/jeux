#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./Mesh.hpp"
#include "./Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "./AssimpGLMHelpers.hpp"
#include "./BoneInfo.hpp"

using namespace std;

class Model 
{
public:
    // model data 
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
    inline Model(string const &path, bool gamma = false) : gammaCorrection(gamma)
{
    loadModel(path);
}
    void Draw(Shader &shader);
    std::map<std::string, BoneInfo> GetBoneInfoMap();
    int& GetBoneCount();
private:
    map<string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter = 0;
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    void SetVertexBoneDataToDefault(Vertex& vertex);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};