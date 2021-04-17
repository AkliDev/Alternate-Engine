#pragma once

namespace Alternate
{
	using KeyCode = uint16_t;

	namespace Key
	{
		enum KeyCode
		{
			//From SDL_scancode.h
			ALT_KEY_A = 4,
			ALT_KEY_B = 5,
			ALT_KEY_C = 6,
			ALT_KEY_D = 7,
			ALT_KEY_E = 8,
			ALT_KEY_F = 9,
			ALT_KEY_G = 10,
			ALT_KEY_H = 11,
			ALT_KEY_I = 12,
			ALT_KEY_J = 13,
			ALT_KEY_K = 14,
			ALT_KEY_L = 15,
			ALT_KEY_M = 16,
			ALT_KEY_N = 17,
			ALT_KEY_O = 18,
			ALT_KEY_P = 19,
			ALT_KEY_Q = 20,
			ALT_KEY_R = 21,
			ALT_KEY_S = 22,
			ALT_KEY_T = 23,
			ALT_KEY_U = 24,
			ALT_KEY_V = 25,
			ALT_KEY_W = 26,
			ALT_KEY_X = 27,
			ALT_KEY_Y = 28,
			ALT_KEY_Z = 29,

			ALT_KEY_1 = 30,
			ALT_KEY_2 = 31,
			ALT_KEY_3 = 32,
			ALT_KEY_4 = 33,
			ALT_KEY_5 = 34,
			ALT_KEY_6 = 35,
			ALT_KEY_7 = 36,
			ALT_KEY_8 = 37,
			ALT_KEY_9 = 38,
			ALT_KEY_0 = 39,

			ALT_KEY_RETURN = 40,
			ALT_KEY_ESCAPE = 41,
			ALT_KEY_BACKSPACE = 42,
			ALT_KEY_TAB = 43,
			ALT_KEY_SPACE = 44,

			ALT_KEY_MINUS = 45,
			ALT_KEY_EQUALS = 46,
			ALT_KEY_LEFTBRACKET = 47,
			ALT_KEY_RIGHTBRACKET = 48,
			ALT_KEY_BACKSLASH = 49, /**< Located at the lower left of the return
			*   key on ISO keyboards and at the right end
			*   of the QWERTY row on ANSI keyboards.
			*   Produces REVERSE SOLIDUS (backslash) and
			*   VERTICAL LINE in a US layout REVERSE
			*   SOLIDUS and VERTICAL LINE in a UK Mac
			*   layout NUMBER SIGN and TILDE in a UK
			*   Windows layout DOLLAR SIGN and POUND SIGN
			*   in a Swiss German layout NUMBER SIGN and
			*   APOSTROPHE in a German layout GRAVE
			*   ACCENT and POUND SIGN in a French Mac
			*   layout and ASTERISK and MICRO SIGN in a
			*   French Windows layout.
			*/
			ALT_KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
			*   instead of 49 for the same key but all
			*   OSes I've seen treat the two codes
			*   identically. So as an implementor unless
			*   your keyboard generates both of those
			*   codes and your OS treats them differently
			*   you should generate # define ALT_KEY_BACKSLASH
			*   instead of this code. As a user you
			*   should not rely on this code because SDL
			*   will never generate it with most (all?)
			*   keyboards.
			*/
			ALT_KEY_SEMICOLON = 51,
			ALT_KEY_APOSTROPHE = 52,
			ALT_KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
			*   and ISO keyboards). Produces GRAVE ACCENT and
			*   TILDE in a US Windows layout and in US and UK
			*   Mac layouts on ANSI keyboards GRAVE ACCENT
			*   and NOT SIGN in a UK Windows layout SECTION
			*   SIGN and PLUS-MINUS SIGN in US and UK Mac
			*   layouts on ISO keyboards SECTION SIGN and
			*   DEGREE SIGN in a Swiss German layout (Mac:
			*   only on ISO keyboards) CIRCUMFLEX ACCENT and
			*   DEGREE SIGN in a German layout (Mac: only on
			*   ISO keyboards) SUPERSCRIPT TWO and TILDE in a
			*   French Windows layout COMMERCIAL AT and
			*   NUMBER SIGN in a French Mac layout on ISO
			*   keyboards and LESS-THAN SIGN and GREATER-THAN
			*   SIGN in a Swiss German German or French Mac
			*   layout on ANSI keyboards.
			*/
			ALT_KEY_COMMA = 54,
			ALT_KEY_PERIOD = 55,
			ALT_KEY_SLASH = 56,

