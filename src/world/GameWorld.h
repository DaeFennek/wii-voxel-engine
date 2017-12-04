/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <map>
#include "blocks/BlockManager.h"
#include "chunk/Chunk.h"
#include "PerlinNoise.h"
#include "../renderer/BlockRenderer.h"
#include "../scenes/Basic3DScene.h"
#include "../utils/MathHelper.h"
#include "chunk/chunkloader.h"

#define CHUNK_AMOUNT_X 7
#define CHUNK_AMOUNT_Z 7

#define CHUNK_PLAYER_FOV 7 // how many chunks the player can see

struct ChunkPositionComparer
{
    bool operator()(const Vector3& s1, const Vector3& s2) const
	{
        return s1.GetX() < s2.GetX() || (s1.GetX() == s2.GetX() && s1.GetZ() < s2.GetZ());
	}
};

class GameWorld {
public:
    GameWorld();
	virtual ~GameWorld();
	void GenerateWorld();
	void Draw();

	class BlockManager& GetBlockManager();
	class Chunk* GetChunkAt(const Vector3& centerPosition) const;
    class Chunk* GetCashedChunkByWorldPosition(const Vector3& worldPosition);
	void RemoveBlockByWorldPosition(const Vector3& blockPosition);
	void AddBlockAtWorldPosition(const Vector3& blockPosition, BlockType type);
	void UpdateFocusedBlockByWorldPosition( const Vector3& blockPosition );
	BlockType GetBlockByWorldPosition(const Vector3& worldPosition);
	Vector3 GetBlockPositionByWorldPosition(const Vector3& worldPosition);
	Vector3 GetNewPlayerPosition( const Vector3& playerWorldPosition );   

	const PerlinNoise& GetNoise() const;    

private:
    bool ChunkInFov( const Vector3& chunkPosition, const Vector3& playerPosition, uint32_t fov);
	void DrawFocusOnSelectedCube();

private:	
    std::map<const Vector3, class Chunk*, ChunkPositionComparer> m_chachedChunkMap;

    class ChunkLoader* m_chunkLoader;

	Vector3 m_SelectedBlockPosition;
    bool m_bHasSelectedBlock            = false;

    BlockManager* m_blockManager        = nullptr;
    PerlinNoise* m_pNoise               = nullptr;

};

#endif /* _GAMEWORLD_H_ */
