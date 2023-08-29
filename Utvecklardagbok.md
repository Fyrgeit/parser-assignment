# Dev diary - Parser
---
### TODO:
- [x] Write boilerplate
- [x] Open file
- [x] Define struct for relation entry
- [x] Create array for structs
- [x] Put all relations in array
    - [x] Add letters to source until comma
    - [x] Add letters to target until comma
    - [x] Add number to weight until newline
- [ ] Put all characters in array
    - [x] Make array and counter
---
## Vecka 35
### Måndag
Lyckades parsea all csv till en 2d array med relations. Stötte på problem med att strings som inte är fulla har massa random bokstäver efter att namnet tar slut. Fixade genom att avslute med \0 (string terminator).
### Tisdag
Försökte mig på att göra en array med alla unika namn, men fick bara alla namn. Det visade sig dock bara vara ett litet slarvfel (\n istället för \0). Fick också lära mig att man måste definiera längden på alla förutom den första dimensionen när man har en multidimensionell array som parameter i en funktion. Började också på input-loopen.