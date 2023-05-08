# C++ Započtový projekt - bakteriální evoluce

Jde o zápočtový projekt k C++ kurzu na mff v roce 2022/23. Udělán pod vedením Tomáše Faltína.

## Instalace dependencí

Naklonujte si tento repozitář (tohoto projektu), například pomocí příkazu
```bash
git clone https://github.com/Desperadus/CPP-zapoctak-evoluce.git
```
Pro kompilaci kódu je nutné mít stažnou knihovnu [SMFL-development](https://www.sfml-dev.org/download.php). 
Na Fedora linuxu se dá stáhnout třeba pomocí
```bash
sudo dnf install SFML-devel
```
Na ubuntu (mnou netestováno)
```bash
sudo apt-get install libsfml-dev
```
## Kompilace a spuštění

Nyní kód zkompilujte
```bash
g++ -c main.cpp -I./headers -o ./source/main.o
g++ -c ./source/Grid.cpp -I./headers -o ./source/Grid.o
g++ -c ./source/Organism.cpp -I./headers -o ./source/Organism.o
g++ -c ./source/Game.cpp -I./headers -o ./source/Game.o
g++ -c ./source/Vars.cpp -I./headers -o ./source/Vars.o
g++ -c ./source/Gui.cpp -I./headers -o ./source/Gui.o
g++ -c ./source/Stats.cpp -I./headers -o ./source/Stats.o
g++ -c ./source/Food.cpp -I./headers -o ./source/Food.o
g++ -c ./source/GameWorld.cpp -I./headers -o ./source/GameWorld.o
g++ -c ./source/Maps.cpp -I./headers -o ./source/Maps.o
g++ ./source/main.o ./source/Grid.o ./source/Organism.o ./source/Game.o ./source/Vars.o ./source/Gui.o ./source/Stats.o ./source/Food.o ./source/GameWorld.o ./source/Maps.o -o game -lsfml-graphics -lsfml-window -lsfml-system
```
A nyní pro spuštění programu můžete jen napsat
```bash
./game
```

## Hra

Ve hře můžete pozorovat bakterie, které se na začátku spawnnují se zcela náhodnými pravděpodobnostmi co do šancí pohybu na danou stranu a náhodnou rychlostí svého pohybu. Pohyb ji stojí energii a tak musí žrát - ty co nemají dostatek energie zemřou. Jakmile má bakterie dostatek jídla, tak se rozmnoží a vzniknou dvě dceřiné buňky. Když dojde k rozmnožení může dojít s malou šancí k náhodné mutaci co do směru pohybu dané bakterie - také může proběhout mutace jež sníží/zvýší bakterii rychlost a její velikost.

Záměrem hry je pozorovat jak se bakterie mění a kdy jaké evoluční tlaky působí s jakou silou. Lze vidět, že standardně první za jakýchkoliv podmínek je evoluční tlak na rychlost (s antibiotekem to může byt tedy spis tlak na směr někdy). A pak tlak na směr pohybu převáží (lze pozorovat po rozkliknutí statistik). Bakterie nejvíce evolučně úspěšné (nejvíce dělení proběhlo), jsou červené - hodnoty jedné z nich (ta bude modrá) se pak zobrazují ve statistikách.


## Nastavení v GUI

Na levé straně vidíte názvy parametrů a vedle nich máte input boxy, kde jejich hodnoty můžete měnit a psát do nich. Rámeček okolo hodnoty je zelený, pokud je hodnota platná, červený je tehdy, když ještě není aktivní (docházé ke změně vámi) - zmáčknutím enteru se hodnota propíše do hry.

### Parametry:

**Map:** 1 - je default mapa s lajnama, 2 - je mapa s obdélníkem uprostřed, 3 - tenky pruh, ktery je sirkou dependentní na *Num of lines*

**Number of lines:"** Kolik lajn bude v mapě 1, taká ovlivninuje velikost antibiotického bloku (viz později).

**Oragnism size:** Defaultní velikost organisme při jejich spawnnutí.

**Reproduction E:** Při hodnotě jaké energie dojde k rozmnožení - bakterie energii dostávají z jezení jídla a při vykonání pohybu ztratí 1 energie. Po mitóze mají dceřiné buňky poloviční energii té mateřské.

**Spawn rate:** Rychlost spawnovaní jídla v organizovaných částech (lajny, obdélník).

**Rand spawn rate:** Rychlost spawnovaní jídla zcela náhodně po celé mapě.

**Number of org:** Kolik organismů se spawne.

**Food energy:** Kolik energie přidá bakteriím energie.

**Max num of food:** Když bude ve hře tolik jídla, další se již nebude tvořit.

**Antibiotic dmg:** Kolik jim antibiotikum sebere energie.

**Anti spawn rate:** Rychlost tvorby antibiotica.

**Max num of anti:** Max číslo antibiotik ve hře.

### Tlačítka:

**Start** - startuje hru (odznovu)

**Pause/Resume** - Pausne a pak resumne hru

**Add oragnisms** - přidá do hry další organismy (závislé na parametru *Number of org*

**Speed up** - zrychlí ingame time

**Slow down** - zpomalí ingame time

**Show stats** - zobrazí statistiky.

**Add anti** - je-li rámeček červený kliknutí na herní plochu nic neudělá, je-li to zelené tak se objeví na daném místě blok antibiotika - jeho velikost a zacentrování polohy je určeno parametrem *Number of lines*

## Licence

MIT
