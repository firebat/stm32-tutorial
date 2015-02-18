cat <<EOF | JLinkExe
exec device=STM32F103C8
loadbin main.bin, 0x8000000
EOF

