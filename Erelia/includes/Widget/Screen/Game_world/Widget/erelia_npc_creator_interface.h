#pragma once

#include "jgl.h"

#include "widget/Commun/erelia_slider_widget.h"
#include "structure/data/Entity/erelia_entity.h"

class NPC_creator_interface : public jgl::Widget
{
private:
	class Entity_renderer : public jgl::Widget
	{
	private:
		Entity* _entity;

		void _on_geometry_change()
		{

		}
		void _render()
		{
			_entity->render(_anchor, _area, _depth);
		}

	public:
		Entity_renderer(Entity* p_entity, jgl::Widget* p_parent) : jgl::Widget(p_parent)
		{
			_entity = p_entity;
		}
	};

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	Slider* _slider;

	jgl::Button* _slider_button;
	jgl::Frame* _frame;

	Entity* _entity_to_create;

	Entity_renderer* _entity_renderer;
	jgl::Text_entry* _name_entry;

	jgl::Button* _previous_type_button;
	jgl::Text_label* _entity_type_label;
	jgl::Button* _next_type_button;

	jgl::Text_label* _entity_position_label;
	jgl::Button* _entity_position_definition_button;

	jgl::Button* _previous_movement_type_button;
	jgl::Text_label* _entity_movement_type_label;
	jgl::Button* _entity_movement_path_definition_button;
	jgl::Button* _entity_movement_path_reset_button;
	jgl::Button* _next_movement_type_button;

	jgl::Button* _creation_confirmation_button;
	jgl::Button* _creation_reset_button;

public:
	NPC_creator_interface(jgl::Widget* p_parent);
};