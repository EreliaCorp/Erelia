#pragma once

#include "jgl.h"

#include "Structure/Data/Engine/erelia_item.h"

#include "widget/Commun/erelia_slider_widget.h"

class Editor_inventory : public jgl::Widget
{
private:
	struct Inventory_page
	{
		static const jgl::Size_t C_ITEM_SIZE = 32u;
		static const jgl::Size_t C_NB_ITEM_PER_LINE = 8u;
		jgl::String name;
		jgl::Vector2Uint size;
		jgl::Map<jgl::Vector2Uint, Item*> map;
		jgl::Vector2 unit;
		jgl::Image_output* output;
		jgl::Image* texture;

		Inventory_page(jgl::String p_name = "Undefined");
		void clear();
		void add_item(jgl::Vector2Uint p_pos, Item* p_item);
		void calc_unit();
		void compute();

		Item* item(jgl::Vector2Uint p_pos)
		{
			if (map.count(p_pos) == 0)
				return (nullptr);
			return (map[p_pos]);
		}
	};

	jgl::Vector2 _element_unit;
	jgl::Vector2 _nb_element_on_screen;
	jgl::Vector2 _page_offset;

	Slider* _slider;

	jgl::Text_label* _page_name_label;
	jgl::Button* _previous_page_button;
	jgl::Button* _next_page_button;

	jgl::Text_label* _level_selected_label;
	jgl::Button* _lower_level_button;
	jgl::Button* _raise_level_button;

	jgl::Button* _slider_button;
	jgl::Frame* _inventory_frame;

	class Inventory_renderer : public jgl::Widget
	{
	protected:
		jgl::Image* _image = nullptr;
		jgl::Vector2 _UV_pos = 0;
		jgl::Vector2 _UV_size = 1;

		void _render();
		void _on_geometry_change();
	public:
		Inventory_renderer(jgl::Widget* p_parent);

		void set_texture(jgl::Image* p_image) { _image = p_image; }
		void set_UVs(jgl::Vector2 p_UV_pos, jgl::Vector2 p_UV_size) { _UV_pos = p_UV_pos; _UV_size = p_UV_size; }
	};
	Inventory_renderer* _inventory_frame_contener;

	jgl::Array<Inventory_page*> _pages;

	Item* _selected_item;
	jgl::Vector2Int _selected_item_pos;
	jgl::Size_t _selected_page_index;

	jgl::Int _selected_level;
	jgl::Size_t _inventory_page_index;

	void _render();
	void _on_geometry_change();
	jgl::Bool _update();
	jgl::Bool _fixed_update();

	void _compose_predefined_page();
	void _compose_custom_page();

public:
	Editor_inventory(jgl::Widget* p_parent);

	Item* selected_item() { return (_selected_item); }
	jgl::Int selected_level() { return (_selected_level); }

	void set_inventory_page(jgl::Size_t p_level_value);
	void set_level_value(jgl::Size_t p_page_index);

	jgl::Bool is_pointed();
};