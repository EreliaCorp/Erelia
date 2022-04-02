#include "erelia.h"

int main(int argc, char **argv)
{
	jgl::Application app = jgl::Application("Erelia", jgl::Vector2Int(1600, 900), jgl::Color(50, 50, 50));
	app.add_shader_from_file("Chunk shader", "ressource/shader/chunk_shader.vert", "ressource/shader/chunk_shader.frag");
	app.set_default_font("ressource/font/karma suture.ttf");
	app.active_multithread();

	Main_application win_app(nullptr);
	win_app.set_geometry(0, app.size());
	win_app.activate();

	return (app.run());
}