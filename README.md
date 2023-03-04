# CPP-zapoctak-evoluce

Jedná se o zápočtový program k CPP předmětu na MFF.

Zatím je hra funkční jen v omezeném stavu - pro její spuštení si naklonujte repozitář a napište v něm (pro linux): ```g++ -c main.cpp && g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app```

Je nutné mít stažené SFML devel. Na fedoře se zařídí například napsaním ```sudo dnf install SFML-devel```

Pro mac os je smfl přidáno v repozitáři a je nutné jej ukázat compileru - lze pouzít z vscode ```tasks.json``` pro spuštění.

Stiskem kláves ```o``` a ```p``` zpomalíte a případně zrychlíte plynutí ingame času.
