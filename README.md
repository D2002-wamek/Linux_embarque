# Linux_embarque
TP Linux embarqué
# 1.3.1 Liaison série

Le premier moyen pour se connecter sur un objet embarqué, c’est très souvent par le port série. Une fois que l’on aura eu accès au DE-10, on configurera le réseau, pour pouvoir ensuite y accéder via ssh. Tout d’abord, déterminer le port à utiliser pour se connecter à la carte. Il y a plusieurs ports USB sur la carte :  

— 2 hôtes usb A  
— 1 usb B : max blaster pour la programmation 
— 1 usb mini : uart to usb ← c’est celui-là qui nous intéresse.
