
class GameObject;

class Command {
    public:
        virtual ~Command() {}
        virtual void execute(GameObject& go)  = 0;
};

class JumpCommand : public Command {
    public:
        virtual ~JumpCommand();
        virtual void execute(GameObject& go) override;
 };

class FireCommand : public Command {
    public:
        virtual ~FireCommand();
        virtual void execute(GameObject& go) override;
};

class InputHanlder {
    public:
        void handleInput();
    private:
        Command* buttonX_;
        Command* buttonY_;
        Command* buttonA_;
        Command* buttonB_;
};

