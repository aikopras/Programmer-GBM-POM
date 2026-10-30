# Programmer-GBM-POM (macOS)
Program to initialise the Gleis Besetz Meldung (GBM)

This program allows the initialisation (by reading and modifying CV variables) of the [occupancy detection (feedback) / Gleis Besetz Meldung decoder](https://github.com/aikopras/OPENDECODER22GBM). This decoder sends feedback messages via the RS-Bus and can, for initialisation purposes but also to switch relays, listen to DCC commands. Given that it uses RS-Bus messages for feedback, the decoders will primarily be interesting in environments with LENZ Master stations (like the LZV 100) connected via the LAN/USB interface (23151).<BR>
The program is written for macOS; the executable can be [downloaded directly](/Compiled%20Application/Programmer%20GBM-POM.zip) or can be compiled from scratch using Xcode (see below).<BR>

## Requirements ##
- macOS 12 (Monterey) or later.
- Universal binary: runs natively on Apple silicon Macs and on Intel Macs.
- One or two Lenz LAN/USB interfaces (23151).

## Installation ##
1. Download [Programmer GBM-POM.zip](/Compiled%20Application/Programmer%20GBM-POM.zip), unzip it and move the application to the Applications folder.
2. The application is not notarized by Apple, so macOS blocks it the first time it is opened. To allow it, open System Settings → Privacy & Security (on macOS 12: System Preferences → Security & Privacy → General) and click "Open Anyway".
3. On recent macOS versions the system may ask whether the application may access devices on the local network. Allow this; otherwise the TCP connections to the Lenz interface(s) fail.

## Main screen ##
After startup the program shows its main screen. After entering the current RS-Bus address of the decoder all CV values are being downloaded from the decoder. Screenshots for the other tabs can be seen [here](/Screenshots/).
![Main](/Screenshots/Main.png)

## How does the program work? ##
To initialise and modify the decoder's Configuration Variables (CVs) the program sends Programming on the Main (PoM) messages. Since the XPressNet specification supports PoM messages only for train decoders (but not for accessory / feedback decoders), the "trick" the GBM decoder uses is to listen to the loco address equal to the <I>RS-Bus address + 6000</I>.<BR>
The requested CV values are send back via the RS-Bus.

The program communicates with the LENZ Master station via the LAN/USB interface (23151). If different master stations are used for DCC commands and RS-Bus feedback messages, two LAN/USB interfaces may be used. The IP address(es) of the LAN interfaces can be entered via the program preferences.<BR>
![Main](/Screenshots/Preferences.png)

## Connections to the Lenz interface(s) ##
When the program starts, it connects to the Lenz interface(s). If an interface does not respond within 3 seconds (for example because it is switched off), the program stops trying and shows this in the status line. The connection is made again as soon as an RS-Bus address is entered (followed by Return) or SELECT is pressed; if the connection already exists, nothing changes.

As described in the Lenz specification of the LAN/USB Interface 23151 (section 2.1), the interface stops sending broadcasts (including the RS-Bus feedback messages) to a LAN device it has not heard from for some time. Therefore the program sends the XpressNet "Interface Status" command every 10 seconds, but only when no other command is pending. If an interface does not answer within 5 seconds, the connection is closed and this is shown in the status line.

## Building from source ##
Open `Programmer GBM-POM.xcodeproj` in Xcode 26 or later. The Release configuration (for example via Product → Build For → Profiling, or Product → Archive) produces a universal binary for Apple silicon and Intel. The help files are described in [Helpfiles/readme.txt](/Helpfiles/readme.txt).

The TCP connections are handled by `TCPSocketClass` (`TCPSocket.h` / `TCPSocket.m`), which is based on Apple's Network framework. This class contains no DCC, RS-Bus or Lenz specific code; the same class is used in [OSX-DCC-Monitor](https://github.com/aikopras/OSX-DCC-Monitor) and [Programmer-Decoder-POM](https://github.com/aikopras/Programmer-Decoder-POM).

## Version history ##
**2.0** (October 2026)
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
