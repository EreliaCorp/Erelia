#include "Structure/Data/Map/erelia_node.h"

jgl::Size_t Node::size = 48;

jgl::Array<Node*> g_node_array =
{	
	new Node(                  "Grass", jgl::Vector2Int( 0,  0),  true,  Node::WALKABLE,  0u), //   0
	new Node(                 "Forest", jgl::Vector2Int( 4,  0),  true,  Node::WALKABLE,  0u), //   1
	new Node(                   "Sand", jgl::Vector2Int( 8,  0),  true,  Node::WALKABLE,  0u), //   2
	new Node(                   "Dirt", jgl::Vector2Int(12,  0),  true,  Node::WALKABLE,  0u), //   3
	new Node(                   "Road", jgl::Vector2Int(16,  0),  true,  Node::WALKABLE,  0u), //   4
	new Node(                  "Stone", jgl::Vector2Int(20,  0),  true,  Node::WALKABLE,  0u), //   5
	new Node(           "Stone - dark", jgl::Vector2Int(24,  0),  true,  Node::WALKABLE,  0u), //   6
	new Node(       "Enchanted forest", jgl::Vector2Int(28,  0),  true,  Node::WALKABLE,  0u), //   7
	new Node(            "Brown stone", jgl::Vector2Int( 0,  6),  true,  Node::WALKABLE,  0u), //   8
	new Node(             "Wood plank", jgl::Vector2Int( 4,  6),  true,  Node::WALKABLE,  0u), //   9
	new Node(            "Tiled stone", jgl::Vector2Int( 8,  6),  true,  Node::WALKABLE,  0u), //   10
	new Node(          "Wall interior", jgl::Vector2Int(12,  6),  true,  Node::OBSTACLE,  0u), //   11
	new Node(                   "Lava", jgl::Vector2Int(16,  6),  true,  Node::OBSTACLE,  4u), //   12
	new Node(                  "Water", jgl::Vector2Int( 0, 12),  true,  Node::OBSTACLE,  4u), //   13
	new Node(             "Deep water", jgl::Vector2Int(16, 12),  true,  Node::OBSTACLE,  4u), //   14
	new Node(       "Dungeon - Purple", jgl::Vector2Int( 0, 18),  true,  Node::WALKABLE,  0u), //   15
	new Node(          "Dungeon - Red", jgl::Vector2Int( 4, 18),  true,  Node::WALKABLE,  0u), //   16
	new Node(         "Dungeon - Blue", jgl::Vector2Int( 8, 18),  true,  Node::WALKABLE,  0u), //   17
	new Node(        "Dungeon - Green", jgl::Vector2Int(12, 18),  true,  Node::WALKABLE,  0u), //   18
	new Node(        "Dungeon - White", jgl::Vector2Int(16, 18),  true,  Node::WALKABLE,  0u), //   19
	new Node(        "Dungeon - Black", jgl::Vector2Int(20, 18),  true,  Node::WALKABLE,  0u), //   20
	new Node(       "Dungeon - Orange", jgl::Vector2Int(24, 18),  true,  Node::WALKABLE,  0u), //   21
	new Node(         "Dungeon - Pink", jgl::Vector2Int(28, 18),  true,  Node::WALKABLE,  0u), //   22
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 24), false,  Node::OBSTACLE,  0u), //   23
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 24), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   24
	new Node(      "Stair - undefined", jgl::Vector2Int( 2, 24), false,  Node::WALKABLE,  0u), //   25
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 24), false,  Node::OBSTACLE,  0u), //   26
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 24), false,  Node::OBSTACLE,  0u), //   27
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 24), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   28
	new Node(      "Stair - undefined", jgl::Vector2Int( 6, 24), false,  Node::WALKABLE,  0u), //   29
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 24), false,  Node::OBSTACLE,  0u), //   30
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 24), false,  Node::OBSTACLE,  0u), //   31
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 24), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   32
	new Node(      "Stair - undefined", jgl::Vector2Int(10, 24), false,  Node::WALKABLE,  0u), //   33
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 24), false,  Node::OBSTACLE,  0u), //   34
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 24), false,  Node::OBSTACLE,  0u), //   35
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 24), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   36
	new Node(      "Stair - undefined", jgl::Vector2Int(14, 24), false,  Node::WALKABLE,  0u), //   37
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 24), false,  Node::OBSTACLE,  0u), //   38
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 24), false,  Node::OBSTACLE,  0u), //   39
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 24), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   40
	new Node(      "Stair - undefined", jgl::Vector2Int(18, 24), false,  Node::WALKABLE,  0u), //   41
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 24), false,  Node::OBSTACLE,  0u), //   42
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 24), false,  Node::OBSTACLE,  0u), //   43
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 24), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   44
	new Node(      "Stair - undefined", jgl::Vector2Int(22, 24), false,  Node::WALKABLE,  0u), //   45
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 24), false,  Node::OBSTACLE,  0u), //   46
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 24), false,  Node::OBSTACLE,  0u), //   47
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 24), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   48
	new Node(      "Stair - undefined", jgl::Vector2Int(26, 24), false,  Node::WALKABLE,  0u), //   49
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 24), false,  Node::OBSTACLE,  0u), //   50
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 24), false,  Node::OBSTACLE,  0u), //   51
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 24), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   52
	new Node(      "Stair - undefined", jgl::Vector2Int(30, 24), false,  Node::WALKABLE,  0u), //   53
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 24), false,  Node::OBSTACLE,  0u), //   54
	new Node(      "Stair - undefined", jgl::Vector2Int( 0, 25), false,  Node::WALKABLE,  0u), //   55
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 25), false,  Node::OBSTACLE,  0u), //   56
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 25), false,  Node::OBSTACLE,  0u), //   57
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 25), false,  Node::OBSTACLE,  0u), //   58
	new Node(      "Stair - undefined", jgl::Vector2Int( 4, 25), false,  Node::WALKABLE,  0u), //   59
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 25), false,  Node::OBSTACLE,  0u), //   60
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 25), false,  Node::OBSTACLE,  0u), //   61
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 25), false,  Node::OBSTACLE,  0u), //   62
	new Node(      "Stair - undefined", jgl::Vector2Int( 8, 25), false,  Node::WALKABLE,  0u), //   63
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 25), false,  Node::OBSTACLE,  0u), //   64
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 25), false,  Node::OBSTACLE,  0u), //   65
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 25), false,  Node::OBSTACLE,  0u), //   66
	new Node(      "Stair - undefined", jgl::Vector2Int(12, 25), false,  Node::WALKABLE,  0u), //   67
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 25), false,  Node::OBSTACLE,  0u), //   68
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 25), false,  Node::OBSTACLE,  0u), //   69
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 25), false,  Node::OBSTACLE,  0u), //   70
	new Node(      "Stair - undefined", jgl::Vector2Int(16, 25), false,  Node::WALKABLE,  0u), //   71
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 25), false,  Node::OBSTACLE,  0u), //   72
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 25), false,  Node::OBSTACLE,  0u), //   73
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 25), false,  Node::OBSTACLE,  0u), //   74
	new Node(      "Stair - undefined", jgl::Vector2Int(20, 25), false,  Node::WALKABLE,  0u), //   75
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 25), false,  Node::OBSTACLE,  0u), //   76
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 25), false,  Node::OBSTACLE,  0u), //   77
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 25), false,  Node::OBSTACLE,  0u), //   78
	new Node(      "Stair - undefined", jgl::Vector2Int(24, 25), false,  Node::WALKABLE,  0u), //   79
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 25), false,  Node::OBSTACLE,  0u), //   80
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 25), false,  Node::OBSTACLE,  0u), //   81
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 25), false,  Node::OBSTACLE,  0u), //   82
	new Node(      "Stair - undefined", jgl::Vector2Int(28, 25), false,  Node::WALKABLE,  0u), //   83
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 25), false,  Node::OBSTACLE,  0u), //   84
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 25), false,  Node::OBSTACLE,  0u), //   85
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 25), false,  Node::OBSTACLE,  0u), //   86
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 26), false,  Node::OBSTACLE,  0u), //   87
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   88
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   89
	new Node(      "Stair - undefined", jgl::Vector2Int( 3, 26), false,  Node::WALKABLE,  0u), //   90
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 26), false,  Node::OBSTACLE,  0u), //   91
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   92
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   93
	new Node(      "Stair - undefined", jgl::Vector2Int( 7, 26), false,  Node::WALKABLE,  0u), //   94
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 26), false,  Node::OBSTACLE,  0u), //   95
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   96
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   97
	new Node(      "Stair - undefined", jgl::Vector2Int(11, 26), false,  Node::WALKABLE,  0u), //   98
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 26), false,  Node::OBSTACLE,  0u), //   99
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   100
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   101
	new Node(      "Stair - undefined", jgl::Vector2Int(15, 26), false,  Node::WALKABLE,  0u), //   102
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 26), false,  Node::OBSTACLE,  0u), //   103
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   104
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   105
	new Node(      "Stair - undefined", jgl::Vector2Int(19, 26), false,  Node::WALKABLE,  0u), //   106
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 26), false,  Node::OBSTACLE,  0u), //   107
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   108
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   109
	new Node(      "Stair - undefined", jgl::Vector2Int(23, 26), false,  Node::WALKABLE,  0u), //   110
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 26), false,  Node::OBSTACLE,  0u), //   111
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   112
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   113
	new Node(      "Stair - undefined", jgl::Vector2Int(27, 26), false,  Node::WALKABLE,  0u), //   114
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 26), false,  Node::OBSTACLE,  0u), //   115
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   116
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 26), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   117
	new Node(      "Stair - undefined", jgl::Vector2Int(31, 26), false,  Node::WALKABLE,  0u), //   118
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 27), false,  Node::OBSTACLE,  0u), //   119
	new Node(      "Stair - undefined", jgl::Vector2Int( 1, 27), false,  Node::WALKABLE,  0u), //   120
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 27), false,  Node::OBSTACLE,  0u), //   121
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 27), false,  Node::OBSTACLE,  0u), //   122
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 27), false,  Node::OBSTACLE,  0u), //   123
	new Node(      "Stair - undefined", jgl::Vector2Int( 5, 27), false,  Node::WALKABLE,  0u), //   124
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 27), false,  Node::OBSTACLE,  0u), //   125
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 27), false,  Node::OBSTACLE,  0u), //   126
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 27), false,  Node::OBSTACLE,  0u), //   127
	new Node(      "Stair - undefined", jgl::Vector2Int( 9, 27), false,  Node::WALKABLE,  0u), //   128
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 27), false,  Node::OBSTACLE,  0u), //   129
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 27), false,  Node::OBSTACLE,  0u), //   130
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 27), false,  Node::OBSTACLE,  0u), //   131
	new Node(      "Stair - undefined", jgl::Vector2Int(13, 27), false,  Node::WALKABLE,  0u), //   132
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 27), false,  Node::OBSTACLE,  0u), //   133
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 27), false,  Node::OBSTACLE,  0u), //   134
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 27), false,  Node::OBSTACLE,  0u), //   135
	new Node(      "Stair - undefined", jgl::Vector2Int(17, 27), false,  Node::WALKABLE,  0u), //   136
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 27), false,  Node::OBSTACLE,  0u), //   137
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 27), false,  Node::OBSTACLE,  0u), //   138
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 27), false,  Node::OBSTACLE,  0u), //   139
	new Node(      "Stair - undefined", jgl::Vector2Int(21, 27), false,  Node::WALKABLE,  0u), //   140
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 27), false,  Node::OBSTACLE,  0u), //   141
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 27), false,  Node::OBSTACLE,  0u), //   142
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 27), false,  Node::OBSTACLE,  0u), //   143
	new Node(      "Stair - undefined", jgl::Vector2Int(25, 27), false,  Node::WALKABLE,  0u), //   144
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 27), false,  Node::OBSTACLE,  0u), //   145
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 27), false,  Node::OBSTACLE,  0u), //   146
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 27), false,  Node::OBSTACLE,  0u), //   147
	new Node(      "Stair - undefined", jgl::Vector2Int(29, 27), false,  Node::WALKABLE,  0u), //   148
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 27), false,  Node::OBSTACLE,  0u), //   149
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 27), false,  Node::OBSTACLE,  0u), //   150
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 28), false,  Node::OBSTACLE,  0u), //   151
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 28), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   152
	new Node(      "Stair - undefined", jgl::Vector2Int( 2, 28), false,  Node::WALKABLE,  0u), //   153
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 28), false,  Node::OBSTACLE,  0u), //   154
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 28), false,  Node::OBSTACLE,  0u), //   155
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 28), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   156
	new Node(      "Stair - undefined", jgl::Vector2Int( 6, 28), false,  Node::WALKABLE,  0u), //   157
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 28), false,  Node::OBSTACLE,  0u), //   158
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 28), false,  Node::OBSTACLE,  0u), //   159
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 28), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   160
	new Node(      "Stair - undefined", jgl::Vector2Int(10, 28), false,  Node::WALKABLE,  0u), //   161
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 28), false,  Node::OBSTACLE,  0u), //   162
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 28), false,  Node::OBSTACLE,  0u), //   163
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 28), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   164
	new Node(      "Stair - undefined", jgl::Vector2Int(14, 28), false,  Node::WALKABLE,  0u), //   165
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 28), false,  Node::OBSTACLE,  0u), //   166
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 28), false,  Node::OBSTACLE,  0u), //   167
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 28), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   168
	new Node(      "Stair - undefined", jgl::Vector2Int(18, 28), false,  Node::WALKABLE,  0u), //   169
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 28), false,  Node::OBSTACLE,  0u), //   170
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 28), false,  Node::OBSTACLE,  0u), //   171
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 28), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   172
	new Node(      "Stair - undefined", jgl::Vector2Int(22, 28), false,  Node::WALKABLE,  0u), //   173
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 28), false,  Node::OBSTACLE,  0u), //   174
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 28), false,  Node::OBSTACLE,  0u), //   175
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 28), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   176
	new Node(      "Stair - undefined", jgl::Vector2Int(26, 28), false,  Node::WALKABLE,  0u), //   177
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 28), false,  Node::OBSTACLE,  0u), //   178
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 28), false,  Node::OBSTACLE,  0u), //   179
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 28), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   180
	new Node(      "Stair - undefined", jgl::Vector2Int(30, 28), false,  Node::WALKABLE,  0u), //   181
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 28), false,  Node::OBSTACLE,  0u), //   182
	new Node(      "Stair - undefined", jgl::Vector2Int( 0, 29), false,  Node::WALKABLE,  0u), //   183
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 29), false,  Node::OBSTACLE,  0u), //   184
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 29), false,  Node::OBSTACLE,  0u), //   185
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 29), false,  Node::OBSTACLE,  0u), //   186
	new Node(      "Stair - undefined", jgl::Vector2Int( 4, 29), false,  Node::WALKABLE,  0u), //   187
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 29), false,  Node::OBSTACLE,  0u), //   188
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 29), false,  Node::OBSTACLE,  0u), //   189
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 29), false,  Node::OBSTACLE,  0u), //   190
	new Node(      "Stair - undefined", jgl::Vector2Int( 8, 29), false,  Node::WALKABLE,  0u), //   191
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 29), false,  Node::OBSTACLE,  0u), //   192
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 29), false,  Node::OBSTACLE,  0u), //   193
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 29), false,  Node::OBSTACLE,  0u), //   194
	new Node(      "Stair - undefined", jgl::Vector2Int(12, 29), false,  Node::WALKABLE,  0u), //   195
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 29), false,  Node::OBSTACLE,  0u), //   196
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 29), false,  Node::OBSTACLE,  0u), //   197
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 29), false,  Node::OBSTACLE,  0u), //   198
	new Node(      "Stair - undefined", jgl::Vector2Int(16, 29), false,  Node::WALKABLE,  0u), //   199
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 29), false,  Node::OBSTACLE,  0u), //   200
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 29), false,  Node::OBSTACLE,  0u), //   201
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 29), false,  Node::OBSTACLE,  0u), //   202
	new Node(      "Stair - undefined", jgl::Vector2Int(20, 29), false,  Node::WALKABLE,  0u), //   203
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 29), false,  Node::OBSTACLE,  0u), //   204
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 29), false,  Node::OBSTACLE,  0u), //   205
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 29), false,  Node::OBSTACLE,  0u), //   206
	new Node(      "Stair - undefined", jgl::Vector2Int(24, 29), false,  Node::WALKABLE,  0u), //   207
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 29), false,  Node::OBSTACLE,  0u), //   208
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 29), false,  Node::OBSTACLE,  0u), //   209
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 29), false,  Node::OBSTACLE,  0u), //   210
	new Node(      "Stair - undefined", jgl::Vector2Int(28, 29), false,  Node::WALKABLE,  0u), //   211
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 29), false,  Node::OBSTACLE,  0u), //   212
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 29), false,  Node::OBSTACLE,  0u), //   213
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 29), false,  Node::OBSTACLE,  0u), //   214
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 30), false,  Node::OBSTACLE,  0u), //   215
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   216
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   217
	new Node(      "Stair - undefined", jgl::Vector2Int( 3, 30), false,  Node::WALKABLE,  0u), //   218
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 30), false,  Node::OBSTACLE,  0u), //   219
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   220
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   221
	new Node(      "Stair - undefined", jgl::Vector2Int( 7, 30), false,  Node::WALKABLE,  0u), //   222
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 30), false,  Node::OBSTACLE,  0u), //   223
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   224
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   225
	new Node(      "Stair - undefined", jgl::Vector2Int(11, 30), false,  Node::WALKABLE,  0u), //   226
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 30), false,  Node::OBSTACLE,  0u), //   227
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   228
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   229
	new Node(      "Stair - undefined", jgl::Vector2Int(15, 30), false,  Node::WALKABLE,  0u), //   230
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 30), false,  Node::OBSTACLE,  0u), //   231
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   232
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   233
	new Node(      "Stair - undefined", jgl::Vector2Int(19, 30), false,  Node::WALKABLE,  0u), //   234
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 30), false,  Node::OBSTACLE,  0u), //   235
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   236
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   237
	new Node(      "Stair - undefined", jgl::Vector2Int(23, 30), false,  Node::WALKABLE,  0u), //   238
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 30), false,  Node::OBSTACLE,  0u), //   239
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   240
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   241
	new Node(      "Stair - undefined", jgl::Vector2Int(27, 30), false,  Node::WALKABLE,  0u), //   242
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 30), false,  Node::OBSTACLE,  0u), //   243
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   244
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 30), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   245
	new Node(      "Stair - undefined", jgl::Vector2Int(31, 30), false,  Node::WALKABLE,  0u), //   246
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 31), false,  Node::OBSTACLE,  0u), //   247
	new Node(      "Stair - undefined", jgl::Vector2Int( 1, 31), false,  Node::WALKABLE,  0u), //   248
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 31), false,  Node::OBSTACLE,  0u), //   249
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 31), false,  Node::OBSTACLE,  0u), //   250
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 31), false,  Node::OBSTACLE,  0u), //   251
	new Node(      "Stair - undefined", jgl::Vector2Int( 5, 31), false,  Node::WALKABLE,  0u), //   252
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 31), false,  Node::OBSTACLE,  0u), //   253
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 31), false,  Node::OBSTACLE,  0u), //   254
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 31), false,  Node::OBSTACLE,  0u), //   255
	new Node(      "Stair - undefined", jgl::Vector2Int( 9, 31), false,  Node::WALKABLE,  0u), //   256
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 31), false,  Node::OBSTACLE,  0u), //   257
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 31), false,  Node::OBSTACLE,  0u), //   258
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 31), false,  Node::OBSTACLE,  0u), //   259
	new Node(      "Stair - undefined", jgl::Vector2Int(13, 31), false,  Node::WALKABLE,  0u), //   260
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 31), false,  Node::OBSTACLE,  0u), //   261
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 31), false,  Node::OBSTACLE,  0u), //   262
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 31), false,  Node::OBSTACLE,  0u), //   263
	new Node(      "Stair - undefined", jgl::Vector2Int(17, 31), false,  Node::WALKABLE,  0u), //   264
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 31), false,  Node::OBSTACLE,  0u), //   265
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 31), false,  Node::OBSTACLE,  0u), //   266
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 31), false,  Node::OBSTACLE,  0u), //   267
	new Node(      "Stair - undefined", jgl::Vector2Int(21, 31), false,  Node::WALKABLE,  0u), //   268
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 31), false,  Node::OBSTACLE,  0u), //   269
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 31), false,  Node::OBSTACLE,  0u), //   270
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 31), false,  Node::OBSTACLE,  0u), //   271
	new Node(      "Stair - undefined", jgl::Vector2Int(25, 31), false,  Node::WALKABLE,  0u), //   272
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 31), false,  Node::OBSTACLE,  0u), //   273
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 31), false,  Node::OBSTACLE,  0u), //   274
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 31), false,  Node::OBSTACLE,  0u), //   275
	new Node(      "Stair - undefined", jgl::Vector2Int(29, 31), false,  Node::WALKABLE,  0u), //   276
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 31), false,  Node::OBSTACLE,  0u), //   277
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 31), false,  Node::OBSTACLE,  0u), //   278
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 32), false,  Node::OBSTACLE,  0u), //   279
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 32), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   280
	new Node(      "Stair - undefined", jgl::Vector2Int( 2, 32), false,  Node::WALKABLE,  0u), //   281
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 32), false,  Node::OBSTACLE,  0u), //   282
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 32), false,  Node::OBSTACLE,  0u), //   283
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 32), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   284
	new Node(      "Stair - undefined", jgl::Vector2Int( 6, 32), false,  Node::WALKABLE,  0u), //   285
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 32), false,  Node::OBSTACLE,  0u), //   286
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 32), false,  Node::OBSTACLE,  0u), //   287
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 32), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   288
	new Node(      "Stair - undefined", jgl::Vector2Int(10, 32), false,  Node::WALKABLE,  0u), //   289
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 32), false,  Node::OBSTACLE,  0u), //   290
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 32), false,  Node::OBSTACLE,  0u), //   291
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 32), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   292
	new Node(      "Stair - undefined", jgl::Vector2Int(14, 32), false,  Node::WALKABLE,  0u), //   293
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 32), false,  Node::OBSTACLE,  0u), //   294
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 32), false,  Node::OBSTACLE,  0u), //   295
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 32), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   296
	new Node(      "Stair - undefined", jgl::Vector2Int(18, 32), false,  Node::WALKABLE,  0u), //   297
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 32), false,  Node::OBSTACLE,  0u), //   298
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 32), false,  Node::OBSTACLE,  0u), //   299
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 32), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   300
	new Node(      "Stair - undefined", jgl::Vector2Int(22, 32), false,  Node::WALKABLE,  0u), //   301
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 32), false,  Node::OBSTACLE,  0u), //   302
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 32), false,  Node::OBSTACLE,  0u), //   303
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 32), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   304
	new Node(      "Stair - undefined", jgl::Vector2Int(26, 32), false,  Node::WALKABLE,  0u), //   305
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 32), false,  Node::OBSTACLE,  0u), //   306
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 32), false,  Node::OBSTACLE,  0u), //   307
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 32), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   308
	new Node(      "Stair - undefined", jgl::Vector2Int(30, 32), false,  Node::WALKABLE,  0u), //   309
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 32), false,  Node::OBSTACLE,  0u), //   310
	new Node(      "Stair - undefined", jgl::Vector2Int( 0, 33), false,  Node::WALKABLE,  0u), //   311
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 33), false,  Node::OBSTACLE,  0u), //   312
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 33), false,  Node::OBSTACLE,  0u), //   313
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 33), false,  Node::OBSTACLE,  0u), //   314
	new Node(      "Stair - undefined", jgl::Vector2Int( 4, 33), false,  Node::WALKABLE,  0u), //   315
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 33), false,  Node::OBSTACLE,  0u), //   316
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 33), false,  Node::OBSTACLE,  0u), //   317
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 33), false,  Node::OBSTACLE,  0u), //   318
	new Node(      "Stair - undefined", jgl::Vector2Int( 8, 33), false,  Node::WALKABLE,  0u), //   319
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 33), false,  Node::OBSTACLE,  0u), //   320
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 33), false,  Node::OBSTACLE,  0u), //   321
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 33), false,  Node::OBSTACLE,  0u), //   322
	new Node(      "Stair - undefined", jgl::Vector2Int(12, 33), false,  Node::WALKABLE,  0u), //   323
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 33), false,  Node::OBSTACLE,  0u), //   324
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 33), false,  Node::OBSTACLE,  0u), //   325
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 33), false,  Node::OBSTACLE,  0u), //   326
	new Node(      "Stair - undefined", jgl::Vector2Int(16, 33), false,  Node::WALKABLE,  0u), //   327
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 33), false,  Node::OBSTACLE,  0u), //   328
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 33), false,  Node::OBSTACLE,  0u), //   329
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 33), false,  Node::OBSTACLE,  0u), //   330
	new Node(      "Stair - undefined", jgl::Vector2Int(20, 33), false,  Node::WALKABLE,  0u), //   331
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 33), false,  Node::OBSTACLE,  0u), //   332
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 33), false,  Node::OBSTACLE,  0u), //   333
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 33), false,  Node::OBSTACLE,  0u), //   334
	new Node(      "Stair - undefined", jgl::Vector2Int(24, 33), false,  Node::WALKABLE,  0u), //   335
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 33), false,  Node::OBSTACLE,  0u), //   336
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 33), false,  Node::OBSTACLE,  0u), //   337
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 33), false,  Node::OBSTACLE,  0u), //   338
	new Node(      "Stair - undefined", jgl::Vector2Int(28, 33), false,  Node::WALKABLE,  0u), //   339
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 33), false,  Node::OBSTACLE,  0u), //   340
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 33), false,  Node::OBSTACLE,  0u), //   341
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 33), false,  Node::OBSTACLE,  0u), //   342
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 34), false,  Node::OBSTACLE,  0u), //   343
	new Node(       "Wall - undefined", jgl::Vector2Int( 1, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   344
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   345
	new Node(      "Stair - undefined", jgl::Vector2Int( 3, 34), false,  Node::WALKABLE,  0u), //   346
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 34), false,  Node::OBSTACLE,  0u), //   347
	new Node(       "Wall - undefined", jgl::Vector2Int( 5, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   348
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   349
	new Node(      "Stair - undefined", jgl::Vector2Int( 7, 34), false,  Node::WALKABLE,  0u), //   350
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 34), false,  Node::OBSTACLE,  0u), //   351
	new Node(       "Wall - undefined", jgl::Vector2Int( 9, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   352
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   353
	new Node(      "Stair - undefined", jgl::Vector2Int(11, 34), false,  Node::WALKABLE,  0u), //   354
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 34), false,  Node::OBSTACLE,  0u), //   355
	new Node(       "Wall - undefined", jgl::Vector2Int(13, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   356
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   357
	new Node(      "Stair - undefined", jgl::Vector2Int(15, 34), false,  Node::WALKABLE,  0u), //   358
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 34), false,  Node::OBSTACLE,  0u), //   359
	new Node(       "Wall - undefined", jgl::Vector2Int(17, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   360
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   361
	new Node(      "Stair - undefined", jgl::Vector2Int(19, 34), false,  Node::WALKABLE,  0u), //   362
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 34), false,  Node::OBSTACLE,  0u), //   363
	new Node(       "Wall - undefined", jgl::Vector2Int(21, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   364
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   365
	new Node(      "Stair - undefined", jgl::Vector2Int(23, 34), false,  Node::WALKABLE,  0u), //   366
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 34), false,  Node::OBSTACLE,  0u), //   367
	new Node(       "Wall - undefined", jgl::Vector2Int(25, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   368
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   369
	new Node(      "Stair - undefined", jgl::Vector2Int(27, 34), false,  Node::WALKABLE,  0u), //   370
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 34), false,  Node::OBSTACLE,  0u), //   371
	new Node(       "Wall - undefined", jgl::Vector2Int(29, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   372
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 34), false,  Node::SOUTH_WALKABLE | Node::EAST_WALKABLE | Node::WEST_WALKABLE,  0u), //   373
	new Node(      "Stair - undefined", jgl::Vector2Int(31, 34), false,  Node::WALKABLE,  0u), //   374
	new Node(       "Wall - undefined", jgl::Vector2Int( 0, 35), false,  Node::OBSTACLE,  0u), //   375
	new Node(      "Stair - undefined", jgl::Vector2Int( 1, 35), false,  Node::WALKABLE,  0u), //   376
	new Node(       "Wall - undefined", jgl::Vector2Int( 2, 35), false,  Node::OBSTACLE,  0u), //   377
	new Node(       "Wall - undefined", jgl::Vector2Int( 3, 35), false,  Node::OBSTACLE,  0u), //   378
	new Node(       "Wall - undefined", jgl::Vector2Int( 4, 35), false,  Node::OBSTACLE,  0u), //   379
	new Node(      "Stair - undefined", jgl::Vector2Int( 5, 35), false,  Node::WALKABLE,  0u), //   380
	new Node(       "Wall - undefined", jgl::Vector2Int( 6, 35), false,  Node::OBSTACLE,  0u), //   381
	new Node(       "Wall - undefined", jgl::Vector2Int( 7, 35), false,  Node::OBSTACLE,  0u), //   382
	new Node(       "Wall - undefined", jgl::Vector2Int( 8, 35), false,  Node::OBSTACLE,  0u), //   383
	new Node(      "Stair - undefined", jgl::Vector2Int( 9, 35), false,  Node::WALKABLE,  0u), //   384
	new Node(       "Wall - undefined", jgl::Vector2Int(10, 35), false,  Node::OBSTACLE,  0u), //   385
	new Node(       "Wall - undefined", jgl::Vector2Int(11, 35), false,  Node::OBSTACLE,  0u), //   386
	new Node(       "Wall - undefined", jgl::Vector2Int(12, 35), false,  Node::OBSTACLE,  0u), //   387
	new Node(      "Stair - undefined", jgl::Vector2Int(13, 35), false,  Node::WALKABLE,  0u), //   388
	new Node(       "Wall - undefined", jgl::Vector2Int(14, 35), false,  Node::OBSTACLE,  0u), //   389
	new Node(       "Wall - undefined", jgl::Vector2Int(15, 35), false,  Node::OBSTACLE,  0u), //   390
	new Node(       "Wall - undefined", jgl::Vector2Int(16, 35), false,  Node::OBSTACLE,  0u), //   391
	new Node(      "Stair - undefined", jgl::Vector2Int(17, 35), false,  Node::WALKABLE,  0u), //   392
	new Node(       "Wall - undefined", jgl::Vector2Int(18, 35), false,  Node::OBSTACLE,  0u), //   393
	new Node(       "Wall - undefined", jgl::Vector2Int(19, 35), false,  Node::OBSTACLE,  0u), //   394
	new Node(       "Wall - undefined", jgl::Vector2Int(20, 35), false,  Node::OBSTACLE,  0u), //   395
	new Node(      "Stair - undefined", jgl::Vector2Int(21, 35), false,  Node::WALKABLE,  0u), //   396
	new Node(       "Wall - undefined", jgl::Vector2Int(22, 35), false,  Node::OBSTACLE,  0u), //   397
	new Node(       "Wall - undefined", jgl::Vector2Int(23, 35), false,  Node::OBSTACLE,  0u), //   398
	new Node(       "Wall - undefined", jgl::Vector2Int(24, 35), false,  Node::OBSTACLE,  0u), //   399
	new Node(      "Stair - undefined", jgl::Vector2Int(25, 35), false,  Node::WALKABLE,  0u), //   400
	new Node(       "Wall - undefined", jgl::Vector2Int(26, 35), false,  Node::OBSTACLE,  0u), //   401
	new Node(       "Wall - undefined", jgl::Vector2Int(27, 35), false,  Node::OBSTACLE,  0u), //   402
	new Node(       "Wall - undefined", jgl::Vector2Int(28, 35), false,  Node::OBSTACLE,  0u), //   403
	new Node(      "Stair - undefined", jgl::Vector2Int(29, 35), false,  Node::WALKABLE,  0u), //   404
	new Node(       "Wall - undefined", jgl::Vector2Int(30, 35), false,  Node::OBSTACLE,  0u), //   405
	new Node(       "Wall - undefined", jgl::Vector2Int(31, 35), false,  Node::OBSTACLE,  0u), //   406
	new Node(              "Undefined", jgl::Vector2Int( 0, 36),  true,  Node::WALKABLE,  0u), //   407
	new Node(              "Undefined", jgl::Vector2Int( 4, 36),  true,  Node::WALKABLE,  0u), //   408
	new Node(              "Undefined", jgl::Vector2Int( 8, 36),  true,  Node::WALKABLE,  0u), //   409
	new Node(              "Undefined", jgl::Vector2Int(12, 36),  true,  Node::WALKABLE,  0u), //   410
	new Node(              "Undefined", jgl::Vector2Int(16, 36),  true,  Node::WALKABLE,  0u), //   411
	new Node(              "Undefined", jgl::Vector2Int(20, 36),  true,  Node::WALKABLE,  0u), //   412
	new Node(              "Undefined", jgl::Vector2Int(24, 36),  true,  Node::WALKABLE,  0u), //   413
	new Node(              "Undefined", jgl::Vector2Int(28, 36),  true,  Node::WALKABLE,  0u), //   414
	new Node(              "Undefined", jgl::Vector2Int( 0, 42), false,  Node::OBSTACLE,  0u), //   415
	new Node(              "Undefined", jgl::Vector2Int( 1, 42), false,  Node::OBSTACLE,  0u), //   416
	new Node(              "Undefined", jgl::Vector2Int( 2, 42), false,  Node::OBSTACLE,  0u), //   417
	new Node(              "Undefined", jgl::Vector2Int( 3, 42), false,  Node::OBSTACLE,  0u), //   418
	new Node(              "Undefined", jgl::Vector2Int( 4, 42), false,  Node::OBSTACLE,  0u), //   419
	new Node(              "Undefined", jgl::Vector2Int( 5, 42), false,  Node::OBSTACLE,  0u), //   420
	new Node(              "Undefined", jgl::Vector2Int( 6, 42), false,  Node::OBSTACLE,  0u), //   421
	new Node(              "Undefined", jgl::Vector2Int( 7, 42), false,  Node::OBSTACLE,  0u), //   422
	new Node(              "Undefined", jgl::Vector2Int( 8, 42), false,  Node::OBSTACLE,  0u), //   423
	new Node(              "Undefined", jgl::Vector2Int( 9, 42), false,  Node::OBSTACLE,  0u), //   424
	new Node(              "Undefined", jgl::Vector2Int(10, 42), false,  Node::OBSTACLE,  0u), //   425
	new Node(              "Undefined", jgl::Vector2Int(11, 42), false,  Node::OBSTACLE,  0u), //   426
	new Node(              "Undefined", jgl::Vector2Int(12, 42), false,  Node::OBSTACLE,  0u), //   427
	new Node(              "Undefined", jgl::Vector2Int(13, 42), false,  Node::OBSTACLE,  0u), //   428
	new Node(              "Undefined", jgl::Vector2Int(14, 42), false,  Node::OBSTACLE,  0u), //   429
	new Node(              "Undefined", jgl::Vector2Int(15, 42), false,  Node::OBSTACLE,  0u), //   430
	new Node(             "Bush green", jgl::Vector2Int(16, 42), false,  Node::WALKABLE | Node::BUSH,  0u), //   431
	new Node(            "Bush orange", jgl::Vector2Int(17, 42), false,  Node::WALKABLE | Node::BUSH,  0u), //   432
	new Node(              "Bush pink", jgl::Vector2Int(18, 42), false,  Node::WALKABLE | Node::BUSH,  0u), //   433
	new Node(             "Bush brown", jgl::Vector2Int(19, 42), false,  Node::WALKABLE | Node::BUSH,  0u), //   434
	new Node(        "Bush dark green", jgl::Vector2Int(20, 42), false,  Node::WALKABLE | Node::BUSH,  0u), //   435
	new Node(              "Bush blue", jgl::Vector2Int(21, 42), false,  Node::WALKABLE | Node::BUSH,  0u), //   436
	new Node(            "Bush purple", jgl::Vector2Int(22, 42), false,  Node::WALKABLE | Node::BUSH,  0u), //   437
	new Node(             "Bush white", jgl::Vector2Int(23, 42), false,  Node::WALKABLE | Node::BUSH,  0u), //   438
	new Node(              "Undefined", jgl::Vector2Int(24, 42), false,  Node::OBSTACLE,  0u), //   439
	new Node(              "Undefined", jgl::Vector2Int(25, 42), false,  Node::OBSTACLE,  0u), //   440
	new Node(              "Undefined", jgl::Vector2Int(26, 42), false,  Node::OBSTACLE,  0u), //   441
	new Node(              "Undefined", jgl::Vector2Int(27, 42), false,  Node::OBSTACLE,  0u), //   442
	new Node(              "Undefined", jgl::Vector2Int(28, 42), false,  Node::OBSTACLE,  0u), //   443
	new Node(              "Undefined", jgl::Vector2Int(29, 42), false,  Node::OBSTACLE,  0u), //   444
	new Node(              "Undefined", jgl::Vector2Int(30, 42), false,  Node::OBSTACLE,  0u), //   445
	new Node(              "Undefined", jgl::Vector2Int(31, 42), false,  Node::OBSTACLE,  0u), //   446
	new Node(              "Undefined", jgl::Vector2Int( 0, 43), false,  Node::WALKABLE,  0u), //   447
	new Node(              "Undefined", jgl::Vector2Int( 1, 43), false,  Node::WALKABLE,  0u), //   448
	new Node(              "Undefined", jgl::Vector2Int( 2, 43), false,  Node::WALKABLE,  0u), //   449
	new Node(              "Undefined", jgl::Vector2Int( 3, 43), false,  Node::WALKABLE,  0u), //   450
	new Node(              "Undefined", jgl::Vector2Int( 4, 43), false,  Node::WALKABLE,  0u), //   451
	new Node(              "Undefined", jgl::Vector2Int( 5, 43), false,  Node::WALKABLE,  0u), //   452
	new Node(              "Undefined", jgl::Vector2Int( 6, 43), false,  Node::WALKABLE,  0u), //   453
	new Node(              "Undefined", jgl::Vector2Int( 7, 43), false,  Node::WALKABLE,  0u), //   454
	new Node(              "Undefined", jgl::Vector2Int( 8, 43), false,  Node::WALKABLE,  0u), //   455
	new Node(              "Undefined", jgl::Vector2Int( 9, 43), false,  Node::WALKABLE,  0u), //   456
	new Node(              "Undefined", jgl::Vector2Int(10, 43), false,  Node::WALKABLE,  0u), //   457
	new Node(              "Undefined", jgl::Vector2Int(11, 43), false,  Node::WALKABLE,  0u), //   458
	new Node(              "Undefined", jgl::Vector2Int(12, 43), false,  Node::WALKABLE,  0u), //   459
	new Node(              "Undefined", jgl::Vector2Int(13, 43), false,  Node::WALKABLE,  0u), //   460
	new Node(              "Undefined", jgl::Vector2Int(14, 43), false,  Node::WALKABLE,  0u), //   461
	new Node(              "Undefined", jgl::Vector2Int(15, 43), false,  Node::WALKABLE,  0u), //   462
	new Node(              "Undefined", jgl::Vector2Int(16, 43), false,  Node::WALKABLE,  0u), //   463
	new Node(              "Undefined", jgl::Vector2Int(17, 43), false,  Node::WALKABLE,  0u), //   464
	new Node(              "Undefined", jgl::Vector2Int(18, 43), false,  Node::WALKABLE,  0u), //   465
	new Node(              "Undefined", jgl::Vector2Int(19, 43), false,  Node::WALKABLE,  0u), //   466
	new Node(              "Undefined", jgl::Vector2Int(20, 43), false,  Node::WALKABLE,  0u), //   467
	new Node(              "Undefined", jgl::Vector2Int(21, 43), false,  Node::WALKABLE,  0u), //   468
	new Node(              "Undefined", jgl::Vector2Int(22, 43), false,  Node::WALKABLE,  0u), //   469
	new Node(              "Undefined", jgl::Vector2Int(23, 43), false,  Node::WALKABLE,  0u), //   470
	new Node(              "Undefined", jgl::Vector2Int(24, 43), false,  Node::WALKABLE,  0u), //   471
	new Node(              "Undefined", jgl::Vector2Int(25, 43), false,  Node::WALKABLE,  0u), //   472
	new Node(              "Undefined", jgl::Vector2Int(26, 43), false,  Node::WALKABLE,  0u), //   473
	new Node(              "Undefined", jgl::Vector2Int(27, 43), false,  Node::WALKABLE,  0u), //   474
	new Node(              "Undefined", jgl::Vector2Int(28, 43), false,  Node::WALKABLE,  0u), //   475
	new Node(              "Undefined", jgl::Vector2Int(29, 43), false,  Node::WALKABLE,  0u), //   476
	new Node(              "Undefined", jgl::Vector2Int(30, 43), false,  Node::WALKABLE,  0u), //   477
	new Node(              "Undefined", jgl::Vector2Int(31, 43), false,  Node::WALKABLE,  0u), //   478
	new Node(              "Undefined", jgl::Vector2Int( 0, 44), false,  Node::OBSTACLE,  0u), //   479
	new Node(              "Undefined", jgl::Vector2Int( 1, 44), false,  Node::OBSTACLE,  0u), //   480
	new Node(              "Undefined", jgl::Vector2Int( 2, 44), false,  Node::OBSTACLE,  0u), //   481
	new Node(              "Undefined", jgl::Vector2Int( 3, 44), false,  Node::OBSTACLE,  0u), //   482
	new Node(              "Undefined", jgl::Vector2Int( 4, 44), false,  Node::OBSTACLE,  0u), //   483
	new Node(              "Undefined", jgl::Vector2Int( 5, 44), false,  Node::OBSTACLE,  0u), //   484
	new Node(              "Undefined", jgl::Vector2Int( 6, 44), false,  Node::OBSTACLE,  0u), //   485
	new Node(              "Undefined", jgl::Vector2Int( 7, 44), false,  Node::OBSTACLE,  0u), //   486
	new Node(              "Undefined", jgl::Vector2Int( 8, 44), false,  Node::OBSTACLE,  0u), //   487
	new Node(              "Undefined", jgl::Vector2Int( 9, 44), false,  Node::OBSTACLE,  0u), //   488
	new Node(              "Undefined", jgl::Vector2Int(10, 44), false,  Node::OBSTACLE,  0u), //   489
	new Node(              "Undefined", jgl::Vector2Int(11, 44), false,  Node::OBSTACLE,  0u), //   490
	new Node(              "Undefined", jgl::Vector2Int(12, 44), false,  Node::OBSTACLE,  0u), //   491
	new Node(              "Undefined", jgl::Vector2Int(13, 44), false,  Node::OBSTACLE,  0u), //   492
	new Node(              "Undefined", jgl::Vector2Int(14, 44), false,  Node::OBSTACLE,  0u), //   493
	new Node(              "Undefined", jgl::Vector2Int(15, 44), false,  Node::OBSTACLE,  0u), //   494
	new Node(              "Undefined", jgl::Vector2Int(16, 44), false,  Node::WALKABLE,  0u), //   495
	new Node(              "Undefined", jgl::Vector2Int(17, 44), false,  Node::WALKABLE,  0u), //   496
	new Node(              "Undefined", jgl::Vector2Int(18, 44), false,  Node::WALKABLE,  0u), //   497
	new Node(              "Undefined", jgl::Vector2Int(19, 44), false,  Node::WALKABLE,  0u), //   498
	new Node(              "Undefined", jgl::Vector2Int(20, 44), false,  Node::WALKABLE,  0u), //   499
	new Node(              "Undefined", jgl::Vector2Int(21, 44), false,  Node::WALKABLE,  0u), //   500
	new Node(              "Undefined", jgl::Vector2Int(22, 44), false,  Node::WALKABLE,  0u), //   501
	new Node(              "Undefined", jgl::Vector2Int(23, 44), false,  Node::WALKABLE,  0u), //   502
	new Node(              "Undefined", jgl::Vector2Int(24, 44), false,  Node::WALKABLE,  0u), //   503
	new Node(              "Undefined", jgl::Vector2Int(25, 44), false,  Node::WALKABLE,  0u), //   504
	new Node(              "Undefined", jgl::Vector2Int(26, 44), false,  Node::WALKABLE,  0u), //   505
	new Node(              "Undefined", jgl::Vector2Int(27, 44), false,  Node::WALKABLE,  0u), //   506
	new Node(              "Undefined", jgl::Vector2Int(28, 44), false,  Node::WALKABLE,  0u), //   507
	new Node(              "Undefined", jgl::Vector2Int(29, 44), false,  Node::WALKABLE,  0u), //   508
	new Node(              "Undefined", jgl::Vector2Int(30, 44), false,  Node::WALKABLE,  0u), //   509
	new Node(              "Undefined", jgl::Vector2Int(31, 44), false,  Node::WALKABLE,  0u), //   510
	new Node(              "Undefined", jgl::Vector2Int( 0, 45), false,  Node::WALKABLE,  0u), //   511
	new Node(              "Undefined", jgl::Vector2Int( 1, 45), false,  Node::WALKABLE,  0u), //   512
	new Node(              "Undefined", jgl::Vector2Int( 2, 45), false,  Node::WALKABLE,  0u), //   513
	new Node(              "Undefined", jgl::Vector2Int( 3, 45), false,  Node::WALKABLE,  0u), //   514
	new Node(              "Undefined", jgl::Vector2Int( 4, 45), false,  Node::WALKABLE,  0u), //   515
	new Node(              "Undefined", jgl::Vector2Int( 5, 45), false,  Node::WALKABLE,  0u), //   516
	new Node(              "Undefined", jgl::Vector2Int( 6, 45), false,  Node::WALKABLE,  0u), //   517
	new Node(              "Undefined", jgl::Vector2Int( 7, 45), false,  Node::WALKABLE,  0u), //   518
	new Node(              "Undefined", jgl::Vector2Int( 8, 45), false,  Node::WALKABLE,  0u), //   519
	new Node(              "Undefined", jgl::Vector2Int( 9, 45), false,  Node::WALKABLE,  0u), //   520
	new Node(              "Undefined", jgl::Vector2Int(10, 45), false,  Node::WALKABLE,  0u), //   521
	new Node(              "Undefined", jgl::Vector2Int(11, 45), false,  Node::WALKABLE,  0u), //   522
	new Node(              "Undefined", jgl::Vector2Int(12, 45), false,  Node::WALKABLE,  0u), //   523
	new Node(              "Undefined", jgl::Vector2Int(13, 45), false,  Node::WALKABLE,  0u), //   524
	new Node(              "Undefined", jgl::Vector2Int(14, 45), false,  Node::WALKABLE,  0u), //   525
	new Node(              "Undefined", jgl::Vector2Int(15, 45), false,  Node::WALKABLE,  0u), //   526
	new Node(              "Undefined", jgl::Vector2Int(16, 45), false,  Node::WALKABLE,  0u), //   527
	new Node(              "Undefined", jgl::Vector2Int(17, 45), false,  Node::WALKABLE,  0u), //   528
	new Node(              "Undefined", jgl::Vector2Int(18, 45), false,  Node::WALKABLE,  0u), //   529
	new Node(              "Undefined", jgl::Vector2Int(19, 45), false,  Node::WALKABLE,  0u), //   530
	new Node(              "Undefined", jgl::Vector2Int(20, 45), false,  Node::WALKABLE,  0u), //   531
	new Node(              "Undefined", jgl::Vector2Int(21, 45), false,  Node::WALKABLE,  0u), //   532
	new Node(              "Undefined", jgl::Vector2Int(22, 45), false,  Node::WALKABLE,  0u), //   533
	new Node(              "Undefined", jgl::Vector2Int(23, 45), false,  Node::WALKABLE,  0u), //   534
	new Node(              "Undefined", jgl::Vector2Int(24, 45), false,  Node::OBSTACLE,  0u), //   535
	new Node(              "Undefined", jgl::Vector2Int(25, 45), false,  Node::OBSTACLE,  0u), //   536
	new Node(              "Undefined", jgl::Vector2Int(26, 45), false,  Node::OBSTACLE,  0u), //   537
	new Node(              "Undefined", jgl::Vector2Int(27, 45), false,  Node::OBSTACLE,  0u), //   538
	new Node(              "Undefined", jgl::Vector2Int(28, 45), false,  Node::OBSTACLE,  0u), //   539
	new Node(              "Undefined", jgl::Vector2Int(29, 45), false,  Node::OBSTACLE,  0u), //   540
	new Node(              "Undefined", jgl::Vector2Int(30, 45), false,  Node::OBSTACLE,  0u), //   541
	new Node(              "Undefined", jgl::Vector2Int(31, 45), false,  Node::OBSTACLE,  0u), //   542
	new Node(              "Undefined", jgl::Vector2Int( 0, 46), false,  Node::OBSTACLE,  0u), //   543
	new Node(              "Undefined", jgl::Vector2Int( 1, 46), false,  Node::OBSTACLE,  0u), //   544
	new Node(              "Undefined", jgl::Vector2Int( 2, 46), false,  Node::OBSTACLE,  0u), //   545
	new Node(              "Undefined", jgl::Vector2Int( 3, 46), false,  Node::OBSTACLE,  0u), //   546
	new Node(              "Undefined", jgl::Vector2Int( 4, 46), false,  Node::OBSTACLE,  0u), //   547
	new Node(              "Undefined", jgl::Vector2Int( 5, 46), false,  Node::OBSTACLE,  0u), //   548
	new Node(              "Undefined", jgl::Vector2Int( 6, 46), false,  Node::OBSTACLE,  0u), //   549
	new Node(              "Undefined", jgl::Vector2Int( 7, 46), false,  Node::OBSTACLE,  0u), //   550
	new Node(              "Undefined", jgl::Vector2Int( 8, 46), false,  Node::OBSTACLE,  0u), //   551
	new Node(              "Undefined", jgl::Vector2Int( 9, 46), false,  Node::OBSTACLE,  0u), //   552
	new Node(              "Undefined", jgl::Vector2Int(10, 46), false,  Node::OBSTACLE,  0u), //   553
	new Node(              "Undefined", jgl::Vector2Int(11, 46), false,  Node::OBSTACLE,  0u), //   554
	new Node(              "Undefined", jgl::Vector2Int(12, 46), false,  Node::OBSTACLE,  0u), //   555
	new Node(              "Undefined", jgl::Vector2Int(13, 46), false,  Node::OBSTACLE,  0u), //   556
	new Node(              "Undefined", jgl::Vector2Int(14, 46), false,  Node::OBSTACLE,  0u), //   557
	new Node(              "Undefined", jgl::Vector2Int(15, 46), false,  Node::OBSTACLE,  0u), //   558
	new Node(              "Undefined", jgl::Vector2Int(16, 46), false,  Node::WALKABLE,  0u), //   559
	new Node(              "Undefined", jgl::Vector2Int(17, 46), false,  Node::WALKABLE,  0u), //   560
	new Node(              "Undefined", jgl::Vector2Int(18, 46), false,  Node::WALKABLE,  0u), //   561
	new Node(              "Undefined", jgl::Vector2Int(19, 46), false,  Node::WALKABLE,  0u), //   562
	new Node(              "Undefined", jgl::Vector2Int(20, 46), false,  Node::WALKABLE,  0u), //   563
	new Node(              "Undefined", jgl::Vector2Int(21, 46), false,  Node::WALKABLE,  0u), //   564
	new Node(              "Undefined", jgl::Vector2Int(22, 46), false,  Node::WALKABLE,  0u), //   565
	new Node(              "Undefined", jgl::Vector2Int(23, 46), false,  Node::WALKABLE,  0u), //   566
	new Node(              "Undefined", jgl::Vector2Int(24, 46), false,  Node::OBSTACLE,  0u), //   567
	new Node(              "Undefined", jgl::Vector2Int(25, 46), false,  Node::OBSTACLE,  0u), //   568
	new Node(              "Undefined", jgl::Vector2Int(26, 46), false,  Node::OBSTACLE,  0u), //   569
	new Node(              "Undefined", jgl::Vector2Int(27, 46), false,  Node::OBSTACLE,  0u), //   570
	new Node(              "Undefined", jgl::Vector2Int(28, 46), false,  Node::OBSTACLE,  0u), //   571
	new Node(              "Undefined", jgl::Vector2Int(29, 46), false,  Node::OBSTACLE,  0u), //   572
	new Node(              "Undefined", jgl::Vector2Int(30, 46), false,  Node::OBSTACLE,  0u), //   573
	new Node(              "Undefined", jgl::Vector2Int(31, 46), false,  Node::OBSTACLE,  0u), //   574
	new Node(              "Undefined", jgl::Vector2Int( 0, 47), false,  Node::WALKABLE,  0u), //   575
	new Node(              "Undefined", jgl::Vector2Int( 1, 47), false,  Node::WALKABLE,  0u), //   576
	new Node(              "Undefined", jgl::Vector2Int( 2, 47), false,  Node::WALKABLE,  0u), //   577
	new Node(              "Undefined", jgl::Vector2Int( 3, 47), false,  Node::WALKABLE,  0u), //   578
	new Node(              "Undefined", jgl::Vector2Int( 4, 47), false,  Node::WALKABLE,  0u), //   579
	new Node(              "Undefined", jgl::Vector2Int( 5, 47), false,  Node::WALKABLE,  0u), //   580
	new Node(              "Undefined", jgl::Vector2Int( 6, 47), false,  Node::WALKABLE,  0u), //   581
	new Node(              "Undefined", jgl::Vector2Int( 7, 47), false,  Node::WALKABLE,  0u), //   582
	new Node(              "Undefined", jgl::Vector2Int( 8, 47), false,  Node::WALKABLE,  0u), //   583
	new Node(              "Undefined", jgl::Vector2Int( 9, 47), false,  Node::WALKABLE,  0u), //   584
	new Node(              "Undefined", jgl::Vector2Int(10, 47), false,  Node::WALKABLE,  0u), //   585
	new Node(              "Undefined", jgl::Vector2Int(11, 47), false,  Node::WALKABLE,  0u), //   586
	new Node(              "Undefined", jgl::Vector2Int(12, 47), false,  Node::WALKABLE,  0u), //   587
	new Node(              "Undefined", jgl::Vector2Int(13, 47), false,  Node::WALKABLE,  0u), //   588
	new Node(              "Undefined", jgl::Vector2Int(14, 47), false,  Node::WALKABLE,  0u), //   589
	new Node(              "Undefined", jgl::Vector2Int(15, 47), false,  Node::WALKABLE,  0u), //   590
	new Node(              "Undefined", jgl::Vector2Int(16, 47), false,  Node::WALKABLE,  0u), //   591
	new Node(              "Undefined", jgl::Vector2Int(17, 47), false,  Node::WALKABLE,  0u), //   592
	new Node(              "Undefined", jgl::Vector2Int(18, 47), false,  Node::WALKABLE,  0u), //   593
	new Node(              "Undefined", jgl::Vector2Int(19, 47), false,  Node::WALKABLE,  0u), //   594
	new Node(              "Undefined", jgl::Vector2Int(20, 47), false,  Node::WALKABLE,  0u), //   595
	new Node(              "Undefined", jgl::Vector2Int(21, 47), false,  Node::WALKABLE,  0u), //   596
	new Node(              "Undefined", jgl::Vector2Int(22, 47), false,  Node::WALKABLE,  0u), //   597
	new Node(              "Undefined", jgl::Vector2Int(23, 47), false,  Node::WALKABLE,  0u), //   598
	new Node(              "Undefined", jgl::Vector2Int(24, 47), false,  Node::OBSTACLE,  0u), //   599
	new Node(              "Undefined", jgl::Vector2Int(25, 47), false,  Node::OBSTACLE,  0u), //   600
	new Node(              "Undefined", jgl::Vector2Int(26, 47), false,  Node::OBSTACLE,  0u), //   601
	new Node(              "Undefined", jgl::Vector2Int(27, 47), false,  Node::OBSTACLE,  0u), //   602
	new Node(              "Undefined", jgl::Vector2Int(28, 47), false,  Node::OBSTACLE,  0u), //   603
	new Node(              "Undefined", jgl::Vector2Int(29, 47), false,  Node::OBSTACLE,  0u), //   604
	new Node(              "Undefined", jgl::Vector2Int(30, 47), false,  Node::OBSTACLE,  0u), //   605
	new Node(              "Undefined", jgl::Vector2Int(31, 47), false,  Node::OBSTACLE,  0u), //   606
	new Node(              "Undefined", jgl::Vector2Int( 0, 48), false,  Node::OBSTACLE,  0u), //   607
	new Node(              "Undefined", jgl::Vector2Int( 1, 48), false,  Node::OBSTACLE,  0u), //   608
	new Node(              "Undefined", jgl::Vector2Int( 2, 48), false,  Node::OBSTACLE,  0u), //   609
	new Node(              "Undefined", jgl::Vector2Int( 3, 48), false,  Node::OBSTACLE,  0u), //   610
	new Node(              "Undefined", jgl::Vector2Int( 4, 48), false,  Node::OBSTACLE,  0u), //   611
	new Node(              "Undefined", jgl::Vector2Int( 5, 48), false,  Node::OBSTACLE,  0u), //   612
	new Node(              "Undefined", jgl::Vector2Int( 6, 48), false,  Node::OBSTACLE,  0u), //   613
	new Node(              "Undefined", jgl::Vector2Int( 7, 48), false,  Node::OBSTACLE,  0u), //   614
	new Node(              "Undefined", jgl::Vector2Int( 8, 48), false,  Node::OBSTACLE,  0u), //   615
	new Node(              "Undefined", jgl::Vector2Int( 9, 48), false,  Node::OBSTACLE,  0u), //   616
	new Node(              "Undefined", jgl::Vector2Int(10, 48), false,  Node::OBSTACLE,  0u), //   617
	new Node(              "Undefined", jgl::Vector2Int(11, 48), false,  Node::OBSTACLE,  0u), //   618
	new Node(              "Undefined", jgl::Vector2Int(12, 48), false,  Node::OBSTACLE,  0u), //   619
	new Node(              "Undefined", jgl::Vector2Int(13, 48), false,  Node::OBSTACLE,  0u), //   620
	new Node(              "Undefined", jgl::Vector2Int(14, 48), false,  Node::OBSTACLE,  0u), //   621
	new Node(              "Undefined", jgl::Vector2Int(15, 48), false,  Node::OBSTACLE,  0u), //   622
	new Node(              "Undefined", jgl::Vector2Int(16, 48), false,  Node::WALKABLE,  0u), //   623
	new Node(              "Undefined", jgl::Vector2Int(17, 48), false,  Node::WALKABLE,  0u), //   624
	new Node(              "Undefined", jgl::Vector2Int(18, 48), false,  Node::WALKABLE,  0u), //   625
	new Node(              "Undefined", jgl::Vector2Int(19, 48), false,  Node::WALKABLE,  0u), //   626
	new Node(              "Undefined", jgl::Vector2Int(20, 48), false,  Node::WALKABLE,  0u), //   627
	new Node(              "Undefined", jgl::Vector2Int(21, 48), false,  Node::WALKABLE,  0u), //   628
	new Node(              "Undefined", jgl::Vector2Int(22, 48), false,  Node::WALKABLE,  0u), //   629
	new Node(              "Undefined", jgl::Vector2Int(23, 48), false,  Node::WALKABLE,  0u), //   630
	new Node(              "Undefined", jgl::Vector2Int(24, 48), false,  Node::OBSTACLE,  0u), //   631
	new Node(              "Undefined", jgl::Vector2Int(25, 48), false,  Node::OBSTACLE,  0u), //   632
	new Node(              "Undefined", jgl::Vector2Int(26, 48), false,  Node::OBSTACLE,  0u), //   633
	new Node(              "Undefined", jgl::Vector2Int(27, 48), false,  Node::OBSTACLE,  0u), //   634
	new Node(              "Undefined", jgl::Vector2Int(28, 48), false,  Node::OBSTACLE,  0u), //   635
	new Node(              "Undefined", jgl::Vector2Int(29, 48), false,  Node::OBSTACLE,  0u), //   636
	new Node(              "Undefined", jgl::Vector2Int(30, 48), false,  Node::OBSTACLE,  0u), //   637
	new Node(              "Undefined", jgl::Vector2Int(31, 48), false,  Node::OBSTACLE,  0u), //   638
	new Node(              "Undefined", jgl::Vector2Int( 0, 49), false,  Node::WALKABLE,  0u), //   639
	new Node(              "Undefined", jgl::Vector2Int( 1, 49), false,  Node::WALKABLE,  0u), //   640
	new Node(              "Undefined", jgl::Vector2Int( 2, 49), false,  Node::WALKABLE,  0u), //   641
	new Node(              "Undefined", jgl::Vector2Int( 3, 49), false,  Node::WALKABLE,  0u), //   642
	new Node(              "Undefined", jgl::Vector2Int( 4, 49), false,  Node::WALKABLE,  0u), //   643
	new Node(              "Undefined", jgl::Vector2Int( 5, 49), false,  Node::WALKABLE,  0u), //   644
	new Node(              "Undefined", jgl::Vector2Int( 6, 49), false,  Node::WALKABLE,  0u), //   645
	new Node(              "Undefined", jgl::Vector2Int( 7, 49), false,  Node::WALKABLE,  0u), //   646
	new Node(              "Undefined", jgl::Vector2Int( 8, 49), false,  Node::WALKABLE,  0u), //   647
	new Node(              "Undefined", jgl::Vector2Int( 9, 49), false,  Node::WALKABLE,  0u), //   648
	new Node(              "Undefined", jgl::Vector2Int(10, 49), false,  Node::WALKABLE,  0u), //   649
	new Node(              "Undefined", jgl::Vector2Int(11, 49), false,  Node::WALKABLE,  0u), //   650
	new Node(              "Undefined", jgl::Vector2Int(12, 49), false,  Node::OBSTACLE,  0u), //   651
	new Node(              "Undefined", jgl::Vector2Int(13, 49), false,  Node::OBSTACLE,  0u), //   652
	new Node(              "Undefined", jgl::Vector2Int(14, 49), false,  Node::OBSTACLE,  0u), //   653
	new Node(              "Undefined", jgl::Vector2Int(15, 49), false,  Node::OBSTACLE,  0u), //   654
	new Node(              "Undefined", jgl::Vector2Int(16, 49), false,  Node::WALKABLE,  0u), //   655
	new Node(              "Undefined", jgl::Vector2Int(17, 49), false,  Node::WALKABLE,  0u), //   656
	new Node(              "Undefined", jgl::Vector2Int(18, 49), false,  Node::WALKABLE,  0u), //   657
	new Node(              "Undefined", jgl::Vector2Int(19, 49), false,  Node::WALKABLE,  0u), //   658
	new Node(              "Undefined", jgl::Vector2Int(20, 49), false,  Node::WALKABLE,  0u), //   659
	new Node(              "Undefined", jgl::Vector2Int(21, 49), false,  Node::WALKABLE,  0u), //   660
	new Node(              "Undefined", jgl::Vector2Int(22, 49), false,  Node::WALKABLE,  0u), //   661
	new Node(              "Undefined", jgl::Vector2Int(23, 49), false,  Node::WALKABLE,  0u), //   662
	new Node(              "Undefined", jgl::Vector2Int(24, 49), false,  Node::WALKABLE,  0u), //   663
	new Node(              "Undefined", jgl::Vector2Int(25, 49), false,  Node::WALKABLE,  0u), //   664
	new Node(              "Undefined", jgl::Vector2Int(26, 49), false,  Node::WALKABLE,  0u), //   665
	new Node(              "Undefined", jgl::Vector2Int(27, 49), false,  Node::WALKABLE,  0u), //   666
	new Node(              "Undefined", jgl::Vector2Int(28, 49), false,  Node::WALKABLE,  0u), //   667
	new Node(              "Undefined", jgl::Vector2Int(29, 49), false,  Node::WALKABLE,  0u), //   668
	new Node(              "Undefined", jgl::Vector2Int(30, 49), false,  Node::WALKABLE,  0u), //   669
	new Node(              "Undefined", jgl::Vector2Int(31, 49), false,  Node::WALKABLE,  0u), //   670
	new Node(              "Undefined", jgl::Vector2Int( 0, 50), false,  Node::WALKABLE,  0u), //   671
	new Node(              "Undefined", jgl::Vector2Int( 1, 50), false,  Node::WALKABLE,  0u), //   672
	new Node(              "Undefined", jgl::Vector2Int( 2, 50), false,  Node::WALKABLE,  0u), //   673
	new Node(              "Undefined", jgl::Vector2Int( 3, 50), false,  Node::WALKABLE,  0u), //   674
	new Node(              "Undefined", jgl::Vector2Int( 4, 50), false,  Node::WALKABLE,  0u), //   675
	new Node(              "Undefined", jgl::Vector2Int( 5, 50), false,  Node::WALKABLE,  0u), //   676
	new Node(              "Undefined", jgl::Vector2Int( 6, 50), false,  Node::WALKABLE,  0u), //   677
	new Node(              "Undefined", jgl::Vector2Int( 7, 50), false,  Node::WALKABLE,  0u), //   678
	new Node(              "Undefined", jgl::Vector2Int( 8, 50), false,  Node::WALKABLE,  0u), //   679
	new Node(              "Undefined", jgl::Vector2Int( 9, 50), false,  Node::WALKABLE,  0u), //   680
	new Node(              "Undefined", jgl::Vector2Int(10, 50), false,  Node::WALKABLE,  0u), //   681
	new Node(              "Undefined", jgl::Vector2Int(11, 50), false,  Node::WALKABLE,  0u), //   682
	new Node(              "Undefined", jgl::Vector2Int(12, 50), false,  Node::WALKABLE,  0u), //   683
	new Node(              "Undefined", jgl::Vector2Int(13, 50), false,  Node::WALKABLE,  0u), //   684
	new Node(              "Undefined", jgl::Vector2Int(14, 50), false,  Node::WALKABLE,  0u), //   685
	new Node(              "Undefined", jgl::Vector2Int(15, 50), false,  Node::WALKABLE,  0u), //   686
	new Node(              "Undefined", jgl::Vector2Int(16, 50), false,  Node::WALKABLE,  0u), //   687
	new Node(              "Undefined", jgl::Vector2Int(17, 50), false,  Node::WALKABLE,  0u), //   688
	new Node(              "Undefined", jgl::Vector2Int(18, 50), false,  Node::WALKABLE,  0u), //   689
	new Node(              "Undefined", jgl::Vector2Int(19, 50), false,  Node::WALKABLE,  0u), //   690
	new Node(              "Undefined", jgl::Vector2Int(20, 50), false,  Node::WALKABLE,  0u), //   691
	new Node(              "Undefined", jgl::Vector2Int(21, 50), false,  Node::WALKABLE,  0u), //   692
	new Node(              "Undefined", jgl::Vector2Int(22, 50), false,  Node::WALKABLE,  0u), //   693
	new Node(              "Undefined", jgl::Vector2Int(23, 50), false,  Node::WALKABLE,  0u), //   694
	new Node(              "Undefined", jgl::Vector2Int(24, 50), false,  Node::OBSTACLE,  0u), //   695
	new Node(              "Undefined", jgl::Vector2Int(25, 50), false,  Node::OBSTACLE,  0u), //   696
	new Node(              "Undefined", jgl::Vector2Int(26, 50), false,  Node::OBSTACLE,  0u), //   697
	new Node(              "Undefined", jgl::Vector2Int(27, 50), false,  Node::OBSTACLE,  0u), //   698
	new Node(              "Undefined", jgl::Vector2Int(28, 50), false,  Node::OBSTACLE,  0u), //   699
	new Node(              "Undefined", jgl::Vector2Int(29, 50), false,  Node::OBSTACLE,  0u), //   700
	new Node(              "Undefined", jgl::Vector2Int(30, 50), false,  Node::OBSTACLE,  0u), //   701
	new Node(              "Undefined", jgl::Vector2Int(31, 50), false,  Node::OBSTACLE,  0u), //   702
	new Node(              "Undefined", jgl::Vector2Int( 0, 51), false,  Node::WALKABLE,  0u), //   703
	new Node(              "Undefined", jgl::Vector2Int( 1, 51), false,  Node::WALKABLE,  0u), //   704
	new Node(              "Undefined", jgl::Vector2Int( 2, 51), false,  Node::WALKABLE,  0u), //   705
	new Node(              "Undefined", jgl::Vector2Int( 3, 51), false,  Node::WALKABLE,  0u), //   706
	new Node(              "Undefined", jgl::Vector2Int( 4, 51), false,  Node::WALKABLE,  0u), //   707
	new Node(              "Undefined", jgl::Vector2Int( 5, 51), false,  Node::WALKABLE,  0u), //   708
	new Node(              "Undefined", jgl::Vector2Int( 6, 51), false,  Node::WALKABLE,  0u), //   709
	new Node(              "Undefined", jgl::Vector2Int( 7, 51), false,  Node::WALKABLE,  0u), //   710
	new Node(              "Undefined", jgl::Vector2Int( 8, 51), false,  Node::OBSTACLE,  0u), //   711
	new Node(              "Undefined", jgl::Vector2Int( 9, 51), false,  Node::OBSTACLE,  0u), //   712
	new Node(              "Undefined", jgl::Vector2Int(10, 51), false,  Node::OBSTACLE,  0u), //   713
	new Node(              "Undefined", jgl::Vector2Int(11, 51), false,  Node::OBSTACLE,  0u), //   714
	new Node(              "Undefined", jgl::Vector2Int(12, 51), false,  Node::OBSTACLE,  0u), //   715
	new Node(              "Undefined", jgl::Vector2Int(13, 51), false,  Node::OBSTACLE,  0u), //   716
	new Node(              "Undefined", jgl::Vector2Int(14, 51), false,  Node::OBSTACLE,  0u), //   717
	new Node(              "Undefined", jgl::Vector2Int(15, 51), false,  Node::OBSTACLE,  0u), //   718
	new Node(              "Undefined", jgl::Vector2Int(16, 51), false,  Node::WALKABLE,  0u), //   719
	new Node(              "Undefined", jgl::Vector2Int(17, 51), false,  Node::WALKABLE,  0u), //   720
	new Node(              "Undefined", jgl::Vector2Int(18, 51), false,  Node::WALKABLE,  0u), //   721
	new Node(              "Undefined", jgl::Vector2Int(19, 51), false,  Node::WALKABLE,  0u), //   722
	new Node(              "Undefined", jgl::Vector2Int(20, 51), false,  Node::WALKABLE,  0u), //   723
	new Node(              "Undefined", jgl::Vector2Int(21, 51), false,  Node::WALKABLE,  0u), //   724
	new Node(              "Undefined", jgl::Vector2Int(22, 51), false,  Node::WALKABLE,  0u), //   725
	new Node(              "Undefined", jgl::Vector2Int(23, 51), false,  Node::WALKABLE,  0u), //   726
	new Node(              "Undefined", jgl::Vector2Int(24, 51), false,  Node::OBSTACLE,  0u), //   727
	new Node(              "Undefined", jgl::Vector2Int(25, 51), false,  Node::OBSTACLE,  0u), //   728
	new Node(              "Undefined", jgl::Vector2Int(26, 51), false,  Node::OBSTACLE,  0u), //   729
	new Node(              "Undefined", jgl::Vector2Int(27, 51), false,  Node::OBSTACLE,  0u), //   730
	new Node(              "Undefined", jgl::Vector2Int(28, 51), false,  Node::OBSTACLE,  0u), //   731
	new Node(              "Undefined", jgl::Vector2Int(29, 51), false,  Node::OBSTACLE,  0u), //   732
	new Node(              "Undefined", jgl::Vector2Int(30, 51), false,  Node::OBSTACLE,  0u), //   733
	new Node(              "Undefined", jgl::Vector2Int(31, 51), false,  Node::OBSTACLE,  0u), //   734
	new Node(              "Undefined", jgl::Vector2Int( 0, 52), false,  Node::OBSTACLE,  0u), //   735
	new Node(              "Undefined", jgl::Vector2Int( 1, 52), false,  Node::OBSTACLE,  0u), //   736
	new Node(              "Undefined", jgl::Vector2Int( 2, 52), false,  Node::OBSTACLE,  0u), //   737
	new Node(              "Undefined", jgl::Vector2Int( 3, 52), false,  Node::OBSTACLE,  0u), //   738
	new Node(              "Undefined", jgl::Vector2Int( 4, 52), false,  Node::OBSTACLE,  0u), //   739
	new Node(              "Undefined", jgl::Vector2Int( 5, 52), false,  Node::OBSTACLE,  0u), //   740
	new Node(              "Undefined", jgl::Vector2Int( 6, 52), false,  Node::OBSTACLE,  0u), //   741
	new Node(              "Undefined", jgl::Vector2Int( 7, 52), false,  Node::OBSTACLE,  0u), //   742
	new Node(              "Undefined", jgl::Vector2Int( 8, 52), false,  Node::OBSTACLE,  0u), //   743
	new Node(              "Undefined", jgl::Vector2Int( 9, 52), false,  Node::OBSTACLE,  0u), //   744
	new Node(              "Undefined", jgl::Vector2Int(10, 52), false,  Node::OBSTACLE,  0u), //   745
	new Node(              "Undefined", jgl::Vector2Int(11, 52), false,  Node::OBSTACLE,  0u), //   746
	new Node(              "Undefined", jgl::Vector2Int(12, 52), false,  Node::OBSTACLE,  0u), //   747
	new Node(              "Undefined", jgl::Vector2Int(13, 52), false,  Node::OBSTACLE,  0u), //   748
	new Node(              "Undefined", jgl::Vector2Int(14, 52), false,  Node::OBSTACLE,  0u), //   749
	new Node(              "Undefined", jgl::Vector2Int(15, 52), false,  Node::OBSTACLE,  0u), //   750
	new Node(              "Undefined", jgl::Vector2Int(16, 52), false,  Node::WALKABLE,  0u), //   751
	new Node(              "Undefined", jgl::Vector2Int(17, 52), false,  Node::WALKABLE,  0u), //   752
	new Node(              "Undefined", jgl::Vector2Int(18, 52), false,  Node::WALKABLE,  0u), //   753
	new Node(              "Undefined", jgl::Vector2Int(19, 52), false,  Node::WALKABLE,  0u), //   754
	new Node(              "Undefined", jgl::Vector2Int(20, 52), false,  Node::WALKABLE,  0u), //   755
	new Node(              "Undefined", jgl::Vector2Int(21, 52), false,  Node::WALKABLE,  0u), //   756
	new Node(              "Undefined", jgl::Vector2Int(22, 52), false,  Node::WALKABLE,  0u), //   757
	new Node(              "Undefined", jgl::Vector2Int(23, 52), false,  Node::WALKABLE,  0u), //   758
	new Node(              "Undefined", jgl::Vector2Int(24, 52), false,  Node::OBSTACLE,  0u), //   759
	new Node(              "Undefined", jgl::Vector2Int(25, 52), false,  Node::OBSTACLE,  0u), //   760
	new Node(              "Undefined", jgl::Vector2Int(26, 52), false,  Node::OBSTACLE,  0u), //   761
	new Node(              "Undefined", jgl::Vector2Int(27, 52), false,  Node::OBSTACLE,  0u), //   762
	new Node(              "Undefined", jgl::Vector2Int(28, 52), false,  Node::OBSTACLE,  0u), //   763
	new Node(              "Undefined", jgl::Vector2Int(29, 52), false,  Node::OBSTACLE,  0u), //   764
	new Node(              "Undefined", jgl::Vector2Int(30, 52), false,  Node::OBSTACLE,  0u), //   765
	new Node(              "Undefined", jgl::Vector2Int(31, 52), false,  Node::OBSTACLE,  0u), //   766
	new Node(              "Undefined", jgl::Vector2Int( 0, 53), false,  Node::WALKABLE,  0u), //   767
	new Node(              "Undefined", jgl::Vector2Int( 1, 53), false,  Node::WALKABLE,  0u), //   768
	new Node(              "Undefined", jgl::Vector2Int( 2, 53), false,  Node::WALKABLE,  0u), //   769
	new Node(              "Undefined", jgl::Vector2Int( 3, 53), false,  Node::WALKABLE,  0u), //   770
	new Node(              "Undefined", jgl::Vector2Int( 4, 53), false,  Node::WALKABLE,  0u), //   771
	new Node(              "Undefined", jgl::Vector2Int( 5, 53), false,  Node::WALKABLE,  0u), //   772
	new Node(              "Undefined", jgl::Vector2Int( 6, 53), false,  Node::WALKABLE,  0u), //   773
	new Node(              "Undefined", jgl::Vector2Int( 7, 53), false,  Node::WALKABLE,  0u), //   774
	new Node(              "Undefined", jgl::Vector2Int( 8, 53), false,  Node::OBSTACLE,  0u), //   775
	new Node(              "Undefined", jgl::Vector2Int( 9, 53), false,  Node::OBSTACLE,  0u), //   776
	new Node(              "Undefined", jgl::Vector2Int(10, 53), false,  Node::OBSTACLE,  0u), //   777
	new Node(              "Undefined", jgl::Vector2Int(11, 53), false,  Node::OBSTACLE,  0u), //   778
	new Node(              "Undefined", jgl::Vector2Int(12, 53), false,  Node::OBSTACLE,  0u), //   779
	new Node(              "Undefined", jgl::Vector2Int(13, 53), false,  Node::OBSTACLE,  0u), //   780
	new Node(              "Undefined", jgl::Vector2Int(14, 53), false,  Node::OBSTACLE,  0u), //   781
	new Node(              "Undefined", jgl::Vector2Int(15, 53), false,  Node::OBSTACLE,  0u), //   782
	new Node(              "Undefined", jgl::Vector2Int(16, 53), false,  Node::WALKABLE,  0u), //   783
	new Node(              "Undefined", jgl::Vector2Int(17, 53), false,  Node::WALKABLE,  0u), //   784
	new Node(              "Undefined", jgl::Vector2Int(18, 53), false,  Node::WALKABLE,  0u), //   785
	new Node(              "Undefined", jgl::Vector2Int(19, 53), false,  Node::WALKABLE,  0u), //   786
	new Node(              "Undefined", jgl::Vector2Int(20, 53), false,  Node::WALKABLE,  0u), //   787
	new Node(              "Undefined", jgl::Vector2Int(21, 53), false,  Node::WALKABLE,  0u), //   788
	new Node(              "Undefined", jgl::Vector2Int(22, 53), false,  Node::WALKABLE,  0u), //   789
	new Node(              "Undefined", jgl::Vector2Int(23, 53), false,  Node::WALKABLE,  0u), //   790
	new Node(              "Undefined", jgl::Vector2Int(24, 53), false,  Node::OBSTACLE,  0u), //   791
	new Node(              "Undefined", jgl::Vector2Int(25, 53), false,  Node::OBSTACLE,  0u), //   792
	new Node(              "Undefined", jgl::Vector2Int(26, 53), false,  Node::OBSTACLE,  0u), //   793
	new Node(              "Undefined", jgl::Vector2Int(27, 53), false,  Node::OBSTACLE,  0u), //   794
	new Node(              "Undefined", jgl::Vector2Int(28, 53), false,  Node::OBSTACLE,  0u), //   795
	new Node(              "Undefined", jgl::Vector2Int(29, 53), false,  Node::OBSTACLE,  0u), //   796
	new Node(              "Undefined", jgl::Vector2Int(30, 53), false,  Node::OBSTACLE,  0u), //   797
	new Node(              "Undefined", jgl::Vector2Int(31, 53), false,  Node::OBSTACLE,  0u), //   798
	new Node(              "Undefined", jgl::Vector2Int( 0, 54), false,  Node::OBSTACLE,  0u), //   799
	new Node(              "Undefined", jgl::Vector2Int( 1, 54), false,  Node::OBSTACLE,  0u), //   800
	new Node(              "Undefined", jgl::Vector2Int( 2, 54), false,  Node::OBSTACLE,  0u), //   801
	new Node(              "Undefined", jgl::Vector2Int( 3, 54), false,  Node::OBSTACLE,  0u), //   802
	new Node(              "Undefined", jgl::Vector2Int( 4, 54), false,  Node::OBSTACLE,  0u), //   803
	new Node(              "Undefined", jgl::Vector2Int( 5, 54), false,  Node::OBSTACLE,  0u), //   804
	new Node(              "Undefined", jgl::Vector2Int( 6, 54), false,  Node::OBSTACLE,  0u), //   805
	new Node(              "Undefined", jgl::Vector2Int( 7, 54), false,  Node::OBSTACLE,  0u), //   806
	new Node(              "Undefined", jgl::Vector2Int( 8, 54), false,  Node::OBSTACLE,  0u), //   807
	new Node(              "Undefined", jgl::Vector2Int( 9, 54), false,  Node::OBSTACLE,  0u), //   808
	new Node(              "Undefined", jgl::Vector2Int(10, 54), false,  Node::OBSTACLE,  0u), //   809
	new Node(              "Undefined", jgl::Vector2Int(11, 54), false,  Node::OBSTACLE,  0u), //   810
	new Node(              "Undefined", jgl::Vector2Int(12, 54), false,  Node::OBSTACLE,  0u), //   811
	new Node(              "Undefined", jgl::Vector2Int(13, 54), false,  Node::OBSTACLE,  0u), //   812
	new Node(              "Undefined", jgl::Vector2Int(14, 54), false,  Node::WALKABLE,  0u), //   813
	new Node(              "Undefined", jgl::Vector2Int(15, 54), false,  Node::WALKABLE,  0u), //   814
	new Node(              "Undefined", jgl::Vector2Int(16, 54), false,  Node::WALKABLE,  1u), //   815
	new Node(              "Undefined", jgl::Vector2Int(20, 54), false,  Node::WALKABLE,  1u), //   816
	new Node(              "Undefined", jgl::Vector2Int(24, 54), false,  Node::WALKABLE,  1u), //   817
	new Node(              "Undefined", jgl::Vector2Int(28, 54), false,  Node::WALKABLE,  1u), //   818
	new Node(              "Undefined", jgl::Vector2Int( 0, 55), false,  Node::WALKABLE,  0u), //   819
	new Node(              "Undefined", jgl::Vector2Int( 1, 55), false,  Node::WALKABLE,  0u), //   820
	new Node(              "Undefined", jgl::Vector2Int( 2, 55), false,  Node::WALKABLE,  0u), //   821
	new Node(              "Undefined", jgl::Vector2Int( 3, 55), false,  Node::WALKABLE,  0u), //   822
	new Node(              "Undefined", jgl::Vector2Int( 4, 55), false,  Node::WALKABLE,  0u), //   823
	new Node(              "Undefined", jgl::Vector2Int( 5, 55), false,  Node::WALKABLE,  0u), //   824
	new Node(              "Undefined", jgl::Vector2Int( 6, 55), false,  Node::OBSTACLE,  0u), //   825
	new Node(              "Undefined", jgl::Vector2Int( 7, 55), false,  Node::OBSTACLE,  0u), //   826
	new Node(              "Undefined", jgl::Vector2Int( 8, 55), false,  Node::OBSTACLE,  0u), //   827
	new Node(              "Undefined", jgl::Vector2Int( 9, 55), false,  Node::OBSTACLE,  0u), //   828
	new Node(              "Undefined", jgl::Vector2Int(10, 55), false,  Node::OBSTACLE,  0u), //   829
	new Node(              "Undefined", jgl::Vector2Int(11, 55), false,  Node::OBSTACLE,  0u), //   830
	new Node(              "Undefined", jgl::Vector2Int(12, 55), false,  Node::OBSTACLE,  0u), //   831
	new Node(              "Undefined", jgl::Vector2Int(13, 55), false,  Node::OBSTACLE,  0u), //   832
	new Node(              "Undefined", jgl::Vector2Int(14, 55), false,  Node::OBSTACLE,  0u), //   833
	new Node(              "Undefined", jgl::Vector2Int(15, 55), false,  Node::OBSTACLE,  0u), //   834
	new Node(              "Undefined", jgl::Vector2Int(16, 55), false,  Node::WALKABLE,  1u), //   835
	new Node(              "Undefined", jgl::Vector2Int(20, 55), false,  Node::WALKABLE,  1u), //   836
	new Node(              "Undefined", jgl::Vector2Int(24, 55), false,  Node::WALKABLE,  1u), //   837
	new Node(              "Undefined", jgl::Vector2Int(28, 55), false,  Node::WALKABLE,  1u), //   838
	new Node(              "Undefined", jgl::Vector2Int( 0, 56), false,  Node::WALKABLE,  0u), //   839
	new Node(              "Undefined", jgl::Vector2Int( 1, 56), false,  Node::WALKABLE,  0u), //   840
	new Node(              "Undefined", jgl::Vector2Int( 2, 56), false,  Node::WALKABLE,  0u), //   841
	new Node(              "Undefined", jgl::Vector2Int( 3, 56), false,  Node::WALKABLE,  0u), //   842
	new Node(              "Undefined", jgl::Vector2Int( 4, 56), false,  Node::WALKABLE,  0u), //   843
	new Node(              "Undefined", jgl::Vector2Int( 5, 56), false,  Node::WALKABLE,  0u), //   844
	new Node(              "Undefined", jgl::Vector2Int( 6, 56), false,  Node::OBSTACLE,  0u), //   845
	new Node(              "Undefined", jgl::Vector2Int( 7, 56), false,  Node::OBSTACLE,  0u), //   846
	new Node(              "Undefined", jgl::Vector2Int( 8, 56), false,  Node::WALKABLE,  0u), //   847
	new Node(              "Undefined", jgl::Vector2Int( 9, 56), false,  Node::WALKABLE,  0u), //   848
	new Node(              "Undefined", jgl::Vector2Int(10, 56), false,  Node::WALKABLE,  0u), //   849
	new Node(              "Undefined", jgl::Vector2Int(11, 56), false,  Node::WALKABLE,  0u), //   850
	new Node(              "Undefined", jgl::Vector2Int(12, 56), false,  Node::WALKABLE,  0u), //   851
	new Node(              "Undefined", jgl::Vector2Int(13, 56), false,  Node::WALKABLE,  0u), //   852
	new Node(              "Undefined", jgl::Vector2Int(14, 56), false,  Node::WALKABLE,  0u), //   853
	new Node(              "Undefined", jgl::Vector2Int(15, 56), false,  Node::WALKABLE,  0u), //   854
	new Node(              "Undefined", jgl::Vector2Int(16, 56), false,  Node::WALKABLE,  1u), //   855
	new Node(              "Undefined", jgl::Vector2Int(20, 56), false,  Node::WALKABLE,  1u), //   856
	new Node(              "Undefined", jgl::Vector2Int(24, 56), false,  Node::WALKABLE,  1u), //   857
	new Node(              "Undefined", jgl::Vector2Int(28, 56), false,  Node::WALKABLE,  1u), //   858
	new Node(              "Undefined", jgl::Vector2Int( 0, 57), false,  Node::WALKABLE,  0u), //   859
	new Node(              "Undefined", jgl::Vector2Int( 1, 57), false,  Node::WALKABLE,  0u), //   860
	new Node(              "Undefined", jgl::Vector2Int( 2, 57), false,  Node::WALKABLE,  0u), //   861
	new Node(              "Undefined", jgl::Vector2Int( 3, 57), false,  Node::WALKABLE,  0u), //   862
	new Node(              "Undefined", jgl::Vector2Int( 4, 57), false,  Node::WALKABLE,  0u), //   863
	new Node(              "Undefined", jgl::Vector2Int( 5, 57), false,  Node::WALKABLE,  0u), //   864
	new Node(              "Undefined", jgl::Vector2Int( 6, 57), false,  Node::WALKABLE,  0u), //   865
	new Node(              "Undefined", jgl::Vector2Int( 7, 57), false,  Node::WALKABLE,  0u), //   866
	new Node(              "Undefined", jgl::Vector2Int( 8, 57), false,  Node::WALKABLE,  0u), //   867
	new Node(              "Undefined", jgl::Vector2Int( 9, 57), false,  Node::WALKABLE,  0u), //   868
	new Node(              "Undefined", jgl::Vector2Int(10, 57), false,  Node::WALKABLE,  0u), //   869
	new Node(              "Undefined", jgl::Vector2Int(11, 57), false,  Node::WALKABLE,  0u), //   870
	new Node(              "Undefined", jgl::Vector2Int(12, 57), false,  Node::WALKABLE,  0u), //   871
	new Node(              "Undefined", jgl::Vector2Int(13, 57), false,  Node::WALKABLE,  0u), //   872
	new Node(              "Undefined", jgl::Vector2Int(14, 57), false,  Node::WALKABLE,  0u), //   873
	new Node(              "Undefined", jgl::Vector2Int(15, 57), false,  Node::WALKABLE,  0u), //   874
	new Node(              "Undefined", jgl::Vector2Int(16, 57), false,  Node::WALKABLE,  1u), //   875
	new Node(              "Undefined", jgl::Vector2Int(20, 57), false,  Node::WALKABLE,  1u), //   876
	new Node(              "Undefined", jgl::Vector2Int(24, 57), false,  Node::WALKABLE,  1u), //   877
	new Node(              "Undefined", jgl::Vector2Int(28, 57), false,  Node::WALKABLE,  1u), //   878
	new Node(              "Undefined", jgl::Vector2Int( 0, 58), false,  Node::OBSTACLE,  0u), //   879
	new Node(              "Undefined", jgl::Vector2Int( 1, 58), false,  Node::OBSTACLE,  0u), //   880
	new Node(              "Undefined", jgl::Vector2Int( 2, 58), false,  Node::OBSTACLE,  0u), //   881
	new Node(              "Undefined", jgl::Vector2Int( 3, 58), false,  Node::OBSTACLE,  0u), //   882
	new Node(              "Undefined", jgl::Vector2Int( 4, 58), false,  Node::OBSTACLE,  0u), //   883
	new Node(              "Undefined", jgl::Vector2Int( 5, 58), false,  Node::OBSTACLE,  0u), //   884
	new Node(              "Undefined", jgl::Vector2Int( 6, 58), false,  Node::OBSTACLE,  0u), //   885
	new Node(              "Undefined", jgl::Vector2Int( 7, 58), false,  Node::OBSTACLE,  0u), //   886
	new Node(              "Undefined", jgl::Vector2Int( 8, 58), false,  Node::OBSTACLE,  0u), //   887
	new Node(              "Undefined", jgl::Vector2Int( 9, 58), false,  Node::OBSTACLE,  0u), //   888
	new Node(              "Undefined", jgl::Vector2Int(10, 58), false,  Node::OBSTACLE,  0u), //   889
	new Node(              "Undefined", jgl::Vector2Int(11, 58), false,  Node::OBSTACLE,  0u), //   890
	new Node(              "Undefined", jgl::Vector2Int(12, 58), false,  Node::OBSTACLE,  0u), //   891
	new Node(              "Undefined", jgl::Vector2Int(13, 58), false,  Node::OBSTACLE,  0u), //   892
	new Node(              "Undefined", jgl::Vector2Int(14, 58), false,  Node::OBSTACLE,  0u), //   893
	new Node(              "Undefined", jgl::Vector2Int(15, 58), false,  Node::OBSTACLE,  0u), //   894
	new Node(                 "Flower", jgl::Vector2Int(16, 58), false,  Node::WALKABLE,  1u), //   895
	new Node(                 "Flower", jgl::Vector2Int(20, 58), false,  Node::WALKABLE,  1u), //   896
	new Node(                 "Flower", jgl::Vector2Int(24, 58), false,  Node::WALKABLE,  1u), //   897
	new Node(                 "Flower", jgl::Vector2Int(28, 58), false,  Node::WALKABLE,  1u), //   898
	new Node(                   "Ruin", jgl::Vector2Int( 0, 59), false,  Node::OBSTACLE,  0u), //   899
	new Node(                   "Ruin", jgl::Vector2Int( 1, 59), false,  Node::OBSTACLE,  0u), //   900
	new Node(                   "Ruin", jgl::Vector2Int( 2, 59), false,  Node::OBSTACLE,  0u), //   901
	new Node(                   "Ruin", jgl::Vector2Int( 3, 59), false,  Node::OBSTACLE,  0u), //   902
	new Node(                   "Ruin", jgl::Vector2Int( 4, 59), false,  Node::OBSTACLE,  0u), //   903
	new Node(                   "Ruin", jgl::Vector2Int( 5, 59), false,  Node::OBSTACLE,  0u), //   904
	new Node(                   "Ruin", jgl::Vector2Int( 6, 59), false,  Node::OBSTACLE,  0u), //   905
	new Node(                   "Ruin", jgl::Vector2Int( 7, 59), false,  Node::OBSTACLE,  0u), //   906
	new Node(              "Undefined", jgl::Vector2Int( 8, 59), false,  Node::WALKABLE,  0u), //   907
	new Node(              "Undefined", jgl::Vector2Int( 9, 59), false,  Node::WALKABLE,  0u), //   908
	new Node(              "Undefined", jgl::Vector2Int(10, 59), false,  Node::WALKABLE,  0u), //   909
	new Node(              "Undefined", jgl::Vector2Int(11, 59), false,  Node::WALKABLE,  0u), //   910
	new Node(              "Undefined", jgl::Vector2Int(12, 59), false,  Node::WALKABLE,  0u), //   911
	new Node(              "Undefined", jgl::Vector2Int(13, 59), false,  Node::WALKABLE,  0u), //   912
	new Node(              "Undefined", jgl::Vector2Int(14, 59), false,  Node::WALKABLE,  0u), //   913
	new Node(              "Undefined", jgl::Vector2Int(15, 59), false,  Node::WALKABLE,  0u), //   914
	new Node(              "Undefined", jgl::Vector2Int(16, 59), false,  Node::WALKABLE,  1u), //   915
	new Node(              "Undefined", jgl::Vector2Int(20, 59), false,  Node::WALKABLE,  1u), //   916
	new Node(              "Undefined", jgl::Vector2Int(24, 59), false,  Node::WALKABLE,  1u), //   917
	new Node(              "Undefined", jgl::Vector2Int(28, 59), false,  Node::WALKABLE,  1u), //   918
	new Node(                   "Ruin", jgl::Vector2Int( 0, 60), false,  Node::OBSTACLE,  0u), //   919
	new Node(                   "Ruin", jgl::Vector2Int( 1, 60), false,  Node::OBSTACLE,  0u), //   920
	new Node(                   "Ruin", jgl::Vector2Int( 2, 60), false,  Node::OBSTACLE,  0u), //   921
	new Node(                   "Ruin", jgl::Vector2Int( 3, 60), false,  Node::OBSTACLE,  0u), //   922
	new Node(                   "Ruin", jgl::Vector2Int( 4, 60), false,  Node::OBSTACLE,  0u), //   923
	new Node(                   "Ruin", jgl::Vector2Int( 5, 60), false,  Node::OBSTACLE,  0u), //   924
	new Node(                   "Ruin", jgl::Vector2Int( 6, 60), false,  Node::OBSTACLE,  0u), //   925
	new Node(                   "Ruin", jgl::Vector2Int( 7, 60), false,  Node::OBSTACLE,  0u), //   926
	new Node(              "Undefined", jgl::Vector2Int( 8, 60), false,  Node::OBSTACLE,  0u), //   927
	new Node(              "Undefined", jgl::Vector2Int( 9, 60), false,  Node::OBSTACLE,  0u), //   928
	new Node(              "Undefined", jgl::Vector2Int(10, 60), false,  Node::OBSTACLE,  0u), //   929
	new Node(              "Undefined", jgl::Vector2Int(11, 60), false,  Node::OBSTACLE,  0u), //   930
	new Node(              "Undefined", jgl::Vector2Int(12, 60), false,  Node::OBSTACLE,  0u), //   931
	new Node(              "Undefined", jgl::Vector2Int(13, 60), false,  Node::OBSTACLE,  0u), //   932
	new Node(              "Undefined", jgl::Vector2Int(14, 60), false,  Node::OBSTACLE,  0u), //   933
	new Node(              "Undefined", jgl::Vector2Int(15, 60), false,  Node::WALKABLE,  0u), //   934
	new Node(              "Undefined", jgl::Vector2Int(16, 60), false,  Node::OBSTACLE,  1u), //   935
	new Node(              "Undefined", jgl::Vector2Int(20, 60), false,  Node::OBSTACLE,  1u), //   936
	new Node(              "Undefined", jgl::Vector2Int(24, 60), false,  Node::OBSTACLE,  1u), //   937
	new Node(              "Undefined", jgl::Vector2Int(28, 60), false,  Node::OBSTACLE,  1u), //   938
	new Node(              "Undefined", jgl::Vector2Int( 0, 61), false,  Node::OBSTACLE,  0u), //   939
	new Node(              "Undefined", jgl::Vector2Int( 1, 61), false,  Node::OBSTACLE,  0u), //   940
	new Node(              "Undefined", jgl::Vector2Int( 2, 61), false,  Node::OBSTACLE,  0u), //   941
	new Node(              "Undefined", jgl::Vector2Int( 3, 61), false,  Node::OBSTACLE,  0u), //   942
	new Node(              "Undefined", jgl::Vector2Int( 4, 61), false,  Node::OBSTACLE,  0u), //   943
	new Node(              "Undefined", jgl::Vector2Int( 5, 61), false,  Node::OBSTACLE,  0u), //   944
	new Node(              "Undefined", jgl::Vector2Int( 6, 61), false,  Node::OBSTACLE,  0u), //   945
	new Node(              "Undefined", jgl::Vector2Int( 7, 61), false,  Node::OBSTACLE,  0u), //   946
	new Node(              "Undefined", jgl::Vector2Int( 8, 61), false,  Node::OBSTACLE,  0u), //   947
	new Node(              "Undefined", jgl::Vector2Int( 9, 61), false,  Node::OBSTACLE,  0u), //   948
	new Node(              "Undefined", jgl::Vector2Int(10, 61), false,  Node::OBSTACLE,  0u), //   949
	new Node(              "Undefined", jgl::Vector2Int(11, 61), false,  Node::OBSTACLE,  0u), //   950
	new Node(              "Undefined", jgl::Vector2Int(12, 61), false,  Node::OBSTACLE,  0u), //   951
	new Node(              "Undefined", jgl::Vector2Int(13, 61), false,  Node::OBSTACLE,  0u), //   952
	new Node(              "Undefined", jgl::Vector2Int(14, 61), false,  Node::OBSTACLE,  0u), //   953
	new Node(              "Undefined", jgl::Vector2Int(15, 61), false,  Node::OBSTACLE,  0u), //   954
	new Node(                  "Torch", jgl::Vector2Int(16, 61), false,  Node::OBSTACLE,  1u), //   955
	new Node(                  "Torch", jgl::Vector2Int(20, 61), false,  Node::OBSTACLE,  1u), //   956
	new Node(                  "Torch", jgl::Vector2Int(24, 61), false,  Node::OBSTACLE,  1u), //   957
	new Node(                  "Torch", jgl::Vector2Int(28, 61), false,  Node::OBSTACLE,  1u), //   958
	new Node(              "Undefined", jgl::Vector2Int( 0, 62), false,  Node::OBSTACLE,  0u), //   959
	new Node(              "Undefined", jgl::Vector2Int( 1, 62), false,  Node::OBSTACLE,  0u), //   960
	new Node(              "Undefined", jgl::Vector2Int( 2, 62), false,  Node::OBSTACLE,  0u), //   961
	new Node(              "Undefined", jgl::Vector2Int( 3, 62), false,  Node::OBSTACLE,  0u), //   962
	new Node(              "Undefined", jgl::Vector2Int( 4, 62), false,  Node::OBSTACLE,  0u), //   963
	new Node(              "Undefined", jgl::Vector2Int( 5, 62), false,  Node::OBSTACLE,  0u), //   964
	new Node(              "Undefined", jgl::Vector2Int( 6, 62), false,  Node::OBSTACLE,  0u), //   965
	new Node(              "Undefined", jgl::Vector2Int( 7, 62), false,  Node::OBSTACLE,  0u), //   966
	new Node(              "Undefined", jgl::Vector2Int( 8, 62), false,  Node::OBSTACLE,  0u), //   967
	new Node(              "Undefined", jgl::Vector2Int( 9, 62), false,  Node::OBSTACLE,  0u), //   968
	new Node(              "Undefined", jgl::Vector2Int(10, 62), false,  Node::OBSTACLE,  0u), //   969
	new Node(              "Undefined", jgl::Vector2Int(11, 62), false,  Node::OBSTACLE,  0u), //   970
	new Node(              "Undefined", jgl::Vector2Int(12, 62), false,  Node::OBSTACLE,  0u), //   971
	new Node(              "Undefined", jgl::Vector2Int(13, 62), false,  Node::OBSTACLE,  0u), //   972
	new Node(              "Undefined", jgl::Vector2Int(14, 62), false,  Node::OBSTACLE,  0u), //   973
	new Node(              "Undefined", jgl::Vector2Int(15, 62), false,  Node::OBSTACLE,  0u), //   974
	new Node(                   "Fire", jgl::Vector2Int(16, 62), false,  Node::OBSTACLE,  1u), //   975
	new Node(                   "Fire", jgl::Vector2Int(20, 62), false,  Node::OBSTACLE,  1u), //   976
	new Node(                   "Fire", jgl::Vector2Int(24, 62), false,  Node::OBSTACLE,  1u), //   977
	new Node(                   "Fire", jgl::Vector2Int(28, 62), false,  Node::OBSTACLE,  1u), //   978
	new Node(              "Undefined", jgl::Vector2Int( 0, 63), false,  Node::OBSTACLE,  0u), //   979
	new Node(              "Undefined", jgl::Vector2Int( 1, 63), false,  Node::OBSTACLE,  0u), //   980
	new Node(              "Undefined", jgl::Vector2Int( 2, 63), false,  Node::OBSTACLE,  0u), //   981
	new Node(              "Undefined", jgl::Vector2Int( 3, 63), false,  Node::OBSTACLE,  0u), //   982
	new Node(              "Undefined", jgl::Vector2Int( 4, 63), false,  Node::OBSTACLE,  0u), //   983
	new Node(              "Undefined", jgl::Vector2Int( 5, 63), false,  Node::OBSTACLE,  0u), //   984
	new Node(              "Undefined", jgl::Vector2Int( 6, 63), false,  Node::OBSTACLE,  0u), //   985
	new Node(              "Undefined", jgl::Vector2Int( 7, 63), false,  Node::OBSTACLE,  0u), //   986
	new Node(              "Undefined", jgl::Vector2Int( 8, 63), false,  Node::OBSTACLE,  0u), //   987
	new Node(              "Undefined", jgl::Vector2Int( 9, 63), false,  Node::OBSTACLE,  0u), //   988
	new Node(              "Undefined", jgl::Vector2Int(10, 63), false,  Node::OBSTACLE,  0u), //   989
	new Node(              "Undefined", jgl::Vector2Int(11, 63), false,  Node::OBSTACLE,  0u), //   990
	new Node(              "Undefined", jgl::Vector2Int(12, 63), false,  Node::OBSTACLE,  0u), //   991
	new Node(              "Undefined", jgl::Vector2Int(13, 63), false,  Node::OBSTACLE,  0u), //   992
	new Node(              "Undefined", jgl::Vector2Int(14, 63), false,  Node::OBSTACLE,  0u), //   993
	new Node(              "Undefined", jgl::Vector2Int(15, 63), false,  Node::OBSTACLE,  0u), //   994
	new Node(                   "Fire", jgl::Vector2Int(16, 63), false,  Node::WALKABLE,  1u), //   995
	new Node(                   "Fire", jgl::Vector2Int(20, 63), false,  Node::WALKABLE,  1u), //   996
	new Node(                   "Fire", jgl::Vector2Int(24, 63), false,  Node::WALKABLE,  1u), //   997
	new Node(                   "Fire", jgl::Vector2Int(28, 63), false,  Node::WALKABLE,  1u), //   998
	new Node(              "Undefined", jgl::Vector2Int( 0, 64), false,  Node::OBSTACLE,  0u), //   999
	new Node(              "Undefined", jgl::Vector2Int( 1, 64), false,  Node::OBSTACLE,  0u), //   1000
	new Node(              "Undefined", jgl::Vector2Int( 2, 64), false,  Node::OBSTACLE,  0u), //   1001
	new Node(              "Undefined", jgl::Vector2Int( 3, 64), false,  Node::OBSTACLE,  0u), //   1002
	new Node(              "Undefined", jgl::Vector2Int( 4, 64), false,  Node::OBSTACLE,  0u), //   1003
	new Node(              "Undefined", jgl::Vector2Int( 5, 64), false,  Node::OBSTACLE,  0u), //   1004
	new Node(              "Undefined", jgl::Vector2Int( 6, 64), false,  Node::OBSTACLE,  0u), //   1005
	new Node(              "Undefined", jgl::Vector2Int( 7, 64), false,  Node::OBSTACLE,  0u), //   1006
	new Node(              "Undefined", jgl::Vector2Int( 8, 64), false,  Node::OBSTACLE,  0u), //   1007
	new Node(              "Undefined", jgl::Vector2Int( 9, 64), false,  Node::OBSTACLE,  0u), //   1008
	new Node(              "Undefined", jgl::Vector2Int(10, 64), false,  Node::OBSTACLE,  0u), //   1009
	new Node(              "Undefined", jgl::Vector2Int(11, 64), false,  Node::OBSTACLE,  0u), //   1010
	new Node(              "Undefined", jgl::Vector2Int(12, 64), false,  Node::OBSTACLE,  0u), //   1011
	new Node(              "Undefined", jgl::Vector2Int(13, 64), false,  Node::OBSTACLE,  0u), //   1012
	new Node(              "Undefined", jgl::Vector2Int(14, 64), false,  Node::OBSTACLE,  0u), //   1013
	new Node(              "Undefined", jgl::Vector2Int(15, 64), false,  Node::OBSTACLE,  0u), //   1014
	new Node(                   "Fire", jgl::Vector2Int(16, 64), false,  Node::WALKABLE,  1u), //   1015
	new Node(                   "Fire", jgl::Vector2Int(20, 64), false,  Node::WALKABLE,  1u), //   1016
	new Node(                   "Fire", jgl::Vector2Int(24, 64), false,  Node::WALKABLE,  1u), //   1017
	new Node(                   "Fire", jgl::Vector2Int(28, 64), false,  Node::WALKABLE,  1u), //   1018
	new Node(              "Undefined", jgl::Vector2Int( 0, 65), false,  Node::OBSTACLE,  0u), //   1019
	new Node(              "Undefined", jgl::Vector2Int( 1, 65), false,  Node::OBSTACLE,  0u), //   1020
	new Node(              "Undefined", jgl::Vector2Int( 2, 65), false,  Node::OBSTACLE,  0u), //   1021
	new Node(              "Undefined", jgl::Vector2Int( 3, 65), false,  Node::OBSTACLE,  0u), //   1022
	new Node(              "Undefined", jgl::Vector2Int( 4, 65), false,  Node::OBSTACLE,  0u), //   1023
	new Node(              "Undefined", jgl::Vector2Int( 5, 65), false,  Node::OBSTACLE,  0u), //   1024
	new Node(              "Undefined", jgl::Vector2Int( 6, 65), false,  Node::OBSTACLE,  0u), //   1025
	new Node(              "Undefined", jgl::Vector2Int( 7, 65), false,  Node::OBSTACLE,  0u), //   1026
	new Node(              "Undefined", jgl::Vector2Int( 8, 65), false,  Node::OBSTACLE,  0u), //   1027
	new Node(              "Undefined", jgl::Vector2Int( 9, 65), false,  Node::OBSTACLE,  0u), //   1028
	new Node(              "Undefined", jgl::Vector2Int(10, 65), false,  Node::OBSTACLE,  0u), //   1029
	new Node(              "Undefined", jgl::Vector2Int(11, 65), false,  Node::OBSTACLE,  0u), //   1030
	new Node(              "Undefined", jgl::Vector2Int(12, 65), false,  Node::OBSTACLE,  0u), //   1031
	new Node(              "Undefined", jgl::Vector2Int(13, 65), false,  Node::OBSTACLE,  0u), //   1032
	new Node(              "Undefined", jgl::Vector2Int(14, 65), false,  Node::OBSTACLE,  0u), //   1033
	new Node(              "Undefined", jgl::Vector2Int(15, 65), false,  Node::OBSTACLE,  0u), //   1034
	new Node(                   "Fire", jgl::Vector2Int(16, 65), false,  Node::WALKABLE,  1u), //   1035
	new Node(                   "Fire", jgl::Vector2Int(20, 65), false,  Node::WALKABLE,  1u), //   1036
	new Node(                   "Fire", jgl::Vector2Int(24, 65), false,  Node::WALKABLE,  1u), //   1037
	new Node(                   "Fire", jgl::Vector2Int(28, 65), false,  Node::WALKABLE,  1u), //   1038
};

