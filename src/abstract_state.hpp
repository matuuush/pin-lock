#ifndef ABSTRACT_STATE_HPP
#define ABSTRACT_STATE_HPP

class AbstractLockState {
public:
    virtual void lock_action() = 0;
    virtual void display_action() = 0;
};

#endif