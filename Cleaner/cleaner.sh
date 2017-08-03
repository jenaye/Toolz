#!/bin/bash

sudo -s <<EOF

echo "Updating apt-get ..."
sudo apt-get update -y > /dev/null
sudo apt-get upgrade -y > /dev/null
sudo apt-get dist-upgrade -y > /dev/null
echo "Removing unused package ... "
sudo apt-get autoremove --purge -y > /dev/null
sudo apt-get install -f > /dev/null
sudo apt-get clean > /dev/null
echo "Cleaning temp files..."
rm -rf /home/antoxyde/Tmp/* > /dev/null
rm -rf /home/antoxyde/Downloads/* > /dev/null
echo "Cleaning cache files..."
sudo find / -type f -name "*~" -delete 2>/dev/null
echo "Emptying trash ..."
sudo rm -rf /home/antoxyde/.local/share/Trash/* > /dev/null
rm /home/antoxyde/.php_history > /dev/null
rm /home/antoxyde/.wget-hsts > /dev/null
rm /home/antoxyde/.xsession* > /dev/null
rm -rf /home/antoxyde/.cache/* > /dev/null
