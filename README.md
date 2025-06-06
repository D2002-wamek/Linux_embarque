# Linux_embarque
TP Linux embarqué
# 1.3.1 Liaison série

Le premier moyen pour se connecter sur un objet embarqué, c’est très souvent par le port série. Une fois que l’on aura eu accès au DE-10, on configurera le réseau, pour pouvoir ensuite y accéder via ssh. Tout d’abord, déterminer le port à utiliser pour se connecter à la carte. Il y a plusieurs ports USB sur la carte :  

— 2 hôtes usb A  
— 1 usb B : max blaster pour la programmation 
— 1 usb mini : uart to usb ← c’est celui-là qui nous intéresse.

# 1.3.2 Utilisons un logiciel de liaison série  
Sous Windows : Utilisons le logiciel PuTTy pour nous connecter grace au port série. Sélectionnons serial, et à l’aide du panneau de configuration de windows, cherchons le port COM de notre carte SoC. Pour la vitesse, entrons 115200. 

Quelle est la taille occupée ? 
La taille occupée est de 1.3GB sur les 3 GB de disponible. 
Des scripts sont fournis pour augmenter la taille du système de fichiers et profiter de l’ensemble de la carte SD. (voir image dans le compte rendu pdf)

Rebootons la carte (proprement !), puis, une fois loggé : Vérifions que nous avons bien 32GB de disponible sur la carte SD. 
La carte ne dispose pas de 32 GB, ça taille est de 14 GB avec 12GB de disponible. 
Pour être sûre de la taille de notre carte SD, nous avons exécuté la commande lsblk et nous avons bien la confirmation que la taille de la carte SD est de 14 GB. (voir pdf question 1.3.2)



