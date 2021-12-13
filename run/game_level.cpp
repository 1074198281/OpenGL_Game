#include "game_level.h"

#include <fstream>
#include <iostream>
#include <sstream>

void CGameLevel::Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight)
{
	//��չ�������
	this->Bricks.clear();
	//���ļ��м���
	GLuint tileCode;
	CGameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;

	if (fstream)
	{
		while (std::getline(fstream, line))	//��ȡ�ؿ��ļ���ÿһ��
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;

			while (sstream >> tileCode)		//��ȡ���ո�ָ���ÿ������
			{
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
		{
			this->init(tileData, levelWidth, levelHeight);
		}
	}
}

void CGameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
	GLuint height = tileData.size();
	GLuint width = tileData[0].size();
	GLfloat uint_width = levelWidth / static_cast<GLfloat>(width);
	GLfloat uint_height = levelHeight / height;
	//����tileData��ʼ���ؿ�
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			//���ש������
			if (tileData[y][x] == 1)
			{
				glm::vec2 pos(uint_width * x, uint_height * y);
				glm::vec2 size(uint_width, uint_height);
				CGameObject obj(pos, size, CResourceManager::GetTexture("block_solid"),
					glm::vec3(0.8f, 0.8f, 0.7f));
				obj.IsSolid = GL_TRUE;
				this->Bricks.push_back(obj);
			}
			else if (tileData[y][x] > 1) {
				glm::vec3 color = glm::vec3(1.0f);		//Ĭ��Ϊ��ɫ
				if (tileData[y][x] == 2)
				{
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				}
				else if (tileData[y][x] == 3) {
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				}
				else if (tileData[y][x] == 4) {
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				}
				else if (tileData[y][x] == 5) {
					color = glm::vec3(1.0f, 0.f, 0.0f);
				}
				glm::vec2 pos(uint_width * x, uint_height * y);
				glm::vec2 size(uint_width, uint_height);
				this->Bricks.push_back(CGameObject(pos, size, CResourceManager::GetTexture("block"), color));
			}
		}
	}
}

void CGameLevel::Draw(CSpriteRenderer& renderer)
{
	for (CGameObject& tile : this->Bricks)
		if (!tile.Destroyed)
			tile.Draw(renderer);
}


GLboolean CGameLevel::IsCompleted()
{
	for (CGameObject& tile : this->Bricks)
		if (!tile.IsSolid && !tile.Destroyed)
			return GL_FALSE;
	return GL_TRUE;
}