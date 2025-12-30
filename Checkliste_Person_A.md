# Person A – Lexer, Parser, AST

Zeitraum: **02.01.26 – 20.01.26**
Arbeitsaufwand: **1–3 h pro Tag**

---

## 02.01. – Projektstart & Überblick

* Repo klonen, Build prüfen
* Aufgabenblatt vollständig lesen
* Grobe Parser-/AST-Verantwortung verstehen
* Notizen zu benötigten Sprachkonstrukten machen

## 03.01. – AST-Design

* AST-Knoten für:

  * Expressions
  * Statements
  * Declarations (Function, Class, Method)
* AST-Dateien anlegen
* Mit Team abstimmen (Fixpunkt!)

## 04.01. – Lexer Grundlagen

* Tokens für Keywords, Identifier, Literale
* Operatoren und Separatoren
* Zeilenkommentare (`//`, `#`)

## 05.01. – Lexer Erweiterungen

* Block-Kommentare `/* */`
* String- und Char-Literale mit Escapes
* Erste Lexer-Tests

## 06.01. – Parser: Expressions

* Operatorpräzedenz korrekt umsetzen
* Assignment als Expression
* Funktionsaufrufe

## 07.01. – Parser: Statements

* if / else
* while
* return
* Block `{}`

## 08.01. – Parser: Variablen & Funktionen

* Variablendeklarationen
* Referenz-Deklarationen
* Funktionsdefinitionen

## 09.01. – Parser: Klassen

* class-Definition
* Vererbungssyntax
* Felder & Methoden

## 10.01. – Parser: Konstruktoren & Methoden

* Konstruktor-Syntax
* virtual-Keyword
* Method Calls `obj.m()`

## 11.01. – Parser-Feinschliff

* Fehlerbehandlung
* Ambiguitäten entfernen
* Grammar Cleanup

## 12.01. – REPL-tauglicher Parser

* Mehrzeilige Eingaben unterstützen
* Erkennen unvollständiger Eingaben

## 13.01. – Dateiinput & main()

* Parsing kompletter Dateien
* main()-Signaturen zulassen

## 14.01. – Integration

* Parser + AST mit Semantik/Interpreter testen
* Bugs fixen

## 15.01. – Eigene Tests

* Positivtests (Parser)
* Negativtests (Syntaxfehler)

## 16.01. – Edge Cases

* Verschachtelte Klassen/Blöcke
* Komplexe Expressions

## 17.01. – Dokumentation

* Grammatik erklären (README)
* AST-Struktur dokumentieren

## 18.01. – Walk-Through Vorbereitung

* Relevante Parser-Stellen markieren

## 19.01. – Bugfix-Tag

* Letzte Parser-Probleme beheben

## 20.01. – Abgabe-Check

* Finaler Build-Test
* Commit & Push
