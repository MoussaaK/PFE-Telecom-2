# IoT platform management App

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

A CoAP request is made by a client on node-red to sensors working as CoAP servers and then the server is return in **JSON format** and then bind to an UI, and store in an MySQL database.

