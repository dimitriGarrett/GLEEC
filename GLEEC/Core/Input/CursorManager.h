#pragma once

#include "Cursor.h"
#include "math/utility/defines.h"

namespace GLEEC::Input
{
    struct CursorManager
    {
        GLEEC_API static void setPosition(const Cursor& cursor,
            const math::vec2& pos);

        GLEEC_API static math::vec2 getPosition(const Cursor& cursor);

        GLEEC_API static void hideCursor(const Cursor& cursor);
        GLEEC_API static void showCursor(const Cursor& cursor);
        GLEEC_API static void disableCursor(const Cursor& cursor);

/*         GLEEC_API static void setShape( */
    };
}
