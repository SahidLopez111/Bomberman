#!/bin/bash

# Script para verificar archivos de audio en la carpeta assets
# Uso: ./verificar_audio.sh

echo "🔍 Verificando archivos de audio en assets/..."
echo ""

ASSETS_DIR="$(dirname "$0")"
cd "$ASSETS_DIR" || exit

# Colores para output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Lista de archivos requeridos
declare -a REQUIRED_FILES=(
    "background_music"
    "bomb_place"
    "bomb_explode"
    "game_over"
    "you_win"
    "powerup"
)

# Contador
found=0
missing=0

echo "Archivos encontrados:"
echo "===================="

for file_base in "${REQUIRED_FILES[@]}"; do
    # Buscar archivos .ogg o .wav
    if [ -f "${file_base}.ogg" ] || [ -f "${file_base}.wav" ]; then
        if [ -f "${file_base}.ogg" ]; then
            size=$(du -h "${file_base}.ogg" | cut -f1)
            echo -e "${GREEN}✓${NC} ${file_base}.ogg (${size})"
        fi
        if [ -f "${file_base}.wav" ]; then
            size=$(du -h "${file_base}.wav" | cut -f1)
            echo -e "${GREEN}✓${NC} ${file_base}.wav (${size})"
        fi
        ((found++))
    else
        echo -e "${RED}✗${NC} ${file_base}.ogg o ${file_base}.wav (NO ENCONTRADO)"
        ((missing++))
    fi
done

echo ""
echo "===================="
echo "Resumen:"
echo -e "${GREEN}Encontrados: ${found}${NC}"
echo -e "${RED}Faltantes: ${missing}${NC}"
echo ""

if [ $missing -eq 0 ]; then
    echo -e "${GREEN}¡Todos los archivos de audio están presentes!${NC}"
    echo "El juego reproducirá sonidos y música."
else
    echo -e "${YELLOW}Algunos archivos faltan.${NC}"
    echo "El juego funcionará pero sin esos sonidos específicos."
    echo ""
    echo "Para conseguir los archivos, consulta:"
    echo "  - GUIA_DESCARGA_AUDIO.md"
    echo "  - README_AUDIO.md"
fi

echo ""

