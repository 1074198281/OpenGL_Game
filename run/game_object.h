#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../../OpenGL/glm-0.9.8.0/glm-0.9.8.0/glm/glm.hpp"
#include "../../OpenGL/include/glew/include/GL/glew.h"
#include "texture.h"
#include "sprite_renderer.h"

class CGameObject
{
public:
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation;
	GLboolean IsSolid;
	GLboolean Destroyed;

	CTexture2D Sprite;
	CGameObject();
	CGameObject(glm::vec2 pos, glm::vec2 size, CTexture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Draw(CSpriteRenderer& renderer);

};

class CBallObject : public CGameObject
{
public:
	GLfloat Radius;
	GLboolean Stuck;

	CBallObject();
	CBallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, CTexture2D sprite);
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};



#endif