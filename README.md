# IoT platform management App

## Project Overview

This project is about setting up a platform of **IoT** devices, we use here :

* sensors type : **Zolertia RE-Mote**
* Contiki-ng,
* **CoAP** Servers and client to request the Data from sensors
* MySQl Database to Store Data comming from those sensors
* And node-red, a JavaScript framework to build the backend App

Dependancies :

* nodejs >= 10.x.x
* npm >= 5.x.x
* node-red >= 0.18.x
* mysql version >= 5.x.x

A CoAP request is made by a client on node-red to sensors working as CoAP servers, the data is return in **JSON format** and then bind to an UI, and stored in an MySQL database.

A User **Interface (UI)** is also available from a browser on the host OS at {docker_ip_address}/1880/ui1

## Test

After installing all the dependancy below inside the docker container running contiki-ng, clone the repository :

* --> $ git clone <https://MoussaK@bitbucket.org/MoussaK/pfe-telecom-2.git>
* Launch node-red and import the flows :* First IPv6s_flow.json
  ..* Then database.json
  ..* And App_flow.json
* And --> **deploy**

Inject the timestamp for IPv6s_flow.json, and the timestamp for the database.json and then go to the UI url.

See more at <https://github.com/contiki-ng/contiki-ng/tree/develop/examples>.