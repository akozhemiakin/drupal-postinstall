
Postinstall module
---------------------
by Artem Kozhjemyakin, xenus.t@gmail.com

This simple module allows other modules to display and handle there 
postinstall settings forms immediately after they are installed.

To show, validate and submit your postinstall settings form you need to depend 
your module on Postinstall module and implement hook_postinstall(). You can 
read more about how to implement hook_postinstall in postinstall.api.php.
