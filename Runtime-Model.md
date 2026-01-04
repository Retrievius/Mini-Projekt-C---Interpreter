# Runtime Model (ASCII)

Dieses Dokument beschreibt das Runtime-Modell des C++-Subset-Interpreters.
Es kann direkt ins Repository übernommen und im README referenziert werden.

---

## Überblick

Der Interpreter verwendet ein **zellbasiertes Runtime-Modell**:

* **Variablen besitzen Cells** (Speicherzellen)
* **Referenzen zeigen auf Cells** (Alias)
* **Values** liegen in Cells
* **Objekte** sind Values mit Feldern + `dynamicType`
* **Stack Frames** enthalten lokale Variablen
* **Polymorphie** erfolgt nur über Referenzen

---

## Gesamtübersicht Runtime

```
+--------------------------------------------------+
|                  Global Scope                    |
|--------------------------------------------------|
|  Class B { virtual f(); }                        |
|  Class D : public B { override f(); }            |
|  function main()                                 |
+--------------------------------------------------+

                 |
                 v

+--------------------------------------------------+
|                    Call Stack                    |
|--------------------------------------------------|
| StackFrame: main                                 |
|                                                  |
|  d : Cell ----------------------------------+    |
|                                              |   |
|  b : Reference ---------------------------+  |   |
|                                           |  |   |
|  x : Cell ----> Value(int = 2)             |  |   |
|                                           |  |   |
+-------------------------------------------|--|---+
                                            |  |
                                            v  |
                                +---------------------------+
                                |        Object Value        |
                                |---------------------------|
                                | dynamicType = D            |
                                | fields:                    |
                                |   (from B)                 |
                                |   (from D)                 |
                                +---------------------------+

b references the same Cell as d
```

---

## Referenz vs Kopie

### Kopie (Value-Semantik)

```
int a = 1;
int b = a;

Cell a ---> [1]
Cell b ---> [1]   (separate cell)
```

### Referenz (Alias-Semantik)

```
int a = 1;
int& r = a;

Cell a ---> [1]
   ^
   |
Reference r
```

Zuweisung an `r` schreibt in die Cell von `a`.

---

## Slicing

```
class D : public B { ... }

D d;
B b = d;

Object D (B-part + D-part)
        |
        | assignment (copy only B-part)
        v
Object B (only B-part)
```

Der D-spezifische Teil geht verloren.

---

## Virtueller Methodenaufruf

Beispiel:

```
B& b = d;
b.f();
```

Ablauf:

```
1. b ist Reference -> zeigt auf Cell von d
2. Statischer Typ: B
3. Methode f() in B ist virtual
4. DynamicType = D
5. Aufruf von D::f()
```

Nicht-virtuelle Methoden werden **immer statisch** gebunden.

---

## Wichtige Invarianten

* Referenzen haben **keinen eigenen Value**
* Objekte liegen **nicht auf einem Heap**, sondern sind normale Values
* Polymorphie nur über Referenzen
* Stack Frames kapseln lokale Variablen

---

## Zweck dieses Dokuments

Dieses Diagramm dient:

* als Designgrundlage
* zur Erklärung im Walk-Through
* zur Rechtfertigung von Dispatch-Logik
* als Referenz beim Implementieren des Interpreters
