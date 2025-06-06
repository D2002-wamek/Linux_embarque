# Linux_embarque
TP LINUX EMBARQUE 

# Daniela DJEUNGA & Debora KITSOUKOU 

# 1 Prise en main 
# 1.1 Préparation de la carte SD 

Avant de commencer, il faut flasher la carte SD avec l’image fournie par Terasic. Elle est disponible sur le lien ci-dessus. Il s’agit du fichier suivant. 

# 1.2 Démarrage 

Insérons la carte SD fraichement programmée, branchons la carte VEEK-MT2S et allumons-la : bouton rouge ! Ça clignote de partout et un linux se lance. Prenons un peu de temps pour explorer les différents programmes fournis sur le bureau de Lxde. Mais sans clavier, ce n’est pas très pratique pour programmer cette « brique ».  

 

# 1.3 Connexion au système  
# 1.3.1 Liaison série  

Le premier moyen pour se connecter sur un objet embarqué, c’est très souvent par le port série. Une fois que l’on aura eu accès au DE-10, on configurera le réseau, pour pouvoir ensuite y accéder via ssh. Tout d’abord, déterminer le port à utiliser pour se connecter à la carte. Il y a plusieurs ports USB sur la carte :  
— 2 hôtes usb A  
— 1 usb B : max blaster pour la programmation 
— 1 usb mini : uart to usb ← c’est celui-là qui nous intéresse. 

# 1.3.2 Utilisons un logiciel de liaison série  
Sous Windows : Utilisons le logiciel PuTTy pour nous connecter grace au port série. Sélectionnons serial, et à l’aide du panneau de configuration de windows, cherchons le port COM de notre carte SoC. Pour la vitesse, entrons 115200. 

Quelle est la taille occupée ? 
La taille occupée est de 1.3GB sur les 3 GB de disponible. 
<img width="446" alt="Capture1" src="https://github.com/user-attachments/assets/2d9b0c2c-1559-4d6e-a784-d6c223fceeff" />

Des scripts sont fournis pour augmenter la taille du système de fichiers et profiter de l’ensemble de la carte SD : 
Rebootons la carte (proprement !), puis, une fois loggé : Vérifions que nous avons bien 32GB de disponible sur la carte SD. 
<img width="410" alt="image2" src="https://github.com/user-attachments/assets/7364e2f2-e305-4a06-9c83-ee04b16ec809" />
<img width="548" alt="image3" src="https://github.com/user-attachments/assets/0a96e7d5-c184-4263-a757-1596147f90dc" />
La carte ne dispose pas de 32 GB, ça taille est de 14 GB avec 12GB de disponible. 
Pour être sûre de la taille de notre carte SD, nous avons exécuté la commande lsblk et nous avons bien la confirmation que la taille de la carte SD est de 14 GB. 

 
# 1.3.3 Configuration réseau 

— Branchons la carte VEEK sur le switch via un câble réseau, 
— À l’aide de la commande ifconfig, vérifions que la carte dispose d’une adresse IP, 
<img width="552" alt="4" src="https://github.com/user-attachments/assets/9b4d746b-1040-49da-8745-16492eb6bb95" />

— Éditons le fichier /etc/network/interfaces 
<img width="401" alt="5" src="https://github.com/user-attachments/assets/47510133-eb01-48a1-bdff-9e6fef9db9cc" />

Rebootons  une nouvelle fois, et là normalement nous allons avoir une adresse IP correcte. Vérifions avec ifconfig. 
<img width="458" alt="6" src="https://github.com/user-attachments/assets/fc6dc512-ca6c-4291-b471-cd1cabe3693c" />

— Si tout est correct, nous devons pouvoir pinger avec le PC dans les 2 sens 
<img width="455" alt="7" src="https://github.com/user-attachments/assets/d69fd307-f909-46d8-89e7-1efd32577c3b" />

— Vérifions que dans le fichier /etc/ssh/sshd_config, la ligne suivante est présente : 
<img width="473" alt="8" src="https://github.com/user-attachments/assets/c89993d9-8db8-4ac7-9de7-e34d9184c4cf" />

