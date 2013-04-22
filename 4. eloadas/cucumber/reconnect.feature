Feature: Reconnect
	In order to handle wifi and network disconnections
	As a user of the program
	I want the program to try reconnect after network disconnection happened

Scenario: Disconnect notification
	Given I have disabled the network
	When I wait 10 sec
	Then the error message should be network is down

Scenario: Reconnect notification
	Given I have enabled the network
	When I wait 10 sec
	Then the error message should be network is up


