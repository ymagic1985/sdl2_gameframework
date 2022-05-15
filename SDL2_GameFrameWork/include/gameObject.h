
class GameObject {
    public:
        GameObject(){}
        virtual ~GameObject();
        GameObject(const GameObject& rhs);
        GameObject& operator=(const GameObject& rhs);
        GameObject(GameObject&& rhs);
        GameObject& operator=(GameObject&& rhs);

        virtual void Jump();
        virtual void Fire();

    private:
};