— Nous pouvons nous logger en ssh sur la carte VEEK, avec Putty ou par le terminal : 
<img width="545" alt="9" src="https://github.com/user-attachments/assets/9df1cd0f-7818-4a2c-8eb9-476a6c1ca2c6" />

# 1.4 Découverte de la cible  
# 1.4.1 Exploration des dossiers /sys/class et /proc 
# 1.4.2 Compilation croisée 

Il existe deux méthodes pour compiler un programme sur le SoC . 

# 1.4.3 Hello world ! 
Réalisons un programme "Hello World !", compilons-le et testons-le sur la carte SoC. 

— Pour compiler sur la VM, utilisons le cross-compilateur 
<img width="547" alt="10" src="https://github.com/user-attachments/assets/acf69e4b-50dc-473a-aca5-dde24c238149" />

Nous pouvons vérifier le type de nos exécutables avec la commande file. 
Il ne se passe rien car le fichier hello.o a été créé spécialement pour le SoC et le terminale ne peut pas le lire. 

 

Comme la carte SOC est sur le réseau, nous pouvons copier l’exécutable directement sur la cible : 

 

Quand on teste sur la carte, on observe bien le message “hello world”. 

 

1.4.4 Accès au matériel 

Testons d’allumer et d’éteindre d’autres LED. 

 

 

1.4.5 Chenillard (Et oui, encore !) 

Le chénillard fonctionne bien.  

#include <stdio.h> #include <stdlib.h> // Pour system() 

#ifdef _WIN32 #include <windows.h> // Pour Sleep() #else #include <unistd.h> // Pour usleep() sur Unix/Linux #endif 

#include <fcntl.h> #include <string.h> 

#define NUM_LEDS 9 // Adapté à 9 LEDs 

const char *led_paths[NUM_LEDS] = { "/sys/class/leds/fpga_led0/brightness", "/sys/class/leds/fpga_led1/brightness", "/sys/class/leds/fpga_led2/brightness", "/sys/class/leds/fpga_led3/brightness", "/sys/class/leds/fpga_led4/brightness", "/sys/class/leds/fpga_led5/brightness", "/sys/class/leds/fpga_led6/brightness", "/sys/class/leds/fpga_led7/brightness", "/sys/class/leds/fpga_led8/brightness" }; 

// Allumer ou éteindre une LED void set_led(int index, int state) { int fd = open(led_paths[index], O_WRONLY); if (fd < 0) { perror("Erreur ouverture LED"); return; } 

const char *value = state ? "1" : "0"; 
if (write(fd, value, strlen(value)) < 0) { 
    perror("Erreur écriture LED"); 
} 
 
close(fd); 
  

} 

int main() { int position = 0; 

while (1) { 
    // Éteindre toutes les LEDs 
    for (int i = 0; i < NUM_LEDS; i++) { 
        set_led(i, 0); 
    } 
 
    // Allumer la LED courante 
    set_led(position, 1); 
 
    // Avancer à la LED suivante 
    position = (position + 1) % NUM_LEDS; 
 
    usleep(200000); // Pause de 200 ms 
} 
 
return 0; 
  

} 

2 Modules kernel (TP2) 

2.0 Reprise du TP1 

Assurons-nous de pouvoir communiquer avec la carte VEEK en ssh ou via le port série. Nous devons pour cela reprendre la configuration du réseau faite au TP1. 

 

2.1 Accès aux registres 

Avant de travailler avec les modules, nous allons créer un programme qui accède directement aux registres depuis l’espace utilisateur. À cause de la virtualisation de la mémoire, il n’est pas possible d’écrire facilement dans un registre comme nous en avons l’habitude. Il faut en effet remapper la mémoire pour demander à l’OS de nous fournir une adresse virtuelle. 

Pour cela, on utilisera la fonction mmap() 

Le registre du GPIO connecté aux LED est disponible à l’adresse suivante : 

— 0xFF203000 

Cette méthode permet de prototyper rapidement, mais pose quelques problème et limites. Quels sont-ils ? 

1.  Nécessite des droits root 

Accéder à /dev/mem ou à des adresses physiques nécessite généralement sudo. Cela limite l’utilisation dans un environnement sécurisé ou multi-utilisateur. 

