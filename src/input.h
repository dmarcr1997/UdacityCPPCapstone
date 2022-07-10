#define IS_MOUSEBUTTON_HELD(mouse_button) (MOUSE[ mouse_button ])
#define IS_KEY_PRESSED(key)               (KEYS[ key ])

enum MouseButtons
{
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MOUSE_X1,
    MOUSE_X2,
    MOUSE_TOTAL
};