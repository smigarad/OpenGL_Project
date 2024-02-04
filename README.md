# ZPG PROJEKT
## Zadání
* Cílem projektu bude vytvořit funkčí aplikaci.
*  Aplikace bude napsána objektově v jazyku c++. 
*  Bude obsahovat návrhové vzory jako Composite, Observer apod.
*  Ve finálním produktu se bude moct procházet uživatel po scéně, která bude obsahovat objekty, které budou mít vlastní chování.
  
## Popis struktury projektu
* Projekt obsahuje jednotlivé source soubory ve složce `src`.
* Projekt obsahuje hlavičkové soubory ve složce `include`.
* Projekt obsahuje složku `models`, která obsahuje modely pro jednotlivé objekty.
  

## Popis změn
* 2 cviko -- Vytvoření základních tříd, jako  je `Application`, `Scene`, `DrawableObject`, `Shader`, `ShaderProgram`, `Model`.
* 3 cviko -- Vytvoření tříd `Transformation`, `Rotate`, `Scale`, `Translation` a načítání složitějších modelů.
* 4 cviko -- Přidání Kamery, otáčení kamery pomocí myši, chození pomocí kláves WASD.
* 5 cviko -- Přídání světla do fragment shaderů. Refaktoring kódu. Přidání vzoru `Observer` pro managování předávání informací mezi kamerou, shadery a scénou.
* 6 cviko -- Dělání scén pro kontrolu projektu, refaktoring kódu.
* 7 cviko -- Přidání vícero druhů světel jako `Point Light`, `Directional Light` a `Spotlight`. Taktéž úprava Fragment shaderů pro možnost zpracování více světel ve scéně.
* 8 cviko -- Načítání textur.
* 9 cviko -- Načítání složitějších modelů s příponou .obj.
* 10 cviko -- Stencil buffer, indexování objektů, unproject.
* 11 cviko -- Finální úpravy projektu, Finální scéna prezentující jednotlivé náplně předešlých cvičení.


## Aktuální stav
![Suzi picture](../cv2/monke.png)

## SMI0132 - Radek Šmiga
### 2020/2021
