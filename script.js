// script.js

 // create the module and name it scotchApp
 // also include ngRoute for all our routing needs
 var scotchApp = angular.module('scotchApp', ['ngRoute']);

 // configure our routes
 scotchApp.config(function($routeProvider) {
 $routeProvider

 // route for the home page
 .when('/', {
 templateUrl : 'pages/home.html',
 controller : 'mainController'
 })

 // route for the about page
 .when('/sensors', {
 templateUrl : 'pages/sensors.html',
 controller : 'sensorsController'
 })

 // route for the contact page
 .when('/contact', {
 templateUrl : 'pages/contact.html',
 controller : 'contactController'
 });
 });

 // create the controller and inject Angular's $scope
 scotchApp.controller('mainController', function($scope) {
 // create a message to display in our view
 $scope.message = 'Welcome on your managment Platform !';
 });

 scotchApp.controller('sensorsController', function($scope) {
 $scope.message = 'Look! I am the sensors page.';
 });

 scotchApp.controller('contactController', function($scope) {
 $scope.message = 'Contact us! JK. This is just a demo.';
 });