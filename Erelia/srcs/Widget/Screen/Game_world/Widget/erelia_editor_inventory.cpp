#include "Widget/Screen/Game_world/Widget/erelia_editor_inventory.h"
#include "structure/Atlas/erelia_texture_atlas.h"
#include "structure/Atlas/erelia_translation_atlas.h"
#include "structure/Data/Map/erelia_chunk.h"
#include "structure/Data/Map/erelia_node.h"

extern jgl::Map< jgl::String, jgl::Array <std::tuple <jgl::Int, jgl::Vector2Int, jgl::Size_t> > > g_page_content;

void Editor_inventory::Inventory_renderer::_render()
{
	if (_image != nullptr)
	{
		_image->draw(_anchor, _area, _UV_pos, _UV_size, _depth + 1, 1.0f);
	}
}

void Editor_inventory::Inventory_renderer::_on_geometry_change()
{
	_UV_pos = 0;
	_UV_size = 1;
}

Editor_inventory::Inventory_renderer::Inventory_renderer(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}

void Editor_inventory::_render()
{
	if (_pages[_inventory_page_index] != nullptr && _pages[_inventory_page_index]->texture == nullptr)
	{
		_pages[_inventory_page_index]->compute();
		_inventory_frame_contener->set_texture(_pages[_inventory_page_index]->texture);
		_inventory_frame_contener->set_UVs(_pages[_inventory_page_index]->unit * _page_offset, _pages[_inventory_page_index]->unit * _nb_element_on_screen);
	}
	if (_inventory_page_index == _selected_page_index && _selected_item_pos.y >= _page_offset.y)
	{
		jgl::Vector2Int anchor = _inventory_frame_contener->cumuled_anchor() + _element_unit * (_selected_item_pos - _page_offset) - 5;
		jgl::Vector2Int area = _element_unit + 10;

		Texture_atlas::instance()->UI_sprite_sheet()->draw(
				jgl::Vector2Int(0, 0),
				anchor,
				area,
				_inventory_frame_contener->depth() + 1,
				1.0f);
	}
}

#define SET_BUTTON_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->unselected_box().set_border_size(space.x); widget->selected_box().set_border_size(space.x);}
#define SET_FRAME_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->box().set_border_size(space.x); }
#define SET_LABEL_LOOK(widget, anchor, area){widget->set_geometry(anchor, area); widget->box().set_border_size(space.x); }

void Editor_inventory::_on_geometry_change()
{
	jgl::Vector2Int button_size = _area.y / 15;
	jgl::Vector2Int space = button_size / 10;
	jgl::Vector2Int layer_label_size = jgl::Vector2Int(button_size.x * 3, button_size.y);
	jgl::Vector2Int slider_size = button_size * 1.3f;
	jgl::Vector2Int frame_size = jgl::Vector2Int(_area.x / 4, _area.y);
	jgl::Vector2Int page_name_label_size = jgl::Vector2Int(frame_size.x - button_size.x * 2 - space.x * 6, button_size.y);
	jgl::Vector2Int inventory_page_size = jgl::Vector2Int(frame_size.x - space.x * 4, frame_size.y - space.y * 5 - button_size.y);

	_slider->define_position(jgl::Vector2Int(_area.x - button_size.x * 2 - space.x * 2 - layer_label_size.x, 0), jgl::Vector2Int(_area.x - button_size.x * 2 - space.x * 2 - layer_label_size.x - frame_size.x, 0));

	if (_slider->is_opened() == true)
		_slider->set_geometry(_slider->opened_position(), _area);
	else
		_slider->set_geometry(_slider->closed_position(), _area);

	SET_BUTTON_LOOK(_lower_level_button, jgl::Vector2Int(0, 0), button_size);
	SET_LABEL_LOOK(_level_selected_label, jgl::Vector2Int(button_size.x + space.x, 0), layer_label_size);
	SET_BUTTON_LOOK(_raise_level_button, jgl::Vector2Int(button_size.x + space.x + layer_label_size.x + space.x, 0), button_size);

	SET_BUTTON_LOOK(_slider_button, jgl::Vector2Int(button_size.x + space.x + layer_label_size.x + space.x + button_size.x - slider_size.x, slider_size.y), slider_size);

	SET_LABEL_LOOK(_inventory_frame, jgl::Vector2Int(_slider_button->anchor().x + slider_size.x, 0), frame_size);

	SET_BUTTON_LOOK(_previous_page_button, _inventory_frame->anchor() + space * 2, button_size);
	SET_LABEL_LOOK(_page_name_label, _previous_page_button->anchor() + jgl::Vector2Int(button_size.x + space.x, 0), page_name_label_size);
	SET_BUTTON_LOOK(_next_page_button, _page_name_label->anchor() + jgl::Vector2Int(page_name_label_size.x + space.x, 0), button_size);

	_inventory_frame_contener->set_geometry(_previous_page_button->anchor() + jgl::Vector2Int(0, button_size.y + space.y), inventory_page_size);

	_element_unit = static_cast<jgl::Float>(_inventory_frame_contener->area().x) / Inventory_page::C_NB_ITEM_PER_LINE;
	_nb_element_on_screen = jgl::Vector2(_inventory_frame_contener->area()) / _element_unit;
	_page_offset = 0;

	if (_pages[_inventory_page_index] != nullptr)
		_inventory_frame_contener->set_UVs(_pages[_inventory_page_index]->unit * _page_offset, _pages[_inventory_page_index]->unit * _nb_element_on_screen);
}

