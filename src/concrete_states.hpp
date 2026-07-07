#ifndef CONCRETE_STATES_HPP
#define CONCRETE_STATES_HPP

#include "abstract_state.hpp"
#include "button.hpp"
#include "constants.hpp"
#include "display.hpp"
#include "death.hpp"
#include "light.hpp"
#include "lock.hpp"
#include "storage.hpp"

extern Lock lock;
extern Death death;
extern Display display;
extern Light lights[LIGHTS_COUNT];
extern Button buttons[BUTTON_COUNT];
extern Storage storage;

inline void show_remaining_attempts_count() {
    for (byte i = 0; i < LIGHTS_COUNT; i++) {
        Light light = lights[i];
        bool status = light.index < lock.attempts;
        lights[i].change(status);
    }
}

inline void turn_off_lights() {
    for (byte i = 0; i < LIGHTS_COUNT; i++) {
        lights[i].change(false);
    }
}

class LockedState : public AbstractLockState {
public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()) {
            lock.increment_digit();
        }
        if (buttons[SECOND].is_triggered()) {
            lock.move_cursor();
        }
        if (buttons[THIRD].is_triggered()) {
            lock.unlock_attempt();
        }
        show_remaining_attempts_count();
    }

    void display_action() override {
        // intentionally do nothing
    }

};

class ModifiedState : public AbstractLockState {
    public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()) {
            lock.increment_digit();
        }
        if (buttons[SECOND].is_triggered()) {
            lock.move_cursor();
        }
        if (buttons[THIRD].is_triggered()) {
            lock.change_pin_after();
            word new_pin = lock.pin_code;
            storage.write_pin(new_pin);
        }
    }
    
    void display_action() override {
        display.write_number(lock.current_code);
        display.write_cursor(lock.cursor);
    }
    
};

// LOCK, FREE, PASS, FAIL, SET, GOOD, DEAD

class PassState : public AbstractLockState {
    public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()) {
            lock.change_pin_beginning();
        }
        if (buttons[SECOND].is_triggered()
        || buttons[THIRD].is_triggered()) {
            lock.hide_message();
        }
    }
    
    void display_action() override {
        display.write_string(PASS_MESSAGE);
    }
    
};

class FailState : public AbstractLockState {
    public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()
        || buttons[SECOND].is_triggered()
        || buttons[THIRD].is_triggered()) {
            lock.hide_message();
        }
        show_remaining_attempts_count();
    }
    
    void display_action() override {
        display.write_string(FAIL_MESSAGE);
    }
    
};

class LockState : public AbstractLockState {
    public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()
        || buttons[SECOND].is_triggered()
        || buttons[THIRD].is_triggered()) {
            lock.set_current_code(DEFAULT_CODE);
            lock.hide_message();
        }
        show_remaining_attempts_count();
    }
    
    void display_action() override {
        display.write_string(LOCK_MESSAGE);
    }
    
};

class FreeState : public AbstractLockState {
    public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()) {
            // do nothing
        }
        if (buttons[SECOND].is_triggered()) {
            lock.lock_system();
        }
        if (buttons[THIRD].is_triggered()) {
            lock.change_pin_beginning();
        }
    }
    
    void display_action() override {
        display.write_string(FREE_MESSAGE);
    }
    
};

class SetState : public AbstractLockState {
    public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()
        || buttons[SECOND].is_triggered()
        || buttons[THIRD].is_triggered()) {
            lock.change_pin_during();
        }
    }
    
    void display_action() override {
        display.write_string(SET_MESSAGE);
    }
    
};

class GoodState : public AbstractLockState {
    public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()
        || buttons[SECOND].is_triggered()
        || buttons[THIRD].is_triggered()) {
            lock.hide_message();
        }
    }
    
    void display_action() override {
        display.write_string(GOOD_MESSAGE);
    }
    
};

class DeadState : public AbstractLockState {
    public:
    void lock_action() override {
        if (buttons[FIRST].is_triggered()) {
            death.increment_char();
        }
        if (buttons[SECOND].is_triggered()) {
            death.move_cursor();
        }
        if (buttons[THIRD].is_triggered()) {
            death.unlock_attempt();
        }
    }
    
    void display_action() override {
        display.write_string((const char*)death.current_word);
        display.write_cursor(death.cursor);
    }
    
};

extern LockedState locked_state;
extern PassState pass_state;
extern FailState fail_state;
extern LockState lock_message_state;
extern FreeState free_state;
extern SetState set_state;
extern GoodState good_state;
extern ModifiedState modified_state;
extern DeadState dead_state;

extern AbstractLockState* LOCKED;
extern AbstractLockState* PASS;
extern AbstractLockState* FAIL;
extern AbstractLockState* LOCK;
extern AbstractLockState* FREE;
extern AbstractLockState* SET;
extern AbstractLockState* GOOD;
extern AbstractLockState* MODIFIED;
extern AbstractLockState* DEAD;

#endif