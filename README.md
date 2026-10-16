# AMB-1 Evolved

Generative Ambient-Firmware für den **M-VAVE FM-1**: die vertraute AMB-1-Bedienung, erweitert um **64 Klangpresets**, **32 Themen**, **20 Skalen** und das Bunkai-Wolf-A1-Design.

**E1 · FM-1_7080001** — vom Projektinhaber am 17.10.2026 erfolgreich am Gerät erprobt. Das ist keine allgemeine Hardware-Dauerlauffreigabe.

- [Website & Hörbeispiele](https://amb1-evolved.sugarypixie10.chatgpt.site/)
- [Web-Installer](https://amb1-evolved.sugarypixie10.chatgpt.site/install/)
- [Anleitung & Tutorial](https://amb1-evolved.sugarypixie10.chatgpt.site/anleitung/)
- [Firmware E1](https://amb1-evolved.sugarypixie10.chatgpt.site/install/amb1-evolved-e1.fwsc)
- [Testbericht](https://amb1-evolved.sugarypixie10.chatgpt.site/install/test-status.txt)

## AMB-1 bleibt die Grundlage

Evolved ist ein eigenständiger Ableger von [AMB-1](https://github.com/charlesvestal/fm1-amb) von Charles Vestal. Die vier Klangbereiche, vier Melodieschleifen, Harmonie, Bass, Puls und sieben Seiten bleiben vertraut. Die Farbpalette und Animationen kommen aus Bunkai Wolf A1. Das separate Projekt Bunkai Wolf A3 wird nicht verändert; A2/A3-Noteneditorseiten sind nicht enthalten.

## Features

- Je 16 Sounds für Pad, Melodie, Bass und Puls. Klangbeschreibungen, keine Samples.
- Acht bekannte AMB-1-Themen plus 24 neue; Zustände je Thema gespeichert.
- 20 Skalen und fünf vorhandene Generatorvarianten: Garden, Walk, Mirror, Rotate, Gravity.
- Sieben Seiten: Garden, Pad, Bells, Bass, Pulse, Space, Setup.
- Vorhandene Schutzmechanismen: Watchdog, Safe Mode und Audio-Deadline-Schutz.

## Bedienung

| Eingabe | Funktion |
| --- | --- |
| PRESETS | Thema wechseln |
| ENV / ARP / LFO / SEQ halten + PRESETS | Sound der jeweiligen Ebene wählen |
| SELECT | Seite wechseln |
| ALGORITHM | Skala wählen |
| HOME + ALGORITHM | Generatorvariante wählen |
| HOME + SELECT | Tempo einstellen |
| REC | Freeze umschalten |
| PLAY | Start / Ruhe |
| SAVE kurz | Alle Themenzustände speichern |

## Installation und Speicher

Chrome auf dem Mac, ein eingeschalteter FM-1 und ein USB-Datenkabel. Der Installer prüft Paketkennung und SHA-256, schreibt erst nach Bestätigung und bietet einen Rückweg zu AMB-1 1.2 bzw. der geprüften Herstellerdatei.

**EOV1 / Format 100:** Alte AMB-/Wolf-Projekte werden nicht importiert. Speichern ersetzt den bisherigen Projektinhalt. Firmware-Rückkehr ist kein Datenbackup. Stromverlust beim Flashen ist nicht garantiert abfangbar.

E1 SHA-256: `61755b43e6dad1080b0db84aad36972116be703fdf4ff910c5b2c8c1b4546e5b`

## Entwicklung und Tests

`firmware/` enthält die Firmware, deren Tools und Tests. Siehe [BUILDING.md](firmware/BUILDING.md) für Toolchain und SDK. `dist/` ist die statische Website samt Installer und Firmwarepaketen. `tests/` enthält Website-/Installerprüfungen.

Der E1-Bericht dokumentiert 22 bestandene Testgruppen, 64 Sound-/32 Themen-Audiovergleiche, Stress- und ASan/UBSan-Läufe. Laufzeiten sind simulierte Audiozeit. Browser-Hörbeispiele sind Host-Renderings des C-DSP, keine Hardwareaufnahmen. Die Firmware wurde beim Website-Ausbau nicht geändert oder neu gebaut.

## Credits und Lizenz

**GPL-3.0-only**, siehe [LICENSE](LICENSE) und die vollständigen [Herkunfts- und Lizenzhinweise](firmware/LICENSING.md). Plattform: [Felucca](https://github.com/hugelton/Felucca), Copyright 2026 Leo Kuroshita / Hügelton Instruments, über X0X und FoMni. AMB-1: Charles Vestal. Reverb nach Jon Dattorro; euklidische Rhythmik nach Bjorklund / Toussaint. Barlow: SIL OFL 1.1.

Eigenständiges Community-Projekt, nicht von M-VAVE, den ursprünglichen Autoren oder deren Marken offiziell unterstützt. Alle bestehenden Urheber- und Lizenzhinweise bleiben erhalten.
