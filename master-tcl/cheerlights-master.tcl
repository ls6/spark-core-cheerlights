package require http
package require tls

#we are going to use https
::http::register https 443 ::tls::socket

proc getCheerlightsColor {} {
	set token [::http::geturl http://api.thingspeak.com/channels/1417/field/1/last.txt]
	set color [lindex [array get $token body] 1]
	::http::cleanup $token
	return $color
}

proc subscribeToCheerlights {} {
	puts [getCheerlightsColor]
	after 2000 subscribeToCheerlights
}

proc updateSparkCore {} {
	#set q [::http::formatQuery access_token NNNNN]
	#set token [::http::geturl https://api.spark.io/v1/devices/NNNNNN/ledColor -query $q]
	#set answer [lindex [array get $token body] 1]
	#if ![string equal $answer OK] {
	#	puts {Couldn't connect to Spark}
	#}
}

#run forever
subscribeToCheerlights
vwait forever