			ALT_KEY_CAPSLOCK = 57,

			ALT_KEY_F1 = 58,
			ALT_KEY_F2 = 59,
			ALT_KEY_F3 = 60,
			ALT_KEY_F4 = 61,
			ALT_KEY_F5 = 62,
			ALT_KEY_F6 = 63,
			ALT_KEY_F7 = 64,
			ALT_KEY_F8 = 65,
			ALT_KEY_F9 = 66,
			ALT_KEY_F10 = 67,
			ALT_KEY_F11 = 68,
			ALT_KEY_F12 = 69,

			ALT_KEY_PRINTSCREEN = 70,
			ALT_KEY_SCROLLLOCK = 71,
			ALT_KEY_PAUSE = 72,
			ALT_KEY_INSERT = 73, /**< insert on PC help on some Mac keyboards (but
			does send code 73 not 117) */
			ALT_KEY_HOME = 74,
			ALT_KEY_PAGEUP = 75,
			ALT_KEY_DELETE = 76,
			ALT_KEY_END = 77,
			ALT_KEY_PAGEDOWN = 78,
			ALT_KEY_RIGHT = 79,
			ALT_KEY_LEFT = 80,
			ALT_KEY_DOWN = 81,
			ALT_KEY_UP = 82,

			ALT_KEY_NUMLOCKCLEAR = 83, /**< num lock on PC clear on Mac keyboards*/
			ALT_KEY_KP_DIVIDE = 84,
			ALT_KEY_KP_MULTIPLY = 85,
			ALT_KEY_KP_MINUS = 86,
			ALT_KEY_KP_PLUS = 87,
			ALT_KEY_KP_ENTER = 88,
			ALT_KEY_KP_1 = 89,
			ALT_KEY_KP_2 = 90,
			ALT_KEY_KP_3 = 91,
			ALT_KEY_KP_4 = 92,
			ALT_KEY_KP_5 = 93,
			ALT_KEY_KP_6 = 94,
			ALT_KEY_KP_7 = 95,
			ALT_KEY_KP_8 = 96,
			ALT_KEY_KP_9 = 97,
			ALT_KEY_KP_0 = 98,
			ALT_KEY_KP_PERIOD = 99,

			ALT_KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
			*   keyboards have over ANSI ones
			*   located between left shift and Y.
			*   Produces GRAVE ACCENT and TILDE in a
			*   US or UK Mac layout REVERSE SOLIDUS
			*   (backslash) and VERTICAL LINE in a
			*   US or UK Windows layout and
			*   LESS-THAN SIGN and GREATER-THAN SIGN
			*   in a Swiss German German or French
			*   layout. */
			ALT_KEY_APPLICATION = 101, /**< windows contextual menu compose */
			ALT_KEY_POWER = 102, /**< The USB document says this is a status flag
			*   not a physical key - but some Mac keyboards
			*   do have a power key. */
			ALT_KEY_KP_EQUALS = 103,
			ALT_KEY_F13 = 104,
			ALT_KEY_F14 = 105,
			ALT_KEY_F15 = 106,
			ALT_KEY_F16 = 107,
			ALT_KEY_F17 = 108,
			ALT_KEY_F18 = 109,
			ALT_KEY_F19 = 110,
			ALT_KEY_F20 = 111,
			ALT_KEY_F21 = 112,
			ALT_KEY_F22 = 113,
			ALT_KEY_F23 = 114,
			ALT_KEY_F24 = 115,
			ALT_KEY_EXECUTE = 116,
			ALT_KEY_HELP = 117,
			ALT_KEY_MENU = 118,
			ALT_KEY_SELECT = 119,
			ALT_KEY_STOP = 120,
			ALT_KEY_AGAIN = 121,   /**< redo */
			ALT_KEY_UNDO = 122,
			ALT_KEY_CUT = 123,
			ALT_KEY_COPY = 124,
			ALT_KEY_PASTE = 125,
			ALT_KEY_FIND = 126,
			ALT_KEY_MUTE = 127,
			ALT_KEY_VOLUMEUP = 128,
			ALT_KEY_VOLUMEDOWN = 129,
			/* not sure whether there's a reason to enable these */
			/*     # define ALT_KEY_LOCKINGCAPSLOCK  130  */
			/*     # define ALT_KEY_LOCKINGNUMLOCK  131 */
			/*     # define ALT_KEY_LOCKINGSCROLLLOCK  132 */
			ALT_KEY_KP_COMMA = 133,
			ALT_KEY_KP_EQUALSAS400 = 134,

