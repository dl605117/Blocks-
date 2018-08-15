/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	tester( "Images\\text.bmp" )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	while( !wnd.kbd.KeyIsEmpty() && !brd.IsOver() && !brd.IsAnimating() )
	{
		const auto e = wnd.kbd.ReadKey();
		if( e.IsRelease() )
		{
			if( gameOn )
			{
				if( e.GetCode() == VK_LEFT )
				{
					brd.PushColumn( Board::Column::Left );
				}
				else if( e.GetCode() == VK_UP )
				{
					brd.PushColumn( Board::Column::Middle );
				}
				else if( e.GetCode() == VK_RIGHT )
				{
					brd.PushColumn( Board::Column::Right );
				}
			}
			else if ( e.GetCode() == VK_RETURN )
			{
				brd.SpawnBlock();
				gameOn = true;
			}
		}
	}
	brd.UpdateAnimation( dt );
}

void Game::ComposeFrame()
{
	brd.Draw( gfx );
	if( brd.IsOver() )
	{
		gfx.DrawRect( RectI( 100,100,200,200 ),Colors::Magenta );
	}
	gfx.DrawSurface( 100,100,tester );
}