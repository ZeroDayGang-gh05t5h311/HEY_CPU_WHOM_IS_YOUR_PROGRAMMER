/*
=====================================================================
                ADVANCED C++ CHEAT SHEET
    Memory • Pointers • RAII • Stack vs Heap • Move Semantics
=====================================================================
This file is BOTH:
1) A working C++ program
2) A deep explanation of advanced C++ systems concepts
=====================================================================
                        MEMORY LAYOUT
=====================================================================
Typical program memory layout:
+----------------------+
|      TEXT SEGMENT    |  (Compiled instructions)
+----------------------+
|  GLOBAL / STATIC     |  (Initialized globals)
+----------------------+
|        BSS           |  (Uninitialized globals)
+----------------------+
|        HEAP          |  (Dynamic memory - grows upward)
|                      |
+----------------------+
|                      |
|        STACK         |  (Function calls - grows downward)
+----------------------+
STACK:
- Local variables
- Function parameters
- Automatic storage
- Fast, limited size
HEAP:
- Dynamic allocation
- Manual or smart management
- Flexible, slower
=====================================================================
*/

#include <iostream>
#include <memory>   // smart pointers
#include <cstring>

/*
=====================================================================
                        GLOBAL VARIABLES
=====================================================================
Stored in global/static memory segment
*/

int globalVar = 100;

/*
=====================================================================
                        REFERENCES
=====================================================================

A reference is an alias to an existing variable.

int x = 10;
int& ref = x;

- Cannot be null
- Cannot be reseated
- Safer than pointers in many cases
*/

void referenceDemo() {
    std::cout << "=== REFERENCES ===\n";

    int x = 10;
    int& ref = x;

    ref = 20;

    std::cout << "x after modifying ref: " << x << "\n\n";
}

/*
=====================================================================
                        RAW POINTERS
=====================================================================

Stores memory address.

Operators:
    &  -> address-of
    *  -> dereference

C++ still supports pointer arithmetic (like C).
*/

void pointerDemo() {
    std::cout << "=== RAW POINTERS ===\n";

    int x = 5;
    int* ptr = &x;

    std::cout << "Address of x: " << ptr << "\n";
    std::cout << "Value at ptr: " << *ptr << "\n";

    *ptr = 50;

    std::cout << "Modified x: " << x << "\n\n";
}

/*
=====================================================================
                        STACK VS HEAP
=====================================================================
*/

void stackVsHeap() {
    std::cout << "=== STACK VS HEAP ===\n";

    int stackVar = 10;          // Stack allocation

    int* heapVar = new int(20); // Heap allocation

    std::cout << "Stack: " << stackVar << "\n";
    std::cout << "Heap: " << *heapVar << "\n";

    delete heapVar;  // Must manually free raw pointer

    std::cout << "Heap memory freed\n\n";
}

/*
=====================================================================
                        RAII PRINCIPLE
=====================================================================

RAII = Resource Acquisition Is Initialization

Core idea:
- Resource tied to object lifetime
- Constructor acquires resource
- Destructor releases resource

This prevents memory leaks.
*/

class Resource {
public:
    Resource() {
        std::cout << "Resource acquired\n";
    }

    ~Resource() {
        std::cout << "Resource released\n";
    }
};

/*
=====================================================================
                        STRUCT VS CLASS
=====================================================================

Difference in C++:
- struct members default to PUBLIC
- class members default to PRIVATE

Otherwise almost identical.
*/

struct Person {
    std::string name;
    int age;
};

/*
=====================================================================
                        COPY vs MOVE SEMANTICS
=====================================================================

Copy:
    Duplicates resource

Move:
    Transfers ownership
    Leaves original in valid but empty state

Move constructor:
    ClassName(ClassName&& other)

Move is used for performance.
*/

class Buffer {
private:
    int* data;
    size_t size;

public:
    Buffer(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Buffer allocated\n";
    }

    // Destructor
    ~Buffer() {
        delete[] data;
        std::cout << "Buffer destroyed\n";
    }

    // Copy constructor (deep copy)
    Buffer(const Buffer& other) : size(other.size) {
        data = new int[size];
        std::memcpy(data, other.data, size * sizeof(int));
        std::cout << "Buffer copied\n";
    }

