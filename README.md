
# Esame Tecniche di Programmazione Avanzata 3 Settembre 2021 - Fabbrica


Una fabbrica costruisce diversi tipi di prodotti (X,Y,Z ...). Un pezzo in assemblamento viene chiamato artefatto e necessita di essere instradato su una serie di linee di assemblaggio (A,B,C,D, ....). Ogni linea di assemblaggio ha diversi macchinari (e,f,g,h, ...) che possono o meno operare sull'artefatto. Le operazioni da compiere sull'artefatto sono prescritte in un piano che al momento della definizione di un tipo di prodotto vengono inserite da un ingegnere sotto forma di sequenza di identificatori di linee di assemblaggio e macchinari.
Ogni volta che un macchinario opera su un artefatto, viene compiuto un ciclo macchina. Ogni macchinario ha associato un numero limite di cicli, dopo il quale si ferma e richiede una revisione. Se un macchinario è in revisione, non può processare artefatti. 

Anche le linee di assemblaggio hanno un limite di cicli: in questo caso per cicli intendiamo il numero di artefatti che entrano nella catena. Raggiunto il limite l'intera catena richiederà revisione, e pertanto tutti i macchinari si dovranno fermare (a prescindire dai loro limiti singoli).


```
 
         Stopped?   Cycle
 X  A               5/10
 Z  |-e             2/3              
    |-f             3/4              
 X  |-g             2/4
 X  |-h     *       5/5
    |-i             2/7

           
 Z  B               6/30            
 Z  |-l             2/3             
    |-m             2/5
 Y  |-n     *       4/4 
    |-o             1/7


 Z  C       *       20/20
    |-p     *       1/4
 Z  |-q     *       8/8
 Y  |-r     *       2/3          


```


## Modello dati


- assumi che non possano esserci macchinari con identificatori duplicati
- assumi che non possano esserci linee di assemblaggio con identificatori duplicati
- assumi che ogni assembly line abbia almeno una macchina
- una stazione può contenere solo un artefatto alla volta
- ogni stazione ha scorrimento indipendente dalle altre
- assumiamo che lo scorrimento sia veloce: a condizione che non ci altri artefatti che ostruiscono la corsa, in un solo step un artefatto può saltare subito al macchinario successivo indicato dal proprio piano anche se è a più posizioni di distanza nella linea di assemblaggio.


## Metodologia:

- **IMPORTANTE**: TUTTO il codice può essere implementato negli header .h come inline, **NON** perdere tempo a creare cpp e/o separare il corpo dei metodi
- Si suppone che l'utente sviluppatore interagisca col software solo attraverso la classe Factory: non dovrebbe essergli possibile manomettere le classi interne, quindi se esponete qualcosa usate opportuni meccanismi di protezione (incapsulamento / const)
- Detto ciò, **NON** perdete tempo a creare classi super incapsulate con getter / setter, se vi serve qualche struttura di appoggio semplicemente usate una struct che di default ha già tutto public
- vi vengono forniti un abbozzo di main.cpp e la libreria smart.h con qualche struttura e funzione di utilità
- La minimizzazione del codice attraverso scomposizione in classi, riuso metodi, etc sarà premiata
- l'uso di puntatori e allocazione dinamica verrà opportunamente premiato in fase di valutazione


## Che fare:


1.1 Implementare `Factory` e overload cout factory in modo da mostrare la situazione. Implementare step assumendo un solo tipo di prodotto

1.2 provare esempi e supportare più tipi di prodotto

1.3 Tenere conto dei fermi macchina: se una macchina è ferma, se è vuota può accettare artefatti ma non può processarli.

2. **Una volta fatto quanto sopra**, si potrebbero:

- supportare più di una assembly line, con piani complessi tipo A e g h B l m C q
- implementare comando di revisione per sbloccare i macchinari
- implementare movimento manuale: se un macchinario è bloccato, artefatti in coda potrebbero essere manualmente spostati a quello successivo

**IMPORTANTE 1**: sicuramente non avrete il tempo di implementare a dovere tutto quanto, piuttosto scegliete alcuni aspetti e aggiungete dei test **significativi** (max 100 righe di codice) che dimostrino l'efficacia della vostra soluzione. 

**IMPORTANTE 2**: ai fini dell'esame quando viene incontrata una condizione d'errore è sufficiente che che il programma termini (i.e. sollevando eccezioni), non perdete tempo a fare gestione accurata degli errori (blocchi try) che vi porterebbero via troppo tempo.

## Esempio di esecuzione

**NOTA**: è **solo** un abbozzo di display del main, ogni cosa va opportunamente valutata


DEBUG: adding machine e maintenance: 4
DEBUG: adding machine f maintenance: 8
DEBUG: adding machine g maintenance: 5
DEBUG: adding machine h maintenance: 3
DEBUG: adding machine i maintenance: 7
DEBUG: adding machine l maintenance: 9
DEBUG: adding machine m maintenance: 4
DEBUG: adding machine n maintenance: 4

DEBUG: adding assembly line A maintenance:10, machines: e, f, g, h, i, m

  A     0/10
  |-e   0/4
  |-f   0/8
  |-g   0/5
  |-h   0/3
  |-i   0/7
  |-m   0/4


DEBUG: adding product type X plan: A, e, f, h, i, m
DEBUG: factory.enqueue of product type X
DEBUG: AssemblyLine A: enqueue:
X A     0/10
  |-e   0/4
  |-f   0/8
  |-g   0/5
  |-h   0/3
  |-i   0/7
  |-m   0/4


DEBUG: factory.step()
stepping assembly line A ....
  A     1/10
X |-e   0/4
  |-f   0/8
  |-g   0/5
  |-h   0/3
  |-i   0/7
  |-m   0/4

DEBUG: factory.step()
stepping assembly line A ....
  A     1/10
  |-e   1/4
X |-f   0/8
  |-g   0/5
  |-h   0/3
  |-i   0/7
  |-m   0/4


DEBUG: factory.step()
stepping assembly line A ....
  A     1/10
  |-e   1/4
  |-f   1/8
  |-g   0/5
X |-h   0/3
  |-i   0/7
  |-m   0/4


DEBUG: factory.enqueue of product type X

X A     1/10
  |-e   1/4
  |-f   1/8
  |-g   0/5
X |-h   0/3
  |-i   0/7
  |-m   0/4

DEBUG: factory.step()

stepping assembly line A ....
  A     2/10
X |-e   1/4
  |-f   1/8
  |-g   0/5
  |-h   1/3
X |-i   0/7
  |-m   0/4


DEBUG: factory.step()

stepping assembly line A ....
  A     2/10
  |-e   2/4
X |-f   1/8
  |-g   0/5
  |-h   1/3
  |-i   1/7
X |-m   0/4

DEBUG: factory.step()

stepping assembly line A ....
  A     2/10
  |-e   2/4
  |-f   2/8
  |-g   0/5
X |-h   1/3
  |-i   1/7
  |-m   1/4

```
