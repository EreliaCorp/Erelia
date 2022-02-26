#include "erelia.h"

jgl::Vector2Int Chunk::_baking_neightbour_node[4][3] = {
		{
			jgl::Vector2Int(-1, 0),
			jgl::Vector2Int(-1, -1),
			jgl::Vector2Int(0, -1),
		},
		{
			jgl::Vector2Int(0, 1),
			jgl::Vector2Int(-1, 1),
			jgl::Vector2Int(-1, 0),
		},
		{
			jgl::Vector2Int(0, -1),
			jgl::Vector2Int(1, -1),
			jgl::Vector2Int(1, 0),
		},
		{
			jgl::Vector2Int(1, 0),
			jgl::Vector2Int(1, 1),
			jgl::Vector2Int(0, 1),
		},
};

jgl::Vector2Int Chunk::_baking_delta_node_sprite[4][2][2][2] = {
	/*
		if next node == actual -> 0
		else -> 1
	*/
	{// Passe 1
		{// A = 1
			{// B = 1
				jgl::Vector2Int(1, 3), // ABC
				jgl::Vector2Int(1, 2)  // AB
			},
			{// B = 0
				jgl::Vector2Int(2, 0), // A C
				jgl::Vector2Int(1, 2)  // A
			}
		},
		{// A = 0
			{// B = 1
				jgl::Vector2Int(0, 3), //  BC
				jgl::Vector2Int(0, 0)  //  B
			},
			{// B = 0
				jgl::Vector2Int(0, 3), //   C
				jgl::Vector2Int(0, 0)  // 
			}
		}
	},
	{// Passe 2
		{// A = 1
			{// B = 1
				jgl::Vector2Int(1, 4), // ABC
				jgl::Vector2Int(0, 4)  // AB
			},
			{// B = 0
				jgl::Vector2Int(2, 1), // A C
				jgl::Vector2Int(0, 4)  // A
			}
		},
		{// A = 0
			{// B = 1
				jgl::Vector2Int(1, 5), //  BC
				jgl::Vector2Int(0, 1)  //  B
			},
			{// B = 0
				jgl::Vector2Int(1, 5), //   C
				jgl::Vector2Int(0, 1)  // 
			}
		}
	},
	{// Passe 3
		{// A = 1
			{// B = 1
				jgl::Vector2Int(2, 3), // ABC
				jgl::Vector2Int(3, 3)  // AB
			},
			{// B = 0
				jgl::Vector2Int(3, 0), // A C
				jgl::Vector2Int(3, 3)  // A
			}
		},
		{// A = 0
			{// B = 1
				jgl::Vector2Int(2, 2), //  BC
				jgl::Vector2Int(1, 0)  //  B
			},
			{// B = 0
				jgl::Vector2Int(2, 2), //   C
				jgl::Vector2Int(1, 0)  // 
			}
		}
	},
	{// Passe 4
		{// A = 1
			{// B = 1
				jgl::Vector2Int(2, 4), // ABC
				jgl::Vector2Int(2, 5)  // AB
			},
			{// B = 0
				jgl::Vector2Int(3, 1), // A C
				jgl::Vector2Int(2, 5)  // A
			}
		},
		{// A = 0
			{// B = 1
				jgl::Vector2Int(3, 4), //  BC
				jgl::Vector2Int(1, 1)  //  B
			},
			{// B = 0
				jgl::Vector2Int(3, 4), //   C
				jgl::Vector2Int(1, 1)  // 
			}
		}
	},
};

jgl::Vector3 Chunk::_delta_autotile_position[4] = {
	jgl::Vector3(0.0f, 0.0f, 0.0f),
	jgl::Vector3(0.0f, 0.5f, 0.0f),
	jgl::Vector3(0.5f, 0.0f, 0.0f),
	jgl::Vector3(0.5f, 0.5f, 0.0f)
};

jgl::Vector3 Chunk::_delta_tile_position[4] = {
	jgl::Vector3(0.0f, 0.0f, 0.0f),
	jgl::Vector3(0.0f, 1.0f, 0.0f),
	jgl::Vector3(1.0f, 0.0f, 0.0f),
	jgl::Vector3(1.0f, 1.0f, 0.0f)
};

jgl::Vector2 Chunk::_delta_uvs[4] = {
	jgl::Vector2(0.0f, 0.0f),
	jgl::Vector2(0.0f, 1.0f),
	jgl::Vector2(1.0f, 0.0f),
	jgl::Vector2(1.0f, 1.0f)
};

jgl::Uint Chunk::_delta_indexes[6] = {
	0, 3, 1, 2, 3, 0
};