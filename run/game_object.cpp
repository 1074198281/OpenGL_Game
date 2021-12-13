#include "game_object.h"

CGameObject::CGameObject()
	: Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), \
	Sprite(), IsSolid(false), Destroyed(false){ }

CGameObject::CGameObject(glm::vec2 pos, glm::vec2 size, CTexture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), \
	IsSolid(false), Destroyed(false){ }

void CGameObject::Draw(CSpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}



glm::vec2 CBallObject::Move(GLfloat dt, GLuint window_width)
{
	//如果没有被固定在挡板上
	if (!this->Stuck)
	{
		//移动球
		this->Position += Velocity * dt;
		//检查是否在窗口边界以外，如果是的话反转速度并回复到正确的位置
		if (this->Position.x <= 0.0f)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = 0.0f;
		}
		else if (this->Position.x + this->Size.x >= window_width)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = window_width - this->Size.x;
		}
		if (this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}
	}
	return this->Position;
}

CBallObject::CBallObject()
{

}

CBallObject::CBallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, CTexture2D sprite)
	: CGameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), Stuck(true)
{

}


void CBallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
}