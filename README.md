# Corex NT

**Corex NT** is an independent x86-64 operating system project developed by **The Corex Team**.

The goal of Corex NT is to build a modern, modular operating system with an architecture inspired by the ideas behind NT-style systems: a clear separation between the kernel, executive services, hardware abstraction, user-mode APIs, and the desktop environment.

> **Corex NT is an independent project. It does not contain Microsoft source code or proprietary Windows binaries.**

## Architecture

The long-term architecture is planned around several major layers:

```text
┌─────────────────────────────────────────────┐
│                 Corex Desktop               │
│          Shell / Explorer / Settings        │
├─────────────────────────────────────────────┤
│                 Corex Userland              │
│       Corex API / Compatibility APIs        │
├─────────────────────────────────────────────┤
│               Corex Executive               │
│ Process │ Memory │ I/O │ Security │ IPC    │
│ Object  │ Config │ Filesystem               │
├─────────────────────────────────────────────┤
│                    HAL                      │
├─────────────────────────────────────────────┤
│                Corex Kernel                 │
├─────────────────────────────────────────────┤
│                  Hardware                   │
└─────────────────────────────────────────────┘
```

The architecture is intended to keep low-level hardware mechanisms separate from higher-level operating-system services.

## Current Status

Corex NT is currently in **early kernel development**.

Current functionality includes:

* x86-64 kernel
* Limine-based boot process
* UEFI boot through QEMU/OVMF
* Higher-half kernel layout
* Limine framebuffer initialization
* Basic framebuffer console subsystem
* Pixel rendering
* Rectangle rendering
* Freestanding C runtime memory functions
* Initial kernel/module structure

The current graphical milestone is simple but important:

```text
Framebuffer
    ↓
Corex Console
    ↓
Pixel primitive
    ↓
Rectangle primitive
```

The next console milestones are:

```text
Bounds checking
    ↓
Bitmap font
    ↓
Glyph rendering
    ↓
Character rendering
    ↓
String rendering
    ↓
Cursor / newline / scrolling
```

## Planned Kernel Components

The kernel and executive are intended to eventually contain:

* Scheduler
* Thread management
* Process management
* Virtual memory manager
* Physical memory manager
* Kernel heap
* Interrupt management
* System-call interface
* Object manager
* I/O manager
* Security manager
* IPC subsystem
* Configuration manager
* Filesystem/VFS layer
* Device manager
* Driver infrastructure
* Networking
* Hardware abstraction layer

## Security

Security is a core design consideration rather than an afterthought.

Planned security mechanisms include:

* User/kernel privilege separation
* Access tokens
* ACL-based authorization
* Address Space Layout Randomization (ASLR)
* DEP/NX
* Stack protection
* Least-privilege services
* Sandboxing
* Code-signing infrastructure
* Secure update mechanisms
* Secure Boot support

These features will be implemented independently as the kernel architecture matures.

## Development

The initial development target is:

* **Architecture:** x86-64
* **Platform:** QEMU
* **Firmware:** UEFI / OVMF
* **Bootloader:** Limine
* **Kernel language:** C
* **Assembly:** x86-64 where required
* **Higher-level components:** C++ where appropriate
* **Build system:** GNU Make

The project is developed primarily on Linux.

## Project Structure

```text
corex-nt/
├── kernel/
│   ├── linker-scripts/
│   └── src/
│       ├── console/
│       ├── main.c
│       ├── memory.c
│       └── memory.h
├── limine-binary/
├── edk2-ovmf-bins/
├── GNUmakefile
├── limine.conf
├── LICENSE
└── README.md
```

## Building

Clone the repository:

```bash
git clone git@github.com:The-Corex-Team/Corex-NT.git
cd Corex-NT
```

Build the kernel and bootable image:

```bash
make
```

Run Corex NT in QEMU:

```bash
make run
```

The project currently targets development and experimentation rather than production hardware.

## Design Philosophy

Corex NT is built around a few principles:

**Understandability**

Operating-system components should have clear responsibilities and interfaces.

**Modularity**

The kernel, executive, drivers, userland and desktop should remain separate wherever practical.

**Performance**

The system should avoid unnecessary abstraction overhead in performance-critical paths.

**Security**

Security should be designed into the architecture from the beginning.

**User control**

The operating system should give users meaningful control over their system and data.

**Independent implementation**

Corex NT is implemented independently and does not depend on proprietary Windows implementation code.

## Roadmap

### Phase 1 — Kernel Foundation

* [x] Boot kernel with Limine
* [x] x86-64 kernel entry
* [x] Higher-half kernel
* [x] Framebuffer initialization
* [x] Pixel rendering
* [x] Rectangle rendering
* [ ] Safe framebuffer primitives
* [ ] Bitmap font
* [ ] Kernel console
* [ ] Physical memory manager
* [ ] Virtual memory manager
* [ ] Interrupt subsystem
* [ ] Kernel heap
* [ ] System-call mechanism

### Phase 2 — Core Executive

* [ ] Process manager
* [ ] Thread scheduler
* [ ] Object manager
* [ ] IPC
* [ ] I/O manager
* [ ] Configuration manager
* [ ] Security manager
* [ ] Driver infrastructure

### Phase 3 — Userland

* [ ] User-mode initialization
* [ ] Core system services
* [ ] Corex API
* [ ] Command shell
* [ ] Filesystem support
* [ ] Networking

### Phase 4 — Desktop

* [ ] Window manager
* [ ] GUI toolkit
* [ ] Corex Desktop
* [ ] File manager
* [ ] System settings
* [ ] System administration tools

### Phase 5 — Compatibility

* [ ] Compatibility API foundation
* [ ] Win32-compatible API surface
* [ ] PE/COFF executable support
* [ ] Compatibility runtime
* [ ] Application compatibility layer

Compatibility functionality will be implemented independently.

## Contributing

Corex NT is an experimental operating-system project.

Contributions, technical discussion, testing, documentation, and architectural ideas are welcome.

Before contributing significant architectural changes, please discuss the design first so that the project remains coherent as the kernel grows.

## License

See [`LICENSE`](LICENSE) for the license applicable to this repository.

## The Corex Team

Corex NT is developed by **The Corex Team**.

The project is part of the broader Corex ecosystem of open-source software and operating-system projects.

---

**Corex NT — Building an operating system from the ground up.**

