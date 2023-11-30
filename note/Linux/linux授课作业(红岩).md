# level0

课件有不懂的多看看，上网搜搜，消化消化课上的内容，多实践实践。（不检查）

# level1

编写shell脚本,实现人机"石头,剪刀,布"游戏(计算机的出拳由随机数决定,出拳可以数字代替)

> 提交源文件和运行截图

# level2

编写shell脚本监控系统内存和磁盘容量，小于给定值(自己根据需求设置)时报警，并创建一个Systemd单位文件来管理脚本的启动、停止和管理。与此同时再写一个timer来调度你的监控脚本，以在指定的时间间隔内运行。

> 提交源文件和systemctl status xxx的截图

# level3

逐步详细阅读以下代码，遇到什么不懂就查什么，为其写出详细注释

```shell
#!/bin/bash
route=/usr/local
path=/usr/src
data=/opt/data

if [ ! -d $path/apr-1.7.0 ];then
	tar xf packages/apr-1.7.0.tar.gz -C $path
fi

if [ ! -d $path/apr-util-1.6.1 ];then
	tar xf packages/apr-util-1.6.1.tar.gz -C $path
fi

if [ ! -d $path/httpd-2.4.51 ];then
	tar xf packages/httpd-2.4.51.tar.gz -C $path
fi

if [ ! -d $route/php-8.0.12 ];then
        tar xf packages/php-8.0.12.tar.gz -C $route
fi

if [ ! -d $route/mysql-5.7.34-linux-glibc2.12-x86_64 ];then
	tar xf packages/mysql-5.7.34-linux-glibc2.12-x86_64.tar.gz -C $route
	cd $route 
	ln -s mysql-5.7.34-linux-glibc2.12-x86_64 mysql
fi

if [ ! -f /etc/yum.repos.d/CentOS-Base.repo ];then
	curl -o /etc/yum.repos.d/CentOS-Base.repo https://mirrors.aliyun.com/repo/Centos-8.repo
fi

yum -y install epel-release wget make openssl openssl-devel pcre pcre-devel gcc gcc-c++ zlib-devel expat-devel zlib expat

yum groups mark install 'Development Tools' -y

id apache &> /dev/null
if [ $? -ne 0 ];then
	useradd -r -M -s /sbin/nologin apache
fi

cd $path/apr-1.7.0
if [ ! -d $route/apr ];then
	sed -i 's/$RM "cfgfile"/d' configure
	./configure --prefix=/usr/local/apr
	make && make install
fi

cd $path/apr-util-1.6.1
if [ ! -d $route/apr-util-1.6.1 ];then
	./configure --prefix=/usr/local/apr-util --with-apr=/usr/local/apr
	make && make install
fi

cd $path/httpd-2.4.51
if [ ! -d $route/httpd-2.4.51 ];then
	./configure --prefix=/usr/local/apache \
        --enable-so \
        --enable-ssl \
        --enable-cgi \
        --enable-rewrite \
        --with-zlib \
        --with-pcre \
        --with-apr=/usr/local/apr \
        --with-apr-util=/usr/local/apr-util/ \
        --enable-modules=most \
        --enable-mpms-shared=all \
        --with-mpm=prefork
	make && make install
fi

if [ $? -eq 0 ];then
        echo "apache 编译完成"
else
	echo "apache 编译失败，请检查"
fi

ln -s /usr/local/apache/include/ /usr/include/httpd
echo 'export PATH=/usr/local/apache/bin:$PATH' > /etc/profile.d/httpd.sh

cd $route/apache/conf/
sed -i '203s/#//g' httpd.conf

touch /usr/lib/systemd/system/httpd.service
sum=$(cat /usr/lib/systemd/system/httpd.service | wc -l)
if [ $sum -lt 2 ];then
cat > /usr/lib/systemd/system/httpd.service << EOF
[Unit]
Description=httpd server daemon
After=network.target

[Service]
Type=forking
ExecStart=/usr/local/apache/bin/apachectl start
ExecStop=/usr/local/apache/bin/apachectl stop
ExecReload=/bin/kill -HUP \$MAINPID

[Install]
WantedBy=multi-user.target
EOF
fi

systemctl daemon-reload
systemctl enable --now httpd


echo "安装mysql依赖"
yum -y install  zlib zlib-devel pcre pcre-devel openssl openssl-devel ncurses-compat-libs perl ncurses-devel cmake

id mysql &> /dev/null
if [ $? -ne 0 ];then
	useradd -r -M -s /sbin/nologin mysql
fi


chown -R mysql.mysql $route/mysql
echo 'export PATH=/usr/local/mysql/bin:$PATH' > /etc/profile.d/mysql.sh

mkdir -p /opt/data
chown -R mysql.mysql /opt/data/


look=$( ls $data | wc -l)
if [ $look -eq 0 ];then	
$route/mysql/bin/mysqld --initialize-insecure --user mysql --datadir /opt/data/

cat > /etc/my.cnf << EOF
[mysqld]
basedir = $route/mysql
datadir = $data
socket = /tmp/mysql.sock
port = 3306
pid-file = /opt/data/mysql.pid
user = mysql
skip-name-resolve
EOF

sed -ri "s#^(basedir=).*#\1$route/mysql#g" /usr/local/mysql/support-files/mysql.server

sed -ri "s#^(datadir=).*#\1$data#g" /usr/local/mysql/support-files/mysql.server

cat > /usr/lib/systemd/system/mysql.service << EOF
[Unit]
Description=mysql server daemon
After=network.target

[Service]
Type=forking
ExecStart=/usr/local/mysql/support-files/mysql.server start
ExecStop= /usr/local/mysql/support-files/mysql.server stop
ExecReload=/bin/kill -HUP \$MAINPID

[Install]
WantedBy=multi-user.target
EOF
fi

systemctl daemon-reload 
systemctl enable --now mysql

echo "部署PHP"


yum -y install libxml2 libxml2-devel openssl openssl-devel bzip2 bzip2-devel libcurl libcurl-devel libicu-devel libjpeg libjpeg-devel libpng libpng-devel openldap-devel  pcre-devel freetype freetype-devel gmp gmp-devel libmcrypt libmcrypt-devel readline readline-devel libxslt libxslt-devel mhash mhash-devel php-mysqlnd libsqlite3x-devel libzip-devel epel-release

if [ ! -f ./oniguruma-devel-6.8.2-2.el8.x86_64.rpm ];then
wget http://mirror.centos.org/centos/8/PowerTools/x86_64/os/Packages/oniguruma-devel-6.8.2-2.el8.x86_64.rpm
yum -y install oniguruma-devel-6.8.2-2.el8.x86_64.rpm
fi

cd $route/php-8.0.12
if [ ! -d $route/php8 ];then
	./configure --prefix=/usr/local/php8  --with-config-file-path=/etc --enable-fpm --disable-debug --disable-rpath --enable-shared --enable-soap --with-openssl --enable-bcmath --with-iconv --with-bz2 --enable-calendar --with-curl --enable-exif  --enable-ftp --enable-gd --with-jpeg --with-zlib-dir --with-freetype --with-gettext --enable-mbstring --enable-pdo --with-mysqli=mysqlnd --with-pdo-mysql=mysqlnd --with-readline --enable-shmop --enable-simplexml --enable-sockets --with-zip --enable-mysqlnd-compression-support --with-pear --enable-pcntl --enable-posix && \
	make && make install
fi

echo 'export PATH=/usr/local/php8/bin:$PATH' > /etc/profile.d/php.sh

cd $route/php-8.0.12
cp php.ini-production /etc/php.ini

cd $route/php-8.0.12/sapi/fpm
cp init.d.php-fpm /etc/init.d/php-fpm

chmod +x /etc/rc.d/init.d/php-fpm

cp $route/php8/etc/php-fpm.conf.default $route/php8/etc/php-fpm.conf
cp $route/php8/etc/php-fpm.d/www.conf.default $route/php8/etc/php-fpm.d/www.conf

touch /usr/lib/systemd/system/php-fpm.service
view=$(cat /usr/lib/systemd/system/php-fpm.service | wc -l)
if [ $view -lt 2 ];then
cat > /usr/lib/systemd/system/php-fpm.service << EOF
[Unit]
Description=php server daemon
After=network.target

[Service]
Type=forking
ExecStart=/etc/init.d/php-fpm start
ExecStop=/etc/init.d/php-fpm stop
ExecReload=/bin/kill -HUP $MAINPID

[Install]
WantedBy=multi-user.target
EOF
fi

systemctl daemon-reload
systemctl enable --now php-fpm

sed -i '120s/#//g' /usr/local/apache/conf/httpd.conf
sed -i '124s/#//g' /usr/local/apache/conf/httpd.conf


cd $route/apache/htdocs && mkdir -p test
cd $route/apache/htdocs/test
if [ ! -s index.php ];then
cat > index.php << EOF
<?php
    phpinfo();
?>
EOF


chown -R apache.apache /usr/local/apache/htdocs/
cd $route/apache/conf
cat >> httpd.conf << EOF
<VirtualHost *:80>
    DocumentRoot "/usr/local/apache/htdocs/test"
    ServerName www.test.com
    ProxyRequests Off
    ProxyPassMatch ^/(.*\.php)$ fcgi://127.0.0.1:9000/usr/local/apache/htdocs/test/$1
    <Directory "/usr/local/apache/htdocs/test">
        Options none
        AllowOverride none
        Require all granted
    </Directory>
</VirtualHost>
EOF

cd $route/apache/conf
sed -i '261s/index.html/index.php &/g' httpd.conf
fi

systemctl restart php-fpm.service
systemctl restart httpd.service  && sleep 5
```

# level4(选做)

初步了解一下nginx，为自己的服务器搭建一个基于nginx的文件分享服务器，可以通过wget下载文件，如果是虚拟机可以就在本地测试。



