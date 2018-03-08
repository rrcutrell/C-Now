//------------------------------------------------------------------------------
//
// File Name:	Mapping.c
// Author(s):	Robb Cutrell (r.cutrell)
// Project:		MyGame
// Course:		GAM150S18
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Trace.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Animation.h"
#include "EnemyManager.h"
#include "Mapping.h"
#include "RandomNumGen.h"

#define SCROLL_SPEED 600
#define SCREEN_SIZE (683 * 2)
#define MAX_TILES 4
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
char* tilePaths[MAX_TILES] =
{
	"Assets\\Background_01.png",
	"Assets\\Background_02.png",
	"Assets\\Background_03.png",
	"Assets\\Background_04.png",

};

typedef struct MapTile
{
	SpritePtr spritePtrLevel;
	SpriteSourcePtr spriteSourceLevel;
	AEGfxTexture *textureLevel;
	AEVec2 tileDisplacement;

}MapTile;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
// Level sprite variables
static AEGfxVertexList *meshLevel;
static MapTile mapTiles[MAX_TILES];


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
void TileTextureLoad(void);
void TileSpriteLoad(void);
void TileShutdown(void);
void TileUnload(void);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void MapLoad(void)
{
	//set the mesh for the level
	meshLevel = MeshCreateQuad(683, 384, 1.0, 1.0, "level");

	//set the texture for the level
	TileTextureLoad();

	//play background music

}

void MapInit(void)
{
	/**************************************************************

	Level sprite assignments

	**************************************************************/
	TileSpriteLoad();
}

void MapUpdate(f32 dt)
{
	int i;
	//draw level sprite at (0, 0)

	for (i = 0; i < MAX_TILES; i++)
	{
		mapTiles[i].tileDisplacement.x -= dt * SCROLL_SPEED;

		//check to see if background has moved off screen and reset it's position
		if (mapTiles[i].tileDisplacement.x <= -SCREEN_SIZE)
		{
			int levelNumCols = 1;
			int levelNumRows = 1;

			//assign the maptile a random new map texture
			mapTiles[i].tileDisplacement.x += SCREEN_SIZE * (MAX_TILES - 1);
			mapTiles[i].textureLevel = AEGfxTextureLoad(tilePaths[RandomNumber(MAX_TILES)]);
			mapTiles[i].spriteSourceLevel = SpriteSourceCreate(levelNumCols, levelNumRows, mapTiles[i].textureLevel);
			SpriteSetSpriteSource(mapTiles[i].spritePtrLevel, mapTiles[i].spriteSourceLevel);
		}

		//draw the map tiles
		SpriteDraw(mapTiles[i].spritePtrLevel, mapTiles[i].tileDisplacement);
	}


}

void MapShutdown(void)
{
	TileShutdown();
}

void MapUnload(void)
{
	TileUnload();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
void TileTextureLoad(void)
{
	int i;

	for (i = 0; i < MAX_TILES; i++)
	{
		mapTiles[i].textureLevel = AEGfxTextureLoad(tilePaths[i]);
		mapTiles[i].tileDisplacement.x = (f32)SCREEN_SIZE * i;
		mapTiles[i].tileDisplacement.y = 0;
	}
}

void TileSpriteLoad(void)
{
	//Only 1 image on sprite sheet for level
	int levelNumCols = 1;
	int levelNumRows = 1;
	int i;

	for (i = 0; i < MAX_TILES; i++)
	{
		//create spriteSource for level
		mapTiles[i].spriteSourceLevel = SpriteSourceCreate(levelNumCols, levelNumRows, mapTiles[i].textureLevel);

		//create sprite for level
		mapTiles[i].spritePtrLevel = SpriteCreate("Level Sprite tile");

		//Set sprite's mesh  for level
		SpriteSetMesh(mapTiles[i].spritePtrLevel, meshLevel);

		//set sprite's spritesource for level
		SpriteSetSpriteSource(mapTiles[i].spritePtrLevel, mapTiles[i].spriteSourceLevel);
	}
}

void TileShutdown(void)
{
	int i;
	//free memory of sprite of level
	for (i = 0; i < MAX_TILES; i++)
	{
		SpriteFree(&(mapTiles[i].spritePtrLevel));
		SpriteSourceFree(&(mapTiles[i].spriteSourceLevel));
	}

}

void TileUnload(void)
{
	int i;
	//free data associated to level
	for (i = 0; i < MAX_TILES; i++)
	{
		AEGfxTextureUnload(mapTiles[i].textureLevel);
	}

	AEGfxMeshFree(meshLevel);
}