			ALT_KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards see
			footnotes in USB doc */
			ALT_KEY_INTERNATIONAL2 = 136,
			ALT_KEY_INTERNATIONAL3 = 137, /**< Yen */
			ALT_KEY_INTERNATIONAL4 = 138,
			ALT_KEY_INTERNATIONAL5 = 139,
			ALT_KEY_INTERNATIONAL6 = 140,
			ALT_KEY_INTERNATIONAL7 = 141,
			ALT_KEY_INTERNATIONAL8 = 142,
			ALT_KEY_INTERNATIONAL9 = 143,
			ALT_KEY_LANG1 = 144, /**< Hangul/English toggle */
			ALT_KEY_LANG2 = 145, /**< Hanja conversion */
			ALT_KEY_LANG3 = 146, /**< Katakana */
			ALT_KEY_LANG4 = 147, /**< Hiragana */
			ALT_KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
			ALT_KEY_LANG6 = 149, /**< reserved */
			ALT_KEY_LANG7 = 150, /**< reserved */
			ALT_KEY_LANG8 = 151, /**< reserved */
			ALT_KEY_LANG9 = 152, /**< reserved */

			ALT_KEY_ALTERASE = 153, /**< Erase-Eaze */
			ALT_KEY_SYSREQ = 154,
			ALT_KEY_CANCEL = 155,
			ALT_KEY_CLEAR = 156,
			ALT_KEY_PRIOR = 157,
			ALT_KEY_RETURN2 = 158,
			ALT_KEY_SEPARATOR = 159,
			ALT_KEY_OUT = 160,
			ALT_KEY_OPER = 161,
			ALT_KEY_CLEARAGAIN = 162,
			ALT_KEY_CRSEL = 163,
			ALT_KEY_EXSEL = 164,

			ALT_KEY_KP_00 = 176,
			ALT_KEY_KP_000 = 177,
			ALT_KEY_THOUSANDSSEPARATOR = 178,
			ALT_KEY_DECIMALSEPARATOR = 179,
			ALT_KEY_CURRENCYUNIT = 180,
			ALT_KEY_CURRENCYSUBUNIT = 181,
			ALT_KEY_KP_LEFTPAREN = 182,
			ALT_KEY_KP_RIGHTPAREN = 183,
			ALT_KEY_KP_LEFTBRACE = 184,
			ALT_KEY_KP_RIGHTBRACE = 185,
			ALT_KEY_KP_TAB = 186,
			ALT_KEY_KP_BACKSPACE = 187,
			ALT_KEY_KP_A = 188,
			ALT_KEY_KP_B = 189,
			ALT_KEY_KP_C = 190,
			ALT_KEY_KP_D = 191,
			ALT_KEY_KP_E = 192,
			ALT_KEY_KP_F = 193,
			ALT_KEY_KP_XOR = 194,
			ALT_KEY_KP_POWER = 195,
			ALT_KEY_KP_PERCENT = 196,
			ALT_KEY_KP_LESS = 197,
			ALT_KEY_KP_GREATER = 198,
			ALT_KEY_KP_AMPERSAND = 199,
			ALT_KEY_KP_DBLAMPERSAND = 200,
			ALT_KEY_KP_VERTICALBAR = 201,
			ALT_KEY_KP_DBLVERTICALBAR = 202,
			ALT_KEY_KP_COLON = 203,
			ALT_KEY_KP_HASH = 204,
			ALT_KEY_KP_SPACE = 205,
			ALT_KEY_KP_AT = 206,
			ALT_KEY_KP_EXCLAM = 207,
			ALT_KEY_KP_MEMSTORE = 208,
			ALT_KEY_KP_MEMRECALL = 209,
			ALT_KEY_KP_MEMCLEAR = 210,
			ALT_KEY_KP_MEMADD = 211,
			ALT_KEY_KP_MEMSUBTRACT = 212,
			ALT_KEY_KP_MEMMULTIPLY = 213,
			ALT_KEY_KP_MEMDIVIDE = 214,
			ALT_KEY_KP_PLUSMINUS = 215,
			ALT_KEY_KP_CLEAR = 216,
			ALT_KEY_KP_CLEARENTRY = 217,
			ALT_KEY_KP_BINARY = 218,
			ALT_KEY_KP_OCTAL = 219,
			ALT_KEY_KP_DECIMAL = 220,
			ALT_KEY_KP_HEXADECIMAL = 221,

