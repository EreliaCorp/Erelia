#pragma once

#include "structure/Data/Entity/erelia_entity.h"

class NPC : public Entity
{
public:
	struct Movement_info
	{
		enum class Pattern
		{
			Static,
			Wondering
		};
		struct Data
		{
			jgl::Vector2Int base;
			jgl::Vector2Int destination;
			jgl::Size_t range;
			jgl::Array<jgl::Vector2Int> path;

			jgl::Vector2Int calc_destination()
			{
				return (base + jgl::Vector2(jgl::generate_nbr(-range, range), jgl::generate_nbr(-range, range)));
			}
		};
	
		Pattern pattern = Pattern::Static;
		Data data;
	};

private:
	Movement_info _movement_info;

public:
	NPC(Entity::Type p_type = Entity::Type::NPC);

	void place(jgl::Vector2 p_pos);

	Movement_info& movement_info() { return (_movement_info); }

	void update();
};