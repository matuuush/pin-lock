#include "concrete_states.hpp"

LockedState locked_state;
PassState pass_state;
FailState fail_state;
LockState lock_message_state;
FreeState free_state;
SetState set_state;
GoodState good_state;
ModifiedState modified_state;
DeadState dead_state;

AbstractLockState* LOCKED = &locked_state;
AbstractLockState* PASS = &pass_state;
AbstractLockState* FAIL = &fail_state;
AbstractLockState* LOCK = &lock_message_state;
AbstractLockState* FREE = &free_state;
AbstractLockState* SET = &set_state;
AbstractLockState* GOOD = &good_state;
AbstractLockState* MODIFIED = &modified_state;
AbstractLockState* DEAD = &dead_state;