jgl::Bool Editor_inventory::_update()
{
	static jgl::Ulong next_input = 0;
	static jgl::Bool last_state = true;

	if (last_state != _slider->is_opened())
	{
		_slider_button->label().set_text((_slider->is_opened() == true ? ">" : "<"));
		last_state = _slider->is_opened();
	}

	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Tab) == jgl::Input_status::Release)
	{
		_slider->change_state();
		return (true);
	}

	if (jgl::Application::active_application()->mouse().wheel() != 0 &&
		_inventory_frame_contener->is_pointed() == true &&
		next_input < jgl::Application::active_application()->time())
	{
		if (jgl::Application::active_application()->mouse().wheel() > 0 && _page_offset.y > 0)
		{
			if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift) == jgl::Input_status::Down)
			{
				_page_offset.y -= 5.0f;
			}
			else
			{
				_page_offset.y -= 1.0f;
			}
		}
		else if (jgl::Application::active_application()->mouse().wheel() < 0 && _page_offset.y < _pages[_inventory_page_index]->size.y)
		{
			if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift) == jgl::Input_status::Down)
			{
				_page_offset.y += 5.0f;
			}
			else
			{
				_page_offset.y += 1.0f;
			}
		}
		_inventory_frame_contener->set_UVs(_pages[_inventory_page_index]->unit* _page_offset, _pages[_inventory_page_index]->unit * _nb_element_on_screen);
		next_input = jgl::Application::active_application()->time() + 5;
	}
	if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Release &&
		_inventory_frame_contener->is_pointed() == true)
	{
		jgl::Vector2 mouse_pos = jgl::Application::active_application()->mouse().pos() - _inventory_frame_contener->cumuled_anchor();
		jgl::Vector2 node_pos = mouse_pos / _element_unit;
		jgl::Vector2 final_pos = node_pos + _page_offset;

		_selected_page_index = _inventory_page_index;
		_selected_item_pos = final_pos;
		_selected_item = _pages[_inventory_page_index]->item(_selected_item_pos);
	}

	return (false);
}

jgl::Bool Editor_inventory::_fixed_update()
{
	return (false);
}

