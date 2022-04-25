#include "widget/Screen/Game_world/widget/erelia_npc_creator_interface.h"

#define SET_BUTTON_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->unselected_box().set_border_size(space.x); widget->selected_box().set_border_size(space.x);}
#define SET_FRAME_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->box().set_border_size(space.x); }
#define SET_LABEL_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->box().set_border_size(space.x); }
#define SET_WIDGET_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); }

void NPC_creator_interface::_on_geometry_change()
{
	jgl::Vector2Int frame_size = jgl::Vector2Int(_area.x / 3, _area.y);
	jgl::Vector2Int button_size = _area.y / 15;
	jgl::Vector2Int slider_size = button_size * 1.3f;
	jgl::Vector2Int space = button_size / 10;
	jgl::Vector2Int renderer_size = frame_size.x / 2;
	jgl::Size_t nb_line = 10;
	jgl::Vector2Int line_size = jgl::Vector2Int(frame_size.x - space.x * 4, (frame_size.y - renderer_size.y - space.y * nb_line) / nb_line - space.y / nb_line);
	jgl::Vector2Int line_sub_part = jgl::Vector2Int(line_size.x - space.x * 2 - line_size.y * 2, line_size.y);
	
	_slider->define_position(jgl::Vector2Int(_area.x - button_size.x * 2 - space.x * 2, 0), jgl::Vector2Int(_area.x - button_size.x * 2 - space.x * 2 - frame_size.x, 0));

	if (_slider->is_opened() == true)
		_slider->set_geometry(_slider->opened_position(), _area);
	else
		_slider->set_geometry(_slider->closed_position(), _area);

	SET_BUTTON_LOOK(_slider_button, jgl::Vector2Int(button_size.x + space.x + space.x + button_size.x - slider_size.x, slider_size.y), slider_size);

	SET_LABEL_LOOK(_frame, jgl::Vector2Int(_slider_button->anchor().x + slider_size.x, 0), frame_size);
	SET_WIDGET_LOOK(_entity_renderer, jgl::Vector2Int(frame_size.x / 4, space.y * 2), renderer_size);

	jgl::Vector2Int pos = jgl::Vector2Int(space.x * 2, space.y * 2 + renderer_size.y + space.y * 2);
	jgl::Vector2Int line_button_size = line_size.y;

	SET_LABEL_LOOK(_name_entry, pos, line_size);

	pos.y += line_size.y + space.y;

	SET_BUTTON_LOOK(_previous_type_button, pos, line_button_size);
	SET_LABEL_LOOK(_entity_type_label, pos + jgl::Vector2Int(line_size.y + space.x, 0), line_sub_part);
	SET_BUTTON_LOOK(_next_type_button, pos + jgl::Vector2Int(line_size.y + space.x + line_sub_part.x + space.x, 0), line_button_size);

	pos.y += line_size.y + space.y;

	jgl::Vector2Int label_size = line_size - jgl::Vector2Int(line_button_size.x + space.x, 0.0f);
	jgl::cout << "Line : " << pos << " / " << label_size << jgl::endl;
	SET_LABEL_LOOK(_entity_position_label, pos, label_size);
	SET_BUTTON_LOOK(_entity_position_definition_button, pos + jgl::Vector2Int(label_size.x + space.x, 0), line_button_size);

	pos.y += line_size.y + space.y;

	SET_BUTTON_LOOK(_previous_movement_type_button, pos, line_button_size);
	SET_LABEL_LOOK(_entity_movement_type_label, pos + jgl::Vector2Int(line_size.y + space.x, 0), line_sub_part);
	SET_BUTTON_LOOK(_entity_movement_path_reset_button, pos + jgl::Vector2Int(line_size.y + space.x + line_sub_part.x + space.x, 0), line_button_size);

	/*
	SET_LABEL_LOOK(_previous_movement_type_button, anchor, area);

	SET_LABEL_LOOK(_entity_movement_type_label, anchor, area);

	SET_LABEL_LOOK(_entity_movement_path_definition_button, anchor, area);

	SET_LABEL_LOOK(_entity_movement_path_reset_button, anchor, area);

	SET_LABEL_LOOK(_next_movement_type_button, anchor, area);

	SET_LABEL_LOOK(_creation_confirmation_button, anchor, area);

	SET_LABEL_LOOK(_creation_reset_button, anchor, area);
	*/
}

void NPC_creator_interface::_render()
{

}

jgl::Bool NPC_creator_interface::_update()
{
	static jgl::Bool last_state = true;

	if (last_state != _slider->is_opened())
	{
		_slider_button->label().set_text((_slider->is_opened() == true ? ">" : "<"));
		last_state = _slider->is_opened();
	}

	return (false);
}

NPC_creator_interface::NPC_creator_interface(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_slider = new Slider(this);
	_slider->activate();

	_slider_button = new jgl::Button([&](jgl::Data_contener& p_param) {
		_slider->change_state();
		}, _slider);
	_slider_button->label().set_text(">");
	_slider_button->activate();

	_frame = new jgl::Frame(_slider);
	_frame->activate();

	_entity_to_create = new Entity("", Entity::Type::NPC, -1);

	_entity_renderer = new Entity_renderer(_entity_to_create, _frame);
	_entity_renderer->activate();

	_name_entry = new jgl::Text_entry("", _frame);
	_name_entry->activate();

	_previous_type_button = new jgl::Button([&](jgl::Data_contener& p_param) {

		}, _frame);
	_previous_type_button->label().set_text("<");
	_previous_type_button->activate();

	_entity_type_label = new jgl::Text_label("", _frame);
	_entity_type_label->activate();

	_next_type_button = new jgl::Button([&](jgl::Data_contener& p_param) {
		
		}, _frame);
	_next_type_button->label().set_text(">");
	_next_type_button->activate();



	_entity_position_label = new jgl::Text_label("", _frame);
	_entity_position_label->activate();

	_entity_position_definition_button = new jgl::Button([&](jgl::Data_contener& p_param) {

		}, _frame);
	_entity_position_definition_button->activate();

	_previous_movement_type_button = new jgl::Button([&](jgl::Data_contener& p_param) {

		}, _frame);
	_previous_movement_type_button->activate();

	_entity_movement_type_label = new jgl::Text_label("", _frame);
	_entity_movement_type_label->activate();

	_entity_movement_path_definition_button = new jgl::Button([&](jgl::Data_contener& p_param) {

		}, _frame);
	_entity_movement_path_definition_button->activate();

	_entity_movement_path_reset_button = new jgl::Button([&](jgl::Data_contener& p_param) {

		}, _frame);
	_entity_movement_path_reset_button->activate();

	_next_movement_type_button = new jgl::Button([&](jgl::Data_contener& p_param) {

		}, _frame);
	_next_movement_type_button->activate();

	_creation_confirmation_button = new jgl::Button([&](jgl::Data_contener& p_param) {

		}, _frame);
	_creation_confirmation_button->activate();

	_creation_reset_button = new jgl::Button([&](jgl::Data_contener& p_param) {

		}, _frame);
	_creation_reset_button->activate();
}