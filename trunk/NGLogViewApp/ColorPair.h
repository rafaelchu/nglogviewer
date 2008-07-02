#pragma once

typedef struct displayColors {
	COLORREF m_cTextColor;
	COLORREF m_cBkColor;

	displayColors()
	{
		m_cTextColor =0;
		m_cBkColor = 0x00FFFFFF;
	}

} COLORPAIR;