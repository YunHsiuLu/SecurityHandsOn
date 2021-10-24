FROM handsonsecurity/seed-server:apache-php

COPY bash_shellshock /bin/
COPY *.cgi /usr/lib/cgi-bin/
COPY *.sh /usr/lib/cgi-bin/
COPY server_name.conf  /etc/apache2/sites-available
RUN  chmod 755 /bin/bash_shellshock \
     && chmod 755 /usr/lib/cgi-bin/*.cgi  \
     && chmod 755 /usr/lib/cgi-bin/*.sh \
     && a2ensite server_name.conf  

CMD service apache2 start && tail -f /dev/null


