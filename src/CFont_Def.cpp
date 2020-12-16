#include "CFont.h"

namespace fontrgb
{
	const SDL_Color red      	= {237,	28,		36};
  const SDL_Color orange   	= {242,	101,	34};
  const SDL_Color yellow   	= {255, 242, 	0};
  const SDL_Color green    	= {57, 	181, 	74};
  const SDL_Color cyan     	= {0, 	174, 	239};
  const SDL_Color blue     	= {0, 	84, 	166};
  const SDL_Color indigo   	= {46, 	49, 	146};
  const SDL_Color violet   	= {102, 45, 	145};
  const SDL_Color gray     	= {155, 155, 	155};
	const SDL_Color black			= {0,		0,		0};
	const SDL_Color white			= {255,	255,	255};
}

SDL_Texture* Font::GetInfo(const int& fontID, int& h_spacing, int& v_spacing)
{
  SDL_Texture* retptr = GetFont(fontID);
	h_spacing = GetHSpacing(fontID);
	v_spacing = GetVSpacing(fontID);

	return retptr;
}

SDL_Texture* Font::GetFont(const int& fontID)
{
  SDL_Texture* font = NULL;
  switch (fontID)
  {
    case FONT_DEFAULT: 	font = FontControl.CS_Font; 		break;
    case FONT_MINI: 		font = FontControl.Mini_Font; 	break;
    default: break;
  }

  return font;
}

int Font::GetHSpacing(const int& fontID)
{
	int h_spacing = 0;
	if (fontID == FONT_DEFAULT)		h_spacing = 2;
	if (fontID == FONT_MINI)			h_spacing = 1;
	return h_spacing;
}

int Font::GetVSpacing(const int& fontID)
{
	int v_spacing = 0;
	if (fontID == FONT_DEFAULT)		v_spacing = 3;
	if (fontID == FONT_MINI)			v_spacing = 1;
	return v_spacing;
}

int Font::GetSymH(const int& fontID)
{
  int symH = 0;
  if (fontID == FONT_DEFAULT)   symH = 14;
  if (fontID == FONT_MINI)      symH = 5;
  return symH;
}

void Font::GetXY(const int& fontID, char symbol, SDL_Rect& symRec)
{
  GetXY(fontID, symbol, symRec.x, symRec.y, symRec.w, symRec.h);
}

// Special character request, which is triggered with a '$' preceding a code symbol
void Font::GetXY_spec(const int& fontID, char symbol, SDL_Rect& symRec)
{
	GetXY_spec(fontID, symbol, symRec.x, symRec.y, symRec.w, symRec.h);
}

