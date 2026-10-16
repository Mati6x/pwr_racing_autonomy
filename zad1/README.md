# Zad 1

## Uruchamianie
### Kompilator
g++ MSYS2/UCRT64 16.1.0
### Uruchamianie
**Kompilacja** (Linux i Windows):
```
g++ -Wall -Wextra -o zad1 zad1.cpp
```

**Uruchomienie:**
```
./zad1 example_input.txt      # Linux
zad1 example_input.txt        # Windows cmd
``` 

### Przykladowy wynik dla pliku example_input.txt
```
CONE 13 10.300 0.400 [2,8]  
CONE 15 5.067 9.700 [10,4,9]  
ENCLOSURE 39.162 [15,5,12,1,11,13,3]  
```
Wynik jest zgodny z przykładowym wyjściem z treści zadania. Jedyna różnica to ID drugiego pachołka (15 zamiast 14) – wyjaśnienie w sekcji 1.1.


## 1.1 Deduplikacja
- Porównuje każdą parę pachołków
- Jeśli odległość jest mniejsza niż minimalna wymagana tworze nowy pachołek składający się z tej pary i dodaje go do końca listy, a stare zaznaczam jako usunięte. Nowy pachołek bierze udział w nastepnych porównaniach.
- Nowe ID = najwieksze ID z pliku + 1 żeby napewno było unikalne
- Dlatego w przykładzie drugi nowy pachołek ma ID 15, a nie 14 jak w treści zadania: najpierw łączą się pachołki 4 i 9 w pachołek 14, a dopiero potem pachołek 14 łączy się z 10 w pachołek 15. Pachołek 14 jest tylko pośredni i nie trafia do wyniku, ale jego ID zostało już zużyte. Zadanie wymaga jedynie, żeby ID było unikalne, więc wynik jest poprawny.
- Złożoność: O(n²).

## 1.2 Najkrótsza otoczka
- Startuje od punktu najdalszego od pierwszego punktu z listy bo musi on być na otoczce
- Kolejne punkty to takie ktorych prosta łacząca ma reszte punktów po lewej stronie   
Stronę sprawdzam iloczynem wektorowym:
  `(xB − xA)(yP − yA) − (yB − yA)(xP − xA)` – wynik ≥ 0 oznacza lewą stronę lub punkt na prostej.
- Punkty znalezione na krawedzi dodawane sa do otoczki a program przechodzi do najdalszego znalezionego
- Koniec to powrót do punktu startowego
- Złożoność to O(h*n²) gdzie h – liczba punktów otoczki.

## Edge case'y i założenia

| Przypadek | Zachowanie |
|---|---|
| Łańcuch A~B, B~C, ale A≁C (np. punkty (0,0), (0.9,0), (1.8,0) przy m = 1) | łączone są tylko 2 z 3, a które – zależy od kolejności w pliku |
| Wszystkie punkty w jednej linii | otoczka to odcinek „tam i z powrotem” |
| 0 lub 1 punkt (także po deduplikacji) | komunikat i zakończenie programu |
| Uszkodzony plik wejściowy | zakładam poprawny format wejścia |