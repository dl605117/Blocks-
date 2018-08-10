#pragma once
#include <vector>
#include "Rect.h"
#include <cassert>
#include <random>
#include "Graphics.h"
#include "Block.h"
#include "Colors.h"

class Board
{
public:
	enum Column
	{
		Left,
		Middle,
		Right
	};
public:
	Board();
	void PushColumn( Column col );
	void SpawnBlock();
	void Draw( Graphics& gfx );
	bool IsOver() const;
	void UpdateCollapse();
private:
	std::mt19937 rng;
	static constexpr Color blockColors[3] = {
		Colors::Red,
		Colors::Green,
		Colors::Blue
	};
	static constexpr int maxRows = 7;
	static constexpr int nColumns = 3;
	static constexpr int blockWidth = 70;
	static constexpr int blockHeight = 30;
	std::vector<Block> field[nColumns];
	std::unique_ptr<Block> choiceBlock;
};