// Takes in a queried symbol, passes X and Y coords
// where to find the queried symbol in a font texture
void Font::GetXY(const int& fontID, char symbol, int& X, int& Y, int& W, int& H)
{
  H = GetSymH(fontID);
	switch (fontID)
	{
		case FONT_DEFAULT:
		{
			switch (symbol)
			{
				case '0': X = 0;  Y = 0;   W = 14; break;
				case '1': X = 15; Y = 0;   W = 12; break;
				case '2': X = 28; Y = 0;   W = 14; break;
				case '3': X = 43; Y = 0;   W = 13; break;
				case '4': X = 0;  Y = 15;  W = 14; break;
				case '5': X = 15; Y = 15;  W = 14; break;
				case '6': X = 30; Y = 15;  W = 14; break;
				case '7': X = 45; Y = 15;  W = 14; break;
				case '8': X = 0;  Y = 30;  W = 14; break;
				case '9': X = 15; Y = 30;  W = 14; break;
				case 'a': X = 30; Y = 30;  W = 14; break;
				case 'b': X = 45; Y = 30;  W = 14; break;
				case 'c': X = 0;  Y = 45;  W = 14; break;
				case 'd': X = 15; Y = 45;  W = 14; break;
				case 'e': X = 30; Y = 45;  W = 12; break;
				case 'f': X = 43; Y = 45;  W = 12; break;
				case 'g': X = 0;  Y = 60;  W = 14; break;
				case 'h': X = 15; Y = 60;  W = 12; break;
				case 'i': X = 28; Y = 60;  W = 12; break;
				case 'j': X = 41; Y = 60;  W = 12; break;
				case 'k': X = 0;  Y = 75;  W = 13; break;
				case 'l': X = 14; Y = 75;  W = 12; break;
				case 'm': X = 27; Y = 75;  W = 14; break;
				case 'n': X = 42; Y = 75;  W = 14; break;
				case 'o': X = 0;  Y = 90;  W = 14; break;
				case 'p': X = 15; Y = 90;  W = 12; break;
				case 'q': X = 28; Y = 90;  W = 14; break;
				case 'r': X = 43; Y = 90;  W = 12; break;
				case 's': X = 0;  Y = 105; W = 14; break;
				case 't': X = 15; Y = 105; W = 12; break;
				case 'u': X = 28; Y = 105; W = 12; break;
				case 'v': X = 41; Y = 105; W = 14; break;
				case 'w': X = 0;  Y = 120; W = 14; break;
				case 'x': X = 15; Y = 120; W = 14; break;
				case 'y': X = 30; Y = 120; W = 14; break;
				case 'z': X = 45; Y = 120; W = 14; break;
				case 'A': X = 30; Y = 30;  W = 14; break;
				case 'B': X = 45; Y = 30;  W = 14; break;
				case 'C': X = 0;  Y = 45;  W = 14; break;
				case 'D': X = 15; Y = 45;  W = 14; break;
				case 'E': X = 30; Y = 45;  W = 12; break;
				case 'F': X = 43; Y = 45;  W = 12; break;
				case 'G': X = 0;  Y = 60;  W = 14; break;
				case 'H': X = 15; Y = 60;  W = 12; break;
				case 'I': X = 28; Y = 60;  W = 12; break;
				case 'J': X = 41; Y = 60;  W = 12; break;
				case 'K': X = 0;  Y = 75;  W = 13; break;
				case 'L': X = 14; Y = 75;  W = 12; break;
				case 'M': X = 27; Y = 75;  W = 14; break;
				case 'N': X = 42; Y = 75;  W = 14; break;
				case 'O': X = 0;  Y = 90;  W = 14; break;
				case 'P': X = 15; Y = 90;  W = 12; break;
				case 'Q': X = 28; Y = 90;  W = 14; break;
				case 'R': X = 43; Y = 90;  W = 12; break;
				case 'S': X = 0;  Y = 105; W = 14; break;
				case 'T': X = 15; Y = 105; W = 12; break;
				case 'U': X = 28; Y = 105; W = 12; break;
				case 'V': X = 41; Y = 105; W = 14; break;
				case 'W': X = 0;  Y = 120; W = 14; break;
				case 'X': X = 15; Y = 120; W = 14; break;
				case 'Y': X = 30; Y = 120; W = 14; break;
				case 'Z': X = 45; Y = 120; W = 14; break;
				case '.': X = 0;  Y = 135; W = 4;  break;
				case '-': X = 5;  Y = 135; W = 9;  break;
				case ' ': X = 53; Y = 60;  W = 6;  break;   // this one will probably have to change in the future
				default:  X = 0;  Y = 0;   W = 0;  H = 0;  break;
			}
			break;
		}
		case FONT_MINI:
		{
			// All symbols in minifont are the same width and on one line
			Y = 0; W = 5;
			switch (symbol)
			{
				case '0': X = 156;  break;
				case '1': X = 162; 	break;
				case '2': X = 168; 	break;
				case '3': X = 174; 	break;
				case '4': X = 180;  break;
				case '5': X = 186; 	break;
				case '6': X = 192; 	break;
				case '7': X = 198; 	break;
				case '8': X = 204;  break;
				case '9': X = 210; 	break;
				case 'a': X = 0; 		break;
				case 'b': X = 6; 		break;
				case 'c': X = 12;  	break;
				case 'd': X = 18; 	break;
				case 'e': X = 24; 	break;
				case 'f': X = 30; 	break;
				case 'g': X = 36;  	break;
				case 'h': X = 42; 	break;
				case 'i': X = 48; 	break;
				case 'j': X = 54; 	break;
				case 'k': X = 60;  	break;
				case 'l': X = 66; 	break;
				case 'm': X = 72; 	break;
				case 'n': X = 78; 	break;
				case 'o': X = 84;  	break;
				case 'p': X = 90; 	break;
				case 'q': X = 96; 	break;
				case 'r': X = 102; 	break;
				case 's': X = 108;  break;
				case 't': X = 114; 	break;
				case 'u': X = 120; 	break;
				case 'v': X = 126; 	break;
				case 'w': X = 132;  break;
				case 'x': X = 138; 	break;
				case 'y': X = 144; 	break;
				case 'z': X = 150; 	break;
				case 'A': X = 0; 		break;
				case 'B': X = 6; 		break;
				case 'C': X = 12;  	break;
				case 'D': X = 18; 	break;
				case 'E': X = 24; 	break;
				case 'F': X = 30; 	break;
				case 'G': X = 36;  	break;
				case 'H': X = 42; 	break;
				case 'I': X = 48; 	break;
				case 'J': X = 54; 	break;
				case 'K': X = 60; 	break;
				case 'L': X = 66; 	break;
				case 'M': X = 72; 	break;
				case 'N': X = 78; 	break;
				case 'O': X = 84;  	break;
				case 'P': X = 90; 	break;
				case 'Q': X = 96; 	break;
				case 'R': X = 102; 	break;
				case 'S': X = 108;  break;
				case 'T': X = 114; 	break;
				case 'U': X = 120; 	break;
				case 'V': X = 126; 	break;
				case 'W': X = 132; 	break;
				case 'X': X = 138; 	break;
				case 'Y': X = 144; 	break;
				case 'Z': X = 150; 	break;
				case '.': X = 216; 	break;
				case '?': X = 222; 	break;
				case '!': X = 228; 	break;
				// case '...': X = 234; break;
				case '_': X = 240; 	break;
				case '-': X = 246; 	break;
				// case '!!!': X = 252; break;
				case ' ': X = 258; 	break;
				case '+': X = 264;	break;
				default:  X = 0; W = 0; H = 0; break;
			}
			break;
		}
		default: X = 0; Y = 0; W = 0; H = 0; break;
	}
}

void Font::GetXY_spec(const int& fontID, char symbol, int& X, int& Y, int& W, int& H)
{
  H = GetSymH(fontID);
	switch (fontID)
	{
		case FONT_DEFAULT:
		{
			switch (symbol)
			{
				case 'C': X = 15; Y = 135; W = 15; H = 14; break;
				default:  X = 0;  Y = 0;   W = 0;  H = 0;  break;
			}
			break;
		}
		case FONT_MINI:
		{
			// All symbols in minifont are the same width and on one line
			Y = 0; W = 5;
			switch (symbol)
			{
				case 'U': X = 270; break;	// Up arrow
				case 'D': X = 276; break;	// Down arrow
				case 'L': X = 282; break;	// Left arrow
				case 'R': X = 288; break;	// Right arrow
				case 'C': X = 294; break; // Fill (cursor)
				default:  X = 0; W = 0; H = 0; break;
			}
			break;
		}
		default: X = 0; Y = 0; W = 0; H = 0; break;
	}
}
