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


//游戏状态
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
		//游戏状态
		GameState State;
		GLboolean Keys[1024];
		GLuint    Width, Height;
		std::vector<CGameLevel> Levels;
		GLuint Level;		


		//构造函数 析构
		CGame(GLuint width, GLuint height);
		~CGame();

		//初始化
		void Init();

		//游戏循环
		void ProcessInput(GLfloat dt);
		void Update(GLfloat dt);
		void Render();

		//碰撞
		void DoCollisions();
		GLboolean CheckCollision(CGameObject& one, CGameObject& two);		//AABB-AABB碰撞检测
		Collision CheckCollision_adv(CBallObject& one, CGameObject& two);	//AABB-Circle
		//方向判断
		Direction VectorDirection(glm::vec2 target);
		
		//重置
		void ResetLevel();
		void ResetPlayer();
};

#endif