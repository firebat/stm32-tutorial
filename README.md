## STM32 Tutorial

### Hardware

* STM32F103C8T6

![STM32F103C8T6](http://gd4.alicdn.com/imgextra/i4/87224073/T2Elr3XutaXXXXXXXX_!!87224073.jpg)

* J-Link

![J-Link](http://www.positive-one.com/images/SEGGER/Segger_jlink.jpg)

### How To

#### Connect

![J-Link connect](http://gd1.alicdn.com/imgextra/i1/87224073/T2Uuf4XE8XXXXXXXXX_!!87224073.jpg)

#### Burn

Download jlink from https://www.segger.com/jlink-software.html

    $ dpkg -i jlink_4.96.7_x86_64.deb
    $ JLinkExe
    J-Link>exec device=STM32F103C8
    J-Link>loadbin main.hex,0x8000000

Press reset button to run
