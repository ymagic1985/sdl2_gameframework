//examples of observer patern
#include "mzpch.h"

class Entity {
    public:
        bool isHero() const { return true; }
};

enum class Event {
    EVENT_START_FALL,
    EVENT_LEVEL_UP,
    NUM_EVENTS
};

enum class Achievement : unsigned short {
    Fell_Of_Bridge
};

class Observer {
    public:
        virtual ~Observer();
        virtual void onNotify(const Entity& entity, Event event) = 0;
    protected:
        Observer* prev_;
        Observer* next_;
};

class Achievements : public Observer {
    public:
        virtual void onNotify(const Entity& entity, Event event) {
            switch(event) {
                case Event::EVENT_START_FALL:
                    if(entity.isHero() && heroIsOnbridge_)
                        unlock(Achievement::Fell_Of_Bridge);
                    break;
                case Event::EVENT_LEVEL_UP:
                    //do something
                    break;
                default:
                    break;
            }
        }

    private:
        void unlock(Achievement achievement);

        bool heroIsOnbridge_;
};

class Subject {
    public:
        void addObserver(Observer* observer);
        void removeObserver(Observer* observer);
    protected:
        void notify(const Entity& entity, Event event) {
            for(int i = 0; i < observers_.size(); i++) {
                observers_[i]->onNotify(entity, event);
            }
        }

        std::vector<Observer*> observers_;
        //another way is to make observer a double linked list 
        //so the removal takes constant time
        Observer* head_;
};
