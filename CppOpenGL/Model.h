#pragma once

#include"Mesh.h"
#include"Texture.h"
#include"Shader.h"
#include"Material.h"

class Model
{
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	void updateUniforms()
	{

	}

public:
	Model(
		glm::vec3 position,
		Material* material,
		Texture* orTexDif,
		Texture* orTexSpec,
		std::vector<Mesh*>& meshes
	)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}
	}

	//OBJ file loaded model
	

	~Model()
	{
		for (auto*& i : this->meshes)
			delete i;
	}

	
	void update()
	{

	}

	void render(Shader* shader)
	{
		//Update the uniforms
		this->updateUniforms();

		//Update uniforms
		this->material->sendToShader(*shader);

		//Use a program (BECAUSE SHADER CLASS LAST UNIFORM UPDATE UNUSES IT)
		shader->use();
		//Activate texture for each mesh
		this->overrideTextureDiffuse->bind(0);
		this->overrideTextureSpecular->bind(1);
		//Draw
		for (auto& i : this->meshes)
		{
		

			i->render(shader); //Activates shader also
		}
	}
};