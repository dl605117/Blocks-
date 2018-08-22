#pragma once
#include <vector>
#include "Rect.h"
#include <cassert>
#include <random>
#include "Graphics.h"
#include "Block.h"
#include "Colors.h"
#include "FrameTimer.h"
#include "Surface.h"

class Board
{
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
	Board( const Board& brd );
	~Board();
	Board& operator=( const Board brd );
	void InitBoard();
	void PushColumn( int col );
	void SpawnBlock();
	void Draw( Graphics& gfx ) const;
	bool IsOver() const;
	void UpdateAnimation( float dt );
	void UpdateTimer( float dt );
	void UpdateBlocks();
	bool IsAnimating() const;
	int GetScore() const;
	float GetTimer() const;
private:
	void PushAnimation( float dt );
	void CollapseAnimation( float dt );
	void EraseAnimation( float dt );
public:
	static constexpr float maxTimer = 3.0f;
private:
	std::mt19937 rng;
	static constexpr Color blockColors[3] = {
		Colors::Red,
		Colors::Green,
		Colors::Blue
	};
	static constexpr int maxRows = 7;
	static constexpr int nColumns = 5;
	static constexpr int blockWidth = 70;
	static constexpr int blockHeight = 30;
	static constexpr int animationSpeed = 600;
	static constexpr float animationEraseTimer = 0.5f;
	std::vector<Block> field[nColumns];
	std::unique_ptr<Block> choiceBlock;
	std::unique_ptr<Block> viewBlock;
	Animations animation = Animations::NotAnimating;
	float currentDisplacement = 0.0f;
	int currentColPush;
	std::vector<int> rowsToDelete;
	int score = 0;
	int* pPointSystem = new int[5]{
		1,
		20,
		70,
		100,
		300
	};
	float timer = 0.0f;
};