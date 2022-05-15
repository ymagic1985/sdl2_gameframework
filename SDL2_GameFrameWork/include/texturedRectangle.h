#include <SDL2/SDL.h>
#include <memory>
#include <string>

class TexturedRectangle {
    public:
        TexturedRectangle(SDL_Renderer*& renderer, const std::string& name);
        TexturedRectangle(const TexturedRectangle& rhs);
        TexturedRectangle(TexturedRectangle&& rhs);
        TexturedRectangle& operator= (const TexturedRectangle& rhs);
        TexturedRectangle& operator= (TexturedRectangle&& rhs);
        ~TexturedRectangle();

        void setRectangeProperties(int x, int y, int w, int h);
        void render(SDL_Renderer*& renderer);
        void update();
        void setRectY(int y) { mRect.y = y; }
        void setRectX(int x) { mRect.x = x; }
        int getRectX() const { return mRect.x; }
        int getRectY() const { return mRect.y; }
        SDL_Texture* getTexture() const { return mTexture; }
    private:
        SDL_Rect mRect;
        SDL_Texture* mTexture;
};

