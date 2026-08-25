# Modello matematico della simulazione gravitazionale N-body

## 1. Obiettivo

La simulazione descrive il moto di \(N\) corpi puntiformi che si attraggono reciprocamente secondo la legge di gravitazione universale di Newton.

Il moto avviene in due dimensioni. Per ogni corpo \(i\) conosciamo:

- la posizione \(\mathbf r_i=(x_i,y_i)\);
- la velocità \(\mathbf v_i=(v_{x,i},v_{y,i})\);
- l'accelerazione \(\mathbf a_i=(a_{x,i},a_{y,i})\);
- la massa \(m_i\).

Lo scopo è calcolare come posizione e velocità cambiano nel tempo.

## 2. Interazione tra due corpi

Consideriamo due corpi, indicati con \(i\) e \(j\), nelle posizioni

$$
\mathbf r_i=(x_i,y_i),
\qquad
\mathbf r_j=(x_j,y_j).
$$

Il vettore che va dal corpo \(i\) al corpo \(j\) è

$$
\mathbf r_{ij}=\mathbf r_j-\mathbf r_i
              =(x_j-x_i,\,y_j-y_i).
$$

Definiamo quindi

$$
\Delta x=x_j-x_i,
\qquad
\Delta y=y_j-y_i.
$$

La distanza tra i due corpi è la norma del vettore \(\mathbf r_{ij}\):

$$
r_{ij}=\lVert\mathbf r_{ij}\rVert
=\sqrt{(x_j-x_i)^2+(y_j-y_i)^2}.
$$

## 3. Legge di gravitazione universale

Il modulo della forza gravitazionale esercitata dal corpo \(j\) sul corpo \(i\) è

$$
F_{ij}=G\frac{m_i m_j}{r_{ij}^2},
$$

dove \(G\) è la costante di gravitazione universale.

La forza è diretta dal corpo \(i\) verso il corpo \(j\). Il versore che individua questa direzione è

$$
\widehat{\mathbf r}_{ij}
=\frac{\mathbf r_{ij}}{r_{ij}}
=\left(
\frac{x_j-x_i}{r_{ij}},
\frac{y_j-y_i}{r_{ij}}
\right).
$$

La forza vettoriale è quindi

$$
\mathbf F_{ij}
=F_{ij}\widehat{\mathbf r}_{ij}
=G\frac{m_i m_j}{r_{ij}^3}\mathbf r_{ij}.
$$

Il termine \(r_{ij}^3\) compare perché al fattore \(1/r_{ij}^2\) della legge gravitazionale si aggiunge il fattore \(1/r_{ij}\) del versore.

## 4. Accelerazione prodotta dal corpo \(j\)

Dalla seconda legge di Newton,

$$
\mathbf F_i=m_i\mathbf a_i,
$$

l'accelerazione del corpo \(i\) dovuta al corpo \(j\) è

$$
\mathbf a_{ij}
=\frac{\mathbf F_{ij}}{m_i}
=Gm_j\frac{\mathbf r_j-\mathbf r_i}{r_{ij}^3}.
$$

La massa \(m_i\) si semplifica: l'accelerazione del corpo \(i\) dipende dalla massa \(m_j\) che genera il campo gravitazionale.

Separando le due componenti otteniamo

$$
a_{x,ij}
=Gm_j\frac{x_j-x_i}{r_{ij}^3},
$$

$$
a_{y,ij}
=Gm_j\frac{y_j-y_i}{r_{ij}^3}.
$$

Sostituendo l'espressione della distanza:

$$
a_{x,ij}
=Gm_j
\frac{x_j-x_i}
{\left[(x_j-x_i)^2+(y_j-y_i)^2\right]^{3/2}},
$$

$$
a_{y,ij}
=Gm_j
\frac{y_j-y_i}
{\left[(x_j-x_i)^2+(y_j-y_i)^2\right]^{3/2}}.
$$

## 5. Estensione a \(N\) corpi

Per il principio di sovrapposizione, l'accelerazione totale del corpo \(i\) è la somma delle accelerazioni prodotte da tutti gli altri corpi:

$$
\mathbf a_i
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{\mathbf r_j-\mathbf r_i}{r_{ij}^3}.
$$

In componenti:

$$
a_{x,i}
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{x_j-x_i}{r_{ij}^3},
$$

$$
a_{y,i}
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{y_j-y_i}{r_{ij}^3},
$$

