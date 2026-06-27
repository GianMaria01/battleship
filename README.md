# Battaglia Navale

Una semplice implementazione di Battaglia Navale scritta in C++ usando la libreria grafica raylib.

## Caratteristiche
- Interfaccia grafica basata su raylib
- Posizionamento semplice delle "hitbox" su una griglia 10x10
- Meccanica base per il cambio turno e visualizzazione giocatori

## Requisiti
- Compilatore C++ (g++, clang++, MSVC)
- raylib (https://www.raylib.com) installata sul sistema
- Toolchain di sviluppo (make, pkg-config opzionale)

Vedi la documentazione ufficiale di raylib per l'installazione: https://github.com/raysan5/raylib

## Build e esecuzione (esempi)

Nota: questi comandi assumono che raylib sia installata e che `pkg-config` sia configurato per raylib. Se non usi pkg-config, sostituisci con i flag di linking appropriati per la tua piattaforma.

Linux/macOS (con pkg-config):
```bash
g++ -std=c++17 Battaglia_navale.cpp -o battaglia `pkg-config --cflags --libs raylib`
./battaglia
