#include <raylib.h>


/// A rectangle defining the position of the element in the resource file.
/// Pass into getTexture function to get scaled texture of the element.
typedef Rectangle UiElement;

#define NOT_FOUND           UiElement{0,0,0,0}

#define IBTN_EMTPY          UiElement{240,64,16,16}

#define UP_ARROW            UiElement{240,80,16,16}

#define IBTN_EXIT           UiElement{192,64,16,16}
#define IBTN_WINDOWED       UiElement{208,64,16,16}
#define IBTN_FULLSCREEN     UiElement{224,64,16,16}

#define BTN_BLUE_ACTIVE     UiElement{0,32,48,16}
#define BTN_BLUE_HOVER      UiElement{0,16,48,16}
#define BTN_BLUE_CLICKED    UiElement{0,48,48,16}

#define CURSOR_ACTIVE       UiElement{240,32,16,16}
#define CURSOR_HOVER        UiElement{240,48,16,16}

/// WIP
/// @returns scaled texture of the given element in ui.png
Texture2D getTexture(UiElement uiElem,float scale);