# Digital 4-digit PIN Code Lock System specification

Author: Matúš Farkaš

## General description

The goal of this project is to implement a 4-digit PIN code lock system on an ATmega328PB microcontroller equipped with a Multi-function Shield. The PIN code itself will be stored in a persistent memory to prevent bypassing the lock by disconnecting the power delivery.

## User Interaction
- Select Value (Potentiometer)
  - The user selects a number (0-9) by rotating the Potentiometer. The selected number appears in real-time on the active digit of the 7-segment display.

- Move Cursor (Button 1)
  - Pressing Button 1 advances the cursor to the next digit. Pressing the Button 1 on the last digit will move the cursor to the first digit.

- Unlock Attempt (Button 2)
  - Pressing Button 2 at any time during the code configuration attempts to unlock the system with the current 4-digit code.
    - If the code is correct, keyword `PASS` will appear
    - If the code is not correct, keyword `FAIL` will appear

- Lock System (Button 2)
  - Pressing Button 2 while the system is unlocked will lock the system.

- Set New PIN Code (Button 3)
  - Pressing Button 3 while the system is unlocked will start the `Set new PIN code` procedure.
  - The user has to set the new code by interacting with the Potentiometer and the Button 1.
  - After setting the new PIN code the user will have to press Button 3 to confirm the code.

## Used Peripherals

- Multi-function Shield
  - 7-segment display
    - User Interface Display - current code
  - Button 1
    - Moves cursor to the next digit
  - Button 2
    - Attempts to unlock the system / Locks the system when unlocked
  - Potentiometer
    - Selects digit value (0-9)
  - 4 LED lights
    - Status lights (remaining attempts)


# poznámky

pridaj časovanie proti útočníkovi aby nedokázal odstopovať čas na chybu a pomocou toho dekódovať správny prístupový kód 