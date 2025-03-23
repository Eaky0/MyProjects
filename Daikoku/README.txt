Beste onderwijsteam,

In deze README file, volgen er instructies i.v.m. het runnen van de foodtrucker project web-applicatie:

INSTRUCTIES VOOR HET DOCKERIZEN VAN DEZE FOLDER:

-Ten eerste, schrijft u het volgende commando in de terminal van deze directory en voert u het uit.
-Hiermee wordt een image gebouwd voor de web-applicatie (vergeet de punt niet!):

docker build -t dockerfile .

-Vervolgens, schrijft u deze commando en voert u het uit.
-De image zal gerund worden en omgevormd worden tot een container en uitgevoerd worden. 

docker run -p "8080:80" -v ${PWD}/codeigniter:/app -v ${PWD}/mysql:/var/lib/mysql dockerfile

-In de docker desktop applicatie, kunt u deze container altijd laten uitvoeren en uitzetten.
-Het is aangeraden om 20 seconden te wachten, vooraleer u de web-applicatie wil bekijken, wegens het opstarten
van de apache-webserver provider en de my-sql server.
-U kunt nu gerust de website surfen en testen, veel succes!

-Opmerking: Meestal doet mysql raar, dus kunt u het best proberen om het opnieuw te runnen.

Met vriendelijke groeten,

Atakan Kumas, Student 2-BACH INF
