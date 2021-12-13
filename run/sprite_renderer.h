#pragma once
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "shader.h"
#include "texture.h"

#include "../../OpenGL/glm-0.9.8.0/glm-0.9.8.0/glm/glm.hpp"
#include "../../OpenGL/glm-0.9.8.0/glm-0.9.8.0/glm/gtc/matrix_transform.hpp"
#include "../../OpenGL/glm-0.9.8.0/glm-0.9.8.0/glm/gtc/type_ptr.hpp"

class CSpriteRenderer
{
public:
	CSpriteRenderer(const CShader& shader);
	~CSpriteRenderer();

	void DrawSprite(const CTexture2D& texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));

private:
	CShader shader;
	GLuint quadVAO;

	void initRenderData();

};

#endif