con

$$
r_{ij}=\sqrt{(x_j-x_i)^2+(y_j-y_i)^2}.
$$

Il termine con \(j=i\) deve essere escluso: un corpo non esercita forza gravitazionale su se stesso e, inoltre, si avrebbe \(r_{ii}=0\), cioè una divisione per zero.

## 6. Sistema di equazioni differenziali

Il problema continuo è descritto dalle equazioni

$$
\frac{d\mathbf r_i}{dt}=\mathbf v_i,
$$

$$
\frac{d\mathbf v_i}{dt}=\mathbf a_i
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j\frac{\mathbf r_j-\mathbf r_i}
{\lVert\mathbf r_j-\mathbf r_i\rVert^3},
$$

per ogni \(i=0,\ldots,N-1\).

Date le posizioni e le velocità iniziali,

$$
\mathbf r_i(0)=\mathbf r_{i,0},
\qquad
\mathbf v_i(0)=\mathbf v_{i,0},
$$

il simulatore approssima la soluzione a istanti discreti.

## 7. Discretizzazione del tempo

Dividiamo il tempo in intervalli di ampiezza \(\Delta t\):

$$
t_n=n\Delta t,
\qquad
t_{n+1}=t_n+\Delta t.
$$

Indichiamo con

$$
\mathbf r_i^n\approx\mathbf r_i(t_n),
\qquad
\mathbf v_i^n\approx\mathbf v_i(t_n)
$$

la posizione e la velocità numeriche al passo \(n\).

### Metodo di Eulero esplicito

Approssimando le derivate con differenze finite in avanti si ottiene

$$
\frac{\mathbf v_i^{n+1}-\mathbf v_i^n}{\Delta t}
\approx\mathbf a_i^n,
$$

$$
\frac{\mathbf r_i^{n+1}-\mathbf r_i^n}{\Delta t}
\approx\mathbf v_i^n.
$$

Da cui

$$
\mathbf v_i^{n+1}
=\mathbf v_i^n+\mathbf a_i^n\Delta t,
$$

$$
\mathbf r_i^{n+1}
=\mathbf r_i^n+\mathbf v_i^n\Delta t.
$$

Questo metodo è semplice, ma nelle simulazioni orbitali tende ad accumulare rapidamente errore energetico: l'orbita può allargarsi o restringersi artificialmente.

### Metodo di Euler–Cromer

Una scelta più adatta, pur restando molto semplice, consiste nell'aggiornare prima la velocità e poi usare la nuova velocità per la posizione:

$$
\boxed{
\begin{aligned}
\mathbf v_i^{n+1}
&=\mathbf v_i^n+\mathbf a_i^n\Delta t,\\
\mathbf r_i^{n+1}
&=\mathbf r_i^n+\mathbf v_i^{n+1}\Delta t.
\end{aligned}}
$$

In componenti:

$$
v_{x,i}^{n+1}=v_{x,i}^n+a_{x,i}^n\Delta t,
\qquad
v_{y,i}^{n+1}=v_{y,i}^n+a_{y,i}^n\Delta t,
$$

$$
x_i^{n+1}=x_i^n+v_{x,i}^{n+1}\Delta t,
\qquad
y_i^{n+1}=y_i^n+v_{y,i}^{n+1}\Delta t.
$$

Euler–Cromer è ancora un metodo del primo ordine, ma in genere descrive le orbite molto meglio dell'Eulero esplicito.

## 8. Singolarità e softening gravitazionale

Quando due corpi sono molto vicini, \(r_{ij}\) diventa piccolo e il termine \(1/r_{ij}^3\) può produrre accelerazioni enormi. Con un passo temporale finito questo può rendere instabile la simulazione.

Una regolarizzazione comune consiste nell'introdurre un piccolo parametro \(\varepsilon>0\):

$$
\mathbf a_i
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j
\frac{\mathbf r_j-\mathbf r_i}
{\left(r_{ij}^2+\varepsilon^2\right)^{3/2}}.
$$

In componenti:

$$
a_{x,i}
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j
\frac{x_j-x_i}
{\left[(x_j-x_i)^2+(y_j-y_i)^2+\varepsilon^2\right]^{3/2}},
$$

$$
a_{y,i}
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j
\frac{y_j-y_i}
{\left[(x_j-x_i)^2+(y_j-y_i)^2+\varepsilon^2\right]^{3/2}}.
$$

