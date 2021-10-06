## Inicjalizacja repozytorium:

    $ git init

Repozytorium zostanie zainicjalizowane w katalogu roboczym (working directory).

--------------------------------------------------------------------------------

## Klonowanie repozytorium

    $ git clone https://git.example.com/john.doe/example-project

Repozytorium zostanie sklonowane do katalogu "example-project". Żeby zmienić
nazwę tego katalogu można ją dodać za adresem URL repozytorium:

    $ git clone https://git.example.com/john.doe/example-project custom-name

Powyższa komenda sklonuje repozytorium do katalogu "custom-name".

--------------------------------------------------------------------------------

## Zapisanie zmian

    $ git commit

Zapisze zmiany w "staging area". Żeby zapisać wszystkie zmiany:

    $ git commit -a

Żeby zapisać zmiany w pojedynczym pliku (lub grupie plików):

    $ git commit <file-0> <file-1> <file-N>

--------------------------------------------------------------------------------

## Dodanie plików i zmian do "staging area" lub zaznaczenie ich do śledzenia

    $ git add <file>

Doda to wszystkie zmiany z pliku. Jeśli plik `<file>` nie był śledzony przez Git
to powyższe polecenie nakaże Gitowi śledzić ten plik.

Żeby dodać tylko wycinek zmian (np. zmiany w jednej funkcji):

    $ git add -p

--------------------------------------------------------------------------------

## Jak utworzyć nową gałąź kodu?

    $ git branch <new-branch>

Utworzy gałąź wywodzącą się z najnowszego commitu na obecnej gałęzi. Można też
utworzyć gałąź i od razu do niej przejść:

    $ git checkout -b <new-branch>

Przykład: utworzenie gałęzi o nazwie "nowa-wersja" i przejście na nią

    $ git checkout -b nowa-wersja

--------------------------------------------------------------------------------

## Jak przejść między gałęziami kodu?

    $ git checkout <switch-to-this-branch>

Spowoduje to przeniesienie się do żądanej gałęzi.

Przykład: przeniesienie się na gałąź o nazwie "master"

    $ git checkout master

--------------------------------------------------------------------------------

## Jak połączyć dwie gałęzie kodu?

    $ git checkout <base-branch>
    $ git merge <patch-branch>

Polecenie `git merge` spowoduje włączenie zmian z podanej gałęzi do obecnej
gałęzi.

Przykład: włączenie zmian z gałęzi "problemy" do gałęzi "master"

    $ git checkout master
    $ git merge problemy

--------------------------------------------------------------------------------

## Jak usunąć gałąź z repozytorium lokalnego? Ze zdalnego?

    $ git branch -d <branch>
    $ git push --delete <remote> <branch>

Pierwsze polecenie usuwa gałąź z repozytorium lokalnego, drugie ze zdalnego.

Przykład: usunięcie gałęzi "problemy" z repozytorium lokalnego

    $ git branch -d problemy

Przykład: usunięcie gałęzi "foo" z repozytorium zdalnego "origin"

    $ git push --delete origin foo

--------------------------------------------------------------------------------

## Jak wypchnąć zmiany w repozytorium lokalnym do repozytorium zdalnego?

Repozytorium lokalne: to jest to, które mamy na komputerze.
Repozytorium zdalne: to jest to, które jest "gdzieś w Internecie"; np. w
serwisach Gitlab, Sourcehut, albo Github.

    $ git push

Jeśli wysłamy jakąś gałąź kodu po raz pierwszy:

    $ git push --set-upstream origin <branch>

--------------------------------------------------------------------------------

## Jak pobrać zmiany z repozytorium zdalnego do repozytorium lokalnego?

    $ git pull

To polecenie pobierze zmiany z repozytorium zdalnego i spróbuje je połączyć ze
zmianami w repozytorium lokalnym.
