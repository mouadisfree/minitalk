# minitalk - My Signal Communication System


*My inter-process communication project*
---
## What is this?
**minitalk** is a communication system between processes using signals that I wrote myself. It's a school project that helps me learn how processes talk to each other and how UNIX signals work. I'll use this knowledge in other system projects later.

---

## What I Built

### Communication Programs
- **Server**: `server` - receives and displays messages
- **Client**: `client` - sends messages to server
- **Signal Handling**: `SIGUSR1`, `SIGUSR2` - binary communication

### Signal Functions
- **Message Sending**: convert text to binary signals
- **Message Receiving**: decode binary signals to text
- **Process Communication**: find and talk to other processes

### Bonus Features
- `Unicode support`: Send any character including emojis
- `Acknowledgment`: Server confirms message received
- `Multiple clients`: Handle several clients at once

---

## How to use it

### What you need
To use this communication system, you need:
- A C compiler (like `gcc`) to turn code into programs.
- A computer with Linux or macOS.

### How to set it up
1. Download the code:
   ```bash
   git clone git@github.com:mouadisfree/minitalk.git
   cd minitalk


2. Build the programs:
   ```bash
   make
   ```

   This makes two programs: `server` and `client` for communication.

---

## Who made this
Made by **mouadisfree** as a student at **1337 School** (part of the 42 coding schools).

---

## Thanks
Thanks to 1337 School and all my peers who helped me learn!