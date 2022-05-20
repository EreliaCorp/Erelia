#include "structure/Data/Entity/erelia_enemy.h"
#include "structure/Data/Entity/erelia_spawner.h"
#include "structure/Data/Engine/erelia_engine.h"


Enemy::Enemy(Spawner* p_owner, jgl::String p_name, jgl::Long p_id) :
	AI_controlled_entity(p_name, Entity::Type::Enemy, AI_controlled_entity::Movement_info::Pattern::Static, p_id),
	_owner(p_owner)
{

}

void Enemy::update()
{

}