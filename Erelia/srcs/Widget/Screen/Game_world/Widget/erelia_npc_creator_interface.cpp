#include "widget/Screen/Game_world/widget/erelia_npc_creator_interface.h"

#define SET_BUTTON_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->unselected_box().set_border_size(space.x); widget->selected_box().set_border_size(space.x);}
#define SET_FRAME_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->box().set_border_size(space.x); }
#define SET_LABEL_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->box().set_border_size(space.x); }

void NPC_creator_interface::_on_geometry_change()
{
	jgl::Vector2Int frame_size = jgl::Vector2Int(_area.x / 3, _area.y);
	jgl::Vector2Int button_size = _area.y / 15;
	jgl::Vector2Int slider_size = button_size * 1.3f;
	jgl::Vector2Int space = button_size / 10;
	
	_slider->define_position(jgl::Vector2Int(_area.x - button_size.x * 2 - space.x * 2, 0), jgl::Vector2Int(_area.x - button_size.x * 2 - space.x * 2 - frame_size.x, 0));

	if (_slider->is_opened() == true)
		_slider->set_geometry(_slider->opened_position(), _area);
	else
		_slider->set_geometry(_slider->closed_position(), _area);

	SET_BUTTON_LOOK(_slider_button, jgl::Vector2Int(button_size.x + space.x + space.x + button_size.x - slider_size.x, slider_size.y), slider_size);

	SET_LABEL_LOOK(_frame, jgl::Vector2Int(_slider_button->anchor().x + slider_size.x, 0), frame_size);
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
	_slider_button->set_depth(_depth + 10000);
	_slider_button->label().set_text(">");
	_slider_button->activate();

	_frame = new jgl::Frame(_slider);
	_frame->set_depth(_depth + 10000);
	_frame->activate();
}