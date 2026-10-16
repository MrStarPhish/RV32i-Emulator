
<img width="1870" height="909" alt="image" src="https://github.com/user-attachments/assets/ea115db2-c239-41e5-a9b5-88841709e07f" />
(The screenshot shows two Windows Consoles. The left one is running the Emulation Engine/System, and the right one is running the Dashboard: the state after each instruction. Both processes are synced via Shared Memory method of IPC. You can see the Memory Region at Bottom Right, with 8 ADD instructions lined up)

(Under Development)

# ===================

# RV32I Emulator & Debugger

An educational RISC-V emulator built to explore processor architecture, instruction execution, memory, and low-level debugging through implementation.

Developed incrementally alongside Computer Architecture studies, this project aims to execute RISC-V machine code while exposing the processor's internal state through a separate console-based debugging dashboard.

> **Status:** Work in progress. Initial execution engine and shared-memory dashboard integration established.

## Overview

Rather than treating the CPU as a black box, this project makes its internal state observable through a fetch–decode–execute workflow and a dedicated dashboard.

The initial architectural target is **RV32I**, the 32-bit base integer instruction set of RISC-V. The engine currently supports a subset of R-type instructions, while the dashboard provides a separate interface for inspecting processor state.

The project is being developed in two independently running programs:

- **Engine:** Owns the CPU, memory, instruction execution, and architectural state.
- **Dashboard:** Displays processor state independently of the engine's internal structures.
- **Shared memory:** Connects the two processes through a shared snapshot of the engine's state.

This separation establishes the foundation for expanding both instruction support and debugging functionality independently.

## Current Progress

### CPU and Memory

- [x] Basic CPU and memory structures
- [x] 32-bit instruction representation
- [x] Byte-addressable RAM
- [x] Little-endian word reads
- [x] Raw binary program-loading workflow
- [x] Initial fetch–decode–execute workflow
- [x] Instruction decoding and execution for a subset of R-type instructions
- [ ] Complete and test the remaining RV32I instruction groups

### Debugging Dashboard

- [x] Standalone console-based dashboard
- [x] Integer register display (`x0`–`x31`) with hexadecimal values and ABI aliases
- [x] Initial control-state display
- [x] Dashboard rendering decoupled from the engine's `SYSTEM` object
- [x] Shared-memory integration between the engine and dashboard
- [ ] Complete stack memory inspection
- [ ] Expand the control and instruction-details panels
- [ ] Add instruction stepping and execution history
- [ ] Add general memory inspection commands

The dashboard can now operate as a separate process and receive processor-state snapshots through shared memory. Snapshot synchronization and additional debugging controls remain areas for further development.

*The checklist reflects the current implementation checkpoint, not complete RV32I compatibility.*

## Design Goals

### 1. CPU Emulation

Implement the core mechanisms of a 32-bit RISC-V processor, including:

- General-purpose registers and the program counter
- Instruction fetching, decoding, and execution
- Arithmetic, logical, memory, and control-flow instructions
- Byte-addressable memory and little-endian data access
- Architectural rules such as `x0` always reading as zero

### 2. Debugging and Observability

Develop a dashboard that makes processor state inspectable without directly depending on the engine's internal objects.

Planned capabilities include:

- Register and control-state inspection
- Current and next instruction visibility
- Stack and general memory inspection
- Instruction-level stepping
- Execution history and undo support
- Decoded instruction-field visualization

### 3. Inter-Process Communication

Use shared memory to exchange a defined snapshot of processor state between the engine and dashboard.

The intended design keeps the engine authoritative over execution while allowing the dashboard to consume snapshots and render the state independently.

Future improvements may include synchronized snapshot access, version-based change detection, and command communication between the two processes.

### 4. Exploring Computer Architecture

Once the basic execution model is stable, the project may expand to explore:

- Memory hierarchy and caching
- Pipeline execution
- Performance measurements and architectural trade-offs

These are future goals, not features of the current implementation.

## Technology

- **Language:** C++
- **Architecture target:** RISC-V RV32I
- **Interface:** Windows console with character-buffer-based dashboard rendering
- **Development environment:** Visual Studio
- **Program tooling:** RISC-V GNU toolchain, with a WSL/Linux workflow for assembling and converting test programs
- **Inter-process communication:** Windows shared memory through file-mapping APIs

## Project Scope

This is an educational project focused on understanding how processor instructions, registers, and memory interact. It is not intended to replace production-grade RISC-V emulators.

The implementation prioritizes correctness, clarity, and inspectable execution before introducing more advanced architectural features.

## Roadmap

- [x] Establish the CPU and memory structures
- [x] Implement the initial fetch–decode–execute workflow
- [x] Implement an initial subset of R-type instructions
- [x] Build the initial dashboard panels
- [x] Run the engine and dashboard as separate processes
- [x] Integrate shared-memory state snapshots
- [ ] Expand and test R-type instruction coverage
- [ ] Implement and test additional RV32I instruction formats
- [ ] Complete stack and memory inspection
- [ ] Improve snapshot synchronization and change detection
- [ ] Add instruction stepping and execution history
- [ ] Implement Memory Based Display and I/O buffer
- [ ] Emulate relevant synchronous interrupts
- [ ] Implement memory hierarchy experiments
- [ ] Explore pipeline modeling and performance visualization
- [ ] Implement Command Parsing from Dashboard to Engine. i.e /step, /undo
- [ ] Integrate /emit functionality, to inject a minimal instruction. Then a short function...naturally making the next plans coherent with upcoming Compiler Construction course.

## Motivation

The purpose of this project is to move beyond studying processor architecture theoretically and implement its mechanisms directly: how instructions are represented, fetched, decoded, and executed, and how they affect registers and memory.

Separating the execution engine from the debugging dashboard is an important step toward making the emulator easier to inspect, extend, and experiment with as the project develops.
