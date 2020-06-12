#pragma once
#include"libs.h"

class Light
{
protected:
	float intensity;
	glm::vec3 color;

public:
	Light(float intensity, glm::vec3 color)
	{
		this->intensity = intensity;
		this->color = color;
	}

	~Light()
	{

	}

	//Functions
	virtual void sendToShader(Shader& program) = 0;
};

class PointLight : public Light
{
protected:
	glm::vec3 position;
	float constant;
	float linerar;
	float quadratic;

public:
	PointLight(glm::vec3 position, float intensity=1.f, glm::vec3 color=glm::vec3(1.f),
		float constant = 1.f,float linear = 0.045f,float quadratic=0.0075f)
		: Light(intensity, color)
	{
		this->position = position;
		this->constant = constant;
		this->linerar = linear;
		this->quadratic = quadratic;
	}

	~PointLight()
	{

	}
	void setPosition(const glm::vec3 position)
	{
		this->position = position;
	}
	void sendToShader(Shader& program)
	{
		program.setVec3f(this->position, "pointlight.position");
		program.set1f(this->intensity, "pointlight.intensity");
		program.setVec3f(this->color, "pointlight.color");
		program.set1f(this->constant, "pointlight.constant");
		program.set1f(this->linerar, "pointlight.linerar");
		program.set1f(this->quadratic, "pointlight.quadratic");
	}
};