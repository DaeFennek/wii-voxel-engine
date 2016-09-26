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

#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

#include <map>
#include <vector>
#include "Block.h"
#include "../../renderer/BlockRenderer.h"
#include "../../textures/TextureHandler.h"
#include "../../utils/Vector3f.h"

#define BLOCK_SIZE .5f

#define BLOCK_TEXTURE_DIRT "BLOCK_TEXTURE_DIRT"
#define BLOCK_TEXTURE_GRASS "BLOCK_TEXTURE_GRASS"

enum BlockType {

	AIR,
	DIRT,
	GRASS
};

class CBlockManager {
public:
	CBlockManager( TextureHandler& ptextureHandler );
	virtual ~CBlockManager();
	void LoadBlocks();
	void UnloadBlocks();

	CBlock* GetBlockByType(const BlockType type);

private:

	std::map<BlockType, CBlock*> m_blocks;
	std::map<BlockType, std::vector<Vector3f*> > m_mBlockRenderList;
	TextureHandler* m_pTextureHandler;
	BlockRenderer* m_blockRenderer;

};

#endif /* _BLOCKMANAGER_H_ */