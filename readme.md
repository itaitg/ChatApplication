# 📡 C++ Chat Application

A lightweight **TCP-based chat system** built with C++ using sockets and multithreading. Supports multiple clients, usernames, and real-time messaging.


## Features 🚀
✔ **Multi-Client Support** (Threaded)  
✔ **Username assignment**   
✔ **Broadcast messaging**   

## Future Upgrades 🔮
- [ ] **Command system** (`/quit`, `/users`)  
- [ ] **Cross-platform** (Linux/Windows with adaptations)
- [ ] **GUI version** (Qt/SDL)
- [ ] **Encrypted messaging** (SSL/TLS)
- [ ] **Private messages** (`/msg <user> <text>`)
- [ ] **Persistent chat history** (File logging)
- [ ] **Emoji reactions**


## How to Run ▶️
### **Prerequisites**
- Linux (or WSL for Windows)
- `g++` and `make`

### **Compile & Run**
```sh
# Clone the repo
git clone https://github.com/itaitg/ChatApplication.git
cd ChatApplication

# Compile (uses Makefile)
make

# Start the server (in one terminal)
./server

# Start clients (in other terminals)
./client