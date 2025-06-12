# The Dining Philosophers Problem
## How to run
Download `DPP.exe` from `cmake-build-debug` and just run it, that should do the trick.
After start, enter number of philosophers.
## Description
This program implements the classic Dining Philosophers Problem, which is a well-known synchronization problem in concurrent programming.

Each philosopher sits at a round table with one fork to their left and one to their right. To eat, a philosopher must pick up both forks. This implementation prevents deadlocks by using a `try_acquire()` approach: if a philosopher fails to acquire both forks, they release any acquired ones and retry after thinking for a while.

## Threads
### Threads used
- Each philosopher runs in a separate thread `(std::thread)`, created inside the `init()` method.
### Critical Sections and Solutions
- Fork access is synchronized using `std::binary_semaphore`.
- Each philosopher:
      1. Tries to acquire the left fork using `try_acquire()`.
      2. If successful, tries to acquire the right fork.
      3. If the right fork is unavailable, releases the left fork.
      4. If both forks are acquired, the philosopher eats and then releases both forks.


---
# Chat server
## How to run
Python 3 must be installed 
### Server
Navigate to the directory where `Server.py` is located. Then run: `python Server.py`

> ! If on Windows, **ESC** pressed should exit the program.


### Client
In a separate terminal, navigate to the directory where `Client.py` is located and run: `python Client.py`. You can run this multiple times, as the server accepts multiple connections.
After starting, enter your **nickname** and enjoy chatting.

## Description
The project implements a multithreaded chat server and client. The goal is to simulate a simple chat system where multiple clients can connect to the server, send messages, and receive messages from others in real-time.

The main challenge is to ensure safe and synchronized communication between threads that represent connected clients — especially when multiple clients are accessing shared resources like the list of connected clients or sending messages simultaneously.

## Threads
### Threads used
|Thread role|Description|
|:---|:---|
|Server-side client handler| 	Created for each newly connected client. Handles receiving and broadcasting messages.|
|Client-side receiver thread|Listens for incoming messages from the server and prints them.|

### Critical Sections and Solutions
1. Adding new client to `clients` dictionary:
   - Protected using a `lock` to avoid race conditions when multiple clients connect at the same time.
2. Broadcasting a message to all clients: 
   - Protected with `lock` to avoid modification of the dictionary while iterating over it. 
3. Removing disconnected client: 
   - Done with a `lock` to ensure no other thread is iterating or modifying it simultaneously.
