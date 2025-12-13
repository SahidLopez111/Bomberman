# Circle Detonation

Un juego inspirado en Bomberman clásico implementado en C++ usando la librería SFML.

## Descripción

Este es un juego donde el jugador puede moverse por un mapa, colocar bombas y destruir bloques. El objetivo es evitar las explosiones mientras destruyes los bloques del mapa.

## Características

- **Movimiento fluido**: Control del jugador con las flechas del teclado
- **Sistema de bombas**: Coloca bombas que explotan después de unos segundos
- **Explosiones**: Las bombas crean explosiones en forma de cruz que destruyen bloques
- **Mapa generado**: Mapa con paredes indestructibles y bloques destructibles
- **Detección de colisiones**: El jugador muere si toca una explosión
- **Sistema de vidas**: El jugador tiene 3 vidas y reaparece al morir
- **Enemigos**: Enemigos que se mueven por el mapa
- **Potenciadores**: Power-ups que otorgan habilidades especiales (bombas extra, vidas extra, mayor alcance)
- **Sistema de audio**: Sonidos y música de fondo (opcional)

## Requisitos

- **Compilador C++**: GCC o Clang con soporte para C++17
- **SFML**: Versión 3.0 o superior (incluye módulo de audio)
  - macOS: `brew install sfml`
  - Ubuntu/Debian: `sudo apt-get install libsfml-dev`
  - Windows: Descargar desde [sfml-dev.org](https://www.sfml-dev.org/)

## Estructura del Proyecto

```
Bomberman/
├── assets/                     # Recursos del juego (imágenes, sonidos, etc.)
│   ├── background_music.ogg
│   ├── bomb_place.wav
│   ├── bomb_explode.wav
│   ├── game_over.wav     
│   ├── you_win.wav
│   └── powerup.wav        
├── vid/             # Videos o recursos multimedia
├── include/         # Archivos de cabecera (.hpp)
│   ├── Player.hpp
│   ├── Bomb.hpp
│   ├── Map.hpp
│   └── Game.hpp
├── src/             # Archivos fuente (.cpp)
│   ├── Player.cpp
│   ├── Bomb.cpp
│   ├── Map.cpp
│   ├── Game.cpp
│   └── main.cpp
├── Makefile         # Archivo de compilación
└── README.md        # Este archivo
```

## Compilación

### Compilar el juego

```bash
make
```

O manualmente:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o bomberman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

### Limpiar archivos de compilación

```bash
make clean
```

### Recompilar desde cero

```bash
make rebuild
```

## Ejecución

```bash
./bomberman
```

O usando make:

```bash
make run
```

## Controles

- **Flechas del teclado**: Mover el jugador
  - ↑ Flecha Arriba: Mover hacia arriba
  - ↓ Flecha Abajo: Mover hacia abajo
  - ← Flecha Izquierda: Mover hacia la izquierda
  - → Flecha Derecha: Mover hacia la derecha
- **Espacio**: Colocar una bomba

## Sistema de Audio

El juego incluye soporte para sonidos y música de fondo. Los archivos de audio son **opcionales** - el juego funcionará perfectamente sin ellos.

### Archivos de audio requeridos

Para habilitar el audio, coloca los siguientes archivos en la carpeta `assets/`:

- `background_music.ogg` o `background_music.wav` - Música de fondo (se reproduce en bucle)
- `bomb_place.wav` o `bomb_place.ogg` - Sonido al colocar una bomba
- `bomb_explode.wav` o `bomb_explode.ogg` - Sonido cuando explota una bomba
- `game_over.wav` o `game_over.ogg` - Sonido cuando pierdes el juego
- `you_win.wav` o `you_win.ogg` - Sonido cuando ganas el juego
- `powerup.wav` o `powerup.ogg` - Sonido al recoger cualquier power-up

### Formatos soportados

El juego soporta archivos de audio en formato **WAV** u **OGG**. Si un archivo no se encuentra, el juego simplemente continuará sin reproducir ese sonido.

### Notas

- La música de fondo se reproduce automáticamente al iniciar el juego
- Los efectos de sonido se reproducen cuando ocurren los eventos correspondientes
- El volumen está preconfigurado pero puede ajustarse en el código si es necesario
- Para más información sobre cómo agregar archivos de audio, consulta `assets/README_AUDIO.md`

## Mecánicas del Juego

### Jugador
- El jugador aparece en la esquina superior izquierda del mapa
- Puede moverse por espacios vacíos
- Puede colocar bombas en su posición actual
- Muere si toca una explosión

### Bombas
- Las bombas se colocan en la posición actual del jugador
- Explotan después de 3 segundos
- Crean explosiones en forma de cruz con un rango de 2 casillas
- Las explosiones destruyen bloques destructibles
- Las explosiones se detienen al encontrar una pared indestructible

### Mapa
- **Paredes (marrón oscuro)**: Indestructibles, bloquean el movimiento y las explosiones
- **Bloques (marrón claro)**: Destructibles, se pueden destruir con bombas
- **Espacios vacíos (gris oscuro)**: El jugador puede caminar aquí
- **Explosiones (rojo)**: Aparecen temporalmente cuando una bomba explota

## Clases Principales

### Player
Maneja la posición, movimiento y estado del jugador. Controla cuántas bombas puede colocar.

### Bomb
Representa una bomba en el mapa. Maneja el temporizador de explosión y el rango de la explosión.

### Map
Gestiona el mapa del juego, incluyendo paredes, bloques y explosiones. Proporciona funciones para verificar colisiones y caminabilidad.

### Game
Clase principal que coordina todos los componentes del juego. Maneja el bucle principal, entrada del usuario, actualización del estado y renderizado.


## Notas Técnicas

- El juego usa SFML para renderizado y manejo de ventanas
- El código está completamente documentado con comentarios Doxygen
- La estructura del proyecto sigue buenas prácticas de organización de código C++
- El Makefile facilita la compilación y gestión del proyecto

## Licencia

Este proyecto es educativo y está disponible para uso libre.

## Autor

- Diego Herrera Gonzalez 24110202
- Sahid Uriel Lopez Salazar 24110183

## Agradecimientos

- SFML por proporcionar una excelente librería multimedia
- La comunidad de desarrolladores de juegos por la inspiración

