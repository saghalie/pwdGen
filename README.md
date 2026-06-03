# pwdGen

pwdGen is a small password generator for Amiga OS 1.3. It opens a custom Intuition screen and lets the user generate passwords with 4, 6, or 8 characters.

The project is written in C and uses AmigaOS 1.3 era headers, gadgets, menus, requesters, and screen/window structures.

## Features

- Generates 4, 6, or 8 character passwords.
- Uses digits, lowercase letters, uppercase letters, and symbols.
- Provides About and Quit requesters.
- Designed for Amiga OS 1.3 and the classic Amiga NDK.

## Repository Contents

- `pwdGen.c` - main application source and password generation logic.
- `pwdMain.h` - main window, gadgets, menu, palette, and text layout.
- `pwdAbout.h` - About requester definition.
- `pwdQuit.h` - Quit requester definition.
- `pwdColors.h` - palette color indexes.
- `pwdGen_rev.h` - version metadata.
- `GUI/pwdGen.pw` - original PowerWindows project data.

## Building

This project targets Amiga OS 1.3. A modern desktop compiler can do a limited syntax check if the Amiga NDK 1.3 headers are available, but a real build should use an Amiga-compatible compiler/toolchain.

Example syntax check on Windows with MinGW and local NDK headers:

```powershell
gcc -fsyntax-only -I C:\mnt\NDK_1.3\INCLUDES1.3\INCLUDE.H pwdGen.c
```

The old NDK headers may emit warnings with modern GCC, especially around historical `#endif` comments and missing library prototypes.

## License

This project is licensed under the GNU General Public License v3.0. See `LICENSE` for the full license text.

## Disclaimer

This software is provided as-is, without warranty of any kind. Use it at your own risk.
