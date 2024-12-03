/*
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"

// Default Network Topology
//
//   Wifi 10.1.3.0
//                 AP
//  *    *    *    *
//  |    |    |    |    10.1.1.0
// n5   n6   n7   n0 -------------- n1   n2   n3   n4
//                   point-to-point  |    |    |    |
//                                   ================
//                                     LAN 10.1.2.0

using namespace ns3;

void CourseChange (std::string context, Ptr < const MobilityModel > model){

    Vector position = model->GetPosition ();

    NS_LOG_UNCOND (context << " x = " << position.x << ", y = " << position.y);

//NS_LOG_UNCOND (position.x << "," << position.y << "," << context.substr (10,1));

};

NS_LOG_COMPONENT_DEFINE("ThirdScriptExample");

int
main(int argc, char* argv[])
{
    bool verbose = true;
    uint32_t nCsma = 3;
    uint32_t nWifi = 3;
    bool tracing = false;

    CommandLine cmd(__FILE__);
    cmd.AddValue("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
    cmd.AddValue("nWifi", "Number of wifi STA devices", nWifi);
    cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);
    cmd.AddValue("tracing", "Enable pcap tracing", tracing);

    cmd.Parse(argc, argv);

    // The underlying restriction of 18 is due to the grid position
    // allocator's configuration; the grid layout will exceed the
    // bounding box if more than 18 nodes are provided.
    if (nWifi > 18)
    {
        std::cout << "nWifi should be 18 or less; otherwise grid layout exceeds the bounding box"
                  << std::endl;
        return 1;
    }

    if (verbose)
    {
        LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
        LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

    NodeContainer p2pNodes;
    p2pNodes.Create(2);

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

    NetDeviceContainer p2pDevices;
    p2pDevices = pointToPoint.Install(p2pNodes);

    NodeContainer csmaNodes;
    csmaNodes.Add(p2pNodes.Get(1));
    csmaNodes.Create(nCsma);

    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));

    NetDeviceContainer csmaDevices;
    csmaDevices = csma.Install(csmaNodes);

    NodeContainer wifiStaNodes;
    wifiStaNodes.Create(nWifi);
    NodeContainer wifiApNode = p2pNodes.Get(0);

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    Ssid ssid = Ssid("ns-3-ssid");

    WifiHelper wifi;

    NetDeviceContainer staDevices;
    mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid), "ActiveProbing", BooleanValue(false));
    staDevices = wifi.Install(phy, mac, wifiStaNodes);

    NetDeviceContainer apDevices;
    mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid));
    apDevices = wifi.Install(phy, mac, wifiApNode);

    MobilityHelper mobility;

    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "X",
                                  DoubleValue(20.0),
                                  "Y",
                                  DoubleValue(20.0),
                                  "Rho", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=20.0]"));

    mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel",
                              "Time", StringValue("1s"),
                              "Speed", StringValue("ns3::UniformRandomVariable[Min=1.0|Max=1.8]"),
                              "Direction", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=20.0]"),
                              "Bounds", StringValue ("0|50|0|50")
                              );
    mobility.Install(wifiStaNodes);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(wifiApNode);

    InternetStackHelper stack;
    stack.Install(csmaNodes);
    stack.Install(wifiApNode);
    stack.Install(wifiStaNodes);

    Ipv4AddressHelper address;

    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer p2pInterfaces;
    p2pInterfaces = address.Assign(p2pDevices);

    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer csmaInterfaces;
    csmaInterfaces = address.Assign(csmaDevices);

    address.SetBase("10.1.3.0", "255.255.255.0");
    address.Assign(staDevices);
    address.Assign(apDevices);

    UdpEchoServerHelper echoServer(7);

    ApplicationContainer serverApps = echoServer.Install(csmaNodes.Get(nCsma));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(csmaInterfaces.GetAddress(nCsma -1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(3));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(0.4)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(wifiStaNodes.Get(nWifi - 1));
    clientApps.Start(Seconds(5.0));
    clientApps.Stop(Seconds(25.0));

    UdpEchoClientHelper echoClient2(csmaInterfaces.GetAddress(nCsma -1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(4));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(0.8)));
    echoClient.SetAttribute("PacketSize", UintegerValue(2048));

    ApplicationContainer clientApps2 = echoClient.Install (wifiStaNodes.Get (nWifi - 2));
    clientApps2.Start(Seconds(10.0));
    clientApps2.Stop(Seconds(25.0));
    
    UdpEchoClientHelper echoClient3(csmaInterfaces.GetAddress(nCsma -1), 7);
    echoClient.SetAttribute("MaxPackets", UintegerValue(5));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.2)));
    echoClient.SetAttribute("PacketSize", UintegerValue(4096));

    ApplicationContainer clientApps3 = echoClient.Install (wifiStaNodes.Get (nWifi - 3));
    clientApps2.Start(Seconds(15.0));
    clientApps2.Stop(Seconds(25.0));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Stop(Seconds(25.0));

    if (tracing)
    {
        phy.SetPcapDataLinkType(WifiPhyHelper::DLT_IEEE802_11_RADIO);
        pointToPoint.EnablePcapAll("third");
        phy.EnablePcap("third", apDevices.Get(0));
        csma.EnablePcap("third", csmaDevices.Get(0), true);
    }

    std::ostringstream oss;
    oss << "/NodeList/" << wifiStaNodes.Get (nWifi - 1)->GetId () << "/ns3::MobilityModel/CourseChange";
    Config::Connect (oss.str(), MakeCallback (&CourseChange));

    std::ostringstream oss2;
    oss2 << "/NodeList/" << wifiStaNodes.Get (nWifi - 2)->GetId () << "/ns3::MobilityModel/CourseChange";
    Config::Connect (oss2.str(), MakeCallback (&CourseChange));

    std::ostringstream oss3;
    oss3 << "/NodeList/" << wifiStaNodes.Get (nWifi - 3)->GetId () << "/ns3::MobilityModel/CourseChange";
    Config::Connect (oss3.str(), MakeCallback (&CourseChange));

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
