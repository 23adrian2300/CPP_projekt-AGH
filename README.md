# Gra Tetris

## Jak uruchomić?

### Biblioteka SFML v2.5.1
Biblioteke należy umieścić w Dysku C pod zmienioną nazwą na `SFML`. Jednocześnie należy dodać zmienne środowiskowe do zmienne path.
W swoim przypadku dodałem ścieżki C:\SFML, C:\SFML\lib, C:\SFML\bin, C:\SFML\include.

### MinGW
Wersja MinGW musi odpowiadać wersji SFML. W moim przypadku jest to MinGW Builds 7.3.0 (64-bit). Następnie podobnie jak poprzednio należy dodać pod zmienioną nazwą MinGW do dysku C.
Następnie ponownie musimy dodać zmienne środkowiskowe do path: C:\MinGW\bin

### Kompilacja
Początkowo musimy za pomocą komendy `cd {ścieżka do katalogu z programem}` dostać się do katalogu z grą, dokładnie tam gdzie jest plik main.cpp. 
Do skompilowania wykorzystałem kompilator g++. Całość odbyła się za pomocą komendy, dostępnej również w pliku kompilacja.txt:

`g++ -I C:\SFML\include main.cpp functions\game.cpp -mwindows -o main.exe -L C:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system`


### Uruchomienie
Aby uruchomić, należy albo z poziomu katalogu dwukrotnie kliknąc na powstały plik main.exe, lub z poziomu konsoli wywołać komendę:  'start main.exe'

## Korzystanie z aplikacji
Po uruchomieniu na ekranie startowym mamy 3 przyciski: Play, How to Play oraz Quit. 

Jeśli chcemy zagrać klikamy Play i wykorzystując strzałki poruszamy klockami:
- strzałka w lewo - przesuwa klocek w lewo,
- strzałka w prawo - przesuwa klocek w prawo,
- strzałka w dół - przyśpiesza spadanie klocka,
- strzałka w górę - obraca nasz klocek.

Gramy i za każdą linie dostajemy punkt. W momencie końca, po 5 sekundach zamyka się okno z grą i wracamy do Menu.

Jeśli chcemy dowiedzieć się na czym polega gra klikamy How to play, które zawiera krótki opis gry.
Aby zamknąć, należy kliknąc Quit, który kończy działanie aplikacji.

