
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
> modify password to **"kmvwqazh"**

> modify SSID WIFI name to **"Raspberry_OSI_@MAC"** 

> modify IP to **"10.3.141.X"** 

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

> First write this in terminal :
```python
sudo chmod -R 777 /var/www/
```
> Then continue typing in terminal :
```python
sudo chmod -R 777 /var/www/*
```
> Check your permission and access
```python
ls -l /var/www/html/
```

### Clear webpage contents
> Go to the repository /home/var/www

> Erase all contents in :file_folder: **www**

### Installation Apache
```python
sudo apt install apache2
```
```python
sudo apt install libapache2-mod-php
```
```python
sudo apt remove lighttpd --yes && sudo service apache2 start
```
> Check it
```python
sudo service --status-all
```

### Html folder
> Copy :file_folder: **html** from github repository

> Past :file_folder: **html** into your local Raspi folder /home/var/www

### Test your html page
> Verify that you are connected to the Raspberry Wifi

> Check if there is any issue with the PHP
```python
sudo tail -n 20 /var/log/apache2/error.log
```
> If there is no issue
```python
sudo service apache2 restart
```
> Reboot the Raspi
```python
sudo reboot 
```
:warning: **Even if you can display the webpage, buttons are not yet running** :warning:

# Main.py Setup

> Copy :page_facing_up: **main.py** from github repository

> Past :page_facing_up: **main.py** into your local Raspi folder /home/Desktop

> Check if it is OK

_Please think to connect the teensy and the Raspi by a usb cable !_

_Please think to upload the Arduino code into the teensy !_

```python
cd Desktop
```
```python
sudo python main.py
```
