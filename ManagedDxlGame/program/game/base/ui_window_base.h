#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// メッセージウィンドウを表示するクラスのベース
class WindowUIBase {
public:
	virtual ~WindowUIBase() {};

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

protected:
	const int STR_TOP_HEIGHT_SPACE = 30;		// コマンドテキストの一番上の高さの間隔
	const int STR_HEIGHT_SPACE = 40;			// コマンドテキストの上下の文字の間隔
	const int STR_WIDTH_SPACE = 50;				// コマンドテキストの横の間隔
	const int STR_FONT_SIZE = 25;				// コマンドテキストのフォントサイズ

	int window_gpc_hdl_;						// コマンドウィンドウの画像
	int window_gpc_hdl_width_;					// コマンドウィンドウの幅
	int window_gpc_hdl_height_;					// コマンドウィンドウの高さ

	tnl::Vector3 window_pos_;					// コマンドウィンドウの画像位置

};