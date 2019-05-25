# 42_Corewar
In this project, you will create a virtual “arena” in which programs will fight against one another (the “Champions”). You will also create an assembler to compile those Champions as well as a Champion to show the world that you can create life from coffee.

## Description
Project consists of 4 parts:
- Virtual machine
- Assembler
- Vizualizer
- Champion

## Run and navigation
```
git clone https://github.com/mbortnichuk/42_Corewar.git
cd 42_Corewar
make
```
**`asm`**
```
Usage: ./asm Champion/Peer_beer.s
```
**`corewar`**
```
Usage: ./corewar	[-dump nbr_cycles] [-n number] [-vis] [-a] <player1.cor> <...> <player.cor>
	-a : Prints output from "aff" (It is hidden by default)
	-n nbr : Sets the number of the next player
	-dump nbr : Dumps memory after nbr cycles then exits
	-vis : Ncurses output mode
```

## Screenshots
`Random bots at starting positions`
![foo](https://github.com/mbortnichuk/42_Corewar/blob/master/pictures/start.png "start")
`Random bots in the middle of the game`
![foo](https://github.com/mbortnichuk/42_Corewar/blob/master/pictures/middle.png "middle")
`Endgame output to the terminal`
![foo](https://github.com/mbortnichuk/42_Corewar/blob/master/pictures/end.png "end")


## Authors
- Ivan Osypenko - [iosypenk](https://github.com/iosypenk "iosypenk")
- Maksym Rybak - [mrybak](https://github.com/Hurubashi "mrybak")
- Mariana Bortnichuk - [mbortnic](https://github.com/mbortnichuk "mbortnic")
- Vasyl Kravets - vkravets
