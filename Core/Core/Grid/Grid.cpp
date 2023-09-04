#include "Grid.h"



namespace OE1Core
{
	Grid::Grid()
	{
		glGenVertexArrays(1, &m_VAO);
		Update();
	}
	Grid::~Grid()
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	void Grid::Update()
	{
		Memory::InfiniteGrid grid;
		grid.ColorBold = m_ColorBold;
		grid.ColorLight = m_ColorLight;
		grid.Scale = m_Scale;
		Memory::UniformBlockManager::UseBuffer(Memory::UniformBufferID::INFIN_GRID)->Update(Memory::s_InfiniteGridBufferSize, 0, &grid);
	}
}