jgl::Array<Prefab*> g_prefab_array =
{
	new Prefab("Tree - Green", jgl::Vector2Int(0, 0), jgl::Vector2Int(1, 2), {
			447,
			479
		}, {
			3,
			0
		}),//  0
	new Prefab("Tree - Brown", jgl::Vector2Int(1, 0), jgl::Vector2Int(1, 2), {
			448,
			480
		}, {
			3,
			0
		}),//  1
	new Prefab("Tree - Pink", jgl::Vector2Int(2, 0), jgl::Vector2Int(1, 2), {
			449,
			481
		}, {
			3,
			0
		}),//  2
	new Prefab("Tree - Dark green", jgl::Vector2Int(3, 0), jgl::Vector2Int(1, 2), {
			450,
			482
		}, {
			3,
			0
		}),//  3
	new Prefab("Tree - Light green", jgl::Vector2Int(4, 0), jgl::Vector2Int(1, 2), {
			451,
			483
		}, {
			3,
			0
		}),//  4
	new Prefab("Tree - Blue", jgl::Vector2Int(5, 0), jgl::Vector2Int(1, 2), {
			452,
			484
		}, {
			3,
			0
		}),//  5
	new Prefab("Tree - Purple", jgl::Vector2Int(6, 0), jgl::Vector2Int(1, 2), {
			453,
			485
		}, {
			3,
			0
		}),//  6
	new Prefab("Tree - White", jgl::Vector2Int(7, 0), jgl::Vector2Int(1, 2), {
			454,
			486
		}, {
			3,
			0
		}),//  7
	new Prefab("Big tree - Green", jgl::Vector2Int(0, 1), jgl::Vector2Int(2, 2), {
			511, 512,
			543, 544
		}, {
			3, 3,
			0, 0
		}),//  8
	new Prefab("Big tree - Brown", jgl::Vector2Int(1, 1), jgl::Vector2Int(2, 2), {
			513, 514,
			545, 546
		}, {
			3, 3,
			0, 0
		}),//  9
	new Prefab("Big tree - Pink", jgl::Vector2Int(2, 1), jgl::Vector2Int(2, 2), {
			515, 516,
			547, 548
		}, {
			3, 3,
			0, 0
		}),//  10
	new Prefab("Big tree - Dark green", jgl::Vector2Int(3, 1), jgl::Vector2Int(2, 2), {
			517, 518, 
			549, 550
		}, {
			3, 3,
			0, 0
		}),//  11
	new Prefab("Big tree - Light green", jgl::Vector2Int(4, 1), jgl::Vector2Int(2, 2), {
			575, 576, 
			607, 608
		}, {
			3, 3,
			0, 0
		}),//  12
	new Prefab("Big tree - Blue", jgl::Vector2Int(5, 1), jgl::Vector2Int(2, 2), {
			577, 578,
			609, 610
		}, {
			3, 3,
			0, 0
		}),//  13
	new Prefab("Big tree - Purple", jgl::Vector2Int(6, 1), jgl::Vector2Int(2, 2), {
			579, 580, 
			611, 612
		}, {
			3, 3,
			0, 0
		}),//  14
	new Prefab("Big tree - White", jgl::Vector2Int(7, 1), jgl::Vector2Int(2, 2), {
			581, 582, 
			613, 614
		}, {
			3, 3,
			0, 0
		}),//  15
	new Prefab("Banner ", jgl::Vector2Int(0, 2), jgl::Vector2Int(1, 2), {
			907,
			927
		}, {
			3,
			0
		}),//  16
	new Prefab("Banner ", jgl::Vector2Int(1, 2), jgl::Vector2Int(1, 2), {
			908,
			928
		}, {
			3,
			0
		}),//  17
	new Prefab("Banner ", jgl::Vector2Int(2, 2), jgl::Vector2Int(1, 2), {
			909,
			929
		}, {
			3,
			0
		}),//  18
	new Prefab("Banner ", jgl::Vector2Int(3, 2), jgl::Vector2Int(1, 2), {
			910,
			930
		}, {
			3,
			0
		}),//  19
	new Prefab("Banner ", jgl::Vector2Int(4, 2), jgl::Vector2Int(1, 2), {
			911,
			931
		}, {
			3,
			0
		}),//  20
	new Prefab("Banner ", jgl::Vector2Int(5, 2), jgl::Vector2Int(1, 2), {
			912,
			932
		}, {
			3,
			0
		}),//  21
	new Prefab("Banner ", jgl::Vector2Int(6, 2), jgl::Vector2Int(1, 2), {
			913,
			933
		}, {
			3,
			0
		}),//  22
	new Prefab("Trunk", jgl::Vector2Int(7, 2), jgl::Vector2Int(2, 2), {
			825, 826,
			845, 846
		}, {
			3, 3,
			0, 0
		}),//  23
	new Prefab("Ruin", jgl::Vector2Int(0, 3), jgl::Vector2Int(2, 1), {
			919, 920
		}, {
			0, 0
		}),//  24
	new Prefab("Ruin", jgl::Vector2Int(1, 3), jgl::Vector2Int(2, 1), {
			921, 922
		}, {
			0, 0
		}),//  25
	new Prefab("Ruin", jgl::Vector2Int(2, 3), jgl::Vector2Int(2, 1), {
			939, 940
		}, {
			0, 0
		}),//  26
	new Prefab("Ruin", jgl::Vector2Int(3, 3), jgl::Vector2Int(2, 1), {
			941, 942
		}, {
			0, 0
		}),//  27
	new Prefab("Ruin", jgl::Vector2Int(4, 3), jgl::Vector2Int(1, 2), {
			911,
			943
		}, {
			3,
			0
		}),//  28
	new Prefab("Ruin", jgl::Vector2Int(5, 3), jgl::Vector2Int(1, 2), {
			912,
			944
		}, {
			3,
			0
		}),//  29
	new Prefab("Ruin", jgl::Vector2Int(6, 3), jgl::Vector2Int(1, 2), {
			913,
			945
		}, {
			3,
			0
		}),//  30
	new Prefab("Ruin", jgl::Vector2Int(7, 3), jgl::Vector2Int(1, 2), {
			914,
			946
		}, {
			3,
			0
		}),//  31
	new Prefab("Column base", jgl::Vector2Int(0, 4), jgl::Vector2Int(2, 2), {
			743, 744,
			775, 776
		}, {
			3, 3,
			0, 0
		}),//  32
	new Prefab("Column base", jgl::Vector2Int(1, 4), jgl::Vector2Int(2, 2), {
			745, 746,
			777, 778
		}, {
			3, 3,
			0, 0
		}),//  33
	new Prefab("Column base", jgl::Vector2Int(2, 4), jgl::Vector2Int(2, 2), {
			747,748,
			779,780
		}, {
			3, 3,
			0, 0
		}),//  34
	new Prefab("Column base - broken", jgl::Vector2Int(3, 4), jgl::Vector2Int(2, 2), {
			749,750,
			781,782
		}, {
			3, 3,
			0, 0
		}),//  35
	new Prefab("Unknow", jgl::Vector2Int(4, 4), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  36
	new Prefab("Unknow", jgl::Vector2Int(5, 4), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  37
	new Prefab("Chair", jgl::Vector2Int(6, 4), jgl::Vector2Int(1, 2), {
			867,
			887
		}, {
			3,
			0
		}),//  38
	new Prefab("Chair", jgl::Vector2Int(7, 4), jgl::Vector2Int(1, 2), {
			868, 
			888
		}, {
			3,
			0
		}),//  39
	new Prefab("Column body", jgl::Vector2Int(0, 5), jgl::Vector2Int(2, 2), {
			807, 808,
			827, 828
		}, {
			3, 3,
			0, 0
		}),//  40
	new Prefab("Column body", jgl::Vector2Int(1, 5), jgl::Vector2Int(2, 2), {
			809, 810,
			829, 830
		}, {
			3, 3,
			0, 0
		}),//  41
	new Prefab("Column body", jgl::Vector2Int(2, 5), jgl::Vector2Int(2, 2), {
			811, 812,
			831, 832
		}, {
			3, 3,
			0, 0
		}),//  42
	new Prefab("Statue", jgl::Vector2Int(3, 5), jgl::Vector2Int(2, 2), {
			813, 814,
			833, 834
		}, {
			3, 3,
			0, 0
		}),//  43
	new Prefab("Shelf - Empty", jgl::Vector2Int(4, 5), jgl::Vector2Int(2, 3), {
			849, 850,
			869, 870,
			889, 890
		}, {
			3, 3,
			3, 3,
			0, 0
		}),//  44
	new Prefab("Shelf - Book", jgl::Vector2Int(5, 5), jgl::Vector2Int(2, 3), {
			851, 852,
			871, 872,
			891, 892
		}, {
			3, 3,
			3, 3,
			0, 0
		}),//  45
	new Prefab("Shelf - Food", jgl::Vector2Int(6, 5), jgl::Vector2Int(2, 3), {
			853, 854,
			873, 874,
			893, 894
		}, {
			3, 3,
			3, 3,
			0, 0
		}),//  46
	new Prefab("Unknow", jgl::Vector2Int(7, 5), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  47
	new Prefab("Torch - Red", jgl::Vector2Int(0, 6), jgl::Vector2Int(1, 2), {
			915,
			935
		}, {
			3,
			0
		}),//  48
	new Prefab("Torch - Green", jgl::Vector2Int(1, 6), jgl::Vector2Int(1, 2), {
			916,
			936
		}, {
			3,
			0
		}),//  49
	new Prefab("Torch - Blue", jgl::Vector2Int(2, 6), jgl::Vector2Int(1, 2), {
			917,
			937
		}, {
			3,
			0
		}),//  50
	new Prefab("Torch - Black", jgl::Vector2Int(3, 6), jgl::Vector2Int(1, 2), {
			918,
			938
		}, {
			3,
			0
		}),//  51
	new Prefab("Unknow", jgl::Vector2Int(4, 6), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  52
	new Prefab("Unknow", jgl::Vector2Int(5, 6), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  53
	new Prefab("Unknow", jgl::Vector2Int(6, 6), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  54
	new Prefab("Unknow", jgl::Vector2Int(7, 6), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  55
	new Prefab("Crystal", jgl::Vector2Int(0, 7), jgl::Vector2Int(1, 2), {
			455,
			487
		}, {
			3,
			0
		}),//  56
	new Prefab("Crystal", jgl::Vector2Int(1, 7), jgl::Vector2Int(1, 2), {
			456, 
			488
		}, {
			3,
			0
		}),//  57
	new Prefab("Crystal", jgl::Vector2Int(2, 7), jgl::Vector2Int(1, 2), {
			457, 
			489
		}, {
			3,
			0
		}),//  58
	new Prefab("Crystal", jgl::Vector2Int(3, 7), jgl::Vector2Int(1, 2), {
			458,
			490
		}, {
			3,
			0
		}),//  59
	new Prefab("Crystal", jgl::Vector2Int(4, 7), jgl::Vector2Int(1, 2), {
			459, 
			491
		}, {
			3,
			0
		}),//  60
	new Prefab("Crystal", jgl::Vector2Int(5, 7), jgl::Vector2Int(1, 2), {
			460, 
			492
		}, {
			3,
			0
		}),//  61
	new Prefab("Crystal", jgl::Vector2Int(6, 7), jgl::Vector2Int(1, 2), {
			461,
			493
		}, {
			3,
			0
		}),//  62
	new Prefab("Crystal", jgl::Vector2Int(7, 7), jgl::Vector2Int(1, 2), {
			462,
			497
		}, {
			3,
			0
		}),//  63
	new Prefab("Big crystal", jgl::Vector2Int(0, 8), jgl::Vector2Int(2, 2), {
			519, 520,
			551, 552
		}, {
			3, 3,
			0, 0
		}),//  64
	new Prefab("Big crystal", jgl::Vector2Int(1, 8), jgl::Vector2Int(2, 2), {
			521, 522,
			553, 554
		}, {
			3, 3,
			0, 0
		}),//  65
	new Prefab("Big crystal", jgl::Vector2Int(2, 8), jgl::Vector2Int(2, 2), {
			523, 524,
			555, 556
		}, {
			3, 3,
			0, 0
		}),//  66
	new Prefab("Big crystal", jgl::Vector2Int(3, 8), jgl::Vector2Int(2, 2), {
			525, 526, 
			557, 558
		}, {
			3, 3,
			0, 0
		}),//  67
	new Prefab("Big crystal", jgl::Vector2Int(4, 8), jgl::Vector2Int(2, 2), {
			583, 584,
			615, 616
		}, {
			3, 3,
			0, 0
		}),//  68
	new Prefab("Big crystal", jgl::Vector2Int(5, 8), jgl::Vector2Int(2, 2), {
			585, 586, 
			617, 618
		}, {
			3, 3,
			0, 0
		}),//  69
	new Prefab("Big crystal", jgl::Vector2Int(6, 8), jgl::Vector2Int(2, 2), {
			587, 588,
			619, 620
		}, {
			3, 3,
			0, 0
		}),//  70
	new Prefab("Big crystal", jgl::Vector2Int(7, 8), jgl::Vector2Int(2, 2), {
			589, 590,
			621, 622
		}, {
			3, 3,
			0, 0
		}),//  71
	new Prefab("Stone", jgl::Vector2Int(0, 9), jgl::Vector2Int(1, 2), {
			767, 
			799
		}, {
			3,
			0
		}),//  72
	new Prefab("Stone", jgl::Vector2Int(1, 9), jgl::Vector2Int(1, 2), {
			768,
			800
		}, {
			3,
			0
		}),//  73
	new Prefab("Stone", jgl::Vector2Int(2, 9), jgl::Vector2Int(1, 2), {
			769, 
			801
		}, {
			3,
			0
		}),//  74
	new Prefab("Stone", jgl::Vector2Int(3, 9), jgl::Vector2Int(1, 2), {
			770, 
			802
		}, {
			3,
			0
		}),//  75
	new Prefab("Big stone", jgl::Vector2Int(4, 9), jgl::Vector2Int(2, 2), {
			771, 772,
			803, 804
		}, {
			3, 3,
			0, 0
		}),//  76
	new Prefab("Big stone", jgl::Vector2Int(5, 9), jgl::Vector2Int(2, 2), {
			773, 774,
			805, 806
		}, {
			3, 3,
			0, 0
		}),//  77
	new Prefab("Unknow", jgl::Vector2Int(6, 9), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  78
	new Prefab("Unknow", jgl::Vector2Int(7, 9), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  79
	new Prefab("Statue", jgl::Vector2Int(0, 10), jgl::Vector2Int(1, 2), {
			679, 
			711
		}, {
			3,
			0
		}),//  80
	new Prefab("Statue", jgl::Vector2Int(1, 10), jgl::Vector2Int(1, 2), {
			680, 
			712
		}, {
			3,
			0
		}),//  81
	new Prefab("Statue", jgl::Vector2Int(2, 10), jgl::Vector2Int(1, 2), {
			681,
			713
		}, {
			3,
			0
		}),//  82
	new Prefab("Statue", jgl::Vector2Int(3, 10), jgl::Vector2Int(1, 2), {
			682,
			714
		}, {
			3,
			0
		}),//  83
	new Prefab("Cactuses", jgl::Vector2Int(4, 10), jgl::Vector2Int(1, 2), {
			683, 
			715
		}, {
			3,
			0
		}),//  84
	new Prefab("Cactuses", jgl::Vector2Int(5, 10), jgl::Vector2Int(1, 2), {
			684, 
			716
		}, {
			3,
			0
		}),//  85
	new Prefab("Cactuses", jgl::Vector2Int(6, 10), jgl::Vector2Int(1, 2), {
			685, 
			717
		}, {
			3,
			0
		}),//  86
	new Prefab("Cactuses", jgl::Vector2Int(7, 10), jgl::Vector2Int(1, 2), {
			686, 
			718
		}, {
			3, 
			0
		}),//  87
	new Prefab("Small house", jgl::Vector2Int(0, 11), jgl::Vector2Int(4, 3), {
			503, 505, 505, 506,
			567, 569, 569, 570,
			631, 632, 633, 634
		}, {
			3, 3, 3, 3,
			0, 0, 0, 0, 
			0, 0, 0, 0
		}),//  88
	new Prefab("Small house", jgl::Vector2Int(1, 11), jgl::Vector2Int(4, 3), {
			507, 509, 509, 510,
			571, 573, 573, 574,
			635, 632, 637, 638
		}, {
			3, 3, 3, 3,
			0, 0, 0, 0, 
			0, 0, 0, 0
		}),//  89
	new Prefab("Small house", jgl::Vector2Int(2, 11), jgl::Vector2Int(4, 3), {
			663, 665, 665, 666,
			727, 728, 729, 730,
			791, 792, 793, 794
		}, {
			3, 3, 3, 3,
			0, 0, 0, 0, 
			0, 0, 0, 0
		}),//  90
	new Prefab("Small house", jgl::Vector2Int(3, 11), jgl::Vector2Int(4, 3), {
			667, 669, 669, 670,
			731, 732, 733, 734,
			795, 796, 797, 798
		}, {
			3, 3, 3, 3,
			0, 0, 0, 0, 
			0, 0, 0, 0
		}),//  91
	new Prefab("Unknow", jgl::Vector2Int(4, 11), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  92
	new Prefab("Unknow", jgl::Vector2Int(5, 11), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  93
	new Prefab("Unknow", jgl::Vector2Int(6, 11), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  94
	new Prefab("Unknow", jgl::Vector2Int(7, 11), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  95
	new Prefab("Medium house", jgl::Vector2Int(0, 12), jgl::Vector2Int(5, 3), {
			503, 504, 505, 505, 506,
			567, 569, 569, 569, 570,
			631, 632, 633, 633, 634
		}, {
			3, 3, 3, 3, 3,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}),//  96
	new Prefab("Medium house", jgl::Vector2Int(1, 12), jgl::Vector2Int(5, 3), {
			507, 508, 509, 509, 510,
			571, 573, 573, 573, 574,
			635, 632, 637, 637, 638
		}, {
			3, 3, 3, 3, 3,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}),//  97
	new Prefab("Medium house", jgl::Vector2Int(2, 12), jgl::Vector2Int(5, 3), {
			663, 664, 665, 665, 666,
			727, 728, 729, 729, 730,
			791, 792, 793, 793, 794
		}, {
			3, 3, 3, 3, 3,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}),//  98
	new Prefab("Medium house", jgl::Vector2Int(3, 12), jgl::Vector2Int(5, 3), {
			667, 668, 669, 669, 670,
			731, 732, 733, 733, 734,
			795, 796, 797, 797, 798
		}, {
			3, 3, 3, 3, 3,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
		}),//  99
	new Prefab("Unknow", jgl::Vector2Int(4, 12), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  100
	new Prefab("Unknow", jgl::Vector2Int(5, 12), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  101
	new Prefab("Unknow", jgl::Vector2Int(6, 12), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  102
	new Prefab("Unknow", jgl::Vector2Int(7, 12), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  103
	new Prefab("Big house", jgl::Vector2Int(0, 13), jgl::Vector2Int(5, 5), {
			503, 505, 505, 505, 506,
			535, 537, 537, 537, 538,
			567, 569, 569, 569, 570,
			599, 600, 600, 600, 602,
			631, 632, 633, 633, 634
		}, {
			3, 3, 3, 3, 3,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0
		}),//  104
	new Prefab("Big house", jgl::Vector2Int(1, 13), jgl::Vector2Int(5, 5), {
			507, 509, 509, 509, 510,
			539, 541, 541, 541, 542,
			571, 573, 573, 573, 574,
			603, 605, 605, 605, 606,
			635, 632, 637, 637, 638
		}, {
			3, 3, 3, 3, 3,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0
		}),//  105
	new Prefab("Big house", jgl::Vector2Int(2, 13), jgl::Vector2Int(5, 5), {
			663, 665, 665, 665, 666,
			695, 697, 697, 697, 698,
			727, 729, 729, 729, 730,
			759, 761, 761, 761, 762,
			791, 792, 793, 793, 794
		}, {
			3, 3, 3, 3, 3,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0
		}),//  106
	new Prefab("Big house", jgl::Vector2Int(3, 13), jgl::Vector2Int(5, 5), {
			667, 669, 669, 669, 670,
			699, 701, 701, 701, 702,
			731, 733, 733, 733, 734,
			763, 765, 765, 765, 766,
			795, 796, 797, 797, 798
		}, {
			3, 3, 3, 3, 3,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0
		}),//  107
	new Prefab("Unknow", jgl::Vector2Int(4, 13), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  108
	new Prefab("Unknow", jgl::Vector2Int(5, 13), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  109
	new Prefab("Unknow", jgl::Vector2Int(6, 13), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  110
	new Prefab("Unknow", jgl::Vector2Int(7, 13), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  111
	new Prefab("Unknow", jgl::Vector2Int(0, 14), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  112
	new Prefab("Unknow", jgl::Vector2Int(1, 14), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  113
	new Prefab("Unknow", jgl::Vector2Int(2, 14), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  114
	new Prefab("Unknow", jgl::Vector2Int(3, 14), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  115
	new Prefab("Unknow", jgl::Vector2Int(4, 14), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  116
	new Prefab("Unknow", jgl::Vector2Int(5, 14), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  117
	new Prefab("Unknow", jgl::Vector2Int(6, 14), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  118
	new Prefab("Unknow", jgl::Vector2Int(7, 14), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  119
	new Prefab("Unknow", jgl::Vector2Int(0, 15), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  120
	new Prefab("Unknow", jgl::Vector2Int(1, 15), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  121
	new Prefab("Unknow", jgl::Vector2Int(2, 15), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  122
	new Prefab("Unknow", jgl::Vector2Int(3, 15), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  123
	new Prefab("Unknow", jgl::Vector2Int(4, 15), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  124
	new Prefab("Unknow", jgl::Vector2Int(5, 15), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  125
	new Prefab("Unknow", jgl::Vector2Int(6, 15), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  126
	new Prefab("Unknow", jgl::Vector2Int(7, 15), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  127
	new Prefab("Unknow", jgl::Vector2Int(0, 16), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  128
	new Prefab("Unknow", jgl::Vector2Int(1, 16), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  129
	new Prefab("Unknow", jgl::Vector2Int(2, 16), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  130
	new Prefab("Unknow", jgl::Vector2Int(3, 16), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  131
	new Prefab("Unknow", jgl::Vector2Int(4, 16), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  132
	new Prefab("Unknow", jgl::Vector2Int(5, 16), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  133
	new Prefab("Unknow", jgl::Vector2Int(6, 16), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  134
	new Prefab("Unknow", jgl::Vector2Int(7, 16), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  135
	new Prefab("Unknow", jgl::Vector2Int(0, 17), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  136
	new Prefab("Unknow", jgl::Vector2Int(1, 17), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  137
	new Prefab("Unknow", jgl::Vector2Int(2, 17), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  138
	new Prefab("Unknow", jgl::Vector2Int(3, 17), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  139
	new Prefab("Unknow", jgl::Vector2Int(4, 17), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  140
	new Prefab("Unknow", jgl::Vector2Int(5, 17), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  141
	new Prefab("Unknow", jgl::Vector2Int(6, 17), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  142
	new Prefab("Unknow", jgl::Vector2Int(7, 17), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  143
	new Prefab("Unknow", jgl::Vector2Int(0, 18), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  144
	new Prefab("Unknow", jgl::Vector2Int(1, 18), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  145
	new Prefab("Unknow", jgl::Vector2Int(2, 18), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  146
	new Prefab("Unknow", jgl::Vector2Int(3, 18), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  147
	new Prefab("Unknow", jgl::Vector2Int(4, 18), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  148
	new Prefab("Unknow", jgl::Vector2Int(5, 18), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  149
	new Prefab("Unknow", jgl::Vector2Int(6, 18), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  150
	new Prefab("Unknow", jgl::Vector2Int(7, 18), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  151
	new Prefab("Unknow", jgl::Vector2Int(0, 19), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  152
	new Prefab("Unknow", jgl::Vector2Int(1, 19), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  153
	new Prefab("Unknow", jgl::Vector2Int(2, 19), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  154
	new Prefab("Unknow", jgl::Vector2Int(3, 19), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  155
	new Prefab("Unknow", jgl::Vector2Int(4, 19), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  156
	new Prefab("Unknow", jgl::Vector2Int(5, 19), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  157
	new Prefab("Unknow", jgl::Vector2Int(6, 19), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  158
	new Prefab("Unknow", jgl::Vector2Int(7, 19), jgl::Vector2Int(0, 0), {
			
		}, {0}),//  159
	new Prefab("Unknow", jgl::Vector2Int(0, 20), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  160
	new Prefab("Unknow", jgl::Vector2Int(1, 20), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  161
	new Prefab("Unknow", jgl::Vector2Int(2, 20), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  162
	new Prefab("Unknow", jgl::Vector2Int(3, 20), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  163
	new Prefab("Unknow", jgl::Vector2Int(4, 20), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  164
	new Prefab("Unknow", jgl::Vector2Int(5, 20), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  165
	new Prefab("Unknow", jgl::Vector2Int(6, 20), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  166
	new Prefab("Unknow", jgl::Vector2Int(7, 20), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  167
	new Prefab("Unknow", jgl::Vector2Int(0, 21), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  168
	new Prefab("Unknow", jgl::Vector2Int(1, 21), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  169
	new Prefab("Unknow", jgl::Vector2Int(2, 21), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  170
	new Prefab("Unknow", jgl::Vector2Int(3, 21), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  171
	new Prefab("Unknow", jgl::Vector2Int(4, 21), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  172
	new Prefab("Unknow", jgl::Vector2Int(5, 21), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  173
	new Prefab("Unknow", jgl::Vector2Int(6, 21), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  174
	new Prefab("Unknow", jgl::Vector2Int(7, 21), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  175
	new Prefab("Unknow", jgl::Vector2Int(0, 22), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  176
	new Prefab("Unknow", jgl::Vector2Int(1, 22), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  177
	new Prefab("Unknow", jgl::Vector2Int(2, 22), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  178
	new Prefab("Unknow", jgl::Vector2Int(3, 22), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  179
	new Prefab("Unknow", jgl::Vector2Int(4, 22), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  180
	new Prefab("Unknow", jgl::Vector2Int(5, 22), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  181
	new Prefab("Unknow", jgl::Vector2Int(6, 22), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  182
	new Prefab("Unknow", jgl::Vector2Int(7, 22), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  183
	new Prefab("Unknow", jgl::Vector2Int(0, 23), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  184
	new Prefab("Unknow", jgl::Vector2Int(1, 23), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  185
	new Prefab("Unknow", jgl::Vector2Int(2, 23), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  186
	new Prefab("Unknow", jgl::Vector2Int(3, 23), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  187
	new Prefab("Unknow", jgl::Vector2Int(4, 23), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  188
	new Prefab("Unknow", jgl::Vector2Int(5, 23), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  189
	new Prefab("Unknow", jgl::Vector2Int(6, 23), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  190
	new Prefab("Unknow", jgl::Vector2Int(7, 23), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  191
	new Prefab("Unknow", jgl::Vector2Int(0, 24), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  192
	new Prefab("Unknow", jgl::Vector2Int(1, 24), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  193
	new Prefab("Unknow", jgl::Vector2Int(2, 24), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  194
	new Prefab("Unknow", jgl::Vector2Int(3, 24), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  195
	new Prefab("Unknow", jgl::Vector2Int(4, 24), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  196
	new Prefab("Unknow", jgl::Vector2Int(5, 24), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  197
	new Prefab("Unknow", jgl::Vector2Int(6, 24), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  198
	new Prefab("Unknow", jgl::Vector2Int(7, 24), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  199
	new Prefab("Unknow", jgl::Vector2Int(0, 25), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  200
	new Prefab("Unknow", jgl::Vector2Int(1, 25), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  201
	new Prefab("Unknow", jgl::Vector2Int(2, 25), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  202
	new Prefab("Unknow", jgl::Vector2Int(3, 25), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  203
	new Prefab("Unknow", jgl::Vector2Int(4, 25), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  204
	new Prefab("Unknow", jgl::Vector2Int(5, 25), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  205
	new Prefab("Unknow", jgl::Vector2Int(6, 25), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  206
	new Prefab("Unknow", jgl::Vector2Int(7, 25), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  207
	new Prefab("Unknow", jgl::Vector2Int(0, 26), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  208
	new Prefab("Unknow", jgl::Vector2Int(1, 26), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  209
	new Prefab("Unknow", jgl::Vector2Int(2, 26), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  210
	new Prefab("Unknow", jgl::Vector2Int(3, 26), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  211
	new Prefab("Unknow", jgl::Vector2Int(4, 26), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  212
	new Prefab("Unknow", jgl::Vector2Int(5, 26), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  213
	new Prefab("Unknow", jgl::Vector2Int(6, 26), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  214
	new Prefab("Unknow", jgl::Vector2Int(7, 26), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  215
	new Prefab("Unknow", jgl::Vector2Int(0, 27), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  216
	new Prefab("Unknow", jgl::Vector2Int(1, 27), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  217
	new Prefab("Unknow", jgl::Vector2Int(2, 27), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  218
	new Prefab("Unknow", jgl::Vector2Int(3, 27), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  219
	new Prefab("Unknow", jgl::Vector2Int(4, 27), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  220
	new Prefab("Unknow", jgl::Vector2Int(5, 27), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  221
	new Prefab("Unknow", jgl::Vector2Int(6, 27), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  222
	new Prefab("Unknow", jgl::Vector2Int(7, 27), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  223
	new Prefab("Unknow", jgl::Vector2Int(0, 28), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  224
	new Prefab("Unknow", jgl::Vector2Int(1, 28), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  225
	new Prefab("Unknow", jgl::Vector2Int(2, 28), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  226
	new Prefab("Unknow", jgl::Vector2Int(3, 28), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  227
	new Prefab("Unknow", jgl::Vector2Int(4, 28), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  228
	new Prefab("Unknow", jgl::Vector2Int(5, 28), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  229
	new Prefab("Unknow", jgl::Vector2Int(6, 28), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  230
	new Prefab("Unknow", jgl::Vector2Int(7, 28), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  231
	new Prefab("Unknow", jgl::Vector2Int(0, 29), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  232
	new Prefab("Unknow", jgl::Vector2Int(1, 29), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  233
	new Prefab("Unknow", jgl::Vector2Int(2, 29), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  234
	new Prefab("Unknow", jgl::Vector2Int(3, 29), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  235
	new Prefab("Unknow", jgl::Vector2Int(4, 29), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  236
	new Prefab("Unknow", jgl::Vector2Int(5, 29), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  237
	new Prefab("Unknow", jgl::Vector2Int(6, 29), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  238
	new Prefab("Unknow", jgl::Vector2Int(7, 29), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  239
	new Prefab("Unknow", jgl::Vector2Int(0, 30), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  240
	new Prefab("Unknow", jgl::Vector2Int(1, 30), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  241
	new Prefab("Unknow", jgl::Vector2Int(2, 30), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  242
	new Prefab("Unknow", jgl::Vector2Int(3, 30), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  243
	new Prefab("Unknow", jgl::Vector2Int(4, 30), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  244
	new Prefab("Unknow", jgl::Vector2Int(5, 30), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  245
	new Prefab("Unknow", jgl::Vector2Int(6, 30), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  246
	new Prefab("Unknow", jgl::Vector2Int(7, 30), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  247
	new Prefab("Unknow", jgl::Vector2Int(0, 31), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  248
	new Prefab("Unknow", jgl::Vector2Int(1, 31), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  249
	new Prefab("Unknow", jgl::Vector2Int(2, 31), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  250
	new Prefab("Unknow", jgl::Vector2Int(3, 31), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  251
	new Prefab("Unknow", jgl::Vector2Int(4, 31), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  252
	new Prefab("Unknow", jgl::Vector2Int(5, 31), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  253
	new Prefab("Unknow", jgl::Vector2Int(6, 31), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  254
	new Prefab("Unknow", jgl::Vector2Int(7, 31), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  255
	new Prefab("Unknow", jgl::Vector2Int(0, 32), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  256
	new Prefab("Unknow", jgl::Vector2Int(1, 32), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  257
	new Prefab("Unknow", jgl::Vector2Int(2, 32), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  258
	new Prefab("Unknow", jgl::Vector2Int(3, 32), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  259
	new Prefab("Unknow", jgl::Vector2Int(4, 32), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  260
	new Prefab("Unknow", jgl::Vector2Int(5, 32), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  261
	new Prefab("Unknow", jgl::Vector2Int(6, 32), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  262
	new Prefab("Unknow", jgl::Vector2Int(7, 32), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  263
	new Prefab("Unknow", jgl::Vector2Int(0, 33), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  264
	new Prefab("Unknow", jgl::Vector2Int(1, 33), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  265
	new Prefab("Unknow", jgl::Vector2Int(2, 33), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  266
	new Prefab("Unknow", jgl::Vector2Int(3, 33), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  267
	new Prefab("Unknow", jgl::Vector2Int(4, 33), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  268
	new Prefab("Unknow", jgl::Vector2Int(5, 33), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  269
	new Prefab("Unknow", jgl::Vector2Int(6, 33), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  270
	new Prefab("Unknow", jgl::Vector2Int(7, 33), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  271
	new Prefab("Unknow", jgl::Vector2Int(0, 34), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  272
	new Prefab("Unknow", jgl::Vector2Int(1, 34), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  273
	new Prefab("Unknow", jgl::Vector2Int(2, 34), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  274
	new Prefab("Unknow", jgl::Vector2Int(3, 34), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  275
	new Prefab("Unknow", jgl::Vector2Int(4, 34), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  276
	new Prefab("Unknow", jgl::Vector2Int(5, 34), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  277
	new Prefab("Unknow", jgl::Vector2Int(6, 34), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  278
	new Prefab("Unknow", jgl::Vector2Int(7, 34), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  279
	new Prefab("Unknow", jgl::Vector2Int(0, 35), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  280
	new Prefab("Unknow", jgl::Vector2Int(1, 35), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  281
	new Prefab("Unknow", jgl::Vector2Int(2, 35), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  282
	new Prefab("Unknow", jgl::Vector2Int(3, 35), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  283
	new Prefab("Unknow", jgl::Vector2Int(4, 35), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  284
	new Prefab("Unknow", jgl::Vector2Int(5, 35), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  285
	new Prefab("Unknow", jgl::Vector2Int(6, 35), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  286
	new Prefab("Unknow", jgl::Vector2Int(7, 35), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  287
	new Prefab("Unknow", jgl::Vector2Int(0, 36), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  288
	new Prefab("Unknow", jgl::Vector2Int(1, 36), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  289
	new Prefab("Unknow", jgl::Vector2Int(2, 36), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  290
	new Prefab("Unknow", jgl::Vector2Int(3, 36), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  291
	new Prefab("Unknow", jgl::Vector2Int(4, 36), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  292
	new Prefab("Unknow", jgl::Vector2Int(5, 36), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  293
	new Prefab("Unknow", jgl::Vector2Int(6, 36), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  294
	new Prefab("Unknow", jgl::Vector2Int(7, 36), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  295
	new Prefab("Unknow", jgl::Vector2Int(0, 37), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  296
	new Prefab("Unknow", jgl::Vector2Int(1, 37), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  297
	new Prefab("Unknow", jgl::Vector2Int(2, 37), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  298
	new Prefab("Unknow", jgl::Vector2Int(3, 37), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  299
	new Prefab("Unknow", jgl::Vector2Int(4, 37), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  300
	new Prefab("Unknow", jgl::Vector2Int(5, 37), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  301
	new Prefab("Unknow", jgl::Vector2Int(6, 37), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  302
	new Prefab("Unknow", jgl::Vector2Int(7, 37), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  303
	new Prefab("Unknow", jgl::Vector2Int(0, 38), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  304
	new Prefab("Unknow", jgl::Vector2Int(1, 38), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  305
	new Prefab("Unknow", jgl::Vector2Int(2, 38), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  306
	new Prefab("Unknow", jgl::Vector2Int(3, 38), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  307
	new Prefab("Unknow", jgl::Vector2Int(4, 38), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  308
	new Prefab("Unknow", jgl::Vector2Int(5, 38), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  309
	new Prefab("Unknow", jgl::Vector2Int(6, 38), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  310
	new Prefab("Unknow", jgl::Vector2Int(7, 38), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  311
	new Prefab("Unknow", jgl::Vector2Int(0, 39), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  312
	new Prefab("Unknow", jgl::Vector2Int(1, 39), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  313
	new Prefab("Unknow", jgl::Vector2Int(2, 39), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  314
	new Prefab("Unknow", jgl::Vector2Int(3, 39), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  315
	new Prefab("Unknow", jgl::Vector2Int(4, 39), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  316
	new Prefab("Unknow", jgl::Vector2Int(5, 39), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  317
	new Prefab("Unknow", jgl::Vector2Int(6, 39), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  318
	new Prefab("Unknow", jgl::Vector2Int(7, 39), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  319
	new Prefab("Unknow", jgl::Vector2Int(0, 40), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  320
	new Prefab("Unknow", jgl::Vector2Int(1, 40), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  321
	new Prefab("Unknow", jgl::Vector2Int(2, 40), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  322
	new Prefab("Unknow", jgl::Vector2Int(3, 40), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  323
	new Prefab("Unknow", jgl::Vector2Int(4, 40), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  324
	new Prefab("Unknow", jgl::Vector2Int(5, 40), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  325
	new Prefab("Unknow", jgl::Vector2Int(6, 40), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  326
	new Prefab("Unknow", jgl::Vector2Int(7, 40), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  327
	new Prefab("Unknow", jgl::Vector2Int(0, 41), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  328
	new Prefab("Unknow", jgl::Vector2Int(1, 41), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  329
	new Prefab("Unknow", jgl::Vector2Int(2, 41), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  330
	new Prefab("Unknow", jgl::Vector2Int(3, 41), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  331
	new Prefab("Unknow", jgl::Vector2Int(4, 41), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  332
	new Prefab("Unknow", jgl::Vector2Int(5, 41), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  333
	new Prefab("Unknow", jgl::Vector2Int(6, 41), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  334
	new Prefab("Unknow", jgl::Vector2Int(7, 41), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  335
	new Prefab("Unknow", jgl::Vector2Int(0, 42), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  336
	new Prefab("Unknow", jgl::Vector2Int(1, 42), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  337
	new Prefab("Unknow", jgl::Vector2Int(2, 42), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  338
	new Prefab("Unknow", jgl::Vector2Int(3, 42), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  339
	new Prefab("Unknow", jgl::Vector2Int(4, 42), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  340
	new Prefab("Unknow", jgl::Vector2Int(5, 42), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  341
	new Prefab("Unknow", jgl::Vector2Int(6, 42), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  342
	new Prefab("Unknow", jgl::Vector2Int(7, 42), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  343
	new Prefab("Unknow", jgl::Vector2Int(0, 43), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  344
	new Prefab("Unknow", jgl::Vector2Int(1, 43), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  345
	new Prefab("Unknow", jgl::Vector2Int(2, 43), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  346
	new Prefab("Unknow", jgl::Vector2Int(3, 43), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  347
	new Prefab("Unknow", jgl::Vector2Int(4, 43), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  348
	new Prefab("Unknow", jgl::Vector2Int(5, 43), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  349
	new Prefab("Unknow", jgl::Vector2Int(6, 43), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  350
	new Prefab("Unknow", jgl::Vector2Int(7, 43), jgl::Vector2Int(0, 0), {
			
		}, {
			
		}),//  351
};
