#pragma once
#include <vector>
#include "game_object.h"
#include "resource_manager.h"

class CGameLevel
{
public:
	std::vector<CGameObject> Bricks;

	CGameLevel() { };
	//从文件中加载关卡
	void Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight);
	//渲染关卡
	void Draw(CSpriteRenderer& renderer);
	//检查一个关卡是否已完成
	GLboolean IsCompleted();
private:
	//由砖块数据初始化关卡
	void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeigght);

	//数字0：无砖块，表示关卡中空的区域
	//数字1：一个坚硬的砖块，不可被摧毁
	//大于1的数字：一个可被摧毁的砖块，不同的数字区分砖块的颜色

};