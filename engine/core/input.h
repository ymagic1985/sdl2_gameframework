#include "mzpch.h"

class Input {
    public:
        inline static bool isKeyboardPressed(int scancode) { return s_Instance->isKeyboardPressedImpl(scancode); }
        inline static bool isMouseLeftPressed() { return s_Instance->isMouseLeftPressedImpl(); }
        inline static bool isMouseRightPressed() { return s_Instance->isMouseRightPressedImpl(); }
        inline static bool isMouseMiddlePressed() { return s_Instance->isMouseMiddlePressedImpl(); }
        inline static std::pair<float, float> getMousePosition() { return s_Instance->getMousePositionImpl(); }
        inline static float getMouseX() { return s_Instance->getMouseXImpl(); }
        inline static float getMouseY() { return s_Instance->getMouseYImpl(); }
    protected:
        virtual bool isKeyboardPressedImpl(int key) = 0;
        virtual bool isMouseLeftPressedImpl() = 0;
        virtual bool isMouseRightPressedImpl() = 0;
        virtual bool isMouseMiddlePressedImpl() = 0;
        virtual std::pair<float, float> getMousePositionImpl() = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;
    private: 
        static Input* s_Instance;
};

class MacInput : public Input {
   protected:
       virtual bool isKeyboardPressedImpl(int scancode) override;
       virtual bool isMouseLeftPressedImpl() override;
       virtual bool isMouseRightPressedImpl() override;
       virtual bool isMouseMiddlePressedImpl() override;
       virtual std::pair<float, float> getMousePositionImpl() override;
       virtual float getMouseXImpl() override;
       virtual float getMouseYImpl() override;
       bool isMouseClicked(int button);
};
