# Enlaces Directos para Descargar Audio

Esta es una lista de enlaces directos y búsquedas específicas para conseguir los archivos de audio más rápido.

## 🎵 Música de Fondo

### Opción 1: Freesound.org
1. Ve a: https://freesound.org/search/?q=8+bit+game+music+loop
2. Filtra por: Licencia CC0
3. Busca archivos de 30-60 segundos
4. Descarga y renombra a `background_music.ogg`

### Opción 2: OpenGameArt
1. Ve a: https://opengameart.org/content/8-bit-music-pack
2. Busca música estilo arcade/retro
3. Descarga y renombra

### Opción 3: Incompetech (Música de Kevin MacLeod)
1. Ve a: https://incompetech.com/music/royalty-free/
2. Busca: "8bit" o "Arcade"
3. Ejemplos populares:
   - "8bit Dungeon Level" 
   - "Arcade Music"
4. Descarga y convierte a OGG si es necesario

## 🔊 Efectos de Sonido

### bomb_place.wav
**Búsquedas recomendadas:**
- Freesound: https://freesound.org/search/?q=click+sound+effect
- Busca: "click", "beep", "button press"
- Duración: < 1 segundo
- Licencia: CC0 preferible

**Alternativas:**
- Usa Bfxr: https://www.bfxr.net/ para generar un sonido simple
- Tipo: "Click" o "Beep"

### bomb_explode.wav
**Búsquedas recomendadas:**
- Freesound: https://freesound.org/search/?q=explosion+sound+effect
- Busca: "explosion", "blast", "boom"
- Duración: 1-2 segundos
- Licencia: CC0 preferible

**Alternativas:**
- Freesound: https://freesound.org/search/?q=bomb+explosion

### game_over.wav
**Búsquedas recomendadas:**
- Freesound: https://freesound.org/search/?q=game+over+sound
- Busca: "game over", "fail", "lose"
- Duración: 1-3 segundos
- Licencia: CC0 o CC BY

**Alternativas:**
- Busca "sad trombone" o "wah wah"

### you_win.wav
**Búsquedas recomendadas:**
- Freesound: https://freesound.org/search/?q=victory+fanfare
- Busca: "victory", "fanfare", "success", "win"
- Duración: 2-5 segundos
- Licencia: CC0 o CC BY

**Alternativas:**
- Busca "triumph" o "achievement"

### powerup.wav
**Búsquedas recomendadas:**
- Freesound: https://freesound.org/search/?q=powerup+sound
- Busca: "powerup", "pickup", "collect", "item get"
- Duración: 0.5-2 segundos
- Licencia: CC0 o CC BY

**Alternativas:**
- Busca "power up" o "item pickup"
- Usa Bfxr para generar un sonido tipo "Powerup"

## 🛠️ Herramientas Útiles

### Convertir Formatos
Si descargas archivos en MP3 u otros formatos:

**Opción 1: Online (sin instalar nada)**
- https://cloudconvert.com/
- https://convertio.co/

**Opción 2: ffmpeg (línea de comandos)**
```bash
# Instalar ffmpeg (macOS)
brew install ffmpeg

# Convertir MP3 a OGG
ffmpeg -i archivo.mp3 archivo.ogg

# Convertir MP3 a WAV
ffmpeg -i archivo.mp3 archivo.wav
```

### Generar Sonidos Básicos
- **Bfxr**: https://www.bfxr.net/ - Generador de sonidos retro
- **ChipTone**: https://sfbgames.itch.io/chiptone - Generador 8-bit

## 📋 Checklist de Descarga

Usa esta lista para verificar que tienes todo:

- [ ] background_music.ogg o .wav
- [ ] bomb_place.wav o .ogg
- [ ] bomb_explode.wav o .ogg
- [ ] game_over.wav o .ogg
- [ ] you_win.wav o .ogg
- [ ] powerup.wav o .ogg

## 🎯 Búsquedas Específicas en Freesound

1. **Música**: 
   - https://freesound.org/search/?q=chiptune+loop
   - Filtra: Licencia CC0, Duración 30-60s

2. **Click/Beep**:
   - https://freesound.org/search/?q=click+sound
   - Filtra: Duración < 1s

3. **Explosión**:
   - https://freesound.org/search/?q=explosion
   - Filtra: Duración 1-2s

4. **Game Over**:
   - https://freesound.org/search/?q=game+over
   - Filtra: Duración 1-3s

5. **Victoria**:
   - https://freesound.org/search/?q=victory+fanfare
   - Filtra: Duración 2-5s

6. **Power-up**:
   - https://freesound.org/search/?q=powerup+sound
   - Filtra: Duración 0.5-2s

## ⚡ Método Rápido (5 minutos)

Si necesitas algo rápido para probar:

1. Ve a https://www.bfxr.net/
2. Genera 5 sonidos:
   - Click (para bomb_place)
   - Explosion (para bomb_explode)
   - Powerup (para powerup)
   - Blip (para game_over)
   - Powerup/Fanfare (para you_win)
3. Descarga cada uno como WAV
4. Renombra según los nombres requeridos
5. Para música, usa https://incompetech.com/ y descarga una pista corta

## 📝 Notas Importantes

- **Licencias**: Siempre revisa la licencia antes de usar
- **Atribución**: Si usas CC BY, agrega créditos en tu README
- **Formato**: El juego acepta tanto WAV como OGG
- **Tamaño**: Intenta mantener archivos < 5MB cada uno
- **Calidad**: 44.1kHz es suficiente para efectos de sonido