			ALT_KEY_LCTRL = 224,
			ALT_KEY_LSHIFT = 225,
			ALT_KEY_LALT = 226, /**< alt option */
			ALT_KEY_LGUI = 227, /**< windows command (apple) meta */
			ALT_KEY_RCTRL = 228,
			ALT_KEY_RSHIFT = 229,
			ALT_KEY_RALT = 230, /**< alt gr option */
			ALT_KEY_RGUI = 231, /**< windows command (apple) meta */

			ALT_KEY_MODE = 257,    /**< I'm not sure if this is really not covered
			*   by any of the above but since there's a
			*   special KMOD_MODE for it I'm adding it here
			*/

			/* @} *//* Usage page 0x07 */

			/**
			 *  \name Usage page 0x0C
			 *
			 *  These values are mapped from usage page 0x0C (USB consumer page).
			 */
			/* @{ */

			ALT_KEY_AUDIONEXT = 258,
			ALT_KEY_AUDIOPREV = 259,
			ALT_KEY_AUDIOSTOP = 260,
			ALT_KEY_AUDIOPLAY = 261,
			ALT_KEY_AUDIOMUTE = 262,
			ALT_KEY_MEDIASELECT = 263,
			ALT_KEY_WWW = 264,
			ALT_KEY_MAIL = 265,
			ALT_KEY_CALCULATOR = 266,
			ALT_KEY_COMPUTER = 267,
			ALT_KEY_AC_SEARCH = 268,
			ALT_KEY_AC_HOME = 269,
			ALT_KEY_AC_BACK = 270,
			ALT_KEY_AC_FORWARD = 271,
			ALT_KEY_AC_STOP = 272,
			ALT_KEY_AC_REFRESH = 273,
			ALT_KEY_AC_BOOKMARKS = 274,

			/* @} *//* Usage page 0x0C */

			/**
			 *  \name Walther keys
			 *
			 *  These are values that Christian Walther added (for mac keyboard?).
			 */
			 /* @{ */

			ALT_KEY_BRIGHTNESSDOWN = 275,
			ALT_KEY_BRIGHTNESSUP = 276,
			ALT_KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
										  switch video mode switch */
			ALT_KEY_KBDILLUMTOGGLE = 278,
			ALT_KEY_KBDILLUMDOWN = 279,
			ALT_KEY_KBDILLUMUP = 280,
			ALT_KEY_EJECT = 281,
			ALT_KEY_SLEEP = 282,

			ALT_KEY_APP1 = 283,
			ALT_KEY_APP2 = 284,

			/* @} *//* Walther keys */

			/**
			 *  \name Usage page 0x0C (additional media keys)
			 *
			 *  These values are mapped from usage page 0x0C (USB consumer page).
			 */
			 /* @{ */

			ALT_KEY_AUDIOREWIND = 285,
			ALT_KEY_AUDIOFASTFORWARD = 286,
		};
	}
}