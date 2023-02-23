#!/bin/bash

sudo mysqldump -uroot -p wpg > /home/Collab8/kramer/wpg.sql

sudo dpkg -P --force-depends mysql-client-5.7 
sudo dpkg -P --force-depends mysql-client-core-5.7 
sudo dpkg -P --force-depends mysql-common 
sudo dpkg -P --force-depends mysql-server 
sudo debconf-set-selections <<< "mysql-server-5.7 mysql-server-5.7/postrm_remove_databases boolean true"
sudo dpkg -P --force-depends mysql-server-5.7 
sudo dpkg -P --force-depends mysql-server-core-5.7 
sudo dpkg -P --force-depends libmysqlclient18

sudo dpkg -i libaio1_0.3.110-5ubuntu0.1_amd64.deb
sudo dpkg -i libmecab2_0.996-5_amd64.deb
sudo dpkg -i mecab-utils_0.996-5_amd64.deb
sudo dpkg -i mecab-ipadic_2.7.0-20070801+main-1_all.deb
sudo dpkg -i mecab-ipadic-utf8_2.7.0-20070801+main-1_all.deb
sudo dpkg -i mysql-community-client-plugins_8.0.32-1ubuntu18.04_amd64.deb
sudo dpkg -i mysql-community-client-core_8.0.32-1ubuntu18.04_amd64.deb
sudo dpkg -i mysql-common_8.0.32-1ubuntu18.04_amd64.deb
sudo dpkg -i mysql-community-client_8.0.32-1ubuntu18.04_amd64.deb
sudo dpkg -i mysql-client_8.0.32-1ubuntu18.04_amd64.deb
sudo dpkg -i mysql-community-server-core_8.0.32-1ubuntu18.04_amd64.deb
sudo debconf-set-selections <<< "mysql-community-server mysql-community-server/root-pass password w0wAdm1n8"
sudo debconf-set-selections <<< "mysql-community-server mysql-community-server/re-root-pass password w0wAdm1n8"
sudo debconf-set-selections <<< "mysql-community-server mysql-server/default-auth-override select Use Legacy Authentication Method (Retain MySQL 5.x Compatibility)"
sudo dpkg -i mysql-community-server_8.0.32-1ubuntu18.04_amd64.deb
sudo dpkg -i mysql-server_8.0.32-1ubuntu18.04_amd64.deb

mysql -uroot -pw0wAdm1n8 -e "create database wpg;"
mysql -uroot -pw0wAdm1n8 wpg < /home/Collab8/kramer/wpg.sql
mysql -uroot -pw0wAdm1n8 -e "CREATE USER 'viadbuser'@'localhost' IDENTIFIED BY 'w0wAdm1n8';"
mysql -uroot -pw0wAdm1n8 -e "GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, INDEX, ALTER, CREATE ROUTINE, ALTER ROUTINE, EXECUTE ON wpg.* TO 'viadbuser'@'localhost';"
mysql -uroot -pw0wAdm1n8 -e "FLUSH PRIVILEGES;"

sudo cp mysqld.cnf /etc/mysql/mysql.conf.d/
