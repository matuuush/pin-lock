# Digital 4-digit PIN Code Lock System

Programmer documentation

Author: Matúš Farkaš

## System Components Behaviour Description

### Main

- Provides initialisation of all components and repeated call of the program main loop.
- The application can be started in one of 3 modes:
  - GUESS_CODE.
    - The default mode.
    - The behaviour of the app is just as described in the user documentation.
  - SHOW_CODE.
    - The mode to show the currently saved PIN code on the display.
    - The app is in immutable state in this mode.
  - RESET_PIN.
    - The mode that resets the PIN back to the default value (0000).
    - Does nothing else.

### States

- The lock system itself runs as a state machine.
  - The controls representing the transitions of the automata are described in the user documentation.
- The possible states are as following:
  - LOCKED
    - Represents the system in the locked state.
  - PASS
    - Represents successful attempt to unlock the system.
  - FAIL
    - Represents unsuccessful attempt to unlock the system.
  - FREE
    - Represents the system in the unlocked state.
  - LOCK
    - Represents the process of locking the system.
  - SET
    - Represents the beginning of the password changing process.
  - MODIFIED
    - Represents the process of changing the password.
  - GOOD
    - Represents the confirmation of the new password.
  - DEAD
    - Represents the system after failing all unlock attempts.

### Lock

- Represents the encapsulation of the whole system, its fields and operations.
- Provides the interface for the States module to call functions when needed.
- Contains the following fields:
  - Current code shown on the display.
  - Hidden PIN code working as a pass word.
  - Number of remaining attempts.
  - Current state of the lock system.
  - Cursor showing the current position of the digit being changed at the moment.
- Contains the following operations:
  - Raise value off the digit pointed to by the cursor.
  - Move cursor to the next position.
  - Set new PIN code.
  - Make the system locked.
  - Try to unlock the system with the current code.
  - Hide message announcing the new current state.

### Button

- Input components connected to the pins A1-A3.
- The module encapsulates reading the input of the physical buttons.
- Provides a higher level interface for buttong press and trigger detection.

### Constants

- Holds global constants used frequently in code.
  - String messages, constants, defaults, ...
- Also provides global wrapper functions for low level information manipulation.

### Display

- Wrapper module used for showing information on the display.
  - Is able to show 4 digits composed of 7 segments at once.
- Each usable and also showable digit and character is encoded in a translation array.
  - Indexing into the array by the order of the digit/character returns its glyph.
  - Only some characters can be shown capital for distinction.
- The actual shown glyphs have to be saved inside the buffer array.
- The buffer array updating interface can only save at most 4-digit number or a 4-character string inside the buffer.
- The display works by showing only a single digit at a time.
  - So it has to get periodically refreshed at a high speed for the human eye to not see catch any disturbancies.
- It is possible to show the current position of the cursor.
  - This lights one digit/character more brightly than the others for distinction.

### Light

- Module serves as a wrapper of the Shield diodes.
- The diodes can be enlighten, shut off or switched on command by the provided interface.

### Storage

- Manages the store of saved PIN code in the persistent EEPROM memory.
- Uses built-in AVR library eeprom.h for low-level storage and retrieval of code.

### Death

- Wrapper of DEAD state.
- Arises when the user fails to unlock the system using the provided number of attempts.
- Acts as a LOCKED state with 4-letter word consisting of characters instead of 4-digit number consisting of numeral digits.
- The state changes to LOCKED with 3 remaining attempts when the user manages to write word LOCK on the display.
