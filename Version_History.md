# Version history

## Version 2.3 (November 2026)
- New: Windows and Linux version, written in C++ with Qt 6 (directory `src/Qt`), with the same functionality as the macOS version. The communication with the Lenz interface(s) uses the XpressNetQt library; a single TCP connection is used if the same interface is used for sending and for feedback. The IP addresses are stored in the settings of the program. The Windows version is an x64 program, that also runs on Windows 11 on ARM. As the macOS version, it accepts the answers to PoM verify messages via RS-Bus address 128 (newer decoders) and via the RS-Bus address of the decoder itself (older decoders).
- A non-initialised decoder (RS-Bus address 0, PoM address 6000) is reported in the status line, and the Initialise tab is shown. The address field is empty at startup; SELECT with an empty address field searches again for a non-initialised decoder.
- Relays tab: the range of relays addresses depends on the command station: 1..2048 for command station software 3.8 or higher, otherwise 1..1024.
- Sensitivity tab: Min_Samples (CV33) can be set to 1..8 (was 1..7), as accepted by the decoder. SET no longer changes the colour of the SET button of the Control tab.
- Speed tab: the explanation gives the track numbers the decoder accepts: 2..7 (0 = no measurement).
- Corrected texts: "Accessory" (Relays tab), "Switch decoder" (decoder type), the title of the preferences window and some typing errors. The help pages describe the accessory addresses up to 2048, and the single TCP connection of the Windows and Linux versions.
- Repository: new structure, with the source code in `src` (`src/Xcode` for macOS, `src/Qt` for Windows and Linux), the compiled programs in `Compiled-Applications` and the manual in `Manual`. The README and the manual are in English, German and Dutch.

## Version 2.0 (October 2026)
- Updated to Xcode 26; universal binary (Apple silicon and Intel); requires macOS 12 or later.
- TCP connections via Apple's Network framework, instead of the NSStream functions that Apple will deprecate. The program no longer hangs if a Lenz interface does not respond.
- The connection is made again when an RS-Bus address is entered or SELECT is pressed.
- XpressNet keep-alive for the Lenz interface(s) every 10 seconds.
- The program now waits up to 1 second (was 0.25 seconds) for the RS-Bus answer to a CV read, which is enough for a fully loaded RS-Bus.
- Reverser tab: the feedback bits are now shown as RS-Bus inputs 1..8. Before, the CV value (0..7) was shown, while a selected value was stored one too high (selecting 8 resulted in an invalid value).
- CV tab: resetting all CVs also resets the RS-Bus address (CV10 becomes 0); the text on the tab now says so. After a reset the program no longer tries to read the CVs at the old address.
- User interface adapted to current macOS versions.
- Several small bug fixes in the communication with the Lenz interface(s).

Earlier versions: see the commit history.
