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

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 10Mb 10ms SFQ

set udp [new Agent/UDP]
$ns attach-agent $n0 $udp

set null0 [new Agent/Null]
$ns attach-agent $n1 $null0
$ns connect $udp $null0

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp
$cbr0 set type_ CBR
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 10Mb
$cbr0 set random_ false

$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

$ns at 5.0 "finish"
$ns run
