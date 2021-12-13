#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "tuple"

#include "../../OpenGL/include/glew/include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#include "../include/GLFW/glfw3native.h"

#include "game_level.h"
#include "sprite_renderer.h"
#include "game_object.h"


//��Ϸ״̬
enum GameState {
	GAME_ACTIVE = 0,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP = 1,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class CGame
{
	public:
		//��Ϸ״̬
		GameState State;
		GLboolean Keys[1024];
		GLuint    Width, Height;
		std::vector<CGameLevel> Levels;
		GLuint Level;		


		//���캯�� ����
		CGame(GLuint width, GLuint height);
		~CGame();

		//��ʼ��
		void Init();

		//��Ϸѭ��
		void ProcessInput(GLfloat dt);
		void Update(GLfloat dt);
		void Render();

		//��ײ
		void DoCollisions();
		GLboolean CheckCollision(CGameObject& one, CGameObject& two);		//AABB-AABB��ײ���
		Collision CheckCollision_adv(CBallObject& one, CGameObject& two);	//AABB-Circle
		//�����ж�
		Direction VectorDirection(glm::vec2 target);
		
		//����
		void ResetLevel();
		void ResetPlayer();
};

#endif