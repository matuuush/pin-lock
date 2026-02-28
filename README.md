# Digital 4-digit PIN code lock system

Winter semester 2025/2026 microcontroller programming semestral project.

Author: Matúš Farkaš

## Entry requirements

- Microcontroller: ATmega328P
- Accessories: Multi-function Shield

## How To Run

Required:

- Change working directory to source files directory.

```
cd src
```

- Build executable file and upload it to the microcontroller.

```
make
```

- Now the Lock system is up and running inside your microcontroller.

Optional:

- Remove all build files

```
make clean
```

Hints:

- If the microcontroller is connected to your personal computer by other port than `COM3` you will have to change the upload configuration in the `src/Makefile`.

## Entry configuration

- Current code: `0000`.
- PIN code: `0000`.
- Number of attempts: 3 (shown by the LED lights).
- After connecting the microcontroller to the power source:
  - Display reads `0000`.
  - Current system state is `LOCKED`.

## User documentation

Read more about the features, controls, behaviour and states of the Lock system in the [User documentation](docs/user-docs.md).

## Programmer documentation

Read more about the way the low level of the Lock system behaviour in the [Programmer documentation](docs/prog-docs.md).
