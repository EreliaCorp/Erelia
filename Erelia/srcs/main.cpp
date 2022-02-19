#include "erelia.h"

int main(int argc, char** argv)
{
	jgl::Application app = jgl::Application("Erelia", jgl::Vector2Int(640, 640), jgl::Color(50, 50, 50));
	app.add_shader_from_file("Movable sprite shader", "ressource/shader/movable_sprite_shader.vert", "ressource/shader/movable_sprite_shader.frag");
	app.set_default_font("ressource/font/karma suture.ttf");
	app.active_multithread();

	Main_application main_app = Main_application(app.central_widget());
	main_app.set_geometry(0, app.size());
	main_app.activate();

	return (app.run());
}