    // Move constructor
    Buffer(Buffer&& other) noexcept
        : data(other.data), size(other.size) {

        other.data = nullptr;  // prevent double free
        other.size = 0;

        std::cout << "Buffer moved\n";
    }
};

/*
=====================================================================
                        SMART POINTERS
=====================================================================

Modern C++ replaces raw new/delete with smart pointers.

1) unique_ptr
   - Single owner
   - Automatically deletes

2) shared_ptr
   - Reference counted
   - Deletes when last owner gone

3) weak_ptr
   - Non-owning reference
*/

void smartPointerDemo() {
    std::cout << "=== SMART POINTERS ===\n";

    std::unique_ptr<int> uptr = std::make_unique<int>(42);

    std::cout << "unique_ptr value: " << *uptr << "\n";

    std::shared_ptr<int> sp1 = std::make_shared<int>(100);
    std::shared_ptr<int> sp2 = sp1;  // shared ownership

    std::cout << "shared_ptr count: " << sp1.use_count() << "\n\n";
}

/*
=====================================================================
                        OBJECT LIFETIME
=====================================================================

Stack objects:
    Destroyed automatically when scope ends

Heap objects:
    Destroyed when delete is called
    Or automatically via smart pointers

Destructors run in reverse order of construction.
*/
/*
int main() {

    std::cout << "ADVANCED C++ SYSTEMS CHEAT SHEET\n\n";

    referenceDemo();
    pointerDemo();
    stackVsHeap();

    {
        Resource r;  // RAII demonstration
    }  // Destructor called here automatically

    std::cout << "\n=== STRUCT DEMO ===\n";
    Person p{"Alice", 30};
    std::cout << p.name << " " << p.age << "\n\n";

    std::cout << "=== COPY vs MOVE ===\n";
    Buffer b1(10);
    Buffer b2 = b1;           // copy
    Buffer b3 = std::move(b1); // move

    std::cout << "\n";
    smartPointerDemo();

    std::cout << "Global variable: " << globalVar << "\n";

    return 0;
} */

/*
=====================================================================
        EMBEDDED SYSTEMS + REVERSE ENGINEERING C++ CHEAT SHEET
=====================================================================

This file demonstrates low-level C++ concepts used in:

- Firmware development
- Bare-metal systems
- Microcontrollers
- Reverse engineering
- Exploit research
- Binary analysis

=====================================================================
                    MEMORY LAYOUT (IMPORTANT FOR RE)
=====================================================================

Typical layout in embedded system:

FLASH (ROM)
+----------------------+
|  Program Code (TEXT) |
+----------------------+

RAM
+----------------------+
|  .data  (initialized globals)
+----------------------+
|  .bss   (zeroed globals)
+----------------------+
|  Heap   (optional)
|         (grows up)
+----------------------+
|         |
|         |
|  Stack  (grows down)
+----------------------+

Stack frames are CRITICAL for reverse engineering.

=====================================================================
*/

#include <iostream>
#include <cstdint>
#include <cstring>

/*
=====================================================================
                        VOLATILE
=====================================================================

volatile tells compiler:
    "This memory may change unexpectedly."

Used for:
- Hardware registers
- Interrupt-modified variables
- Memory-mapped I/O

Without volatile:
    Compiler may optimize reads away.
*/

volatile uint32_t simulatedHardwareRegister = 0;

/*
=====================================================================
                MEMORY-MAPPED I/O (EMBEDDED STYLE)
=====================================================================

In real embedded systems:

#define GPIO_PORT (*(volatile uint32_t*)0x40020000)

Here we simulate it.
*/

volatile uint32_t* const GPIO_PORT =
    &simulatedHardwareRegister;

/*
=====================================================================
                        BIT MANIPULATION
=====================================================================

Common embedded patterns:

Set bit:
    reg |= (1 << n);

Clear bit:
    reg &= ~(1 << n);

Toggle bit:
    reg ^= (1 << n);

Check bit:
    reg & (1 << n);

*/

