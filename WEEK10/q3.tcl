set ns [new Simulator]
set nf [open out.nam w]

$ns namtrace-all $nf

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec /home/150905112/Desktop/nam out.nam &
exit 0
}

set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n1 $n2 2Mb 20ms DropTail
$ns duplex-link $n2 $n4 1Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail

$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n3 $n4 orient right
$ns duplex-link-op $n2 $n4 orient down

$ns duplex-link-op $n1 $n2 queuePos 0.5
$ns duplex-link-op $n3 $n4 queuePos 0.5

set cbr0 [new Agent/CBR]
$ns attach-agent $n1 $cbr0
$cbr0 set packetSize_ 1000
$cbr0 set interval_ 0.005

set cbr1 [new Agent/CBR]
$ns attach-agent $n3 $cbr1
$cbr1 set packetSize_ 1000
$cbr1 set interval_ 0.005

$cbr0 set fid_ 1
$cbr1 set fid_ 2

$ns color 1 Blue
$ns color 2 Red

set null0 [new Agent/Null]
$ns attach-agent $n2 $null0

set null1 [new Agent/Null]
$ns attach-agent $n4 $null1

$ns connect $cbr0 $null0
$ns connect $cbr1 $null1

$ns at 0.5 "$cbr0 start"
$ns at 1.0 "$cbr1 start"
$ns at 4.0 "$cbr1 stop"
$ns at 4.5 "$cbr0 stop"

$ns at 5.0 "finish"
$ns run

