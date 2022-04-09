#pragma once

#include "jgl.h"

#include "erelia_player_interacter.h"

namespace Player_interact_activity
{
	class Abstract_activity : public jgl::Abstract_activity
	{
	protected:
		Player_interacter* _interacter;
	public:
		Abstract_activity(Player_interacter* p_interacter)
		{
			_interacter = p_interacter;
		}
	};
	class Adventure : public Abstract_activity
	{
	private:
	public:
		Adventure(Player_interacter* p_interacter);
		void execute();
		void on_transition();
	};
	class Builder : public Abstract_activity
	{
	private:
	public:
		Builder(Player_interacter* p_interacter);
		void execute();
		void on_transition();
	};
}