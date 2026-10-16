## 2.1 Analiza błędów sensorów

### Narzędzia
Dane przeanalizowałem w Pythonie (pandas, matplotlib).

<img src="graf.png" width="30%">
<img src="graf2.png" width="50%">

### Sensor 1

**Obserwacje:**
- trajektoria gładka i mało zaszumiona,
- dobry kierunek najpierw okrąg prawy, potem lewy,
- pierwsze dwa okrążenia prawie idealnie pokrywają się z torem, potem trajektoria zaczyna odpływać,
- błąd rośnie z czasem: na początku mały, potem coraz większy. Na końcu przejazdu sensor wskazuje ok. (−7.6, −5.2), podczas gdy auto powinno stać ok. 10 m za linią pomiaru czasu,
- odpływanie jest znacznie większe w osi x niż w y.

**Podejrzewane źródło:** czujnik to prawdopodobnie akcelerometr wiec błąd w nim jest prawdopodobnie: blad kalibracji, wpływ temperatury lub bład w montażu.

### Sensor 2

**Obserwacje:**
- pozycja nie odpływa w czasie: start i koniec zgadzają się z treścią zadania ((−15, 0) i ok. 10 m za linią),
- pomiary mają 3 wyraźne błedy, i są dużo rzadsze niż przy sensorze 1
- oś y jest odwrócona: sensor wskazuje najpierw okrąg lewy,

**Podejrzewane źródło:** odbiornik GPS, błędy tutaj mogą wynikać z chwilowej utraty satelitów lub zakłóceń

### Wnioski do 2.2
Sensory mają **uzupełniające się** wady: sensor 1 jest gęsty i gładki, ale odpływa w długim okresie, a sensor 2 jest rzadki i zaszumiony, ale nie odpływa. Dlatego w 2.2 [...].