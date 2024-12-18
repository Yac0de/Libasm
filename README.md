# Assembly Language Basics - libasm Project

---

## **Table of Contents**
1. [Project Overview](#1-project-overview)
2. [Project Structure](#2-project-structure)
3. [How to Use This Project](#3-how-to-use-this-project)
4. [Expectations and Important Guidelines](#4-expectations-and-important-guidelines)
5. [Registers Overview](#5-registers-overview)
6. [Assembly Directives](#6-assembly-directives)
7. [Common Assembly Instructions](#7-common-assembly-instructions)
8. [System Calls (Linux x86-64)](#8-system-calls-linux-x86-64)

---

## **1. Project Overview**

The `libasm` project involves implementing standard C functions in assembly language using NASM. The primary goal is to understand low-level programming concepts such as registers, memory management, system calls, and function conventions.

---
## **2. Project Structure**

```bash
.
├── Makefile
├── README.md
├── ft_read.s
├── ft_strcmp.s
├── ft_strcpy.s
├── ft_strdup.s
├── ft_strlen.s
├── ft_write.s
└── tests
    ├── test_ft_read.c
    ├── test_ft_strcmp.c
    ├── test_ft_strcpy.c
    ├── test_ft_strdup.c
    ├── test_ft_strlen.c
    ├── test_ft_write.c
    └── test_libasm.c
```
---
## **3. How to Use This Project**

### **Environment Setup:**

  - **Install Required Tools:**
   ```sh
   sudo apt update
   sudo apt install nasm gcc make
   ```

### **Building the Library:**

Run the following command to compile the library:

```sh
make
```

### **Running the Tester:**

To test the implemented functions, run:

```sh
make test_libasm
```

This compiles and runs all tests.

### **Testing Individual Functions:**

You can also run specific function tests using:

```sh
./test_libasm <function_name>
```

Example:

```sh
./test_libasm ft_strlen
```
---

## **4. Expectations and Important Guidelines**

The `libasm` project comes with specific constraints that must be respected to ensure proper functionality and compatibility. Below are the critical requirements and how to address them:

### **1. No `-no-pie` Compilation Flag**

- **What It Means:**

  - Position-Independent Executables (PIE) ensure that compiled binaries can be loaded at any memory address, making the program more secure.
  - Disabling PIE with `-no-pie` is **forbidden**.

- **How We Addressed It:**

  - Use **Position-Independent Code (PIC)** syntax when calling external functions.
  - Example:
    ```assembly
    call [rel __errno_location wrt ..got]
    call malloc wrt ..plt
    ```
  - **Why This Works:**
    - Using `rel ... wrt ..got` ensures compatibility with PIE by referencing addresses **relatively** through the **Global Offset Table (GOT)**.
    - `malloc wrt ..plt` uses the **Procedure Linkage Table (PLT)** for dynamic linking at runtime.

### **2. Properly Setting errno**

- **What It Means:**

  - If a function fails, the global variable `errno` must be set to the corresponding error code.

- **Allowed Methods:**

  - The project allows calling:
    - `__errno_location` (Linux) or `___error` (macOS) as external functions.

*Tip: You can inspect the system's standard C library to confirm the availability of these functions using the following command:*

```sh
objdump -T /usr/lib/x86_64-linux-gnu/libc.so.6 | grep errno_location
```

*This will display information about the `__errno_location` symbol, indicating its address and availability in the linked C library.*

- **How We Implemented It:**

  ```assembly
  ; Example from ft_write implementation
  mov rax, -1                  ; Indicate failure
  mov rdi, error_code          ; Load the error code
  call [rel __errno_location wrt ..got] ; Get errno address
  mov [rax], edi               ; Set errno
  ret
  ```

  - **Why This Works:**
    - Calling `__errno_location` returns the address where `errno` is stored.
    - The code then writes the corresponding error code to this address, fulfilling the project requirement.

---

## **5. Registers Overview**

Registers are small, fast memory locations within the CPU. Understanding how to use them is crucial for writing efficient assembly code.

### **General Purpose Registers (64-bit)**

**Caller vs Callee Explained:**

- **Caller-Saved Registers:** Registers that the calling function must save if needed (`rax`, `rcx`, `rdx`, `rsi`, `rdi`, `r8-r11`). If a called function overwrites these, the caller is responsible for preserving their values.
- **Callee-Saved Registers:** Registers that the called function must save and restore (`rbx`, `rbp`, `r12-r15`, `rsp`). If a function uses these registers, it must restore their original values before returning.

| Register  | Meaning                     | Purpose                        | Preservation |
| --------- | --------------------------- | ------------------------------ | ------------ |
| `rax`     | Accumulator Register        | Return value, calculations     | Caller       |
| `rbx`     | Base Register               | General-purpose, preserved     | Callee       |
| `rcx`     | Counter Register            | Loop counter, argument 4       | Caller       |
| `rdx`     | Data Register               | Argument 3, I/O data           | Caller       |
| `rsi`     | Source Index                | Argument 2 (source)            | Caller       |
| `rdi`     | Destination Index           | Argument 1 (destination)       | Caller       |
| `r8-r9`   | Extended Registers          | Arguments 5-6                  | Caller       |
| `r10-r11` | Temporary Registers         | Temporary, system calls        | Caller       |
| `r12-r15` | Preserved General Registers | Preserved for important values | Callee       |
| `rbp`     | Base Pointer                | Frame pointer (stack base)     | Callee       |
| `rsp`     | Stack Pointer               | Current stack pointer          | Callee       |

### **Caller-Saved Registers Summary**

| Register | Usage                 |
| -------- | --------------------- |
| `rax`    | Return value          |
| `rcx`    | Argument 4, Counter    |
| `rdx`    | Argument 3, I/O data  |
| `rsi`    | Argument 2, Source pointer  |
| `rdi`    | Argument 1, Destination pointer  |
| `r8-r11` | Argument 5,6 ..., Extra arguments/temp. |

### **Callee-Saved Registers Summary**

| Register  | Usage                        |
| --------- | ---------------------------- |
| `rbx`     | General-purpose, preserved   |
| `rbp`     | Stack frame base pointer     |
| `rsp`     | Stack pointer (auto-managed) |
| `r12-r15` | General-purpose, preserved   |

### **Register Size Extensions**

Registers can be accessed in different sizes depending on the operation. This is useful for operations involving smaller data sizes.

| Register | 64-bit | 32-bit | 16-bit | 8-bit High | 8-bit Low |
|----------|--------|--------|--------|------------|-----------|
| `rax`    | `rax`  | `eax`  | `ax`   | `ah`       | `al`      |
| `rbx`    | `rbx`  | `ebx`  | `bx`   | `bh`       | `bl`      |
| `rcx`    | `rcx`  | `ecx`  | `cx`   | `ch`       | `cl`      |
| `rdx`    | `rdx`  | `edx`  | `dx`   | `dh`       | `dl`      |
| `rsi`    | `rsi`  | `esi`  | `si`   | *(N/A)*    | *(N/A)*   |
| `rdi`    | `rdi`  | `edi`  | `di`   | *(N/A)*    | *(N/A)*   |
| `rsp`    | `rsp`  | `esp`  | `sp`   | *(N/A)*    | *(N/A)*   |
| `rbp`    | `rbp`  | `ebp`  | `bp`   | *(N/A)*    | *(N/A)*   |

### **Why Use Register Extensions?**

- **Example in `strcpy`:**
  - In `ft_strcpy`, we used `al` because we only needed to load a single byte from memory.
  - Example:
    ```assembly
    mov al, byte [rsi]   ; Load 1 byte from source string
    mov byte [rdi], al   ; Store 1 byte into destination string
    ```

By using `al` instead of `rax`, we avoid unnecessary operations on larger registers, making the code more efficient and easier to manage.

Registers are small, fast memory locations within the CPU. Understanding how to use them is crucial for writing efficient assembly code.

### **Flags Overview**

Flags are special registers used to store the result of arithmetic and logical operations. They help control the flow of programs by influencing conditional jumps and function behavior.

| Flag Name | Description                | Purpose                        |
|-----------|----------------------------|-------------------------------|
| `ZF`     | Zero Flag                  | Set if result is zero         |
| `SF`     | Sign Flag                  | Set if result is negative     |
| `CF`     | Carry Flag                 | Set if unsigned overflow      |
| `OF`     | Overflow Flag              | Set if signed overflow        |
| `PF`     | Parity Flag                | Set if result has even parity |
| `AF`     | Auxiliary Carry Flag       | Used in binary-coded math     |

Example (Using Flags for Comparison):
```assembly
cmp rax, rbx       ; Compare rax and rbx
je equal_label     ; Jump if equal (ZF = 1)
jl less_label      ; Jump if less (SF ≠ OF)
jg greater_label   ; Jump if greater (SF = OF)
```

These flags ensure that conditional jumps and decisions are executed correctly based on the results of previous instructions.

---

## **6. Assembly Directives**

Assembly directives are special instructions used by the assembler to control how the code is organized, compiled, and linked. These directives do not generate machine code but influence the assembler's behavior.

### **Common Assembly Directives Explained:**

- **`section .text`**: Defines the code section where executable instructions are placed. This section is usually marked as read-only and contains the program's main logic.
- **`section .data`**: Contains initialized data such as constants, strings, and variables with predefined values.
- **`section .bss`**: Holds uninitialized variables. These variables are initialized to zero when the program starts.
- **`global <name>`**: Exports a function or variable, making it accessible from other files during linking.
- **`extern <name>`**: Declares an external function or variable, indicating that it is defined in another file.

| Directive       | Purpose                 |
| --------------- | ----------------------- |
| `section .text` | Code (instructions)     |
| `section .data` | Initialized variables   |
| `section .bss`  | Uninitialized variables |
| `global <name>` | Export function         |
| `extern <name>` | Import function         |

---

## **7. Common Assembly Instructions**

| Instruction    | Meaning                   |
| -------------- | ------------------------- |
| `mov dst, src` | Move `src` to `dst`       |
| `add dst, src` | Add `src` to `dst`        |
| `sub dst, src` | Subtract `src` from `dst` |
| `mul src`      | Multiply `rax` by `src`   |
| `div src`      | Divide `rax` by `src`     |
| `inc dst`      | Increment `dst` by 1      |
| `dec dst`      | Decrement `dst` by 1      |
| `cmp a, b`     | Compare `a` and `b`       |
| `jmp label`    | Jump to `label`           |
| `call func`    | Call `func`               |
| `ret`          | Return from function      |

---

## **8. System Calls (Linux x86-64)**

System calls are low-level functions provided by the operating system that allow programs to interact with hardware and perform essential tasks such as reading from or writing to files.

To make a system call, the appropriate syscall number is placed in the `rax` register, and the required arguments are passed using specific registers (`rdi`, `rsi`, `rdx`, etc.). After setting these values, the `syscall` instruction triggers the system call, and the return value is stored in `rax`.

### **Common System Calls**

| Syscall Name | Syscall No | `rax`  | `rdi` | `rsi` | `rdx` |
| ------------ | ---------- | ------ | ----- | ----- | ----- |
| `read`       | 0          | fd     | buf   | count |       |
| `write`      | 1          | fd     | buf   | count |       |
| `exit`       | 60         | status | —     | —     |       |

### **Reference:**
👉 You can see the complete system call table at:  
🔗 [Linux Syscalls Table - w3challs](https://syscalls.w3challs.com/)

### **Example: Write System Call**

```assembly
section .data
msg db "Hello, World!", 10

section .text
global _start

_start:
    mov rax, 1              ; Syscall number for write
    mov rdi, 1              ; File descriptor (stdout)
    mov rsi, msg            ; Buffer address
    mov rdx, 13             ; Number of bytes to write
    syscall                 ; Perform the system call

    mov rax, 60             ; Syscall number for exit
    xor rdi, rdi            ; Exit code 0
    syscall
```

This example demonstrates how to use the `write` system call to display text on the console and then exit the program using the `exit` system call.

Registers are small, fast memory locations within the CPU. Understanding how to use them is crucial for writing efficient assembly code.

###
