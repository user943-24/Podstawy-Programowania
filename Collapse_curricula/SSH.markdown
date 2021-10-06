# SSH

--------------------------------------------------------------------------------

## Logowanie na zdalny serwer

    $ ssh <user>@<host>

Polecenie zaloguje nas na serwer `host` używając użytkownika `user`.

Przykład: logowanie jako "johndoe" na serwer "example.com"

    $ ssh johndoe@example.com

--------------------------------------------------------------------------------

## Generowanie klucza SSH (do logowania bez hasła)

    $ ssh-keygen -t rsa

Klucz publiczny, który można umieszczać w różnych serwisach, będzie znajdował
się w pliku `~/.ssh/id_rsa.pub`.

Klucz prywatny, którego pod żadnym pozorem nie można publikować, będzie
znajdował się w pliku `~/.ssh/id_rsa`. Dobrze jest go nie zgubić, bo inaczej
możemy stracić dostęp do serwerów, na które można zalogować się tylko kluczem.
