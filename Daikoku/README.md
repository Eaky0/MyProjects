# Daikoku, A food trucker web application

<DUTCH>
Dag allemaal!

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

Atakan Kumas

<ENGLISH>
Hello everyone!

In this README file, you will find instructions on how to run the FoodTrucker project web application.

INSTRUCTIONS FOR DOCKERIZING THIS FOLDER:

First, enter the following command in the terminal within this directory and execute it.
This will build an image for the web application (don’t forget the dot!):

docker build -t dockerfile .

Next, enter and execute this command.
The image will be run, converted into a container, and executed:

docker run -p "8080:80" -v ${PWD}/codeigniter:/app -v ${PWD}/mysql:/var/lib/mysql dockerfile

In the Docker Desktop application, you can always start and stop this container.

It is recommended to wait 20 seconds before accessing the web application due to the startup process of the Apache web server and MySQL server.

You can now browse and test the website—good luck!

Note: MySQL often behaves unpredictably, so if you encounter issues, try running it again.

Best regards,
Atakan Kumas


(Note: It has been more than a year since this project was launched, I hope it still works as it used to)
