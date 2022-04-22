#!/bin/bash
# Exemple de script shell qui mesure le temps d'exécution de
# "macommande" avec des arguments différents

/usr/bin/time -f '%e %U %S' macommande a
/usr/bin/time -f '%e %U %S' macommande b
/usr/bin/time -f '%e %U %S' macommande c