
<img width="1325" height="750" alt="image" src="https://github.com/user-attachments/assets/69486aa0-bcc1-4033-a458-92b8a353b6c5" />
(Under Development)
# ===================
# RV32I Emulator & Debugger

An educational RISC-V emulator built to explore processor architecture, instruction execution, memory, and low-level debugging through implementation.

This project is being developed incrementally alongside my Computer Architecture studies. The goal is to build a system that can load and execute RISC-V machine code while exposing the internal state of the processor through a console-based debugging dashboard.

> **Status:** Work in progress . early development.

## Overview

Rather than treating the CPU as a black box, this project aims to make its behavior observable. The emulator is designed around a fetch–decode–execute workflow, with a dashboard for inspecting registers, control state, and memory.

The initial target is **RV32I**, the 32-bit base integer instruction set of RISC-V. More advanced architectural features will be explored as the core implementation develops.

## Current Progress

### Implemented / Under Development

* [x] Basic CPU and memory model
* [x] 32-bit instruction representation
* [x] Byte-addressable RAM with little-endian word reads
* [x] Instruction decoding for the `ADD` instruction
* [x] Initial fetch–decode–execute implementation
* [x] Raw binary program loading workflow
* [x] Console dashboard using a fixed character buffer
* [x] Integer register display (`x0`–`x31`) with hexadecimal values and ABI aliases
* [x] Initial control-state display
* [ ] Stack memory viewer and related inspection commands

*The checklist reflects the current development state and will be updated as features are completed and tested.*

## Design Goals

### 1. CPU Emulation

Model the core components of a 32-bit RISC-V processor, including:

* General-purpose registers and the program counter
* Instruction fetching and decoding
* Instruction execution and control flow
* Memory access
* Architectural rules such as `x0` always reading as zero

### 2. Debugging and Observability

Build a console-based interface that makes the machine state visible while a program executes.

Planned debugging capabilities include:

* Inspecting registers and CPU state
* Stepping through instructions
* Undoing recent execution steps
* Emitting instructions for testing
* Inspecting stack memory and general memory contents
* Viewing decoded instruction fields
* Tracking execution history

### 3. Exploring Computer Architecture

Once the basic execution model is stable, the project may expand to explore concepts such as:

* Memory hierarchy and caching
* Pipeline execution
* Performance measurements and architectural trade-offs

These are future goals, not features of the current implementation.

## Technology

* **Language:** C++
* **Architecture target:** RISC-V RV32I
* **Interface:** Windows console with a character-buffer-based dashboard
* **Development environment:** Visual Studio
* **Program tooling:** RISC-V GNU toolchain, with a WSL/Linux workflow for assembling and converting test programs

## Project Scope

This is an educational project focused on understanding how processor instructions, registers, and memory interact. It is not intended to replace production-grade RISC-V emulators.

The implementation will prioritize correctness, clarity, and inspectable execution before adding more advanced architectural features.

## Roadmap

* [x] Establish the CPU and memory structures
* [x] Implement initial instruction decoding
* [x] Build the first dashboard panels
* [ ] Complete and test the initial instruction execution loop
* [ ] Expand RV32I instruction coverage
* [ ] Improve stack and memory inspection
* [ ] Add instruction-level debugging and execution history
* [ ] Implement memory hierarchy experiments
* [ ] Explore pipeline modeling and performance visualization

## Motivation

The purpose of this project is to move beyond learning processor architecture theoretically and implement the mechanisms directly: how instructions are represented, fetched, decoded, and executed, and how they affect registers and memory.

The project will evolve as I study more of Computer Architecture and gain a deeper understanding of the underlying system.