2.  Pas de protection mémoire 

On accède directement à des registres matériels, donc une mauvaise écriture peut : 

Geler la machine. 

Planter un périphérique. 

-  Créer des conflits si un autre driver (noyau) utilise déjà cette ressource. 

3.  Pas de synchronisation avec les drivers du noyauu 

- On bypasses les pilotes Linux. 

- Si un driver du noyau utilise déjà ce GPIO, tu risques un conflit d’accès 	- concurrent non géré. 

4.  Pas de portabilité 

- Le code est très spécifique au matériel et aux adresses physiques 		définies dans la mémoire du SoC. 

- Il ne fonctionne que sur ta plateforme exacte. 

5.  Pas de gestion d’interruptions 

- Contrairement à un module noyau, tu ne peux pas gérer les interruptions 	matérielles avec ce genre de code. 

- On est limité à du polling actif (boucles bloquantes, peu efficaces). 

6.  Pas de sécurité mémoire 

- Le mapping peut rester actif ou incohérent si le processus plante. 

- Il n’y a aucune abstraction ni vérification comme avec un driver. 

 

2.2 Compilation de module noyau sur la VM  

Pour ce TP, nous allons développer nos propres modules noyau. Nous allons avoir besoin des sources du noyau cible (en fait en théorie il faut seulement les includes). Il nous faut les sources exactes du noyau sur lequel le module va être chargé. 

À partir du Makefile et du fichier source hello.c disponibles sur moodle, nous avons compilé notre premier module. Et lorsque nous utilisons modinfo, lsmod, insmod et rmmod pour tester notre module : nous constatons que le module fonctionne bien (sudo dmesg). 

Nous avons fait :  

Ls 

Cd src 

Ls 

Make 

Ls 

Sudo insmod module_simple.ko : il n’affiche rien 

Sudo dmesg (avant) : affiche le message 

 

Sudo rmmod module_simple : supprime module_simple du noyau 

 

Sudo dmesg (après) : pour vérifier que l’on est bien sortie du noyau 

 

lsmod 

 

  

 2.3 CrossCompilation de modules noyau  

À cause de la puissance limitée du processeur de la carte cible, la compilation, en particulier la compilation de modules noyau, est relativement longue. Nous allons donc, une fois encore, cross-compiler les modules noyau pour la carte SoC, à l’aide de la VM. 

 

2.3.1 Préparation de la compilation 

Notez le chemin vers ces compilateurs : whereis arm-linux-gnueabihf-gcc 

 

2.3.2 Récupération de la configuration actuelle du noyau 

Sur la carte SoC, récupérez le contenu du fichier /proc/config.gz dans le dossier des sources du noyau. Décompressez ce fichier dans le dossier ~/linux-socfpga/ et renommez-le en .config. 

Le <chemin_arm-linux-gnueabihf> est le chemin noté plus haut sans le gcc 

final. Par exemple : /usr/bin/arm-linux-gnueabihf- 

— Quel est le rôle des lignes commençant par export ? 

Ces lignes définissent des variables d’environnement que la commande make utilise pour faire de la compilation croisée du noyau ou des modules. 

 

— Pourquoi le chemin fini par un tiret "-" ? 

CROSS_COMPILE est un préfixe utilisé par make pour retrouver automatiquement les bons outils. Lorsqu’on écrit : CROSS_COMPILE=/usr/bin/arm-linux-gnueabihf- 

alors make cherchera automatiquement les outils comme : 

/usr/bin/arm-linux-gnueabihf-gcc → le compilateur 

/usr/bin/arm-linux-gnueabihf-ld → l'éditeur de liens 

/usr/bin/arm-linux-gnueabihf-as → l'assembleur 

Le tiret - final fait donc partie du nom standard du préfixe des outils croisés. 

 

2.3.3 Hello World 

Nous allons refaire les exercices précédents (Module, timers...) sur la plateforme VEEK. 

 Vérifions que le module fonctionne bien avec la commande dmesg. 

 

 

 

 

 

2.3.4 Chenillard 

On veut créer un chenillard dont on peut modifier : 

 

  

 

 

 

 

 

 

 

 

 