Il softening evita la singolarità numerica, ma modifica leggermente la forza a distanze molto piccole. Non sostituisce un vero modello di collisione.

## 9. Corrispondenza con l'algoritmo

Per ogni passo temporale il programma esegue le seguenti operazioni:

1. azzera l'accelerazione di ogni corpo;
2. per ogni corpo \(i\), somma il contributo gravitazionale di ogni corpo \(j\ne i\);
3. aggiorna tutte le velocità;
4. aggiorna tutte le posizioni;
5. disegna i corpi nelle nuove posizioni.

È importante calcolare tutte le accelerazioni usando le posizioni dello stesso istante \(t_n\). Non bisogna spostare un corpo mentre si stanno ancora calcolando le forze sugli altri, altrimenti alcuni contributi userebbero posizioni al passo \(n\) e altri posizioni al passo \(n+1\).

Il calcolo diretto considera tutte le coppie di corpi e richiede un numero di operazioni proporzionale a

$$
N(N-1),
$$

quindi la complessità temporale di ogni passo è

$$
\boxed{O(N^2)}.
$$

## 10. Caso di un corpo centrale fermo

Se si vuole mantenere un corpo di massa \(M\) fisso nell'origine, si impone

$$
\mathbf r_M=(0,0),
\qquad
\mathbf v_M=(0,0)
$$

e non si aggiornano né la sua posizione né la sua velocità.

Un corpo di massa \(m\), posto a distanza \(R\), descrive idealmente un'orbita circolare se la velocità iniziale è tangenziale e ha modulo

$$
\boxed{v=\sqrt{\frac{GM}{R}}}.
$$

Per esempio, se il corpo parte da \((R,0)\), una possibile velocità iniziale è

$$
\mathbf v=(0,v).
$$

Se invece entrambi i corpi devono muoversi, essi orbitano attorno al comune centro di massa e le condizioni iniziali devono garantire quantità di moto totale nulla.

## 11. Quantità fisiche da controllare

In assenza di collisioni e forze esterne, il sistema continuo conserva alcune grandezze.

### Energia totale

L'energia cinetica è

$$
K=\sum_{i=0}^{N-1}\frac12m_i\lVert\mathbf v_i\rVert^2.
$$

L'energia potenziale gravitazionale è

$$
U=-\sum_{i<j}G\frac{m_i m_j}{r_{ij}}.
$$

L'energia totale è

$$
E=K+U.
$$

### Quantità di moto totale

$$
\mathbf P=\sum_{i=0}^{N-1}m_i\mathbf v_i.
$$

### Momento angolare in due dimensioni

$$
L_z=\sum_{i=0}^{N-1}m_i
\left(x_i v_{y,i}-y_i v_{x,i}\right).
$$

Nel calcolo numerico queste quantità non rimangono perfettamente costanti, ma la loro deriva deve restare piccola. Se l'errore cresce rapidamente, il passo \(\Delta t\) è probabilmente troppo grande oppure il metodo di integrazione è poco adatto.

## 12. Limiti del modello

Il modello assume che:

- i corpi siano puntiformi;
- agisca soltanto la gravità newtoniana;
- non siano presenti attrito o forze esterne;
- non avvengano collisioni, fusioni o frammentazioni;
- il moto sia limitato a due dimensioni.

Queste ipotesi sono sufficienti per studiare orbite e sistemi gravitazionali semplici. Le collisioni possono essere aggiunte in seguito come estensione separata.

## 13. Formula finale usata dalla simulazione

Per ogni corpo \(i\), al passo \(n\), si calcola

$$
\boxed{
\mathbf a_i^n
=\sum_{\substack{j=0\\j\ne i}}^{N-1}
Gm_j
\frac{\mathbf r_j^n-\mathbf r_i^n}
{\left(\lVert\mathbf r_j^n-\mathbf r_i^n\rVert^2+\varepsilon^2\right)^{3/2}}
}
$$

e poi, con Euler–Cromer,

$$
\boxed{
\begin{aligned}
\mathbf v_i^{n+1}
&=\mathbf v_i^n+\mathbf a_i^n\Delta t,\\
\mathbf r_i^{n+1}
&=\mathbf r_i^n+\mathbf v_i^{n+1}\Delta t.
\end{aligned}}
$$

Queste equazioni costituiscono il nucleo matematico del simulatore N-body.
