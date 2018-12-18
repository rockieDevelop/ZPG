#include "Object.h"

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

#include<iostream>

struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};

float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

Object::Object(Shader* shader, int id)
{
	ID = id;
	this->attach(shader);
}

void Object::makeObject(void) {
	glBindVertexArray(VAO);
	// draw triangles
	if (model) {
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, 2880); //mode,first,count
										  // update other events like input handling
	}
}

void Object::rotate(float rotation, float x, float y, float z) {
	M = glm::rotate(M, rotation, glm::vec3(x, y, z));
	notify();
}

void Object::translate(glm::vec3 t) {
	M = glm::translate(M, t);
	notify();
}

void Object::scale(glm::vec3 s) {
	M = glm::scale(M, s);
	notify();
}

void Object::load(std::string fileName)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slou�en� mal�ch plo�ek
		| aiProcess_JoinIdenticalVertices       // NUTN� jinak hodn� duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy


	//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile(fileName, importOptions);

	if (scene) { //pokud bylo nacteni uspesne
		printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

		for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
		{
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			printf("Material [%d] name %s\n", i, name.C_Str());

			aiColor4D d;

			glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);

		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
		{
			aiMesh* mesh = scene->mMeshes[i];

			Vertex* pVertices = new Vertex[mesh->mNumVertices];
			std::memset(pVertices, 0, sizeof(Vertex)* mesh->mNumVertices);

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				if (mesh->HasPositions())
				{
					pVertices[i].Position[0] = mesh->mVertices[i].x;
					pVertices[i].Position[1] = mesh->mVertices[i].y;
					pVertices[i].Position[2] = mesh->mVertices[i].z;
				}
				if (mesh->HasNormals())
				{
					pVertices[i].Normal[0] = mesh->mNormals[i].x;
					pVertices[i].Normal[1] = mesh->mNormals[i].y;
					pVertices[i].Normal[2] = mesh->mNormals[i].z;
				}
				if (mesh->HasTextureCoords(0))
				{
					pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
					pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
				}
				if (mesh->HasTangentsAndBitangents())
				{
					pVertices[i].Tangent[0] = mesh->mTangents[i].x;
					pVertices[i].Tangent[1] = mesh->mTangents[i].y;
					pVertices[i].Tangent[2] = mesh->mTangents[i].z;
				}

			}

			unsigned int* pIndices = nullptr;

			if (mesh->HasFaces())
			{

				pIndices = new unsigned int[mesh->mNumFaces * 3];
				for (unsigned int i = 0; i < mesh->mNumFaces; i++)
				{
					pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
					pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
					pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
				}
			}


			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(VAO);

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
			{
				std::cout << "GL ERROR: " << err << std::endl; return;
			} indicesCount = mesh->mNumFaces * 3;

			delete[] pVertices;
			delete[] pIndices;
		}
	}
	else {
		printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
	}
	glBindVertexArray(0);
}




void Object::attach(Observer *obs) {
	observers.push_back(obs);
}

void Object::notify() {
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->update(M);
	}
}


void Object::setPosition(glm::vec3 position) {
	M = glm::scale(glm::translate(glm::mat4(1.f), position), scaleVec);
	notify();
}

void Object::setColor(glm::vec3 clr) {
	color = clr;
}

void Object::setTexture(int texture)
{
	this->texture = texture;
}

glm::vec3 Object::getColor(void) {
	return color;
}

glm::mat4 Object::getModel(void) {
	return M;
}

float Object::getAmbientStrength(void) {
	return ambientStrength;
}

int Object::getTexture(void) {
	return texture;
}

int Object::getID(void) {
	return ID;
}

bool Object::isModel(void) {
	return model;
}

Object::~Object()
{
}
