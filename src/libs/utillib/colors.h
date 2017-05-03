#pragma once
/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *
 * The LICENSE at the root of this repo details your rights (if any)
 *------------------------------------------------------------------------*/

//---------------------------------------------------------------------------------------------------
// regular colors
#define cBlack    "\e[0;30m"
#define cRed      "\e[0;31m"
#define cGreen    "\e[0;32m"
#define cYellow   "\e[0;33m"
#define cBlue     "\e[0;34m"
#define cMagenta  "\e[0;35m"
#define cTeal     "\e[0;36m"
#define cWhite    "\e[0;37m"

// bold colors
#define bBlack    "\e[1;30m"
#define bRed      "\e[1;31m"
#define bGreen    "\e[1;32m"
#define bYellow   "\e[1;33m"
#define bBlue     "\e[1;34m"
#define bMagenta  "\e[1;35m"
#define bTeal     "\e[1;36m"
#define bWhite    "\e[1;37m"

// italic colors
#define italic    SFString("\e[3m")
#define iBlack    "\e[0m\e[3;30m"
#define iRed      "\e[0m\e[3;31m"
#define iGreen    "\e[0m\e[3;32m"
#define iYellow   "\e[0m\e[3;33m"
#define iBlue     "\e[0m\e[3;34m"
#define iMagenta  "\e[0m\e[3;35m"
#define iTeal     "\e[0m\e[3;36m"
#define iWhite    "\e[0m\e[3;37m"

// turn it off
#define cOff      "\e[0m"

#define asRed(a)      cRed << a << cOff
#define asGreen(a)    cGreen << a << cOff
#define asYellow(a)   cYellow << a << cOff
#define asBlue(a)     cBlue << a << cOff
#define asMagenta(a)  cMagenta << a << cOff
#define asBlueB(a)    bBlue << a << cOff

#define greenCheck (SFString(cGreen) + "✓" + cOff)
#define redX       (SFString(cRed)   + "X" + cOff)

//-----------------------------------------------------------------------
inline SFString convertColor(const SFString& colorIn) {
    bool bold = colorIn.Contains("_b");
    bool ital = colorIn.Contains("_i");
    SFString color = colorIn;
    color = nextTokenClear(color, '_');
    if (color == "black"  ) return (bold ? bBlack   : ital ? iBlack   : cBlack   );
    else if (color == "blue"   ) return (bold ? bBlue    : ital ? iBlue    : cBlue    );
    else if (color == "red"    ) return (bold ? bRed     : ital ? iRed     : cRed     );
    else if (color == "green"  ) return (bold ? bGreen   : ital ? iGreen   : cGreen   );
    else if (color == "yellow" ) return (bold ? bYellow  : ital ? iYellow  : cYellow  );
    else if (color == "magenta") return (bold ? bMagenta : ital ? iMagenta : cMagenta );
    else if (color == "teal"   ) return (bold ? bTeal    : ital ? iTeal    : cTeal    );
    else if (color == "white"  ) return (bold ? bWhite   : ital ? iWhite   : cWhite   );
    return "";
}

#define BARLEN 80
inline void progressBar(int _barLen, int _part, int _whole, const SFString& _tim) {
    double percent = _part / static_cast<double>(_whole);
    SFUint32 p = (SFUint32)(_barLen*percent/.75);

    SFString sss(' ', MAX(0, _barLen - p));

    cerr << cYellow << _part << cOff << " of " << cYellow << _whole << cOff;
    cerr << " (" << cBlue << padLeft(fmtFloatp(100.*percent, 1), 5, ' ') << cOff << "%)";
    cerr << " [" << SFString('x', p).Substitute("x", "░");
    cerr << sss;
    cerr << "] in ";
    cerr << cGreen << _tim << cOff << " seconds.\r";
    cerr.flush();
}
inline void progressBar(int _barLen, int _part, int _whole, int _tim) { progressBar(_barLen, _part, _whole, asString(_tim)); }
/*
// TODO: Do I really need this?
#define BARLEN 80
#define progressBar(_barLen,_part,_whole,_tim) \
{ \
	double percent = _part/(double)_whole; \
	SFUint32 p = (SFUint32)(_barLen*percent); \
	cerr << asYellow(_part) << " of " << asYellow(_whole) \
	<< " (" << asBlueB(padLeft(fmtFloatp(100.*percent,1),5,' ')) << "%)" \
	<< " [" << SFString('x',p).Substitute("x","░") << SFString(' ',_barLen-p) << "] in " << asGreen(_tim) << "seconds.\r"; \
	cerr.flush(); \
}
*/
