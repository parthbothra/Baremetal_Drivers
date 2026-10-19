# Baremetal_Drivers

Register-level, **bare-metal drivers and APIs** for communication protocols and common peripherals, written in C from scratch with no HAL, no CMSIS and no vendor libraries. Everything is built straight from the reference manual: register structs, bit positions, startup code and vector table.

---

## Target hardware

| Item | Details |
|------|---------|
| Board | STM32 "Black Pill" |
| MCU | STM32F411CEU6 |
| Core | ARM Cortex-M4 (with FPU) |
| SRAM | 128 KB |
| Toolchain | `arm-none-eabi-gcc` |

---

## Getting started

### Prerequisites

- [Arm GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) (`arm-none-eabi-gcc`)
- `make`
- A flashing tool such as OpenOCD, `st-flash` or STM32CubeProgrammer, and an ST-Link or USB DFU (Black Pill boot mode)

---

## Why bare-metal?

Writing drivers against the reference manual, with no abstraction layer, makes it clear what the hardware really does: how a peripheral clock gets enabled, how a bit field maps to behaviour, and how a chip goes from reset to `main()`. This repository is both a learning record and a reusable driver base for embedded firmware work.

---

## References

- STM32F411xC/E Reference Manual (RM0383)
- STM32F411xC/E Datasheet
- ARM Cortex-M4 Devices Generic User Guide