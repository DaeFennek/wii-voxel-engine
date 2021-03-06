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

#pragma once

#include <stdint.h>
#include <string>
#include "ChunkData.h"
#include "world/GameWorld.h"
#include "renderer/BlockRenderHelper.h"
#include "renderer/displaylist.h"
#include "utils/Vector3.h"
#include "utils/Mutex.h"

class Chunk {
public:

	Chunk(class GameWorld& gameWorld);
	Chunk(const Chunk&) = delete;
	Chunk(Chunk&&) = delete;
	void operator=(const Chunk&) = delete;
	void operator=(Chunk&&) = delete;
	virtual ~Chunk();

	void Init();
	void Clear();
	void RebuildDisplayList();
	void Render();

	void SetToAir();

	inline bool IsDirty() const { return m_bIsDirty; }
	inline void SetDirty(bool value) { m_bIsDirty = value; }

	uint32_t GetDisplayListSize() const;
	uint64_t GetAmountOfBlocks() const;
	uint64_t GetAmountOfFaces() const;

	void DeleteDisplayList();

	const Vec2i& GetPosition() const;

	void SetChunkNeighbors();
	bool NeighborsLoaded();

	void RemoveBlockByWorldPosition(const Vector3& blockPosition);
	void AddBlockByWorldPosition(const Vector3& blockPosition, BlockType type);
	Vector3 GetBlockPositionByWorldPosition(const Vector3& worldPosition) const;
	BlockType GetBlockTypeByWorldPosition(const Vector3& worldPosition) const;

	BlockType*** GetBlocks() const
	{
		return m_blocks;
	}

	static std::string GetFilePath(const Vec2i& position);

	void SetPosition(const Vec2i& position);

	void SetLoaded(bool value);

	bool IsLoaded();

	bool HasDisplayList() const;

private:
	void CreateDisplayList(size_t sizeOfDisplayList);
	void FinishDisplayList();
	void AddBlockToRenderList(BlockType type, const BlockRenderVO& blockRenderVO);
	void RemoveBlock(const Vector3& position);
	void ClearBlockRenderList();
	void BuildBlockRenderList();
	bool IsBlockVisible(uint32_t iX, uint32_t iY, uint32_t iZ, BlockRenderVO& blockRenderVO);
	Vec3i GetLocalBlockPositionByWorldPosition(const Vector3& blockWorldPosition) const;
	Vector3 LocalPositionToGlobalPosition(const Vec3i& localPosition) const;

	void BlockListUpdated(const BlockChangeData& data);

private:
	Mutex m_mutex;

	bool m_bLoadingDone = false;
	bool m_bIsDirty = false;
	bool m_bNeighbourUpdate = false;
	DisplayList m_displayList;

	uint32_t m_amountOfBlocks = 0;
	uint32_t m_amountOfFaces = 0;

	Vec2i m_Position;

	BlockType*** m_blocks;
	std::map<BlockType, std::vector<BlockRenderVO> > m_mBlockRenderList;
	class GameWorld* m_pWorldManager;

	Chunk* m_pChunkLeft = nullptr;
	Chunk* m_pChunkRight = nullptr;
	Chunk* m_pChunkFront = nullptr;
	Chunk* m_pChunkBack = nullptr;
};
