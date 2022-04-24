#pragma once

#include "structure/Data/Entity/erelia_entity.h"

class AI_controlled_entity : public Entity
{
public:
	struct Movement_info
	{
		enum class Pattern
		{
			Static,
			Wander,
			Path
		};
		struct Data
		{
			jgl::Timer timer;
			jgl::Vector2Int base;
			jgl::Vector2Int destination;
			jgl::Int range;
			jgl::Size_t path_index;
			jgl::Array<jgl::Vector2Int> path;

			jgl::Vector2Int generate_destination()
			{
				return (base + jgl::Vector2(jgl::generate_nbr(-range, range), jgl::generate_nbr(-range, range)));
			}
		};

		Pattern pattern = Pattern::Static;
		Data data;
	};
protected:
	Movement_info _movement_info;
	jgl::Bool _last_moving = false;

public:
	AI_controlled_entity(jgl::String p_name, Type p_type, Movement_info::Pattern p_pattern, jgl::Long p_id);

	void set_movement_info(Movement_info p_movement_info);
	void place(jgl::Vector2 p_pos);
	void update();
	Movement_info& movement_info() { return (_movement_info); }
};