# InfoC++11 Nagy Házi Feladat 1: `MyString` Referenciaszámlálással (Copy-On-Write)

A tárgyban két nagy házi feladatot kell elkészíteni. Az első házinál a feladat kötött, egy összetettebb tároló osztály elkészítése.

## 1. Első feladat: `MyString`

A referenciaszámlálást nem csak arra használjuk, hogy tudjuk, hivatkozik-e még okos pointer egy objektumra, vagy fel lehet-e szabadítani. Arra is jó lehet, hogy a fölösleges másolásokat elkerüljük. Ha több objektum ugyanazzal az értékkel rendelkezik, akkor nincs értelme több másolatot is tartani a memóriában az értékről, hanem az objektumok osztozhatnak az érték egy közös reprezentációján. Így nem csak memóriát, hanem időt is spórolhatunk.

Erre is példa a szokásos állatorvosi lovunk, a sztring:
```cpp
MyString a, b, c;
a = b = c = "helló világ";
```
### Megosztás és Adatszerkezet

1.  **Megosztás nélkül**
    Ha nem osztjuk meg a karaktertömböket az egyes sztring objektumok között, a pazarlás nyilvánvaló.

    
2.  **Megosztással**
    Azt szeretnénk, ha a sztringek közös tömbbel rendelkeznének. Ez azonban így nem működhet, mert azt is kell tudnunk, hogy hány sztring használja ugyanazt a tömböt.

    
3.  **Referenciaszámlálással**
    Ezért jön a referenciaszámlálás a képbe. Fontos megfigyelni, hogy a referenciaszámlálók itt sem a sztring objektumokban, hanem a **sztringértékeket tároló objektumokban** vannak, mert az egyes tömböket hivatkozó objektumokat kell számolni. Ez egy erős csatolást jelent a karaktertömb és a referenciaszámláló között, ezért azokat érdemes egy objektumba tenni.


### Alapvető sztringműveletek

* **Új sztring létrehozásakor:** Új karaktertömb kell.
* **Meglévő sztring lemásolásakor:** A szöveget **nem kell lemásolni**, csak megnövelni a referenciaszámlálóját.
* **Sztring megszűnésekor:** A hivatkozott sztringérték referenciaszámlálóját **csökkenteni kell**. Ha nulla lett, akkor a sztringérték is törölhető.

### Másolás íráskor (Copy-on-Write)

Ez a kép addig ilyen szép, amíg nem engedjük meg a sztringek módosítását. De a sztringek megengedik a tartalmuk módosítását:

```cpp
MyString x = "hello";
MyString y = x;
y[0] = 'c';
// Az x sztringnek nem szabad megváltoznia.
```
Itt az `x` sztringnek nem szabad megváltoznia. Ezt a problémát a **„copy-on-write” (másolás íráskor)** technikával lehet megoldani:

* Ha egy sztring tartalmát módosítani akarjuk (például egy nem-konstans `operator[]` segítségével), előtte ellenőrizni kell, hogy a referenciaszámláló értéke **> 1**-e.
* Ha a számláló > 1, akkor a sztring tartalmáról egy **saját, új másolatot** kell készíteni (új karaktertömbbel és új, 1-es számlálóval), és a `MyString` objektum mutatóját erre kell állítani. A régi objektum referenciaszámlálóját csökkenteni kell.
* Csak ezután engedélyezett a módosítás a *saját* adaton.


***

## A feladat és Követelmények

### A feladat

Implementáld a **`MyString`** osztályt, és írj hozzá rövid tesztprogramot, amelyben minden függvényét legalább egyszer használod!

### Beadandó fájlok

* `mystring.cpp`
* `mystring.h`
* `test.cpp`

> A feltöltött ZIP-nek csak ezt a három fájlt kell tartalmaznia.

### Implementációs követelmények

* A sztring legyen **másolható** és **értékadható**.
* Valósítsd meg a **mozgató konstruktort** és **értékadást** is!
* **NE használj STL-t** (így `std::string`-et sem)! Ha nullával lezárt karaktertömbökkel dolgozol, használd a C-s sztringkezelő függvényeket (pl. `strcpy`).
* Valósítsd meg a következő műveleteket:
    * Létrehozás alapértelmezett konstruktorral
    * Létrehozás karaktertömbből
    * Két sztring összefűzése (`+` és `+=`)
    * Sztring és karakter összefűzése (`+` és `+=`)
    * Kiírás és beolvasás (`<<` és `>>`)
    * Hossz lekérdezése
    * Indexelés (`[]`)
* Írj mindent **≥C++11-esen**, amit csak lehet!

### Értékelési szempontok

* Ne „látszódjanak ki” implementációs részletek (pl. a referenciaszámlálás).
* Robusztus működés – ne lehessen memóriakezelési vagy egyéb hibába „kergetni” az osztályt a publikus interfészen keresztül.
* Memóriakezelés helyessége.
* OOP elvek betartása.
* A feladatkiírás pontos követése.
* Nyelvi eszközök rendeltetésszerű használata.
* A megoldás egyszerűsége (ne erőltess bele szükségtelen eszközöket).

> **Vigyázat:** memóriahiba (túlindexelés, szivárgás, stb.) esetén a program egyáltalán nem elfogadható. Vagyis ha a [Valgrind](http://valgrind.org/) hibát jelez a programra, akkor biztosan rossz. Ez határidő után is érvényes, félév végén is érvényes.
