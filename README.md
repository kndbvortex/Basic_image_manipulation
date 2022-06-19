# Basic image manipulation

Implementation in  C programming languange of simple process with images in computer vision

Après avoir executeé le makefile via la commande **make**, En fonction de l'action à exécuter, certains paramètres seront necessaire à la ligne de commande.<br/>
**image et image_bin** sont les chemins vers des images .pgm.<br/>
**rapport** est un nombre à virgule > 0.<br/>
**rayon** est un nombre entier positif représentant le rayon du filtre<br/>



Exemple d'exécution pour la transformation linéaire avec saturation(transAvecSat): <br />
```
./main transAvecSat images/input/port.pgm 2 100
```

<h2>Liste des arguments possibles </h2> 
<ul>
<li>hist image</li>
<li>luminance image</li>
<li>transLineaire image</li>
<li>transAvecSat image smin smax //2 et 50</li>
<li>inverse image</li>
<li>egalisation image</li>
<li>ou image image_bin</li>
<li>et image image_bin</li>
<li>xor image image_bin</li>
<li>addition image1 image2</li>
<li>soustraction image1 image2</li>
<li>multiplication image nombre</li>
<li>interploationSimple image rapport</li>
<li>interpolationBilineaire image rapport</li>
<li>interpolationBicubique image rapport</li>
<li>rotation image angle</li>
<li>convolution image</li>
<li>filtreMoyenneur image rayon</li>
<li>filtreGaussien image</li>
<li>filtreMedian image taill</li>
</ul>