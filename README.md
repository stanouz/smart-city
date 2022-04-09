# Smart Parking

Projet académique lors du l'UE [LIFPROJET](http://cazabetremy.fr/wiki/doku.php). L’objectif de ce projet est de proposer une méthode distribuée pour l’affectation des places de stationnement à des véhicules intelligents. Le rôle de l’étudiant est de formaliser et d’implémenter l’ensemble des comportements nécessaires aux véhicules pour interagir avec les parkings et négocier le tarif de stationnement qui est décidé dynamiquement en tenant compte d’un ensemble d’information, telles que la durée du stationnement, le profil de l’usager, le taux d’occupation du parking, le créneau horaire, etc.

* ## Dépendances 
    * Pour compiler vous avez besoin d'avoir la librairie [SFML](https://www.sfml-dev.org/index-fr.php) installée.


* ## Comment générer le Makefile avec Cmake : 

    * `cd [CHEMIN-VERS-REPO]/smart-city`
    * `cmake -B build`

* ## Comment compiler avec le Makefile:
    * `make -C build`

* ## Comment executer :
    * `./bin/smart-city_exec`
