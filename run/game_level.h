#pragma once
#include <vector>
#include "game_object.h"
#include "resource_manager.h"

class CGameLevel
{
public:
	std::vector<CGameObject> Bricks;

	CGameLevel() { };
	//���ļ��м��عؿ�
	void Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight);
	//��Ⱦ�ؿ�
	void Draw(CSpriteRenderer& renderer);
	//���һ���ؿ��Ƿ������
	GLboolean IsCompleted();
private:
	//��ש�����ݳ�ʼ���ؿ�
	void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeigght);

	//����0����ש�飬��ʾ�ؿ��пյ�����
	//����1��һ����Ӳ��ש�飬���ɱ��ݻ�
	//����1�����֣�һ���ɱ��ݻٵ�ש�飬��ͬ����������ש�����ɫ

};