# Arbore Fractal 2D - Proiect Grafică pe Calculator / Algoritmi

Aplicație grafică interactivă scrisă în **C++20** folosind biblioteca **Raylib**, care generează și vizualizează în timp real un **arbore fractal binar** prin intermediul recursivității și trigonometriei.

---

## Cuprins
1. [Descrierea Proiectului](#descrierea-proiectului)
2. [Concepte Teoretice și Algoritmice](#concepte-teoretice-și-algoritmice)
3. [Arhitectură și Implementare](#arhitectură-și-implementare)
4. [Complexitate Computațională](#complexitate-computațională)
5. [Controale și Utilizare](#controale-și-utilizare)
6. [Instalare și Rulare](#instalare-și-rulare)
7. [Ghid pentru Prezentare / Întrebări Posibile](#ghid-pentru-prezentare--întrebări-posibile)

---

## Descrierea Proiectului
Proiectul ilustrează principiul **fractalilor naturali** (specific arborilor biologici) printr-un model geometric recursiv. La fiecare nivel de adâncime, o ramură principală se divide în două sub-ramuri simetrice, având lungimea redusă cu un factor scalar fix și un unghi de deviație bine definit față de direcția ramurii părinte.

La nivelul frunzelor (ultimul pas recursiv), aplicația adaugă elemente vizuale specifice (frunze verzi), iar grosimea ramurilor scade progresiv de la trunchi spre vârfuri.

---

## Concepte Teoretice și Algoritmice

### 1. Recursivitatea
Algoritmul utilizează o funcție recursivă `DrawBranch` care se autoapelează pentru fiecare bifurcație:
- **Cazul de bază (Stop condition):** Dacă `step == 0`, funcția se oprește fără a mai desena sau apela alte instanțe.
- **Pasul recursiv:** Pentru fiecare ramură curentă, se generează două apeluri recursive pentru ramura din stânga (`angle - splitAngle`) și din dreapta (`angle + splitAngle`), decrementând parametrul pasului (`step - 1`).

### 2. Trigonometrie în Plan 2D
Poziția punctului final al unei ramuri $(X_{end}, Y_{end})$ este calculată pe baza punctului de start $(X_{start}, Y_{start})$, a lungimii curente $L$ și a unghiului $\theta$:
$$X_{end} = X_{start} + L \cdot \cos(\theta)$$
$$Y_{end} = Y_{start} + L \cdot \sin(\theta)$$

*Notă:* În sistemul de coordonate grafic (ecran), axa $OY$ este orientată în jos. De aceea, direcția inițială orientată în sus este $-\frac{\pi}{2}$ radiani (-90°).

### 3. Factori de scalare
- **Unghi de bifurcație (`splitAngle`):** $0.45 \text{ rad} \approx 25.78^\circ$
- **Raport de scurtare ramură (`lengthScale`):** $0.75$ (fiecare ramură este 75% din lungimea ramurii părinte).
- **Grosime dinamică (`thickness`):** $\text{step} \times 0.8$, oferind realism structurii lemnoase.

---

## Arhitectură și Implementare

### Tehnologii folosite:
- **Limbaj:** C++20
- **Bibliotecă grafică:** [Raylib 5.5](https://www.raylib.com/) (integrată automat prin `CMake FetchContent`)
- **Build System:** CMake (v3.25+)

### Structura Fișierelor:
- `main.cpp`: Conține logica buclei principale de joc/randare (`game loop`), gestiunea input-ului de la tastatură și algoritmul recursiv de desenare.
- `CMakeLists.txt`: Scriptul de configurare și descărcare automată a bibliotecii Raylib.

---

## Complexitate Computațională

| Parametru | Valoare / Formulă |
| :--- | :--- |
| **Număr ramuri pe ultimul nivel (frunze)** | $2^{N - 1}$ |
| **Număr total de ramuri desenate** | $2^N - 1$ |
| **Complexitate Temporală** | $\mathcal{O}(2^N)$ |
| **Complexitate Spațială (Stiva de apeluri)** | $\mathcal{O}(N)$ |

*Unde $N$ reprezintă numărul de pași (`currentSteps`).*

Exemplu practic:
- La $N = 3$: Total ramuri = $2^3 - 1 = 7$.
- La $N = 10$: Total ramuri = $2^{10} - 1 = 1023$.
- La $N = 14$ (limita maximă setată): Total ramuri = $2^{14} - 1 = 16383$.

---

## Controale și Utilizare

- **Săgeată SUS (KEY_UP):** Crește numărul de pași recursivi (până la maxim 14).
- **Săgeată JOS (KEY_DOWN):** Scade numărul de pași recursivi (până la minim 1).
- **ESC sau Închidere Fereastră:** Oprește aplicația.

Pe ecran sunt afișate în timp real:
- Nivelul curent de recursivitate.
- Numărul de frunze generate la pasul curent.
- Numărul total de segmente (crengi) randate pe cadru.

---

## Instalare și Rulare

### Cerințe preliminare:
- Compilator C++ cu suport C++20 (GCC, Clang sau MSVC)
- CMake 3.25+
- Conexiune la internet la primul build (pentru `FetchContent` Raylib)

### Comenzi de compilare:
```bash
# Generare configurare build
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Compilare proiect
cmake --build build

# Rulare executabil
./build/arbore_2d
```
*(Sau deschideți proiectul direct în **CLion** / **VS Code** și apăsați Run).*
