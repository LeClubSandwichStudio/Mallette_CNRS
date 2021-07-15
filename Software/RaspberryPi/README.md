
# TABLE OF CONTENTS

- OS Installation
- Remote desktop test and installation
- Server and webpage setup
- Main.py setup

# OS Installation

### Installation [RaspOS](https://www.raspberrypi.org/software/)
> id : pi

> mdp : kmvwqazh

### Installation [Clavier AZERTY](https://www.framboise314.fr/clavier-virtuel-matchbox-en-azerty-sur-le-raspberry-pi/)

### Installation de [RaspAP](https://raspap.com/#quick) 

Dans les paramètres en se connectant au point d’accès,  
> modifier le mdp en : "kmvwqazh" 

> modifier le nom ddu SSID WIFI en : "Raspberry_OSI_@MAC" 

> modifier l'IP en : "10.3.141.X" 

### Installation [XRDP](https://linuxize.com/post/how-to-install-xrdp-on-raspberry-pi/)

# Remote desktop test and installation

**Work In progress**

*Only use if you need to control remotly the Raspi from your personal desktop without working directly on the Raspi*

# Server and webpage setup

### Check for updates
```python
sudo apt-get update
```
### Upgrade if needed 
```python
sudo apt-get upgrade
```
### Reboot Raspi
```python
sudo reboot
```
### Add permission to modify webpage folder
```python
chmod -R 777 /var/www/
```
> Check your permission and access
```python
ls -l /var/www/html/
```

### Clear webpage contents
> Go to the repository /home/var/www
> Erase all contents in :file_folder: **www**

