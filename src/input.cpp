#include <SDL2/SDL.h>
#include <utility>

#include "input.h"

bool MacInput::isKeyboardPressedImpl(int scancode) {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[scancode];
}

bool MacInput::isMouseClicked(int button) {
    int x, y; 
    
    return ((SDL_GetMouseState(&x,&y) & SDL_BUTTON(button)) != 0);
}

bool MacInput::isMouseLeftPressedImpl() {
    return isMouseClicked(SDL_BUTTON_LMASK);
}

bool MacInput::isMouseMiddlePressedImpl() {
    return isMouseClicked(SDL_BUTTON_MMASK);
}

bool MacInput::isMouseRightPressedImpl() {
    return isMouseClicked(3);
}

std::pair<float, float> MacInput::getMousePositionImpl() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return std::make_pair(x, y);
}

float MacInput::getMouseXImpl() {
    auto[x, y] = getMousePositionImpl();
    return x;
}

float MacInput::getMouseYImpl() {
    auto[x, y] = getMousePositionImpl();
    return y;
}
