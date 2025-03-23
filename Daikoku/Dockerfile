# Web Programming project base from mattrayner/lamp
# Ubuntu 20.04 base-layer with PHP 8
FROM mattrayner/lamp:latest-2004-php8

# CodeIgniter requires intl module
RUN apt-get -y update && apt-get -y install php8.0-intl
RUN sed -i "s/;extension=intl/extension=intl/" /etc/php/8.0/apache2/php.ini

# Fix symlinks for CodeIgniter 4 security model
# .htaccess rewrite by default enables FollowSymlinks
RUN rm /var/www/html
RUN ln -s /app/public /var/www/html
RUN sed -i "s/<Directory \/>/<Directory \/var\/www>/" /etc/apache2/sites-available/000-default.conf

# mattrayner/lamp original boot code
CMD ["/run.sh"]