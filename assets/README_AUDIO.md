# Archivos de Audio para Bomberman

Este directorio debe contener los archivos de audio del juego. Los archivos son **opcionales** - el juego funcionará sin ellos.

## Archivos requeridos

Para habilitar el audio completo, necesitas los siguientes archivos:

### Música de fondo
- `background_music.ogg` o `background_music.wav`
  - Se reproduce automáticamente al iniciar el juego
  - Se reproduce en bucle continuo
  - Volumen: 50%

### Efectos de sonido
- `bomb_place.wav` o `bomb_place.ogg`
  - Se reproduce cuando el jugador coloca una bomba
  - Volumen: 70%

- `bomb_explode.wav` o `bomb_explode.ogg`
  - Se reproduce cuando una bomba explota
  - Volumen: 80%

- `game_over.wav` o `game_over.ogg`
  - Se reproduce cuando el jugador pierde todas sus vidas
  - Volumen: 100%

- `you_win.wav` o `you_win.ogg`
  - Se reproduce cuando el jugador derrota a todos los enemigos
  - Volumen: 100%

- `powerup.wav` o `powerup.ogg`
  - Se reproduce cuando el jugador recoge cualquier power-up
  - Volumen: 80%

## Formatos soportados

- **WAV**: Formato sin compresión, mejor calidad pero archivos más grandes
- **OGG**: Formato comprimido, buena calidad y archivos más pequeños (recomendado)

## Dónde conseguir sonidos

Puedes encontrar sonidos gratuitos en:
- [Freesound.org](https://freesound.org/)
- [OpenGameArt.org](https://opengameart.org/)
- [Zapsplat](https://www.zapsplat.com/)
- [Incompetech](https://incompetech.com/music/) (para música)

**Importante**: Asegúrate de respetar las licencias de los archivos de audio que uses.

## Estructura de carpetas

```
Bomberman/
└── assets/
    ├── background_music.ogg
    ├── bomb_place.wav
    ├── bomb_explode.wav
    ├── game_over.wav
    ├── you_win.wav
    └── powerup.wav
```

## Notas técnicas

- El juego intentará cargar primero el formato `.ogg` y luego `.wav` para cada archivo
- Si un archivo no se encuentra, el juego continuará normalmente sin reproducir ese sonido
- Los volúmenes pueden ajustarse en `src/Game.cpp` en la función `initializeAudio()`

