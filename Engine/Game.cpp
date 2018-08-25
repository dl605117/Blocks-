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
#include <math.h>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brdUI( brd,"Images\\text16x28.bmp" )
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
				if( e.GetCode() == 'Q' )
				{
					brd.PushColumn( 0 );
				}
				else if( e.GetCode() == 'W' )
				{
					brd.PushColumn( 1 );
				}
				else if( e.GetCode() == 'E' )
				{
					brd.PushColumn( 2 );
				}
				else if( e.GetCode() == 'R' )
				{
					//brd.PushColumn( 3 );
				}
				else if( e.GetCode() == 'T' )
				{
					//brd.PushColumn( 4 );
				}
			}
			else if ( e.GetCode() == VK_RETURN )
			{
				brd.InitBoard();
				gameOn = true;
			}
		}
	}
	if( gameOn )
	{
		brd.UpdateAnimation( dt );
		brd.UpdateTimer( dt );
	}
}

void Game::ComposeFrame()
{
	if( gameOn )
	{
		brd.Draw( gfx );
		if( brd.IsOver() )
		{
			gfx.DrawRect( RectI( 300,300,350,350 ),Colors::Gray );
		}
		brdUI.Draw( gfx );
	}
}