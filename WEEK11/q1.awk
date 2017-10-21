BEGIN{
fsRecv_tcp = 0;
numFs_tcp = 0;
fsRecv_udp = 0;
numFs_udp = 0;
}
{
action = $1;
time = $2;
from = $3;
to = $4;
type = $5;
pktsize = $6;
flow_id = $8;
src = $9;
dest = $10;
seq_no = $11;
packet_id = $12;
if(from == 0 && to==1 && action=="+")
numFs_udp++;
if(flow_id == 1 && action == "r")
fsRecv_udp++;
if(from == 0 && to==2 && action =="+")
numFs_tcp++;
if(from == 0 && to == 2 && action == "r")
fsRecv_tcp++;
}
END{
printf("TCP: Sent=%d Received=%d Packet Delivery Ratio=%f\n",numFs_tcp,fsRecv_tcp,(fsRecv_tcp/numFs_tcp));
printf("UDP: Sent=%d Received=%d Packet Delivery Ratio=%f\n",numFs_udp,fsRecv_udp,(fsRecv_udp/numFs_udp));
}
