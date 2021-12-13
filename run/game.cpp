#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "MathHelper.h"

//#include "../../OpenGL/glm-0.9.8.0/glm-0.9.8.0/glm/gtc/matrix_transform.hpp"

CSpriteRenderer* Renderer;

CGameObject* Player;

CBallObject* Ball;

// ��ʼ������Ĵ�С
const glm::vec2 PLAYER_SIZE(100, 20);
// ��ʼ�����������
const GLfloat PLAYER_VELOCITY(1500.0f);

//��ʼ�����ٶ�
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -150.0f);
//��뾶
const GLfloat BALL_RADIUS = 12.5f;




CGame::CGame(GLuint width, GLuint height)
	:State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

CGame::~CGame()
{
	delete Renderer;
	Renderer = nullptr;
	delete Player;
	Player = nullptr;
}

void CGame::Init()
{
	//������ɫ��
	CResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	//������ɫ��
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

	CResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	CResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	//��������
	CResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
	CResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
	CResourceManager::LoadTexture("textures/block.png", GL_FALSE, "block");
	CResourceManager::LoadTexture("textures/block_solid.png", GL_FALSE, "block_solid");
	CResourceManager::LoadTexture("textures/paddle.png", true, "paddle");	

	//����ר������Ⱦ�Ŀ���
	Renderer = new CSpriteRenderer(CResourceManager::GetShader("sprite"));

	//���عؿ�
	CGameLevel one; one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
	CGameLevel two; two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
	CGameLevel three; three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
	CGameLevel four; four.Load("levels/four.lvl", this->Width, this->Height * 0.5);

	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 1;

	glm::vec2 playerPos = glm::vec2(
		this->Width / 2 - PLAYER_SIZE.x / 2,
		this->Height - PLAYER_SIZE.y
	);
	Player = new CGameObject(playerPos, PLAYER_SIZE, CResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new CBallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, CResourceManager::GetTexture("face"));

}

void CGame::Update(GLfloat dt)
{
	//���¶������˶�
	Ball->Move(dt, this->Width);
	//��ײ���
	this->DoCollisions();

	if (Ball->Position.y >= this->Height)
	{
		this->ResetLevel();
		this->ResetPlayer();
	}
}

void CGame::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLuint velocity = PLAYER_VELOCITY * dt;
		//�ƶ�����
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)
			{
				Player->Position.x -= velocity;
				if (Ball->Stuck)
				{
					Ball->Position.x -= velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
			{
				Player->Position.x += velocity;
				if(Ball->Stuck)
				{
					Ball->Position.x += velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
			Ball->Stuck = false;
		}
	}


}

void CGame::Render()
{
	//Renderer->DrawSprite(CResourceManager::GetTexture("face"), glm::vec2(200, 200),
	//	glm::vec2(300, 400), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	//��ת45�㣬 ��ɫ����(0.0,1.0,0.0)

	if (this->State == GAME_ACTIVE)
	{
		//���Ʊ���
		Renderer->DrawSprite(CResourceManager::GetTexture("background"), glm::vec2(0, 0),
			glm::vec2(this->Width, this->Height), 0.0f);
		//���ƹؿ�
		this->Levels[this->Level].Draw(*Renderer);
		Player->Draw(*Renderer);
		Ball->Draw(*Renderer);
	}

}

void CGame::DoCollisions()
{
	for (CGameObject& box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision_adv(*Ball, box);
			if (std::get<0>(collision))
			{
				//��ʵ������
				if (!box.IsSolid)
				{
					box.Destroyed = GL_TRUE;
				}
				//��ײ����
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT)
				{
					Ball->Velocity.x = -Ball->Velocity.x;		//��תˮƽ�ٶ�
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
					{
						Ball->Position.x += penetration;
					}
					else {
						Ball->Position.x -= penetration;
					}
				}
				else {					//��ֱ������ײ
					Ball->Velocity.y = -Ball->Velocity.y;
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
					if (dir == UP)
					{
						Ball->Position.y -= penetration;
					}
					else {
						Ball->Position.y += penetration;
					}
				}

			}
		}
		Collision result = CheckCollision_adv(*Ball, *Player);
		if (!Ball->Stuck && std::get<0>(result))
		{
			//�������������λ���������ٶ�
			GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
			GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
			GLfloat percentage = distance / (Player->Size.x / 2);

			GLfloat strength = 2.0f;
			glm::vec2 oldVelocity = Ball->Velocity;
			Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
			//Ball->Velocity.y = -Ball->Velocity.y;
			Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
			Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
		}
	}
}

GLboolean CGame::CheckCollision(CGameObject& one, CGameObject& two)
{
	//���x�������ײ
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	//���y�������ײ
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	//�����ᶼ������ײ
	return collisionX && collisionY;
}

Collision CGame::CheckCollision_adv(CBallObject& one, CGameObject& two)
{
	//��ȡԲ������
	glm::vec2 center(one.Position + one.Radius);
	//����AABB����Ϣ(���ģ���߳�)
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);

	//��ȡ�������ĵ�ʸ����
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	//AABB_center����clamped�͵õ�����ײ���Ͼ���Բ����ĵ�
	glm::vec2 closest = aabb_center + clamped;
	
	//�ж�length < radius?
	difference = closest - center;
	//return glm::length(difference) < one.Radius;

	if (glm::length(difference) <= one.Radius)
	{
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	}
	else {
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
	}
}

Direction CGame::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),				//��
		glm::vec2(1.0f, 0.0f),				//��
		glm::vec2(0.0f, -1.0f),				//��
		glm::vec2(-1.0f, 0.0f),				//��
	};

	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

void CGame::ResetLevel()
{
	if (this->Level == 0)this->Levels[0].Load("levels/one.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 1)
		this->Levels[1].Load("levels/two.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 2)
		this->Levels[2].Load("levels/three.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 3)
		this->Levels[3].Load("levels/four.lvl", this->Width, this->Height * 0.5f);
}

void CGame::ResetPlayer()
{
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}