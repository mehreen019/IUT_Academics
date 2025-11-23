//
// This program is property of its copyright holder. All rights reserved.
//

package inet.examples.wireless.wiredandwirelesshostswithap;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.mobility.static.StationaryMobility;


network WiredAndWirelessHostsWithAP
{
    parameters:
        int num_wireless;
        int num_wired;
      
    submodules:
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            parameters:
                @display("p=100,300;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                assignDisjunctSubnetAddresses = false;
                @display("p=100,100;is=s");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=100,200;is=s");
        }
        wirelessHost[num_wireless]: WirelessHost {
            parameters:
                @display("i=device/wifilaptop");
        }
        wiredHost[num_wired]: StandardHost {
            parameters:
                @display("i=device/laptop");
        }
        sinkNode: StandardHost {
            parameters:
                @display("p=205,20");
        }

        router: Router {
            parameters:
                @display("p=296,69");
        }
        accessPoint: AccessPoint {
            parameters:
                @display("p=205,100");
        }

    connections allowunconnected:
        accessPoint.ethg++ <--> Eth100M <--> router.ethg++;
        sinkNode.ethg++ <--> Eth100M <--> accessPoint.ethg++;
        
        for i=0..num_wired-1 {
        	wiredHost[i].ethg++ <--> Eth100M <--> router.ethg++;
        }
}