void Editor_inventory::_compose_predefined_page()
{
	for (auto tmp : g_page_content)
	{
		Inventory_page* new_page = new Inventory_page(Translation_atlas::string(tmp.first));

		for (jgl::Size_t i = 0; i < tmp.second.size(); i++)
		{
			jgl::Size_t type = std::get<0>(tmp.second[i]);
			if (type == 0)
				new_page->add_item(std::get<1>(tmp.second[i]), new Node_item(std::get<2>(tmp.second[i])));
			else if (type == 1 && g_prefab_array[std::get<2>(tmp.second[i])]->size != 0)
				new_page->add_item(std::get<1>(tmp.second[i]), new Prefab_item(std::get<2>(tmp.second[i])));
			else if (type == 2)
				new_page->add_item(std::get<1>(tmp.second[i]), new Flag_item(static_cast<Flag_item::Color>(std::get<2>(tmp.second[i]))));
		}

		_pages.push_back(new_page);
	}
}

void Editor_inventory::_compose_custom_page()
{

}

void Editor_inventory::set_inventory_page(jgl::Size_t p_page_index)
{
	_page_offset = 0;
	_inventory_page_index = p_page_index;
	_page_name_label->label().set_text(Translation_atlas::string(_pages[_inventory_page_index]->name));

	if (_pages[_inventory_page_index] != nullptr)
	{
		_inventory_frame_contener->set_texture(_pages[_inventory_page_index]->texture);
		_inventory_frame_contener->set_UVs(_pages[_inventory_page_index]->unit * _page_offset, _pages[_inventory_page_index]->unit * _nb_element_on_screen);
	}

}

void Editor_inventory::set_level_value(jgl::Size_t p_level_value)
{
	_selected_level = p_level_value;
	_level_selected_label->label().set_text("Level : " + jgl::itoa(_selected_level + 1));
}

Editor_inventory::Editor_inventory(jgl::Widget* p_parent) : jgl::Widget(p_parent),
	_page_offset(0)
{
	_slider = new Slider(this);
	_slider->activate();

	_slider_button = new jgl::Button([&](jgl::Data_contener& p_param) {
		_slider->change_state();
		}, _slider);
	_slider_button->activate();

	_inventory_frame = new jgl::Frame(_slider);
	_inventory_frame->set_depth(_depth);
	_inventory_frame->activate();

	_inventory_frame_contener = new Inventory_renderer(_slider);
	_inventory_frame_contener->set_depth(_depth + 2);
	_inventory_frame_contener->activate();

	_previous_page_button = new jgl::Button([&](jgl::Data_contener& p_param)
		{
			if (_inventory_page_index == 0)
				set_inventory_page(_pages.size() - 1);
			else
				set_inventory_page(_inventory_page_index - 1);
		}, _slider);
	_previous_page_button->set_depth(_depth + 40);
	_previous_page_button->label().set_text("<");
	_previous_page_button->activate();

	_page_name_label = new jgl::Text_label("", _slider);
	_page_name_label->set_depth(_depth + 40);
	_page_name_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_page_name_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_page_name_label->activate();

	_next_page_button = new jgl::Button([&](jgl::Data_contener& p_param)
		{
			if (_inventory_page_index == _pages.size() - 1)
				set_inventory_page(0);
			else
				set_inventory_page(_inventory_page_index + 1);
		}, _slider);
	_next_page_button->set_depth(_depth + 40);
	_next_page_button->label().set_text(">");
	_next_page_button->activate();


	_level_selected_label = new jgl::Text_label("Level : ", _slider);
	_level_selected_label->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
	_level_selected_label->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	_level_selected_label->activate();

	_lower_level_button = new jgl::Button([&](jgl::Data_contener& p_param)
		{
			if (_selected_level > 0)
				set_level_value(_selected_level - 1);
		}, _slider);
	_lower_level_button->label().set_text("-");
	_lower_level_button->activate();

	_raise_level_button = new jgl::Button([&](jgl::Data_contener& p_param)
		{
			if (_selected_level < Chunk::C_LAYER_LENGTH - 1)
				set_level_value(_selected_level + 1);
		}, _slider);
	_raise_level_button->label().set_text("+");
	_raise_level_button->activate();

	_slider_button->label().set_text(">");

	_compose_predefined_page();
	_compose_custom_page();

	_selected_item_pos = -1;
	set_inventory_page(0);
	set_level_value(0);
}

