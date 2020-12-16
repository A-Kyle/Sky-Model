#ifndef _C_ASSET_H_
#define _C_ASSET_H_

#include <string>
#include "CSurface.h"
#include "Define.h"

namespace palette
{
  extern const SDL_Point white      ;
  extern const SDL_Point silver     ;
  extern const SDL_Point light_gray ;
  extern const SDL_Point gray       ;
  extern const SDL_Point dark_gray  ;
  extern const SDL_Point black      ;

  extern const SDL_Point red      ;
  extern const SDL_Point orange   ;
  extern const SDL_Point yellow   ;
  extern const SDL_Point green    ;
  extern const SDL_Point cyan     ;
  extern const SDL_Point blue     ;
  extern const SDL_Point indigo   ;
  extern const SDL_Point violet   ;
  extern const SDL_Point magenta  ;

  extern const SDL_Point light_red     ;
  extern const SDL_Point light_orange  ;
  extern const SDL_Point light_yellow  ;
  extern const SDL_Point light_green   ;
  extern const SDL_Point light_cyan    ;
  extern const SDL_Point light_blue    ;
  extern const SDL_Point light_indigo  ;
  extern const SDL_Point light_violet  ;
  extern const SDL_Point light_magenta ;

  extern const SDL_Point dark_red      ;
  extern const SDL_Point dark_orange   ;
  extern const SDL_Point dark_yellow   ;
  extern const SDL_Point dark_green    ;
  extern const SDL_Point dark_cyan     ;
  extern const SDL_Point dark_blue     ;
  extern const SDL_Point dark_indigo   ;
  extern const SDL_Point dark_violet   ;
  extern const SDL_Point dark_magenta  ;
}

namespace rgb
{
  extern const SDL_Color white;
  // extern const SDL_Color silver;
  // extern const SDL_Color light_gray;
  extern const SDL_Color gray;
  // extern const SDL_Color dark_gray;
  extern const SDL_Color black;

  extern const SDL_Color red;
  extern const SDL_Color orange;
  extern const SDL_Color yellow;
  extern const SDL_Color green;
  extern const SDL_Color cyan;
  extern const SDL_Color blue;
  extern const SDL_Color indigo;
  extern const SDL_Color violet;
  extern const SDL_Color magenta;

  extern const SDL_Color light_red;
  extern const SDL_Color light_orange;
  extern const SDL_Color light_yellow;
  extern const SDL_Color light_green;
  extern const SDL_Color light_cyan;
  extern const SDL_Color light_blue;
  extern const SDL_Color light_indigo;
  extern const SDL_Color light_violet;
  extern const SDL_Color light_magenta;

  extern const SDL_Color dark_red;
  extern const SDL_Color dark_orange;
  extern const SDL_Color dark_yellow;
  extern const SDL_Color dark_green;
  extern const SDL_Color dark_cyan;
  extern const SDL_Color dark_blue;
  extern const SDL_Color dark_indigo;
  extern const SDL_Color dark_violet;
  extern const SDL_Color dark_magenta;
}

class CAsset
{
	public:
		CAsset();
		static bool OnInit();         // Initialization function
		static void OnCleanup();      // Termination function

	private:
		static SDL_Texture* paltex;     // color palette
		static SDL_Texture* arrtex;     // arrows texture
    static SDL_Texture* boxtex;     // 1x1 px white square

  public:
    static void paletteAlpha(const short& a);

  public:
    static bool inWorkspace(const SDL_Point* pos);
    static bool inWorkspace(const int& x, const int& y);
    static bool compRect(const SDL_Rect& A, const SDL_Rect& B);

  public:
    // returns a SDL_Rect struct for given X, Y, W, H. Ideal for drawing.
  	static SDL_Rect getRect(unsigned int X, unsigned int Y, unsigned int W, unsigned int H);
    static SDL_Rect getRect(const SDL_Point* A, const SDL_Point* B);
    static SDL_Rect getWinCentRect(const unsigned int& w, const unsigned int& h);
    static SDL_Point getPos(int X, int Y);

    // returns a SDL_Rect struct with W and H equal to 1, given (X, Y).
    // Good for grabbing a pixel of a particular color.
		static SDL_Rect getPixel(const SDL_Point* pix);

	public:
    static bool drawLine(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick);

    static bool drawBox(const SDL_Rect* box, const SDL_Point* color);
    static bool drawBox(const SDL_Rect* box, const SDL_Point* color, const int& thick);
    static bool drawBox(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick);

		static bool drawBoxFill(const SDL_Rect* box, const SDL_Point* color);
    static bool drawBoxFill(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color);
    static bool drawBoxFill(const SDL_Rect* box, const SDL_Color* rgb);

    static bool drawStrBox(const SDL_Rect* box, const int& str_w, const SDL_Point* color);
    static bool drawStrBox(const SDL_Rect* box, const int& str_w, const SDL_Point* color, const SDL_Point* str_col);

    static bool drawArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb);
    static bool drawArrowFill(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb);
    static bool drawStrArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb);
    static bool drawStrArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb);

    static bool drawArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb);
    static bool drawArrowFill(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb);
    static bool drawStrArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb);
    static bool drawStrArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb);

public:
    static bool isInt(const char& c);
    static int charToInt(const char& c);
    static double strToDouble(const std::string& str);
};

#endif
