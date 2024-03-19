#pragma once

#include <cstdint>

#include "Internal/Input/Backend.h"

namespace GLEEC
{
    using Key = uint32_t;

    // same as glfw keys
    inline constexpr Key KEY_UNKNOWN = -1;
    inline constexpr Key KEY_SPACE = 32;
    inline constexpr Key KEY_APOSTROPHE =          39  /* ' */;
    inline constexpr Key KEY_COMMA =               44  /* , */;
    inline constexpr Key KEY_MINUS =               45  /* - */;
    inline constexpr Key KEY_PERIOD =              46  /* . */;
    inline constexpr Key KEY_SLASH =               47  /* / */;
    inline constexpr Key KEY_0 =                   48;
    inline constexpr Key KEY_1 =                   49;
    inline constexpr Key KEY_2 =                   50;
    inline constexpr Key KEY_3 =                   51;
    inline constexpr Key KEY_4 =                   52;
    inline constexpr Key KEY_5 =                   53;
    inline constexpr Key KEY_6 =                   54;
    inline constexpr Key KEY_7 =                   55;
    inline constexpr Key KEY_8 =                   56;
    inline constexpr Key KEY_9 =                   57;
    inline constexpr Key KEY_SEMICOLON =           59  /* ; */;
    inline constexpr Key KEY_EQUAL =               61  /* = */;
    inline constexpr Key KEY_A =                   65;
    inline constexpr Key KEY_B =                   66;
    inline constexpr Key KEY_C =                   67;
    inline constexpr Key KEY_D =                   68;
    inline constexpr Key KEY_E =                   69;
    inline constexpr Key KEY_F =                   70;
    inline constexpr Key KEY_G =                   71;
    inline constexpr Key KEY_H =                   72;
    inline constexpr Key KEY_I =                  73;
    inline constexpr Key KEY_J =                  74;
    inline constexpr Key KEY_K =                  75;
    inline constexpr Key KEY_L =                  76;
    inline constexpr Key KEY_M =                  77;
    inline constexpr Key KEY_N =                  78;
    inline constexpr Key KEY_O =                  79;
    inline constexpr Key KEY_P =                  80;
    inline constexpr Key KEY_Q =                  81;
    inline constexpr Key KEY_R =                  82;
    inline constexpr Key KEY_S =                  83;
    inline constexpr Key KEY_T =                  84;
    inline constexpr Key KEY_U =                  85;
    inline constexpr Key KEY_V =                  86;
    inline constexpr Key KEY_W =                  87;
    inline constexpr Key KEY_X =                  88;
    inline constexpr Key KEY_Y =                  89;
    inline constexpr Key KEY_Z =                  90;
    inline constexpr Key KEY_LEFT_BRACKET =       91  /* [ */;
    inline constexpr Key KEY_BACKSLASH =          92  /* \ */;
    inline constexpr Key KEY_RIGHT_BRACKET =      93  /* ] */;
    inline constexpr Key KEY_GRAVE_ACCENT =       96  /* ` */;
    inline constexpr Key KEY_WORLD_1 =            161 /* non-US #1 */;
    inline constexpr Key KEY_WORLD_2 =            162 /* non-US #2 */;
    inline constexpr Key KEY_ESCAPE =             256;
    inline constexpr Key KEY_ENTER =              257;
    inline constexpr Key KEY_TAB =                258;
    inline constexpr Key KEY_BACKSPACE =          259;
    inline constexpr Key KEY_INSERT =             260;
    inline constexpr Key KEY_DELETE =             261;
    inline constexpr Key KEY_RIGHT =              262;
    inline constexpr Key KEY_LEFT =               263;
    inline constexpr Key KEY_DOWN =               264;
    inline constexpr Key KEY_UP =                 265;
    inline constexpr Key KEY_PAGE_UP =            266;
    inline constexpr Key KEY_PAGE_DOWN =          267;
    inline constexpr Key KEY_HOME =               268;
    inline constexpr Key KEY_END =                269;
    inline constexpr Key KEY_CAPS_LOCK =          280;
    inline constexpr Key KEY_SCROLL_LOCK =        281;
    inline constexpr Key KEY_NUM_LOCK =           282;
    inline constexpr Key KEY_PRINT_SCREEN =       283;
    inline constexpr Key KEY_PAUSE =              284;
    inline constexpr Key KEY_F1 =                 290;
    inline constexpr Key KEY_F2 =                 291;
    inline constexpr Key KEY_F3 =                 292;
    inline constexpr Key KEY_F4 =                 293;
    inline constexpr Key KEY_F5 =                 294;
    inline constexpr Key KEY_F6 =                 295;
    inline constexpr Key KEY_F7 =                 296;
    inline constexpr Key KEY_F8 =                 297;
    inline constexpr Key KEY_F9 =                 298;
    inline constexpr Key KEY_F10 =                299;
    inline constexpr Key KEY_F11 =                300;
    inline constexpr Key KEY_F12 =                301;
    inline constexpr Key KEY_F13 =                302;
    inline constexpr Key KEY_F14 =                303;
    inline constexpr Key KEY_F15 =                304;
    inline constexpr Key KEY_F16 =                305;
    inline constexpr Key KEY_F17 =                306;
    inline constexpr Key KEY_F18 =                307;
    inline constexpr Key KEY_F19 =                308;
    inline constexpr Key KEY_F20 =                309;
    inline constexpr Key KEY_F21 =                310;
    inline constexpr Key KEY_F22 =                311;
    inline constexpr Key KEY_F23 =                312;
    inline constexpr Key KEY_F24 =                313;
    inline constexpr Key KEY_F25 =                314;
    inline constexpr Key KEY_KP_0 =               320;
    inline constexpr Key KEY_KP_1 =               321;
    inline constexpr Key KEY_KP_2 =               322;
    inline constexpr Key KEY_KP_3 =               323;
    inline constexpr Key KEY_KP_4 =               324;
    inline constexpr Key KEY_KP_5 =               325;
    inline constexpr Key KEY_KP_6 =               326;
    inline constexpr Key KEY_KP_7 =               327;
    inline constexpr Key KEY_KP_8 =               328;
    inline constexpr Key KEY_KP_9 =               329;
    inline constexpr Key KEY_KP_DECIMAL =         330;
    inline constexpr Key KEY_KP_DIVIDE =          331;
    inline constexpr Key KEY_KP_MULTIPLY =        332;
    inline constexpr Key KEY_KP_SUBTRACT =        333;
    inline constexpr Key KEY_KP_ADD =             334;
    inline constexpr Key KEY_KP_ENTER =           335;
    inline constexpr Key KEY_KP_EQUAL =           336;
    inline constexpr Key KEY_LEFT_SHIFT =         340;
    inline constexpr Key KEY_LEFT_CONTROL =       341;
    inline constexpr Key KEY_LEFT_ALT =           342;
    inline constexpr Key KEY_LEFT_SUPER =         343;
    inline constexpr Key KEY_RIGHT_SHIFT =        344;
    inline constexpr Key KEY_RIGHT_CONTROL =      345;
    inline constexpr Key KEY_RIGHT_ALT =          346;
    inline constexpr Key KEY_RIGHT_SUPER =        347;
    inline constexpr Key KEY_MENU =               348;
    inline constexpr Key KEY_LAST =               KEY_MENU;

    inline constexpr Key NUM_KEYS = KEY_LAST;

    inline constexpr Key MODIFIER_SHIFT = 1;
    inline constexpr Key MODIFIER_CONTROL = 2;
    inline constexpr Key MODIFIER_ALT = 4;
    inline constexpr Key MODIFIER_SUPER = 8;
    inline constexpr Key MODIFIER_CAPS_LOCK = 16;
    inline constexpr Key MODIFIER_NUM_LOCK = 32;

#if GLEEC_INPUT_BACKEND == INPUT_BACKEND_GLFW
    inline constexpr Key toGLFWKey(Key key)
    {
        return key - KEY_SPACE;
    }

    inline constexpr Key toGLFWModifier(Key key)
    {
        return MODIFIER_SHIFT;
    }
#endif
}
