# SurfaceMeasurer
### Projet Système (M3101) à l'IUT d'Arles, promo 2017

## Compilation
```sh
cd build
./build.sh
```

## Exécution
### Exécution en modes séquentiel et avec threads
```sh
./SurfaceMeasurer -t N chemin/vers/fichier.off
```

avec N threads (eg: -t 0, -t 2, -t 8)

### Exécution en mode OpenMP
```sh
./SurfaceMeasurer -omp chemin/vers/fichier.off
```

