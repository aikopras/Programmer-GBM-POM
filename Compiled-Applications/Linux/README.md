# Programmer-GBM-POM for Linux (EN)
A description of the program itself is in the [main README](../../README.md). The source code and the build instructions are in [src/Qt](../../src/Qt/README.md).

## Installation ##
[Programmer GBM-POM.zip](Programmer%20GBM-POM.zip) contains the program, built on Ubuntu 24.04 (x86_64) with Qt 6.4.2. It uses the Qt 6 libraries of the system. On Ubuntu / Debian these are installed with:

    sudo apt install libqt6widgets6 libqt6network6 libqt6serialport6

Unzip it (`unzip "Programmer GBM-POM.zip"`) and start the program with `./"Programmer GBM-POM"`. If the program is not executable, use `chmod +x "Programmer GBM-POM"` first. On other distributions, or if the program does not start, build it from source (see [src/Qt](../../src/Qt/README.md)).

Enter the IP address(es) of the Lenz interface(s) via File → Preferences. They are stored in `~/.config/Programmer GBM-POM/Settings.conf` and are used the next time the program connects. The XpressNet library writes errors and warnings to a logfile in `~/TMC-Logfiles`.

---

# Programmer-GBM-POM für Linux (DE)
Eine Beschreibung des Programms selbst steht in der [Haupt-README](../../README.md). Quellcode und Anleitung zum Übersetzen stehen in [src/Qt](../../src/Qt/README.md).

## Installation ##
[Programmer GBM-POM.zip](Programmer%20GBM-POM.zip) enthält das Programm, übersetzt unter Ubuntu 24.04 (x86_64) mit Qt 6.4.2. Es verwendet die Qt-6-Bibliotheken des Systems. Unter Ubuntu / Debian werden diese installiert mit:

    sudo apt install libqt6widgets6 libqt6network6 libqt6serialport6

Entpacken (`unzip "Programmer GBM-POM.zip"`) und das Programm mit `./"Programmer GBM-POM"` starten. Ist das Programm nicht ausführbar, zuerst `chmod +x "Programmer GBM-POM"` eingeben. Bei anderen Distributionen, oder wenn das Programm nicht startet, selbst übersetzen (siehe [src/Qt](../../src/Qt/README.md)).

Die IP-Adresse(n) der Lenz-Interfaces über File → Preferences eingeben. Sie werden in `~/.config/Programmer GBM-POM/Settings.conf` gespeichert und beim nächsten Verbindungsaufbau verwendet. Die XpressNet-Bibliothek schreibt Fehler und Warnungen in eine Logdatei in `~/TMC-Logfiles`.

---

# Programmer-GBM-POM voor Linux (NL)
Een beschrijving van het programma zelf staat in de [hoofd-README](../../README.md). De broncode en de bouwinstructies staan in [src/Qt](../../src/Qt/README.md).

## Installatie ##
[Programmer GBM-POM.zip](Programmer%20GBM-POM.zip) bevat het programma, gebouwd op Ubuntu 24.04 (x86_64) met Qt 6.4.2. Het gebruikt de Qt-6-libraries van het systeem. Op Ubuntu / Debian worden die geïnstalleerd met:

    sudo apt install libqt6widgets6 libqt6network6 libqt6serialport6

Pak het uit (`unzip "Programmer GBM-POM.zip"`) en start het programma met `./"Programmer GBM-POM"`. Is het programma niet uitvoerbaar, geef dan eerst `chmod +x "Programmer GBM-POM"`. Bouw het zelf (zie [src/Qt](../../src/Qt/README.md)) bij andere distributies, of als het programma niet start.

Voer het IP-adres (of de IP-adressen) van de Lenz-interface(s) in via File → Preferences. Ze worden bewaard in `~/.config/Programmer GBM-POM/Settings.conf` en gebruikt bij de volgende verbinding. De XpressNet-library schrijft fouten en waarschuwingen naar een logfile in `~/TMC-Logfiles`.