void bitManipulationDemo() {

    std::cout << "=== BIT MANIPULATION ===\n";

    *GPIO_PORT = 0;

    *GPIO_PORT |= (1 << 3);   // Set bit 3

    std::cout << "Register after setting bit 3: "
              << *GPIO_PORT << "\n";

    *GPIO_PORT ^= (1 << 3);   // Toggle bit 3

    std::cout << "Register after toggle: "
              << *GPIO_PORT << "\n\n";
}

/*
=====================================================================
                        ENDIANNESS
=====================================================================

Little Endian:
    Least significant byte first (x86, ARM default)

Big Endian:
    Most significant byte first

Reverse engineers must understand this.
*/

void endiannessDemo() {

    std::cout << "=== ENDIANNESS ===\n";

    uint32_t value = 0x12345678;
    uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&value);

    std::cout << "Memory bytes: ";
    for (int i = 0; i < 4; i++)
        std::cout << std::hex << (int)bytePtr[i] << " ";

    std::cout << std::dec << "\n\n";
}

/*
=====================================================================
                    STACK FRAME DEMO
=====================================================================

Each function call:
- Push return address
- Push parameters
- Allocate local variables

Understanding this is key for:
- Stack overflows
- ROP chains
- Debugging crashes
*/

void stackFrameExample(int a) {

    int localVar = a * 2;

    std::cout << "Address of parameter a: "
              << &a << "\n";

    std::cout << "Address of localVar: "
              << &localVar << "\n\n";
}

/*
=====================================================================
                    FUNCTION POINTERS
=====================================================================

Used heavily in:
- Interrupt tables
- Firmware jump tables
- Virtual dispatch
*/

typedef void (*ISR)();  // Interrupt Service Routine type

void interruptHandler() {
    std::cout << "Interrupt triggered!\n\n";
}

void functionPointerDemo() {

    std::cout << "=== FUNCTION POINTER ===\n";

    ISR handler = interruptHandler;

    handler();  // indirect call
}

/*
=====================================================================
                OBJECT MEMORY LAYOUT & VTABLE
=====================================================================

In polymorphic classes:

[ vptr ]  ---> points to VTABLE
[ data ]
[ data ]

Reverse engineers often:
- Locate vtable in .rodata
- Identify class hierarchy

*/

class Base {
public:
    virtual void greet() {
        std::cout << "Base greet\n";
    }
};

class Derived : public Base {
public:
    void greet() override {
        std::cout << "Derived greet\n";
    }
};

void vtableDemo() {

    std::cout << "=== VTABLE DEMO ===\n";

    Derived obj;
    Base* basePtr = &obj;

    basePtr->greet();  // Virtual dispatch

    std::cout << "Object address: " << &obj << "\n";
}

/*
=====================================================================
                    STRUCT ALIGNMENT & PADDING
=====================================================================

Compiler aligns members for performance.

Example:

struct Example {
    char a;    // 1 byte
    int b;     // 4 bytes
};

This may become 8 bytes total due to padding.
*/

struct AlignmentExample {
    char a;
    int b;
};

void alignmentDemo() {

    std::cout << "\n=== ALIGNMENT ===\n";
    std::cout << "Size of struct: "
              << sizeof(AlignmentExample)
              << "\n\n";
}

/*
=====================================================================
                    RAW MEMORY INSPECTION
=====================================================================

Reverse engineering often involves:
- Dumping memory
- Reinterpreting types
*/

void memoryInspectionDemo() {

    std::cout << "=== MEMORY INSPECTION ===\n";

    int x = 0x41424344;  // ASCII: ABCD
    unsigned char* ptr =
        reinterpret_cast<unsigned char*>(&x);

    for (int i = 0; i < sizeof(int); i++)
        std::cout << ptr[i] << " ";

    std::cout << "\n\n";
}

/*
=====================================================================
                                MAIN
=====================================================================
*/
int main() {
    std::cout << "EMBEDDED + REVERSE ENGINEERING C++ CHEAT SHEET\n\n";
    bitManipulationDemo();
    endiannessDemo();
    stackFrameExample(5);
    functionPointerDemo();
    vtableDemo();
    alignmentDemo();
    memoryInspectionDemo();
    return 0;
}
