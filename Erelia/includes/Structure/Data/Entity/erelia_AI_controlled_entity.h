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
			jgl::Timer timer = jgl::Timer();
			jgl::Vector2Int base = 0;
			jgl::Vector2Int destination = 0;
			jgl::Int range = 5;
			jgl::Size_t path_index = 0;
			jgl::Array<jgl::Vector2Int> path_anchor = jgl::Array<jgl::Vector2Int>();
			jgl::Array<jgl::Vector2Int> path = jgl::Array<jgl::Vector2Int>();

			jgl::Vector2Int generate_destination()
			{
				return (base + jgl::Vector2(jgl::generate_nbr(-range, range), jgl::generate_nbr(-range, range)));
			}
		};

		Pattern pattern = Pattern::Static;
		Data data;
	};
	static jgl::String to_string(Movement_info::Pattern p_pattern)
	{
		switch (p_pattern)
		{
		case Movement_info::Pattern::Static:
			return ("Static");
			break;
		case Movement_info::Pattern::Wander:
			return ("Wander");
			break;
		case Movement_info::Pattern::Path:
			return ("Path");
			break;
		}
		return ("Unknow");
	}
protected:
	Movement_info _movement_info;
	jgl::Bool _last_moving = false;

public:
	AI_controlled_entity(jgl::String p_name, Type p_type, jgl::Long p_id);
	AI_controlled_entity(jgl::String p_name, Type p_type, Movement_info::Pattern p_pattern, jgl::Long p_id);

	void set_movement_info(Movement_info p_movement_info);
	void place(jgl::Vector2 p_pos);
	void update();

	Movement_info& movement_info() { return (_movement_info); }

	void save(jgl::File& p_file);
	static AI_controlled_entity* load(jgl::File& p_file);
};