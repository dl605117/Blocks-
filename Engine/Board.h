#pragma once
#include <vector>
#include "Rect.h"
#include <cassert>
#include <random>
#include "Graphics.h"
#include "Block.h"
#include "Colors.h"
#include "FrameTimer.h"

class Board
{
public:
	enum class Column
	{
		Left,
		Middle,
		Right
	};
public:
	enum class Animations
	{
		NotAnimating,
		PushColumn,
		CollapseRow,
		EraseRow
	};
public:
	Board();
	void PushColumn( Column col );
	void SpawnBlock();
	void Draw( Graphics& gfx );
	bool IsOver() const;
	void UpdateAnimation( float dt );
	void UpdateBlocks();
	bool IsAnimating() const;
	void PushAnimation( float dt );
	void CollapseAnimation( float dt );
	void EraseAnimation( float dt );
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
	static constexpr int animationSpeed = 200;
	static constexpr float animationEraseTimer = 0.5f;
	std::vector<Block> field[nColumns];
	std::unique_ptr<Block> choiceBlock;
	Animations animation = Animations::NotAnimating;
	float currentDisplacement = 0.0f;
	Column currentColPush = Column::Left;
	std::vector<int> rowsToDelete;
};