jgl::Bool Editor_inventory::is_pointed()
{
	jgl::Bool result = false;

	result |= _slider_button->is_pointed();
	result |= _page_name_label->is_pointed();
	result |= _previous_page_button->is_pointed();
	result |= _next_page_button->is_pointed();
	result |= _slider_button->is_pointed();
	result |= _inventory_frame->is_pointed();
	result |= _lower_level_button->is_pointed();
	result |= _level_selected_label->is_pointed();
	result |= _raise_level_button->is_pointed();

	return (result);
}

Editor_inventory::Inventory_page::Inventory_page(jgl::String p_name) :
	name(p_name), size(0), map(), unit(0), output(nullptr), texture(nullptr)
{

}
void Editor_inventory::Inventory_page::clear()
{
	map.clear();
	size = 0;
}
void Editor_inventory::Inventory_page::add_item(jgl::Vector2Uint p_pos, Item* p_item)
{
	map[p_pos] = p_item;

	if (p_pos.x >= size.x)
		size.x = p_pos.x + 1;
	if (p_pos.y >= size.y)
		size.y = p_pos.y + 1;
}
void Editor_inventory::Inventory_page::calc_unit()
{
	if (size != 0)
		unit = jgl::Vector2(1.0f, 1.0f) / size;
	else
		unit = 1;
}
void Editor_inventory::Inventory_page::compute()
{
	static jgl::Vector2Int tmp_delta_node[4] =
	{
		jgl::Vector2Int(0, 0),
		jgl::Vector2Int(0, 1),
		jgl::Vector2Int(1, 0),
		jgl::Vector2Int(1, 1)
	};
	jgl::Vector2Uint image_size = 0;

	image_size = size * C_ITEM_SIZE;

	if (image_size.x != 0 && image_size.y != 0)
	{
		if (output != nullptr)
			delete output;
		output = new jgl::Image_output(image_size);

		output->associate();

		output->clear();

		for (auto tmp : map)
		{
			jgl::Vector2Uint pos = tmp.first;
			Item* item = tmp.second;

			if (item->type == Item_type::Node)
			{
				Node_item* tmp_item = static_cast<Node_item*>(item);
				if (g_node_array[tmp_item->value]->autotiled == true)
				{
					for (jgl::Size_t i = 0; i < 4; i++)
						Texture_atlas::instance()->node_sprite_sheet()->draw(
							g_node_array[tmp_item->value]->sprite + tmp_delta_node[i],
							pos * C_ITEM_SIZE + tmp_delta_node[i] * (C_ITEM_SIZE / 2),
							C_ITEM_SIZE / 2,
							100,
							1.0f
						);
				}
				else
				{
					Texture_atlas::instance()->node_sprite_sheet()->draw(g_node_array[tmp_item->value]->sprite, pos * C_ITEM_SIZE, C_ITEM_SIZE, 100, 1.0f);
				}
				jgl::draw_text(jgl::itoa(tmp_item->value), pos* C_ITEM_SIZE, C_ITEM_SIZE / 2.5, 200, 1.0f, jgl::Color::white(), jgl::Color::white());
			}
			else if (item->type == Item_type::Prefab)
			{
				Prefab_item* tmp_item = static_cast<Prefab_item*>(item);

				Texture_atlas::instance()->prefab_sprite_sheet()->draw(g_prefab_array[tmp_item->value]->sprite, pos * C_ITEM_SIZE, C_ITEM_SIZE, 100, 1.0f);
			}
			else if (item->type == Item_type::Flag)
			{
				Flag_item* tmp_item = static_cast<Flag_item*>(item);

				Texture_atlas::instance()->UI_sprite_sheet()->draw(Flag_item::sprite(tmp_item->color), pos * C_ITEM_SIZE, C_ITEM_SIZE, 100, 1.0f);
			}
		}

		if (texture != nullptr)
			delete texture;

		texture = output->save();

		output->desassociate();
	}
	calc_unit();
}