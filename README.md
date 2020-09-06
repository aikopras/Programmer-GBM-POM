# Programmer-GBM-POM
 Xcode project - MAC software for the GBM

This program allows reading and modifying the CV variables within the Occupancy Detection (Feedback) Decoder (Gleis Besetz Meldung). For that purpose it uses Programming on the Main (PoM) messages. Since the XPressNet specification only supports PoM messages for train decoders (as opposed to accessory / feedback decoders), Feedback decoders listen to a train address equal to the RS-Bus address + 6000. GBM feedback decoders do NOT support service mode programming (thus programming on the programming track), since the GBM hardware is powered from the tracks, and in service mode power has to be removed from the track.
To set a CV to a certain value, a standard CV-Write message is transmitted.
To read a CV value, a standard CV-Verify message is transmitted. Note however that the CV value contained in that message will always be 0. Upon reception of this message, the decoder reacts in a non-standard way, by sending the value of the CV back via RS-Bus feedback messages (two messages for each byte).
Four types of feedback decoders exist: normal feedback decoders, feedback decoders also acting as reversers, feedback decoders with four relays to power-off tracks and finally feedback decoders with a LCD display that shows the speed of a train passing through a certain track.
