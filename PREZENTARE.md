# Ghid de Prezentare Proiect: Arbore Fractal 2D

Acest document conține structura completă a susținerii proiectului în fața profesorului, explicația detaliată a codului și răspunsurile la posibilele întrebări teoretice și practice.

---

## 1. Discursul de Prezentare (Ce spui la început - ~1-2 minute)

> **„Bună ziua, domnule profesor.**  
>  
> Proiectul meu constă într-o aplicație grafică interactivă dezvoltată în **C++20** folosind biblioteca **Raylib**, care generează și vizualizează în timp real un **arbore fractal binar** bazat pe principii de recursivitate și trigonometrie.  
>  
> În natură, structura arborilor respectă principiul fractal de auto-similaritate: fiecare ramură devine trunchiul unor noi sub-ramuri. În aplicație, am modelat acest fenomen printr-un algoritm recursiv în care fiecare ramură generează două noi ramuri simetrice, scalate în lungime și grosime.  
>  
> Aplicația este complet interactivă: utilizatorul poate ajusta în timp real adâncimea fractalului (nivelurile de recursivitate) folosind tastele **SĂGEATĂ SUS** și **SĂGEATĂ JOS**, iar programul recalculează instant numărul de crengi și frunze afișate, menținând o rată stabilă de 120 FPS.”

---

## 2. Explicația Codului Sursă (`main.cpp`)

Dacă profesorul te pune să deschizi codul și să explici linia cu linie, iată punctele-cheie:

### A. Funcția recursivă `DrawBranch`
```cpp
void DrawBranch(Vector2 startPos, float length, float angle, int step, int maxStep) {
    if (step == 0) return; // 1. Condiția de oprire (Base case)

    // 2. Calculul capătului crengii prin trigonometrie
    Vector2 endPos;
    endPos.x = startPos.x + cos(angle) * length;
    endPos.y = startPos.y + sin(angle) * length;

    // 3. Grosimea dinamică
    float thickness = (step > 1) ? (float)step * 0.8f : 1.0f;
    Color branchColor = { 101, 67, 33, 255 }; // Maro

    DrawLineEx(startPos, endPos, thickness, branchColor);

    // 4. Frunze la ultimul nivel
    if (step == 1) {
        DrawCircleV(endPos, 4.0f, GREEN);
    }

    // 5. Scalare și unghiuri pentru bifurcație
    float splitAngle = 0.45f; // ~25.7 grade
    float lengthScale = 0.75f; // fiecare ramură nouă e 75% din cea anterioară

    // 6. Cele două apeluri recursive (stânga și dreapta)
    DrawBranch(endPos, length * lengthScale, angle - splitAngle, step - 1, maxStep);
    DrawBranch(endPos, length * lengthScale, angle + splitAngle, step - 1, maxStep);
}
```

#### Ce explici la fiecare secțiune:
1. **Condiția de oprire (`step == 0`):** Garantează terminarea recursivității. Fără ea, programul ar intra în buclă infinită și ar genera eroare de *Stack Overflow*.
2. **Trigonometrie în 2D:** Punctul de final se calculează transformând coordonatele polare $(L, \theta)$ în coordonate carteziene $(\Delta x, \Delta y)$:
   $$\Delta x = L \cdot \cos(\theta)$$
   $$\Delta y = L \cdot \sin(\theta)$$
3. **De ce unghiul de pornire este `-PI / 2`:** În sistemul de coordonate al ecranului, originea $(0,0)$ este în colțul din stânga-sus, iar axa $OY$ este orientată în jos. Pentru a orienta trunchiul în sus, este necesar un unghi de $-90^\circ$ (adică $-\frac{\pi}{2}$ radiani).
4. **Bifurcația:** Creanga părinte se termină la `endPos`, punct care devine `startPos` pentru cele două crengi copil. Se deviază cu `+splitAngle` spre dreapta și `-splitAngle` spre stânga.
5. **Elemente vizuale:** Grosimea scade proporțional cu nivelul, iar când `step == 1` (frunzele arborelui), desenăm cercuri verzi folosind `DrawCircleV`.

---

## 3. Matematică și Complexitate Algoritmică

| Întrebare Posibilă | Răspuns Exact |
| :--- | :--- |
| **Care este complexitatea în timp?** | **$\mathcal{O}(2^N)$**, unde $N$ este numărul de pași (`currentSteps`). Arborele este binar complet, dublându-și numărul de apeluri la fiecare nivel. |
| **Care este complexitatea în spațiu?** | **$\mathcal{O}(N)$**. Memoria suplimentară este dată de stiva de apeluri a funcției recursive (Call Stack), adâncimea maximă a stivei fiind exact $N$. |
| **Câte crengi sunt desenate în total?** | **$2^N - 1$** segmente (suma unei progresii geometrice: $1 + 2 + 4 + \dots + 2^{N-1} = 2^N - 1$). |
| **Câte frunze sunt la ultimul nivel?** | **$2^{N-1}$** frunze. |
| **De ce maxim 14 pași (`MAX_STEPS = 14`)?** | La pasul 14 se generează $2^{14} - 1 = 16.383$ segmente pe fiecare cadru. La 120 FPS, GPU-ul/CPU-ul randează aproape 2 milioane de segmente pe secundă. O valoare mai mare ar duce la scăderi bruște de cadre pe secundă fără un câștig vizual sesizabil. |

---

## 4. Scenariul Demonstrației Live (Pas cu pas)

1. **Pornirea aplicației:**
   * Rulează programul din CLion sau terminal.
   * Fereastra se deschide la pasul inițial $N = 3$.
2. **Explicarea interfeței:**
   * Arată textul din stânga-sus: Nivel curent, Ramuri la ultimul pas, Total ramuri desenate.
3. **Creșterea complexității:**
   * Apasă tasta **SĂGEATĂ SUS** treptat ($4 \to 5 \to 6 \dots \to 10$).
   * Explică: *„Observați cum la fiecare pas arborele devine mai dens, ramurile se subțiază spre vârf, iar la capete apar frunzele verzi.”*
4. **Testarea limitelor:**
   * Urcă până la pasul 14 pentru a arăta că randarea rămâne fluidă (120 FPS) chiar și la peste 16.000 de crengi.
   * Apasă **SĂGEATĂ JOS** până la pasul 1 (doar trunchiul cu o frunză).

---

## 5. Întrebări „Capcană” și Cum să le Răspunzi

* **Î: De ce ai folosit Raylib și nu OpenGL pur sau SFML?**  
  * **R:** *„Raylib oferă o curbă excelentă de învățare, o interfață C/C++ simplă și modernă, și elimină boilerplate-ul masiv din OpenGL pur (cum ar fi scrierea manuală de shadere și buffere VBO/VAO), permițând concentrarea directă pe algoritmica fractalului.”*

* **Î: Cum ai putea optimiza desenarea dacă am vrea 25 de pași?**  
  * **R:** *„Pentru $N = 25$ ($2^{25} \approx 33$ milioane de crengi), abordarea clasică pe CPU devine ineficientă. Am putea optimiza prin:*
    1. *Calcularea instanțiată pe GPU folosind Compute Shaders sau Instanced Rendering.*
    2. *Randarea într-o textură o singură dată (Render Texture / offscreen buffer) și redesenarea texturii dacă pasul nu se schimbă, evitând recalcularea la fiecare cadru.”*

* **Î: De ce este inclus `<math.h>`?**  
  * **R:** *„Pentru funcțiile trigonometrice `cos()` și `sin()` folosite la calculul vectorilor de deplasare, precum și pentru funcția `pow()` folosită la calcularea statisticilor afișate pe ecran.”*
