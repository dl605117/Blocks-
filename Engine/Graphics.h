/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
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
#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Rect.h"
#include "Surface.h"
#include <cassert>

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	template<typename E>
	void DrawRect( const Rect<E>& rect,Color color )
	{
		for( int i = (int)rect.left; i < (int)rect.right; i++ )
		{
			for( int j = (int)rect.top; j < (int)rect.bottom; j++ )
			{
				PutPixel( i,j,color );
			}
		}
	}
	void DrawRect( const Vei2& topLeft,const Vei2& bottomRight,Color color = Colors::Magenta )
	{
		DrawRect( RectI( topLeft,bottomRight ),color );
	}
	void DrawRect( const Vei2& topLeft,int width,int height,Color color = Colors::Magenta )
	{
		DrawRect( topLeft,Vei2( topLeft.x + width,topLeft.y + height ),color );
	}
	template<typename E>
	void DrawSprite( int x,int y,const Surface& surf,E effect )
	{
		DrawSprite( x,y,surf,RectI( 0,0,surf.GetWidth(),surf.GetHeight() ),effect );
	}
	template<typename E>
	void DrawSprite( int x,int y,const Surface& surf,const RectI& srcRect,E effect )
	{
		assert( srcRect.left >= 0 );
		assert( srcRect.right <= surf.GetWidth() );
		assert( srcRect.top >= 0 );
		assert( srcRect.bottom <= surf.GetHeight() );

		for( int sy = srcRect.top; sy < srcRect.bottom; sy++ )
		{
			for( int sx = srcRect.left; sx < srcRect.right; sx++ )
			{
				effect( surf.GetPixel( sx,sy ),
					x + sx - srcRect.left,
					y + sy - srcRect.top,
					*this
				);
			}
		}
	}
	// DrawCircle:
	// Draws a portion of a circle from starting angle to end angle.
	// Goes counterclockwise and 0.0f begins from ( 1,0 ) in the 
	// coord system. Utilizes Radians
	template <typename E>
	void DrawCircle( const Vei2& pos,int radius,Color c,E effect )
	{
		Vei2 new_pos( pos );
		if ( typeid( E ) != typeid( CircleEffects::SectorFromCenter ) 
			&& typeid( E ) != typeid( CircleEffects::CircleFromCenter ) 
			&& typeid( E ) != typeid( CircleEffects::RingFromCenter ) 
			&& typeid( E ) != typeid( CircleEffects::RingSectorFromCenter ) )
		{
			new_pos = Vei2( pos + Vei2( radius,radius ) );
		}
		const int radiusSq = radius * radius;
		for( int dy = -radius; dy < radius; dy++ )
		{
			for( int dx = -radius; dx < radius; dx++ )
			{
				effect( new_pos,dx,dy,radiusSq,c,*this );
			}
		}
	}
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};