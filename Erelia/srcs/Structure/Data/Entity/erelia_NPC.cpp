#include "structure/Data/Entity/erelia_NPC.h"
#include "structure/Data/Engine/erelia_engine.h"

NPC::NPC(jgl::String p_name, jgl::Long p_id) : AI_controlled_entity(p_name, Entity::Type::NPC, AI_controlled_entity::Movement_info::Pattern::Static, p_id)
{

}