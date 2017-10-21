set ns [new Simulator]
set nt [open simulate.nam w]
$ns namtrace-all $nt

set tr [open simulate.tr w]
$ns trace-all $tr

proc finish {} {
global ns nt tr
$ns flush-trace
close $nt
close $tr
exec /home/150905112/Desktop/nam simulate.nam &
exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n0 $n2 2Mb 10ms DropTail

$ns queue-limit $n0 $n1 10
$ns queue-limit $n0 $n2 10

$ns duplex-link-op $n0 $n1 orient right-up
$ns duplex-link-op $n0 $n2 orient right-down

$ns duplex-link-op $n0 $n1 queuePos 0.5
$ns duplex-link-op $n0 $n2 queuePos 0.5

set tcp [new Agent/TCP]
$tcp set class_ 1
$ns attach-agent $n0 $tcp

set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink
$tcp set fid_ 2


set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

set udp [new Agent/UDP]
$ns attach-agent $n0 $udp

set null0 [new Agent/Null]
$ns attach-agent $n1 $null0
$ns connect $udp $null0
$udp set fid_ 1

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp
$cbr0 set type_ CBR
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 2.1Mb
$cbr0 set random_ false

$ns color 1 Blue
$ns color 2 Red


$ns at 0.1 "$cbr0 start"
$ns at 1.0 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr0 stop"

$ns at 5.0 "finish"
$ns run

