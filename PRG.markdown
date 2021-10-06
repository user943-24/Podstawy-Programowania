# sprawy organizacyjne

- przedstawienie się:
    - email: marecki@pjwstk.edu.pl
    - szuflandia: szuflandia.pjwstk.edu.pl/~marecki
    - strona: edu.marecki.me/~marecki
    - pisać z problemami, będę pomagać
- lista studentów, lista obecności
- zwolnienie z zajęć (CV, doświadczenie)
- dystrybucja VM
- prezentacja narzędzi (Github, Git, konsola, GCC)

--------------------------------------------------------------------------------

# lekcja 0

- wstęp historyczny do komputerów:
    - co to jest komputer? (CPU, pamięć, urządzenia I/O)
    - jak działa CPU? (load, decode, execute, retire)
    - `mov eax, 0`

- wstęp historyczny do języków programowania (od Charles Babagge'a)
- czym jest język programowania (duch w maszynie)
- jakie są języki programowania:
    - funkcyjne (OCaml, Standard ML)
    - obiektowe (Smalltalk, Erlang)
    - strukturalne (C, Rust)
    - wieloparadygmatowe (C++)
    - inne paradygmaty
- języki mogą być kompilowane (np. C++ i Rust) lub
  wykonywane dynamicznie (np. Python i Ruby), lub trochę tak, a
  trochę tak (Java, Javascript)

- podstawowe składniki języka: czyli jak relizowane są podstawowe czynności?
  (Jackson Structured Programming)
    - Michael Jackson, 1975; Principles of Program Design
    - *sequence* (sekwencja, kolejność)
    - *selection*, *alternative* (wybór, alternatywa)
    - *iteration* (iteracja)
    - fajne, ale nadaje się do opisania algorytmów, a to nie wszystko

- dodatkowe składniki języka: czyli jak relizowane są niektóre bardziej
  zaawansowane operacje?
    - Warnier/Orr
    - Jean-Dominique Warnier, 1976; Logical construction of programs
    - Kenneth Orr, 1977; Structured systems development
    - *recursion* (rekurencja): czyli jak wykonać tą samą operację z jej środka;
      da się to załatwić iteracją, ale rekurencja często jest bardziej elegancka
    - *concurrency* (współbieżność): czyli jak zapewnić wykonywanie kilku rzeczy
      naraz
    - panowie mieli spoko pomysł, ale czegoś tu jeszcze brakuje

- ja bym dorzucił do tego jeszcze... czyli jak realizowane są programy, które są
  nieco bardziej skomplikowane niż szkolne algorytmy
    - *error handling* (obsługa błędów): czyli jak obsługiwane są sytuacje, w
      których coś poszło nie tak; moim zdaniem dobrą praktyką jest wydzielenie
      obsługi błędów z uwagi na jej znaczenie dla pisania odpornych ("robust")
      na awarie programów
    - *I/O* (obsługa wejścia i wyjścia): czyli jak program komunikuje się ze
      światem zewnętrznym; ponieważ programy nie działają same dla siebie

- jak to wygląda w C++?
    - *sequence*: stwierdzenia są wykonywane po kolei, a oddzielane są
      najczęściej znakiem
    - *selection*: stwierdzenia `if-else` oraz `switch-case`
    - *iteration*: pętle `for`, `while`, oraz `do-while`
    - *recursion*: funkcje (mogą wołać same siebie)
    - *concurrency*: wątki (lub procesy, ale te drugie są zapewniane przez
      POSIX, a nie standard C++)
    - *error handling*: wyjątki (lub kody błędu, ale to jest mechanizm
      odziedziczony po C i miesza zwracanie wartości z funkcji z obsługą
      błędów)
    - *I/O*: strumienie `iostream`, `fstream`, itd. (moim zdaniem bardziej
      eleganckie są *file descriptors*, ale te znów dostarcza POSIX)

- abstrakcje i sposoby organizacji kodu:
    - funkcje (sposób na opakowanie zestawu instrukcji w "jedną")
    - struktury (sposób na opakowanie zestawu danych w "jedną")
    - przestrzenie nazw (`namespace`, sposób na opakowanie powiązanych
      abstrakcji)

- programy:
    - instrukcje, operujące na danych
    - standardowe wejście
    - standardowe wyjście
    - standardowe wyjście błędów
    - dodatkowe strumienie I/O otwierane przez program
    - kod wynikowy (kod błędu)
    - (funkcje są dokładnie takie same: mają dane na wejściu, wynik, i mogą
      zakończyć się błędem)

- zastrzeżenia:
    - zakaz używania `using namespace std;`
    - zaliczenia tylko na Linux
    - zaliczenie prezentacją projektu (plus minimalna obecność)

Wszyscy mają mieć założone repozytorium na Github, Gitlab, Szuflandii,
gdziekolwiek. Ważne żeby mieli gdzie trzymać kod.

--------------------------------------------------------------------------------

# lekcja 1

Czego uczy?

- definicja funkcji w C++:
    - nazwa
    - lista parametrów (parametrów formalnych)
    - typ zwracany
    - ciało funkcji
- dołączanie nagłówków w C++

- składniki języka:
    - abstrakcja (funkcja)
    - sekwencja (najpierw print, potem return)

- typy danych:
    - int
    - string

------------------------------------------------------------

- slajdy linijka po linijce, element po elemencie
    - *#include <iostream>*
    - *auto main*
    - auto main*()*
    - auto main() *-> int*
    - {}
    - *std::cout <<*
    - std::cout << *"Hello, World!\n"*
    - std::cout << "Hello, World!\n"*;*
    - *return 0*;

- kompilacja i uruchomienie:
    - g++ -std=c++17 main.cpp
    - ./a.out
    - dlaczego plik wynikowy nazywa się `a.out`?

- "Hello, World!"
- src/00-hello-world.cpp (przykład)
- src/s00-hello-world.cpp (plik studenta)

----------------------------------------

### Zadania

- skompilować i wykonać "Hello, World!"
- zmienić "World" na swoje imię, skompilować i wykonać

Zacommitować, wypchnąć do repozytorium.

--------------------------------------------------------------------------------

# lekcja 2

Czego uczy?

- odczytywanie danych ze standardowego wejścia
- wywołania funkcji
- wywołania funkcji składowych

- składniki języka:
    - sekwencja
    - alternatywa (`if`: użytkownik albo podał, albo nie podał swojego imienia)

- typy danych:
    - int
    - string

------------------------------------------------------------

- "Hello, John Doe!"
- src/01-hello-input.cpp
- src/01-hello-argv.cpp
- src/s01-input.cpp (plik studenta)
- src/s01-mr-or-mrs.cpp (plik studenta)

----------------------------------------

### Zadania

- zmienić kod (s01-input.cpp) tak żeby pytał o imię i nazwisko
    - jeśli podane jest tylko imię: wydrukować "Hi, ..."
    - jeśli podane jest tylko nazwisko: wydrukować "It's you, ..."
    - jeśli podane jest imię i nazwisko: wydrukować "Hello, ..."
    - jeśli nic nie jest podane: wydrukować "OK, keep your secrets"

- wiedząc, że funkcja składowa `std::string::back()` (wywołanie `s.back()`)
  zwraca ostatni znak napisu, napisz program, który wczyta z wiersza poleceń
  imię, a potem powie czy imię to "Pan" czy "Pani":
    - dla "Kasia" drukuje "Pani Kasia"
    - dla "Zbyszek" drukuje "Pan Zbyszek"
    - dodać obsługę błędów dla pustego napisu

Zacommitować, wypchnąć do repozytorium.

--------------------------------------------------------------------------------

# lekcja 3

Czego uczy?

- składniki języka:
    - alternatywa (`switch`: żeby wybrać jaką operację ma wykonać kalkulator)
    - obsługa błędów (`try`: żeby konwertować liczby; `std::cerr`: żeby
      poinformować o błędach)
    - iteration (`while`: żeby zapewnić dłuższe działanie kalkulatora)
- definiowanie stałych (lhs, rhs, action)
- definiowanie zmiennych (result)
- przypisanie do zmiennej

------------------------------------------------------------

- src/02-very-basic-calculator.cpp
- src/03-loops-intro.cpp
- src/s02-calculator.cpp (plik studenta)
- src/s03-fizzbuzz.cpp (plik studenta)
- src/s03-fizzbuzz-turbo.cpp (plik studenta)
- src/s02-echo.cpp (plik studenta)

----------------------------------------

### Zadanie

- do very-basic calculator dodać operacje mnożenia i dzielenia

- zaimplementować Fizz-Bizz (s03-fizzbuzz.cpp)
    - iteracja dowolną pętlą
    - zakres: od 1 do 30 włącznie
    - drukuje liczbę, spację, a potem...
        - jeśli liczba podzielna przez 3 to drukuje "Fizz"
        - jeśli liczba podzielna przez 5 to drukuje "Buzz"
        - jeśli liczba podzielna przez 3 i 5 to drukuje "FizzBuzz"
- niech FizzBuzz (s03-fizzbuzz-turbo.cpp) na początek wczytuje jako argumenty
  wiersza poleceń
    - pierwszą liczbę do testowania
    - drugą liczbę do testowania
    - początek zakresu
    - koniec zakresu
    - poza tym, tak samo jak zwykły fizzbuzz

- napisać program, który w pętli wypisze po kolei argumenty z wiersza poleceń
  (takie `echo(1)`)
- do tego programu dodać opcję `-n`: jeśli `-n` jest pierwszym argumentem to nie
  drukować znaku nowej linii

Zaimplementować kalkulator, który:

1. wczyta jedną liczbę
2. wczyta drugą liczbę
3. wczyta operację do wykonania
4. poda wynik
5. wróci do kroku 1.

Wymagane operacje to dodawanie, odejmowanie, mnożenie, dzielenie, i reszta z
dzielenia. Dla chętnych potęgowanie, silnia, i inne dwuargumentowe funkcje.

Zacommitować, wypchnąć do repozytorium.

--------------------------------------------------------------------------------

# lekcja X

- guessing game
